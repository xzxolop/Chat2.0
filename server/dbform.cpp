#include "dbform.h"
#include "ui_dbform.h"

DBForm::DBForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DBForm)
{
    ui->setupUi(this);
}

DBForm::~DBForm()
{
    delete ui;
}
