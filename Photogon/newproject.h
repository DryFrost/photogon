#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QDialog>


namespace Ui {
class newProject;
}

class newProject : public QDialog
{
    Q_OBJECT

public:
    explicit newProject(QWidget *parent = nullptr);
    ~newProject();
    QString ProjectName;
    QString dir;
    QString ProjectDir;
    int numTreatments;
    int numSamples;
    QStringList treatmentList;



private slots:
    void on_setDirectoryButton_clicked();

    void on_pushButton_2_clicked();

    void on_commandLinkButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_checkQR_clicked();

    void on_lineEdit_returnPressed();

    void on_CreateQRCode_clicked();

private:
    Ui::newProject *ui;

};

#endif // NEWPROJECT_H
