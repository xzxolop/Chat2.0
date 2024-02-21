#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>

class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server(QString ip, int port);
    void sendToClients(QString mes);
    void sendToClient(QString mes, QTcpSocket* client);
    QTcpSocket* socket;
private:
    QByteArray data;
    QVector<QTcpSocket*> clients;
    QSqlDatabase db;
    QSqlQuery *query;

public slots:
    void incomingConnection(qintptr discriptor) override;
    void readyRead();
    void disconnect();
};

#endif // SERVER_H
