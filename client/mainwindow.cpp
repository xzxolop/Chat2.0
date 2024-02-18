#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractSocket>
#include <QException>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    try
    {
        createSocket();
        socket->connectToHost("127.0.0.1", 1234);
        ui->textBrowser->append("Welcome!");
    }
    catch(QException& ex)
    {
        ui->textBrowser->append("Error: failed to conection to server");
    }
}

void MainWindow::on_disconnectButton_clicked()
{
    ui->textBrowser->append("Not impemented. If you want to disconnect, close the client window.");
}

void MainWindow::sendToServer(QString mes)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out << mes;
    socket->write(data);
    ui->lineEdit->clear();
}

void MainWindow::createSocket()
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::ReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
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


void MainWindow::on_sendButton_clicked()
{
    sendToServer(ui->lineEdit->text());
}





