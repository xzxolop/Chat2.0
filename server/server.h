#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server(QString ip, int port);
    void sendToClient(QString mes);
    QTcpSocket* socket;
private:
    QByteArray data;
    QVector<QTcpSocket*> clients;

public slots:
    void incomingConnection(qintptr discriptor) override;
    void readyRead();
    void disconnect();
};

#endif // SERVER_H
