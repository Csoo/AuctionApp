//
// Created by petras on 2020. 03. 24..
//
​
#include "db_server.h"
​
db_server::db_server(const QString &driver, QString connectionName, QString dbName):
    db(QSqlDatabase::addDatabase(driver, connectionName)),
    connectionName(std::move(connectionName)),
    dbName(std::move(dbName)),
    getLoginQuery(db),
    checkRegQuery(db),
    getSelfQuery(db),
    getOtherQuery(db),
    addUserQuery(db),
    updateLastQuery(db),
    checkIdQuery(db)
{
    moveToThread(this);
}
​
bool db_server::init() {
    db.setDatabaseName(dbName);
​
    if (!db.open())
    {
        qWarning() << "ERROR [Database - init]" << db.lastError();
        return false;
    }
​
    getLoginQuery.clear();
    checkRegQuery.clear();
    getSelfQuery.clear();
    getOtherQuery.clear();
    addUserQuery.clear();
    updateLastQuery.clear();
    checkIdQuery.clear();
​
    // if (!getLoginQuery.prepare("SELECT COUNT(*) FROM user WHERE user_name LIKE :un AND password LIKE :pw"))
    // {
    //     return false;
    // }
    if (!checkRegQuery.prepare("SELECT COUNT(*) FROM user WHERE user_name LIKE :un AND e-mail LIKE :em"))
    {
        return false;
    }
    if (!checkIdQuery.prepare("SELECT COUNT(*) FROM user WHERE id LIKE :id"))
    {
        return false;
    }
    if (!getSelfQuery.prepare("SELECT e-mail, user_name, full_name, address, phone, registration_date FROM user WHERE id LIKE :id"))
    {
        return false;
    }
    if (!getOtherQuery.prepare("SELECT user_name, full_name, registration_date, last_login_date FROM user WHERE id LIKE :id"))
    {
        return false;
    }
    if (!addUserQuery.prepare("INSERT INTO user (user_permission, user_name, password, full_name, \"e-mail\", address, phone, registration_date, last_login_date) VALUES (:userP, :userN, :passw, :fullN, :email, :add, :phone, :date, :login)"))
    {
        return false;
    }
    return updateLastQuery.prepare("UPDATE user SET last_login_date = :ll WHERE user_name LIKE :un");
    //'YYYY-MM-DD HH:MM' - date format in string
​
}
​
void db_server::check_login_slot(const QString &user, const QString &passw, bool* ok, bool* hasError) {
​
    *hasError = false;
    *ok = false;
​
    // getLoginQuery.bindValue(":un",user);
    // getLoginQuery.bindValue(":pw",passw);
​
    if(!getLoginQuery.exec("SELECT COUNT(*) as count FROM user WHERE user_name ='"+ user +"' AND password ='"+passw +"'"))
    {
        qWarning() << "[Database::getUsers]  Error: " << getLoginQuery.lastError().text();
        *hasError = true;
        return;
    }
​
    getLoginQuery.next();
​
    if (getLoginQuery.value(0).toInt() == 1)
    {
        *ok = true;
​
        //'YYYY-MM-DD HH:MM' - date format in string
        now = QDateTime::currentDateTime();
​
        QString temp_date = now.toString("YYYY-MM-DD HH:MM");
​
        updateLastQuery.bindValue(":ll", now);
        updateLastQuery.bindValue(":un", user);
​
        updateLastQuery.exec();
​
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
​
void db_server::check_reg_slot(const QString &email, const QString &user, bool* ok, bool *hasError) {
​
    *hasError = false;
    *ok = false;
​
    checkRegQuery.bindValue(":un",user);
    checkRegQuery.bindValue(":em",email);
​
    if(!checkRegQuery.exec())
    {
        qWarning() << "[Database::getReg]  Error: " << checkRegQuery.lastError().text();
        *hasError = true;
        return;
    }
​
    checkRegQuery.next();
​
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
​
void db_server::add_user_slot(const QString &email, const QString &user, const QString &fullName, const QString &passw, const QString &add, const QString &phone, bool *hasError) {
    *hasError = false;
​
    //'YYYY-MM-DD HH:MM' - date format in string
    now = QDateTime::currentDateTime();
​
    QString temp_date = now.toString("YYYY-MM-DD HH:MM");
​
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
​
    if(!addUserQuery.exec()) {
        qWarning() << "[Database::addUser]  Error: " << addUserQuery.lastError().text();
        qWarning() << "INSERT INTO user (user_permission, user_name, password, full_name, \"e-mail\", address, phone, registration_date) VALUES (:userP, :userN, :passw, :fullN, :email, :add, :phone, :date)";
        *hasError = true;
        return;
    }
}
​
void db_server::get_self_slot(int id, QMap<QString,QString> *data, bool* ok, bool *hasError) {
    *hasError = false;
    *ok = false;
​
    checkIdQuery.bindValue(":id", id);
​
    if (!checkIdQuery.exec())
    {
        qWarning() << "[Database::getReg]  Error: " << checkIdQuery.lastError().text();
        *hasError = true;
        return;
    }
​
    checkIdQuery.next();
    if (checkIdQuery.value(0).toInt() == 1)
    {
        getSelfQuery.bindValue(":id", id);
​
        if (!getSelfQuery.exec())
        {
            qWarning() << "[Database::getReg]  Error: " << getSelfQuery.lastError().text();
            *hasError = true;
            return;
        }
​
        getSelfQuery.next();
​
        data->clear();
        data->insert("email",getSelfQuery.value(0).toString());
        data->insert("user",getSelfQuery.value(1).toString());
        data->insert("fullName",getSelfQuery.value(2).toString());
        data->insert("address",getSelfQuery.value(3).toString());
        data->insert("phone",getSelfQuery.value(4).toString());
        data->insert("reg",getSelfQuery.value(5).toString());
​
        *ok = true;
        return;
    }
    if (!checkIdQuery.value(0).toInt())
    {
        return;
    }
    qWarning() << "[Database::getReg]  Error: count > 1";
    qWarning() << "SELECT COUNT(*) FROM user WHERE id LIKE :id";
    *hasError = true;
}
​
void db_server::get_other_slot(int id, QMap<QString, QString> *data, bool* ok, bool *hasError) {
    *hasError = false;
    *ok = false;
​
    checkIdQuery.bindValue(":id", id);
​
    if (!checkIdQuery.exec())
    {
        qWarning() << "[Database::getReg]  Error: " << checkIdQuery.lastError().text();
        *hasError = true;
        return;
    }
​
    checkIdQuery.next();
    if (checkIdQuery.value(0).toInt() == 1)
    {
        getOtherQuery.bindValue(":id", id);
​
        if (!getOtherQuery.exec())
        {
            qWarning() << "[Database::getReg]  Error: " << getOtherQuery.lastError().text();
            *hasError = true;
            return;
        }
​
        getOtherQuery.next();
​
        data->clear();
        data->insert("user",getOtherQuery.value(0).toString());
        data->insert("fullName",getOtherQuery.value(1).toString());
        data->insert("reg",getOtherQuery.value(2).toString());
        data->insert("last",getOtherQuery.value(3).toString());
​
        *ok = true;
        return;
    }
    if (!checkIdQuery.value(0).toInt())
    {
        return;
    }
    qWarning() << "[Database::getReg]  Error: count > 1";
    qWarning() << "SELECT COUNT(*) FROM user WHERE id LIKE :id";
    *hasError = true;
}