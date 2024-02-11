#include "server.h"




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

}

void Server::sendToClient(QString mes)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out << mes;
    socket->write(data);
}


void Server::incomingConnection(qintptr discriptor)
{
    try
    {
        socket = new QTcpSocket;
        socket->setSocketDescriptor(discriptor);
        connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);
        connect(socket, &QTcpSocket::disconnected, this, &Server::deleteLater);
        clients.push_back(socket);
        qDebug() << "Client" << discriptor << "connected";
    }
    catch(const std::exception& ex)
    {
        qDebug() << "Error: failed client connection" << ex.what();
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
        sendToClient(mes);
    }
    else
    {
        qDebug() << "Error: failed to read message";
    }
}
