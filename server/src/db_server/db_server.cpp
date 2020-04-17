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

    return getLoginQuery.prepare("SELECT COUNT(*) FROM user WHERE user_name LIKE :un AND password LIKE :pw");

}

void db_server::check_login_slot(const QString &user, const QString &passw, bool* ok, bool* hasError) {

    *hasError = false;
    *ok = false;

    getLoginQuery.bindValue(":un",user);
    getLoginQuery.bindValue(":pw",passw);

    if(!getLoginQuery.exec()) {
        qWarning() << "[Database::getUsers]  Error: " << getLoginQuery.lastError().text();
        *hasError = true;
        return;
    }

    getLoginQuery.next();

    if (getLoginQuery.value(0).toInt() == 1)
    {
        *ok = true;
        return;
    }
    if (!getLoginQuery.value(0).toInt())
    {
        return;
    }
    qWarning() << "[Database::getUsers]  Error: count > 1";
    qWarning() << "SELECT COUNT(*) FROM user WHERE user_name LIKE :un AND password LIKE :pw";
    *hasError = true;
}

void db_server::check_reg_slot(const QString &email, const QString &user, int* ok, bool *hasError) {

}

void db_server::add_user_slot(const QString &email, const QString &user, const QString &fullName, const QString &passw, const QString &add, const QString &phone, bool *hasError) {

}

void db_server::get_self_slot(int id, QMap<QString,QString> *data, bool *hasError) {

}

void db_server::get_other_slot(int id, QMap<QString, QString> *data, bool *hasError) {

}
