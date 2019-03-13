#include "dbmanager.h"

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open()){
        qDebug() << "Error : " ;// << m_db.lastError().text();
    }
    else
        qDebug() << "Connected to the database";

}

void DbManager::selectAll(QString& field){
    QString q("Select * from ");
    q.append(field);
    QSqlQuery query(q);
    QSqlRecord rec = query.record();
    int categoryCol = rec.indexOf("Category");

    while (query.next())
    {
     qDebug() << query.value(categoryCol).toString();

    }

}

bool DbManager::isOpen(){
    return m_db.isOpen();
}
void DbManager::close(){
    m_db.close();
}
