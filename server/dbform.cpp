#include "dbform.h"
#include "ui_dbform.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

DBForm::DBForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DBForm)
{
    ui->setupUi(this);
    tableView = ui->tableView;

}

DBForm::~DBForm()
{
    delete ui;
}

void DBForm::setModel(QSqlTableModel *model)
{
    //ui->tableView->setModel(model);
}
