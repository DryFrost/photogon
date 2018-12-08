#ifndef NEWPROJECTTREATMENTS_H
#define NEWPROJECTTREATMENTS_H

#include <QDialog>

namespace Ui {
class newProjectTreatments;
}

class newProjectTreatments : public QDialog
{
    Q_OBJECT

public:
    explicit newProjectTreatments(QWidget *parent = nullptr);
    ~newProjectTreatments();

private:
    Ui::newProjectTreatments *ui;
};

#endif // NEWPROJECTTREATMENTS_H
