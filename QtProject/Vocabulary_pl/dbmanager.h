#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

class DbManager
{
public:
    DbManager(const QString &path);
    void selectAll(QString& field);
    bool isOpen();
    void close();


private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
