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
    checkIdQuery(db),
    getSearchQuery(db)
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

    if(!addUserQuery.exec("INSERT INTO user (user_permission, user_name, password, full_name, \"e-mail\", address, phone, registration_date, last_login_date)"
                          " VALUES (1,'" + user + "', '" + passw + "', '" + fullName + "', '" + email + "', '" + add + "', '" + phone + "', '" + temp_date + "', 'never')")) {

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

void db_server::get_search_slot(const QString &text, const QString &category, const QJsonDocument &filters, QJsonDocument *resJSON, bool *hasError) {

    *hasError = false;

    getSearchQuery.clear();

    QVariantMap filterMap = filters.toVariant().toMap();

    QString temp;

    if (filterMap.contains("minPrice"))
    {
        if (filterMap.contains("maxPrice"))
        {
            temp = "where (auction.current_price between " + filterMap["minPrice"].toString() + " and " + filterMap["maxPrice"].toString() + " or "
                              "auction.fix_price between " + filterMap["minPrice"].toString() + " and " + filterMap["maxPrice"].toString() + ")";
        }
        else
        {
            temp = "where (auction.current_price > " + filterMap["minPrice"].toString() + " or auction.fix_price > " + filterMap["minPrice"].toString() + ")";
        }
    }
    else
    {
        if (filterMap.contains("maxPrice"))
        {
            temp = "where (auction.current_price < " + filterMap["maxPrice"].toString() + " or auction.fix_price < " + filterMap["maxPrice"].toString() + ")";
        }
    }

    filterMap.erase(filterMap.find("maxPrice"));
    filterMap.erase(filterMap.find("minPrice"));

    for (const auto &filter : filterMap) {
        temp += " and " + filterMap.key(filter.toString()) + " = '" + filter.toString() + "'";
    }

    if (!getSearchQuery.exec("select auction.id, item_description.title, item_condition.condition_text, auction.current_price from auction\n"
                           "inner join item on auction.item_id=item.id\ninner join item_category on item_category.id=item.category_id\n"
                           "inner join item_description on item.description_id=item_description.id\ninner join item_condition on item_condition.id=item_description.condition_id" + temp))
    {
        std::cout << "[Database::getSearch]  Error: " << getSearchQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    QString resTemp = "{\n[\n";

    while (getSearchQuery.next()) {
        resTemp += "{\n\"auction_id\" : " + getSearchQuery.value(0).toString() + ",\n\"data\" : [\n \"title\" : \"" + getSearchQuery.value(1).toString() + "\",\n"
                                                                                                "\"condition\" : \"" + getSearchQuery.value(2).toString() + "\",\n"
                                                                                                " \"price\" : \"" + getSearchQuery.value(3).toString() + "\"\n]\n},";
    }

    *resJSON = QJsonDocument::fromJson(QByteArray(resTemp.toUtf8()));
}

void db_server::get_auction_slot(int id, QJsonArray &resJSON, bool &hasError) {

}

void db_server::all_auction_slot(QJsonArray &resJSON, bool &hasError) {

}
