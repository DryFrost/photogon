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

private:
    Ui::newProject *ui;
};

#endif // NEWPROJECT_H
