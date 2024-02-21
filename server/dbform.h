#ifndef DBFORM_H
#define DBFORM_H

#include <QWidget>
#include <QApplication>

namespace Ui {
class DBForm;
}

class DBForm : public QWidget
{
    Q_OBJECT

public:
    explicit DBForm(QWidget *parent = nullptr);
    ~DBForm();

private:
    Ui::DBForm *ui;
};

#endif // DBFORM_H
