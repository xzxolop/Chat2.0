#ifndef DBFORM_H
#define DBFORM_H

#include <QWidget>
#include <QApplication>
#include <QSqlTableModel>
#include <QTableView>

namespace Ui {
class DBForm;
}

class DBForm : public QWidget
{
    Q_OBJECT

public:
    explicit DBForm(QWidget *parent = nullptr);
    ~DBForm();
    void setModel(QSqlTableModel* model);
    QTableView *tableView;

private:
    Ui::DBForm *ui;
};

#endif // DBFORM_H
