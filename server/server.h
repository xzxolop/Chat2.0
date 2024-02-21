#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

#include "dbform.h"

class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server(QString ip, int port);
    void sendToClients(QString mes);
    void sendToClient(QString mes, QTcpSocket* client);
    void createForm();
    QTcpSocket* socket;
    DBForm* dbform;
private:
    QByteArray data;
    QVector<QTcpSocket*> clients;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel* dbmodel;

public slots:
    void incomingConnection(qintptr discriptor) override;
    void readyRead();
    void disconnect();
};

#endif // SERVER_H
