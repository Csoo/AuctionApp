//
// Created by petras on 2020. 03. 24..
//

#include <QCoreApplication>
#include "db_server.h"

Db_server::Db_server(const QString &driver, QString connectionName, QString dbName):
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
    getSearchQuery(db),
    getAuctionQuery(db),
    allAuctionQuery(db),
    getAuctionIdQuery(db),
    addAuctionQuery(db),
    checkBidQuery(db),
    setBidQuery(db)
{
    std::cout << "[Db_server] Log: Started" << std::endl;

    moveToThread(this);
}

Db_server::~Db_server() {
    quit();
    wait();
    moveToThread(nullptr);
}

bool Db_server::init() {
    db.setDatabaseName(dbName);

    if (!db.open())
    {
        std::cout << "ERROR [Database - init] " << db.lastError().text().toStdString() << std::endl;
        return false;
    }
    return true;
}

void Db_server::check_login_slot(const QString &user, const QString &passw, int* id, bool* ok, bool* hasError) {

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

    if (getLoginQuery.value(0).toInt() == 0)
    {
        return;
    }

    if (getLoginQuery.value(0).toInt() == 1)
    {
        *ok = true;

        //'YYYY-MM-DD HH:MM' - date format in string -- Qt::ISODate (0-10) + Qt::ISODate (0-5)
        now = QDateTime::currentDateTime();

        QString temp_date = now.toString(Qt::ISODate).mid(-1,11) + " " + now.time().toString(Qt::ISODate).mid(-1,6);

        updateLastQuery.clear();

        updateLastQuery.exec("UPDATE user SET last_login_date = '" + temp_date + "' WHERE user_name = '" + user + "'");

        if(!getLoginQuery.exec("SELECT id FROM user WHERE user_name = '" + user + "' AND password = '" + passw + "'"))
        {
            std::cout << "[Database::getUsers]  Error: " << getLoginQuery.lastError().text().toStdString() << std::endl;
            *hasError = true;
            return;
        }

        getLoginQuery.next();

        *id = getLoginQuery.value(0).toInt();

        return;

        return;
    }

    std::cout << "[Database::getUsers]  Error: count > 1\n";
    std::cout << "SELECT COUNT(*) FROM user WHERE user_name LIKE :un AND password LIKE :pw\n";
    *hasError = true;
}

void Db_server::check_reg_slot(const QString &email, const QString &user, bool* ok, bool *hasError) {

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

void Db_server::add_user_slot(const QString &email, const QString &user, const QString &fullName, const QString &passw, const QString &add, const QString &phone, bool *hasError) {
    *hasError = false;

    //'YYYY-MM-DD HH:MM' - date format in string
    now = QDateTime::currentDateTime();

    QString temp_date = now.toString(Qt::ISODate).mid(-1,11) + " " + now.time().toString(Qt::ISODate).mid(-1,6);

    addUserQuery.clear();

    if(!addUserQuery.exec("INSERT INTO user (user_permission, user_name, password, full_name, \"e-mail\", address, phone, registration_date, last_login_date)"
                          " VALUES (1,'" + user + "', '" + passw + "', '" + fullName + "', '" + email + "', '" + add + "', '" + phone + "', '" + temp_date + "', 'never')")) {

        std::cout << "[Database::addUser]  Error: " << addUserQuery.lastError().text().toStdString() << std::endl;
        std::cout << "INSERT INTO user (user_permission, user_name, password, full_name, \"e-mail\", address, phone, registration_date)";
        *hasError = true;
        return;
    }
}

void Db_server::get_self_slot(int id, QMap<QString,QString> *data, bool* ok, bool *hasError) {
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

        return;
    }
    if (!checkIdQuery.value(0).toInt())
    {
        return;
    }
    std::cout << "[Database::getSelf]  Error: count > 1\n";
    std::cout << "SELECT COUNT(*) FROM user WHERE id LIKE :id\n";
    *hasError = true;
}

void Db_server::get_other_slot(int id, QMap<QString, QString> *data, bool* ok, bool *hasError) {
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
        getOtherQuery.clear();

        if (!getOtherQuery.exec("SELECT user_name, full_name, registration_date, last_login_date FROM user WHERE id = " + temp))
        {
            std::cout << "[Database::getOther]  Error: " << getOtherQuery.lastError().text().toStdString() << std::endl;
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
        return;
    }
    if (!checkIdQuery.value(0).toInt())
    {
        return;
    }
    std::cout << "[Database::getOther]  Error: count > 1\n";
    std::cout << "SELECT COUNT(*) FROM user WHERE id LIKE :id\n";
    *hasError = true;
}

void Db_server::get_search_slot(const QString &text, const QString &category, const QJsonDocument &filters, QJsonDocument *resJSON, bool *hasError) {

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
        resTemp += "{\n\"auction_id\" : \"" + getSearchQuery.value(0).toString() + "\",\n\"data\" : [\n \"title\" : \"" + getSearchQuery.value(1).toString() + "\",\n"
                      "\"condition\" : \"" + getSearchQuery.value(2).toString() + "\",\n\"price\" : \"" + getSearchQuery.value(3).toString() + "\"\n]\n},\n";
    }

    *resJSON = QJsonDocument::fromJson(QByteArray(resTemp.toUtf8()));
}

void Db_server::get_auction_slot(int id, QJsonDocument *resJSON, bool *hasError) {
    *hasError = false;

    QString temp = QString::number(id);

    getAuctionQuery.clear();

    if (!getAuctionQuery.exec("select auction.id, item_description.title, auction.start_date, auction.end_date, auction.current_price, auction.min_step, auction.fix_price,\n"
                              "user.id, user.user_name, item_description.text, item_description.color, item_condition.condition_text\n"
                              "from auction\n"
                              "inner join item on auction.item_id=item.id inner join item_description on item.description_id=item_description.id\n"
                              "inner join item_condition on item_condition.id=item_description.condition_id inner join user on item.user_id=user.id\n"
                              "where auction.id = " + temp))
    {
        std::cout << "[Database::getAuction]  Error: " << getAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    getAuctionQuery.next();

    QString resTemp = "{\n\"auction_id\" : \"" + getAuctionQuery.value(0).toString() + "\",\n\"title\" : \"" + getAuctionQuery.value(1).toString() + "\",\n"
                      "\"start_date\" : \"" + getAuctionQuery.value(2).toString() + "\",\n\"end_date\" : \"" + getAuctionQuery.value(3).toString() + "\",\n"
                      "\"current_price\" : \"" + getAuctionQuery.value(4).toString() + "\",\n\"min_step\" : \"" + getAuctionQuery.value(5).toString() + "\",\n"
                      "\"fix_price\" : \"" + getAuctionQuery.value(6).toString() + "\",\n"
                      "\"user\" : [{\n\"last_licit_user_id\" : \"" + getAuctionQuery.value(7).toString() + "\",\n\"last_licit_user\" : \"" + getAuctionQuery.value(8).toString() + "\"\n}],\n"
                      "\"description_text\" : \"" + getAuctionQuery.value(9).toString() + "\",\n\"description_color\" : \"" + getAuctionQuery.value(10).toString() + "\",\n"
                      "\"condition_text\" : \"" + getAuctionQuery.value(11).toString() + "\"\n}\n";

    *resJSON = QJsonDocument::fromJson(QByteArray(resTemp.toUtf8()));
}

void Db_server::all_auction_slot(QJsonDocument *resJSON, bool *hasError) {
    *hasError = false;

    allAuctionQuery.clear();

    if (!allAuctionQuery.exec("select auction.id, item_description.title, auction.start_date, auction.end_date, auction.current_price, auction.min_step, auction.fix_price,\n"
                              "user.id, user.user_name, item_description.text, item_description.color, item_condition.condition_text\n"
                              "from auction\n"
                              "inner join item on auction.item_id=item.id inner join item_description on item.description_id=item_description.id\n"
                              "inner join item_condition on item_condition.id=item_description.condition_id inner join user on item.user_id=user.id\n"))
    {
        std::cout << "[Database::allAuction]  Error: " << allAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    QString resTemp = "{\n[\n";

     while (allAuctionQuery.next()) {
         if (resTemp.size() != 4)
         {
             resTemp += ",\n";
         }
         resTemp = "{\n\"auction_id\" : \"" + allAuctionQuery.value(0).toString() + "\",\n\"title\" : \"" + allAuctionQuery.value(1).toString() + "\",\n"
         "\"start_date\" : \"" + allAuctionQuery.value(2).toString() + "\",\n\"end_date\" : \"" + allAuctionQuery.value(3).toString() + "\",\n"
         "\"current_price\" : \"" + allAuctionQuery.value(4).toString() + "\",\n\"min_step\" : \"" + allAuctionQuery.value(5).toString() + "\",\n"
         "\"fix_price\" : \"" + allAuctionQuery.value(6).toString() + "\",\n"
         "\"user\" : [\n\"last_licit_user_id\" : \"" + allAuctionQuery.value(7).toString() + "\",\n\"last_licit_user\" : \"" + allAuctionQuery.value(8).toString() + "\"\n],\n"
         "\"description_text\" : \"" + allAuctionQuery.value(9).toString() + "\",\n\"description_color\" : \"" + allAuctionQuery.value(10).toString() + "\",\n"
         "\"condition_text\" : \"" + allAuctionQuery.value(11).toString() + "\"\n}";
     }

     resTemp += "]\n}\n";

    *resJSON = QJsonDocument::fromJson(QByteArray(resTemp.toUtf8()));
}

void Db_server::get_id_slot(const QString &user, QString *id, bool *hasError) {
    *hasError = false;

    getAuctionIdQuery.clear();

    if(!getAuctionIdQuery.exec("SELECT auction.id FROM item\n"
                               "inner join item on auction.item_id=item.id inner join user on item.user_id=user.id\n"
                               "WHRER user.id = " + user + " ORDER BY id DESC LIMIT 1"))
    {
        std::cout << "[Database::getAuctionId]  Error: " << getAuctionIdQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    getAuctionIdQuery.next();

    *id = getAuctionIdQuery.value(0).toString();
}

void Db_server::add_auction_slot(const QMap<QString,QString> &parameters, const QStringList &tags, bool *hasError){
    *hasError = false;

    addAuctionQuery.clear();

    if(!addAuctionQuery.exec("INSERT INTO item_description (title, condition_id, color, text) VALUES (" + parameters["title"] + ", " + parameters["condition"] + ", " + parameters["color"] + ", " + parameters["description"] + ")"))
    {
        std::cout << "[Database::addAuction]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    addAuctionQuery.clear();

    if(!addAuctionQuery.exec("SELECT id FROM item_description ORDER BY id DESC LIMIT 1"))
    {
        std::cout << "[Database::addAuction]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    addAuctionQuery.next();

    QString descId = addAuctionQuery.value(0).toString();

    addAuctionQuery.clear();

    if(!addAuctionQuery.exec("INSERT INTO item (user_id, description_id, category_id) VALUES (" + parameters["user"] + ", " + descId + ", " + parameters["categ"] + ")"))
    {
        std::cout << "[Database::addAuction]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    addAuctionQuery.clear();

    if(!addAuctionQuery.exec("SELECT id FROM item ORDER BY id DESC LIMIT 1"))
    {
        std::cout << "[Database::addAuction]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    addAuctionQuery.next();

    QString itemId = addAuctionQuery.value(0).toString();

    addAuctionQuery.clear();

    //'YYYY-MM-DD HH:MM' - date format in string
    now = QDateTime::currentDateTime();

    QString temp_date = now.toString(Qt::ISODate).mid(-1,11) + " " + now.time().toString(Qt::ISODate).mid(-1,6);

    if(!addAuctionQuery.exec("INSERT INTO auction (item_id, start_date, end_date, current_price, min_step, fix_price, last_licit_user_id) VALUES (" + itemId + ", " + temp_date + ", " + parameters["ed"] + ", " + parameters["cp"] + ", " + parameters["mins"] + ", " + "0" + ", " + parameters["user"] + ")"))
    {
        std::cout << "[Database::addAuction]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }
}

void Db_server::check_bid_slot(const QString &auction, int currentP, bool *ok, bool *hasError) {
    *hasError = false;
    *ok = false;

    checkBidQuery.clear();

    if(!checkBidQuery.exec("select " + QString::number(currentP) + " from auction where id = " + auction))
    {
        std::cout << "[Database::addAuction]  Error: " << checkBidQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    checkBidQuery.next();

    if (currentP == checkBidQuery.value(0).toInt())
    {
        *ok = true;
    }
}

void Db_server::set_bid_slot(const QString &auction, const QString &user, int currentP, bool *hasError) {
    *hasError = false;

    setBidQuery.clear();

    if(!setBidQuery.exec("UPDATE auction SET current_price = " + QString::number(currentP) + ", last_licit_user_id = " + user + " WHERE id = " + auction))
    {
        std::cout << "[Database::addAuction]  Error: " << setBidQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }
}

