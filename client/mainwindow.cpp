#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::ReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1", 1234);
}

void MainWindow::sendToServer(QString mes)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out << mes;
    socket->write(data);
}

void MainWindow::ReadyRead()
{
    QDataStream in(socket);
    if(in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;
        ui->textBrowser->append(str);
    }
    else
    {
        ui->textBrowser->append("Error: failed to read");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    sendToServer(ui->lineEdit->text());
}

