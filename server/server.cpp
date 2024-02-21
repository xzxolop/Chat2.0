#include "server.h"
#include <QTextStream>
#include <QApplication>


Server::Server(QString ip, int port)
{
    if(this->listen(QHostAddress(ip), port))
    {
        qDebug() << "Server start on:" << ip << port;
    }
    else
    {
        qDebug() << "Error: failed to start server";
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");
    if(db.open())
    {
        qDebug() << "Db open";
    }
    else
    {
        qDebug() << "Db no open";
    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE Clients(Name TEXT, id int);");

    dbform = new DBForm();
    dbmodel = new QSqlTableModel(dbform, db);
    dbmodel->setTable("Clients");
    dbmodel->select();
    dbform->tableView->setModel(dbmodel);
    dbform->show();
}

void Server::incomingConnection(qintptr discriptor)
{
    try
    {
        socket = new QTcpSocket;
        socket->setSocketDescriptor(discriptor);
        socket->setProperty("id", discriptor);
        connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);
        connect(socket, &QTcpSocket::disconnected, this, &Server::disconnect);
        clients.push_back(socket);
        qDebug() << "Client" << discriptor << "connected";
    }
    catch(const std::exception& ex)
    {
        qDebug() << "Error: failed client connection" << ex.what();
    }
}

void Server::sendToClient(QString mes, QTcpSocket* client)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out << mes;
    client->write(data);
}

void Server::sendToClients(QString mes)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out << mes;
    for(int i=0; i<clients.size(); i++)
    {
        clients[i]->write(data);
    }
}

void Server::readyRead()
{
    socket = (QTcpSocket*)sender(); // return ptr on object which send a signal.
    QDataStream in(socket);
    if(in.status() == QDataStream::Ok)
    {
        QString mes;
        in >> mes;
        qDebug() << "Server read:" << mes;
        sendToClients(mes);
    }
    else
    {
        qDebug() << "Error: failed to read message";
    }
}

void printClients(const QVector<QTcpSocket*>& v)
{
    QTextStream cout(stdout);
    for(auto x: v)
    {
        cout << x->socketDescriptor() << ' ';
    }
    cout << "\n";
}

void Server::disconnect()
{
    socket = (QTcpSocket*)sender();
    qDebug() << "Client disconnected" << (socket->property("id")).toLongLong();
    clients.removeOne(socket);
}




