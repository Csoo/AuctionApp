//
// Created by petras on 2020. 03. 24..
//

#include <QCoreApplication>
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
    updateLastQuery(db),
    checkIdQuery(db)
{
    moveToThread(this);
}

db_server::~db_server() {
    quit();
    wait();
    moveToThread(nullptr);
}

bool db_server::init() {
    db.setDatabaseName(dbName);

    if (!db.open())
    {
        std::cout << "ERROR [Database - init] " << db.lastError().text().toStdString() << std::endl;
        return false;
    }
    return true;
}

void db_server::check_login_slot(const QString &user, const QString &passw, bool* ok, bool* hasError) {

    *hasError = false;
    *ok = false;

    getLoginQuery.clear();

    if(!getLoginQuery.exec("SELECT COUNT(*) FROM user WHERE user_name = '" + user + "' AND password = '" + passw + "'"))
    {
        std::cout << "[Database::getUsers]  Error: " << getLoginQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    getLoginQuery.next();

    if (getLoginQuery.value(0).toInt() == 1)
    {
        *ok = true;
        //std::cout << "ok -> true\n";

        //'YYYY-MM-DD HH:MM' - date format in string -- Qt::ISODate (0-10) + Qt::ISODate (0-5)
        now = QDateTime::currentDateTime();

        QString temp_date = now.toString(Qt::ISODate).mid(-1,11) + " " + now.time().toString(Qt::ISODate).mid(-1,6);

        updateLastQuery.clear();

        updateLastQuery.exec("UPDATE user SET last_login_date = '" + temp_date + "' WHERE user_name = '" + user + "'");

        return;
    }
    if (!getLoginQuery.value(0).toInt())
    {
        return;
    }
    std::cout << "[Database::getUsers]  Error: count > 1\n";
    std::cout << "SELECT COUNT(*) FROM user WHERE user_name LIKE :un AND password LIKE :pw\n";
    *hasError = true;
}

void db_server::check_reg_slot(const QString &email, const QString &user, bool* ok, bool *hasError) {

    *hasError = false;
    *ok = false;

    checkRegQuery.clear();

    if(!checkRegQuery.exec("SELECT COUNT(*) FROM user WHERE user_name = '" + user + "' OR \"e-mail\" = '" + email + "'"))
    {
        std::cout << "[Database::getReg]  Error: " << checkRegQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    checkRegQuery.next();

    if (checkRegQuery.value(0).toInt() == 1)
    {
        *ok = true;
        //std::cout << "ok -> true\n";
        return;
    }
    if (!checkRegQuery.value(0).toInt())
    {
        return;
    }
    std::cout << "[Database::getReg]  Error: count > 1\n";
    std::cout << "SELECT COUNT(*) FROM user WHERE user_name LIKE :un AND e-mail LIKE :em\n";
    *hasError = true;
}

void db_server::add_user_slot(const QString &email, const QString &user, const QString &fullName, const QString &passw, const QString &add, const QString &phone, bool *hasError) {
    *hasError = false;

    //'YYYY-MM-DD HH:MM' - date format in string
    now = QDateTime::currentDateTime();

    QString temp_date = now.toString(Qt::ISODate).mid(-1,11) + " " + now.time().toString(Qt::ISODate).mid(-1,6);

    //:userP, :userN, :passw, :fullN, :email, :add, :phone, :date, :login)
    addUserQuery.clear();
    std::cout << email.toStdString() << std::endl << user.toStdString() << std::endl << fullName.toStdString() << std::endl << passw.toStdString() << std::endl << add.toStdString() << std::endl << phone.toStdString() << std::endl << temp_date.toStdString() << std::endl;
    if(!addUserQuery.exec("INSERT INTO user (user_permission, user_name, password, full_name, \"e-mail\", address, phone, registration_date, last_login_date) VALUES (1,'" + user + "', '" + passw + "', '" + fullName + "', '" + email + "', '" + add + "', '" + phone + "', '" + temp_date + "', 'never')")) {
        std::cout << "[Database::addUser]  Error: " << addUserQuery.lastError().text().toStdString() << std::endl;
        std::cout << "INSERT INTO user (user_permission, user_name, password, full_name, \"e-mail\", address, phone, registration_date)";
        *hasError = true;
        return;
    }
}

void db_server::get_self_slot(int id, QMap<QString,QString> *data, bool* ok, bool *hasError) {
    *hasError = false;
    *ok = false;

    checkIdQuery.clear();
    QString temp = QString::fromStdString(std::to_string(id));

    if (!checkIdQuery.exec("SELECT COUNT(*) FROM user WHERE id LIKE " + temp))
    {
        std::cout << "[Database::checkId]  Error: " << checkIdQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    checkIdQuery.next();
    if (checkIdQuery.value(0).toInt() == 1)
    {
        getSelfQuery.clear();

        if (!getSelfQuery.exec("SELECT \"e-mail\", user_name, full_name, address, phone, registration_date FROM user WHERE id = " + temp))
        {
            std::cout << "[Database::getSelf]  Error: " << getSelfQuery.lastError().text().toStdString() << std::endl;
            *hasError = true;
            return;
        }

        getSelfQuery.next();

        data->clear();
        data->insert("email",getSelfQuery.value(0).toString());
        data->insert("user",getSelfQuery.value(1).toString());
        data->insert("fullName",getSelfQuery.value(2).toString());
        data->insert("address",getSelfQuery.value(3).toString());
        data->insert("phone",getSelfQuery.value(4).toString());
        data->insert("reg",getSelfQuery.value(5).toString());

        *ok = true;
        //std::cout << "ok -> true\n";
        return;
    }
    if (!checkIdQuery.value(0).toInt())
    {
        return;
    }
    std::cout << "[Database::getReg]  Error: count > 1\n";
    std::cout << "SELECT COUNT(*) FROM user WHERE id LIKE :id\n";
    *hasError = true;
}

void db_server::get_other_slot(int id, QMap<QString, QString> *data, bool* ok, bool *hasError) {
    *hasError = false;
    *ok = false;

    checkIdQuery.clear();
    QString temp = QString::fromStdString(std::to_string(id));

    if (!checkIdQuery.exec("SELECT COUNT(*) FROM user WHERE id LIKE " + temp))
    {
        std::cout << "[Database::getReg]  Error: " << checkIdQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    checkIdQuery.next();
    if (checkIdQuery.value(0).toInt() == 1)
    {
        getOtherQuery.clear();

        if (!getOtherQuery.exec("SELECT user_name, full_name, registration_date, last_login_date FROM user WHERE id = " + temp))
        {
            std::cout << "[Database::getReg]  Error: " << getOtherQuery.lastError().text().toStdString() << std::endl;
            *hasError = true;
            return;
        }

        getOtherQuery.next();

        data->clear();
        data->insert("user",getOtherQuery.value(0).toString());
        data->insert("fullName",getOtherQuery.value(1).toString());
        data->insert("reg",getOtherQuery.value(2).toString());
        data->insert("last",getOtherQuery.value(3).toString());

        *ok = true;
        std::cout << "ok -> true\n";
        return;
    }
    if (!checkIdQuery.value(0).toInt())
    {
        return;
    }
    std::cout << "[Database::getReg]  Error: count > 1\n";
    std::cout << "SELECT COUNT(*) FROM user WHERE id LIKE :id\n";
    *hasError = true;
}
