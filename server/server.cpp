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

void Server::incomingConnection(qintptr d)
{
    try
    {
        socket = new QTcpSocket;
        socket->setSocketDescriptor(d);
        connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);
        connect(socket, &QTcpSocket::disconnected, this, &Server::deleteLater);
        clients.push_back(socket);
    }
    catch(const std::exception& ex)
    {
        qDebug() << "Error: failed client connection" << ex.what();
    }
}
