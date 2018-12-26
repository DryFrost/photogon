#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "qrsegment.hpp"

namespace qrcodegen {


class QrCode final {

public:


	class Ecc final {
	public:
		const static Ecc LOW, MEDIUM, QUARTILE, HIGH;

	public:
		const int ordinal;
		const int formatBits;

	private:
		Ecc(int ord, int fb);
	};



public:


	static QrCode encodeText(const char *text, const Ecc &ecl);



	static QrCode encodeBinary(const std::vector<uint8_t> &data, const Ecc &ecl);



	static QrCode encodeSegments(const std::vector<QrSegment> &segs, const Ecc &ecl,
		int minVersion=1, int maxVersion=40, int mask=-1, bool boostEcl=true);



public:

	const int version;

	const int size;

	const Ecc &errorCorrectionLevel;

private:
	int mask;

private:
	std::vector<std::vector<bool>> modules;
	std::vector<std::vector<bool>> isFunction;



	/*---- Constructors ----*/
public:

	/*
	 * Creates a new QR Code symbol with the given version number, error correction level, binary data array,
	 * and mask number. This is a cumbersome low-level constructor that should not be invoked directly by the user.
	 * To go one level up, see the encodeSegments() function.
	 */
	QrCode(int ver, const Ecc &ecl, const std::vector<uint8_t> &dataCodewords, int mask);


	/*
	 * Creates a new QR Code symbol based on the given existing object, but with a potentially
	 * different mask pattern. The version, error correction level, codewords, etc. of the newly
	 * created object are all identical to the argument object; only the mask may differ.
	 */
	QrCode(const QrCode &qr, int mask);



	/*---- Public instance methods ----*/
public:

	int getMask() const;


	/*
	 * Returns the color of the module (pixel) at the given coordinates, which is either 0 for white or 1 for black. The top
	 * left corner has the coordinates (x=0, y=0). If the given coordinates are out of bounds, then 0 (white) is returned.
	 */
	int getModule(int x, int y) const;


	/*
	 * Based on the given number of border modules to add as padding, this returns a
	 * string whose contents represents an SVG XML file that depicts this QR Code symbol.
	 * Note that Unix newlines (\n) are always used, regardless of the platform.
	 */
	std::string toSvgString(int border) const;



	/*---- Private helper methods for constructor: Drawing function modules ----*/
private:

	void drawFunctionPatterns();


	// Draws two copies of the format bits (with its own error correction code)
	// based on the given mask and this object's error correction level field.
	void drawFormatBits(int mask);


	// Draws two copies of the version bits (with its own error correction code),
	// based on this object's version field (which only has an effect for 7 <= version <= 40).
	void drawVersion();


	// Draws a 9*9 finder pattern including the border separator, with the center module at (x, y).
	void drawFinderPattern(int x, int y);


	// Draws a 5*5 alignment pattern, with the center module at (x, y).
	void drawAlignmentPattern(int x, int y);


	// Sets the color of a module and marks it as a function module.
	// Only used by the constructor. Coordinates must be in range.
	void setFunctionModule(int x, int y, bool isBlack);


	/*---- Private helper methods for constructor: Codewords and masking ----*/
private:

	// Returns a new byte string representing the given data with the appropriate error correction
	// codewords appended to it, based on this object's version and error correction level.
	std::vector<uint8_t> appendErrorCorrection(const std::vector<uint8_t> &data) const;


	// Draws the given sequence of 8-bit codewords (data and error correction) onto the entire
	// data area of this QR Code symbol. Function modules need to be marked off before this is called.
	void drawCodewords(const std::vector<uint8_t> &data);


	// XORs the data modules in this QR Code with the given mask pattern. Due to XOR's mathematical
	// properties, calling applyMask(m) twice with the same value is equivalent to no change at all.
	// This means it is possible to apply a mask, undo it, and try another mask. Note that a final
	// well-formed QR Code symbol needs exactly one mask applied (not zero, not two, etc.).
	void applyMask(int mask);


	// A messy helper function for the constructors. This QR Code must be in an unmasked state when this
	// method is called. The given argument is the requested mask, which is -1 for auto or 0 to 7 for fixed.
	// This method applies and returns the actual mask chosen, from 0 to 7.
	int handleConstructorMasking(int mask);


	// Calculates and returns the penalty score based on state of this QR Code's current modules.
	// This is used by the automatic mask choice algorithm to find the mask pattern that yields the lowest score.
	int getPenaltyScore() const;



	/*---- Private static helper functions ----*/
private:

	// Returns a set of positions of the alignment patterns in ascending order. These positions are
	// used on both the x and y axes. Each value in the resulting array is in the range [0, 177).
	// This stateless pure function could be implemented as table of 40 variable-length lists of unsigned bytes.
	static std::vector<int> getAlignmentPatternPositions(int ver);


	// Returns the number of raw data modules (bits) available at the given version number.
	// These data modules are used for both user data codewords and error correction codewords.
	// This stateless pure function could be implemented as a 40-entry lookup table.
	static int getNumRawDataModules(int ver);


	// Returns the number of 8-bit data (i.e. not error correction) codewords contained in any
	// QR Code of the given version number and error correction level, with remainder bits discarded.
	// This stateless pure function could be implemented as a (40*4)-cell lookup table.
	static int getNumDataCodewords(int ver, const Ecc &ecl);


	/*---- Private tables of constants ----*/
private:

	// For use in getPenaltyScore(), when evaluating which mask is best.
	static const int PENALTY_N1;
	static const int PENALTY_N2;
	static const int PENALTY_N3;
	static const int PENALTY_N4;

	static const int16_t NUM_ERROR_CORRECTION_CODEWORDS[4][41];
	static const int8_t NUM_ERROR_CORRECTION_BLOCKS[4][41];



	/*---- Private helper class ----*/
private:

	/*
	 * Computes the Reed-Solomon error correction codewords for a sequence of data codewords
	 * at a given degree. Objects are immutable, and the state only depends on the degree.
	 * This class exists because the divisor polynomial does not need to be recalculated for every input.
	 */
	class ReedSolomonGenerator final {

		/*-- Immutable field --*/
	private:

		// Coefficients of the divisor polynomial, stored from highest to lowest power, excluding the leading term which
		// is always 1. For example the polynomial x^3 + 255x^2 + 8x + 93 is stored as the uint8 array {255, 8, 93}.
		std::vector<uint8_t> coefficients;


		/*-- Constructor --*/
	public:

		/*
		 * Creates a Reed-Solomon ECC generator for the given degree. This could be implemented
		 * as a lookup table over all possible parameter values, instead of as an algorithm.
		 */
		ReedSolomonGenerator(int degree);


		/*-- Method --*/
	public:

		/*
		 * Computes and returns the Reed-Solomon error correction codewords for the given sequence of data codewords.
		 * The returned object is always a new byte array. This method does not alter this object's state (because it is immutable).
		 */
		std::vector<uint8_t> getRemainder(const std::vector<uint8_t> &data) const;


		/*-- Static function --*/
	private:

		// Returns the product of the two given field elements modulo GF(2^8/0x11D). The arguments and result
		// are unsigned 8-bit integers. This could be implemented as a lookup table of 256*256 entries of uint8.
		static uint8_t multiply(uint8_t x, uint8_t y);

	};

};

}
