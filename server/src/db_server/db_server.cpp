//
// Created by petras on 2020. 03. 24..
//

#include "db_server.h"

db_server::db_server(const QString &driver, QString connectionName, QString dbName):
    db(QSqlDatabase::addDatabase(driver, connectionName)),
    connectionName(std::move(connectionName)),
    dbName(std::move(dbName)),
    getLoginQuery(db)
{
    moveToThread(this);
}

bool db_server::init() {
    db.setDatabaseName(dbName);

    if (!db.open())
    {
        qWarning() << "ERROR [Database - init]" << db.lastError();
        return false;
    }

    getLoginQuery.clear();
    getLoginQuery.prepare("Query for get users & passwords");

    return true;
}

void db_server::check_login(const QString &user, const QString &passw, bool* ok, bool* hasError) {

    *hasError = false;
    *ok = false;

    if(!getLoginQuery.exec()) {
        qWarning() << "[Database::getUsers]  Error: " << getLoginQuery.lastError().text();
        *hasError = true;
        return;
    }

    while(getLoginQuery.next()) {
        //TODO: check functionality
    }
}
