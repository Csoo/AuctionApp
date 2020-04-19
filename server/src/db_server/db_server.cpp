//
// Created by petras on 2020. 03. 24..
//

#include "db_server.h"

db_server::db_server(const QString &driver, QString connectionName, QString dbName):
    db(QSqlDatabase::addDatabase(driver, connectionName)),
    connectionName(std::move(connectionName)),
    dbName(std::move(dbName)),
    getLoginQuery(db),
    checkRegQuery(db),
    getSelfQuery(db),
    getOtherQuery(db),
    addUserQuery(db),
    updateLastQuery(db)
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
    checkRegQuery.clear();
    getSelfQuery.clear();
    getOtherQuery.clear();
    addUserQuery.clear();
    updateLastQuery.clear();

    if (!getLoginQuery.prepare("SELECT COUNT(*) FROM user WHERE user_name LIKE :un AND password LIKE :pw"))
    {
        return false;
    }
    if (!checkRegQuery.prepare("SELECT COUNT(*) FROM user WHERE user_name LIKE :un AND e-mail LIKE :em"))
    {
        return false;
    }
    if (!getSelfQuery.prepare(""))
    {
        return false;
    }
    if (!getOtherQuery.prepare(""))
    {
        return false;
    }
    if (!addUserQuery.prepare("INSERT INTO user (user_permission, user_name, password, full_name, \"e-mail\", address, phone, registration_date, last_login_date) VALUES (:userP, :userN, :passw, :fullN, :email, :add, :phone, :date, :login)"))
    {
        return false;
    }
    return updateLastQuery.prepare("UPDATE user SET last_login_date = :ll WHERE user_name LIKE :un");
    //'YYYY-MM-DD HH:MM' - date format in string

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

        //'YYYY-MM-DD HH:MM' - date format in string
        now = QDateTime::currentDateTime();

        QString temp_date = now.toString("YYYY-MM-DD HH:MM");

        updateLastQuery.bindValue(":ll", now);
        updateLastQuery.bindValue(":un", user);

        updateLastQuery.exec();

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

void db_server::check_reg_slot(const QString &email, const QString &user, bool* ok, bool *hasError) {

    *hasError = false;
    *ok = false;

    checkRegQuery.bindValue(":un",user);
    checkRegQuery.bindValue(":em",email);

    if(!checkRegQuery.exec()) {
        qWarning() << "[Database::getReg]  Error: " << checkRegQuery.lastError().text();
        *hasError = true;
        return;
    }

    checkRegQuery.next();

    if (checkRegQuery.value(0).toInt() == 1)
    {
        *ok = true;
        return;
    }
    if (!checkRegQuery.value(0).toInt())
    {
        return;
    }
    qWarning() << "[Database::getReg]  Error: count > 1";
    qWarning() << "SELECT COUNT(*) FROM user WHERE user_name LIKE :un AND e-mail LIKE :em";
    *hasError = true;
}

void db_server::add_user_slot(const QString &email, const QString &user, const QString &fullName, const QString &passw, const QString &add, const QString &phone, bool *hasError) {
    *hasError = false;

    //'YYYY-MM-DD HH:MM' - date format in string
    now = QDateTime::currentDateTime();

    QString temp_date = now.toString("YYYY-MM-DD HH:MM");

    //:userP, :userN, :passw, :fullN, :email, :add, :phone, :date, :login)
    addUserQuery.bindValue(":userP", 1);
    addUserQuery.bindValue(":userN", user);
    addUserQuery.bindValue(":passw", passw);
    addUserQuery.bindValue(":fullN", fullName);
    addUserQuery.bindValue(":email", email);
    addUserQuery.bindValue(":add", add);
    addUserQuery.bindValue(":phone", phone);
    addUserQuery.bindValue(":date", temp_date);
    addUserQuery.bindValue(":login", "inalid");

    if(!checkRegQuery.exec()) {
        qWarning() << "[Database::addUser]  Error: " << checkRegQuery.lastError().text();
        qWarning() << "INSERT INTO user (user_permission, user_name, password, full_name, \"e-mail\", address, phone, registration_date) VALUES (:userP, :userN, :passw, :fullN, :email, :add, :phone, :date)";
        *hasError = true;
        return;
    }
}

void db_server::get_self_slot(int id, QMap<QString,QString> *data, bool *hasError) {

}

void db_server::get_other_slot(int id, QMap<QString, QString> *data, bool *hasError) {

}
