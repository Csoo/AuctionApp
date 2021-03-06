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
    setBidQuery(db),
    addRatingQuery(db),
    setRatingQuery(db),
    readClosesQuery(db),
    getCloseQuery(db),
    getRateQuery(db),
    getPendingRatingsQuery(db),
    getAllRatingsQuery(db),
    getUserQuery(db)
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
        //std::cout << "ok -> true\n";

        //'YYYY-MM-DD HH:MM' - date format in string -- Qt::ISODate (0-10) + Qt::ISODate (0-5)
        now = QDateTime::currentDateTime();

        QString temp_date = now.toString(Qt::ISODate).mid(-1,11) + " " + now.time().toString(Qt::ISODate).mid(-1,6);

        updateLastQuery.clear();

        updateLastQuery.exec("UPDATE user SET last_login_date = '" + temp_date + "' WHERE user_name = '" + user + "'");

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

    if(!addUserQuery.exec("INSERT INTO user (user_permission, user_name, password, full_name, \"e-mail\", address, phone, registration_date, last_login_date) VALUES (1,'" + user + "', '" + passw + "', '" + fullName + "', '" + email + "', '" + add + "', '" + phone + "', '" + temp_date + "', 'never')")) {
        std::cout << "[Database::addUser]  Error: " << addUserQuery.lastError().text().toStdString() << std::endl;
        std::cout << "INSERT INTO user (user_permission, user_name, password, full_name, \"e-mail\", address, phone, registration_date)" << std::endl;
        *hasError = true;
        return;
    }
}

void Db_server::get_self_slot(int id, QMap<QString,QString> *data, bool* ok, bool *hasError) {
    *hasError = false;
    *ok = false;

    checkIdQuery.clear();
    QString temp = QString::number(id);

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

void Db_server::get_search_slot(const QString &text, const QJsonDocument &filters, const QVariantList &tags, QString *resString, bool *hasError) {

    *hasError = false;

    getSearchQuery.clear();

    QVariantMap filterMap = filters.toVariant().toMap();

    QString temp = "";
    QString tq;

    if (tags.size() != 0) 
    {
        temp += " inner join tag_item_relation on item.id = tag_item_relation.item_id "
                "inner join item_tag on tag_item_relation.tag_id = item_tag.id ";
        for (const auto& tag : tags) {
            if (!tq.isEmpty())
            {
                tq += "' OR ";
            }
            else
            {
                tq += " AND (";
            }
            tq += "tag_name LIKE '" + tag.toString();
        }

        if (!tq.isEmpty())
        {
            tq += "')";
        }
    }
    

    if (filterMap.contains("minPrice"))
    {
        if (filterMap.contains("maxPrice"))
        {
            temp += " where (auction.current_price between " + filterMap["minPrice"].toString() + " and " + filterMap["maxPrice"].toString() + ")";
        }
        else
        {
            temp += " where (auction.current_price > " + filterMap["minPrice"].toString() + ")";
        }
    }
    else
    {
        if (filterMap.contains("maxPrice"))
        {
            temp += " where (auction.current_price < " + filterMap["maxPrice"].toString() + ")";
        }
    }

    filterMap.erase(filterMap.find("maxPrice"));
    filterMap.erase(filterMap.find("minPrice"));

    for (const auto &filter : filterMap) {
        if (filterMap.key(filter.toString()) == "category_id")
            temp += " and item.category_id = '" + filter.toString() + "'"; 
        else
            temp += " and " + filterMap.key(filter.toString()) + " = '" + filter.toString() + "'";
    }

    temp += " and (item_description.title like '%" + text + "%' or item_description.text like '%" + text + "%') ";

    if (!getSearchQuery.exec("select auction.id, item_description.title, item_condition.condition_text, auction.current_price from auction "
                             "inner join item on auction.item_id=item.id "
                             "inner join item_category on item_category.id=item.category_id "
                             "inner join item_description on item.description_id=item_description.id "
                             "inner join item_condition on item_condition.id=item_description.condition_id "
                              + temp + tq))
    {
        std::cout << "[Database::getSearch]  Error: " << getSearchQuery.lastError().text().toStdString() << std::endl;
        std::cout << getSearchQuery.lastQuery().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    std::cout << getSearchQuery.lastQuery().toStdString() << std::endl;

    QString resTemp = "[";

    int results = 0;
    while (getSearchQuery.next()) {
        results++;
        resTemp += R"({"auction_id" : )" + getSearchQuery.value(0).toString() + R"(,"data" : [{ "title" : ")" + getSearchQuery.value(1).toString() +
                    R"(","condition" : ")" + getSearchQuery.value(2).toString() + R"(","price" : )" + getSearchQuery.value(3).toString() + "}]},";
    }

    resTemp += "]";

    if (results != 0) resTemp.remove(resTemp.length()-2, 1);

    *resString = resTemp;
}

void Db_server::get_auction_slot(int id, QJsonDocument *resJSON, bool *hasError) {
    *hasError = false;

    QString temp = QString::fromStdString(std::to_string(id));

    getAuctionQuery.clear();

    if (!getAuctionQuery.exec("select user.id, user.user_name, item_description.title, auction.start_date, "
                              "auction.end_date, auction.current_price, auction.min_step, auction.fix_price, "
                              "auction.last_licit_user_id, item_description.text, item_description.color, item_condition.condition_text "
                              "from auction "
                              "inner join item on auction.item_id=item.id inner join item_description on item.description_id=item_description.id "
                              "inner join item_condition on item_condition.id=item_description.condition_id inner join user on item.user_id=user.id "
                              "where auction.id = '" + temp + "'"))
    {
        std::cout << "[Database::getAuction]  Error: " << getAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    getAuctionQuery.next();

    QString oid, on, title, s_date, e_date, cp, ms, fp, llid, lln, dt, color, ct;

    oid = getAuctionQuery.value(0).toString();
    on = getAuctionQuery.value(1).toString();
    title = getAuctionQuery.value(2).toString();
    s_date = getAuctionQuery.value(3).toString();
    e_date = getAuctionQuery.value(4).toString();
    cp = getAuctionQuery.value(5).toString();
    ms = getAuctionQuery.value(6).toString();
    fp = getAuctionQuery.value(7).toString();
    llid = getAuctionQuery.value(8).toString();
    dt = getAuctionQuery.value(9).toString();
    color = getAuctionQuery.value(10).toString();
    ct = getAuctionQuery.value(11).toString();

    getAuctionQuery.clear();

    QString resTemp;

    if (!llid.isNull()) 
    {
        if (!getAuctionQuery.exec("select user.user_name from user where id = " + llid))
        {
            std::cout << "[Database::getAuction]  Error: " << getAuctionQuery.lastError().text().toStdString() << std::endl;
            *hasError = true;
            return;
        }

        getAuctionQuery.next();

        lln = getAuctionQuery.value(0).toString();

        resTemp = R"({"auction_id" : ")" + QString::number(id) + R"(","owner_id" : ")" + oid + R"(","owner" : ")" + on + R"(","title" : ")" + title +
                        R"(","start_date" : ")" + s_date + R"(","end_date" : ")" + e_date + R"(","current_price" : ")" + cp + R"(","min_step" : ")" + ms +
                        R"(","fix_price" : ")" + fp +
                        "\",\"user\" : [{\n\"last_licit_user_id\" : \"" + llid + R"(","last_licit_user" : ")" + lln + R"("}],"description_text" : ")" + dt +
                        R"(","description_color" : ")" + color + R"(","condition_text" : ")" + ct + "\"}";
    } 
    else
    {
        resTemp = R"({"auction_id" : ")" + QString::number(id) + R"(","owner_id" : ")" + oid + R"(","owner" : ")" + on + R"(","title" : ")" + title +
                        R"(","start_date" : ")" + s_date + R"(","end_date" : ")" + e_date + R"(","current_price" : ")" + cp + R"(","min_step" : ")" + ms +
                        R"(","fix_price" : ")" + fp +
                        R"(","description_text" : ")" + dt +
                        R"(","description_color" : ")" + color + R"(","condition_text" : ")" + ct + "\"}";

    }

    getAuctionQuery.clear();

    if (!getAuctionQuery.exec("select image.content "
                                    "from auction inner join item on item.id=auction.item_id "
                                    "inner join image on image.item_id=item.id "
                                    "where auction.id = " + temp))
    {
        std::cout << "[Database::getAuction]  Error: " << getAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    QJsonArray images;

    while (getAuctionQuery.next())
    {
        images.append(getAuctionQuery.value(0).toJsonValue());
    }

    QJsonDocument json = QJsonDocument::fromJson(QByteArray(resTemp.toUtf8()));
    QJsonObject obj = json.object();
    obj.insert("images", QJsonValue(images));

    *resJSON = QJsonDocument(obj);
}

void Db_server::all_auction_slot(QString *resString, bool *hasError) {
    *hasError = false;

    allAuctionQuery.clear();

    if (!allAuctionQuery.exec("select user.id, user.user_name, item_description.title, auction.start_date, "
                              "auction.end_date, auction.current_price, auction.min_step, auction.fix_price, "
                              "auction.last_licit_user_id, item_description.text, item_description.color, item_condition.condition_text, auction.id "
                              "from auction "
                              "inner join item on auction.item_id=item.id inner join item_description on item.description_id=item_description.id "
                              "inner join item_condition on item_condition.id=item_description.condition_id inner join user on item.user_id=user.id "))
    {
        std::cout << "[Database::allAuction]  Error: " << allAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    QString oid, on, title, s_date, e_date, cp, ms, fp, llid, lln, dt, color, ct, id;
    QString resTemp = "{[";

    while (allAuctionQuery.next()) {
        if (resTemp.size() != 2)
        {
            resTemp += ",";
        }
        oid = allAuctionQuery.value(0).toString();
        on = allAuctionQuery.value(1).toString();
        title = allAuctionQuery.value(2).toString();
        s_date = allAuctionQuery.value(3).toString();
        e_date = allAuctionQuery.value(4).toString();
        cp = allAuctionQuery.value(5).toString();
        ms = allAuctionQuery.value(6).toString();
        fp = allAuctionQuery.value(7).toString();
        llid = allAuctionQuery.value(8).toString();
        dt = allAuctionQuery.value(9).toString();
        color = allAuctionQuery.value(10).toString();
        ct = allAuctionQuery.value(11).toString();
        id = allAuctionQuery.value(12).toString();

        if (!llid.isNull())
        {
            getUserQuery.clear();

            if (!getUserQuery.exec("select user.user_name from user where id = " + llid))
            {
                std::cout << "[Database::getAuction]  Error: " << getUserQuery.lastError().text().toStdString() << std::endl;
                *hasError = true;
                return;
            }

            getUserQuery.next();

            lln = getUserQuery.value(0).toString();


        }
        else
        {
            lln = "";
            llid = "";
        }

        resTemp += R"({"auction_id" : ")" + id + R"(","owner_id" : ")" + oid + R"(","owner" : ")" + on + R"(","title" : ")" + title +
                   R"(","start_date" : ")" + s_date + R"(","end_date" : ")" + e_date + R"(","current_price" : ")" + cp + R"(","min_step" : ")" + ms +
                   R"(","fix_price" : ")" + fp +
                   "\",\"user\" : [{\n\"last_licit_user_id\" : \"" + llid + R"(","last_licit_user" : ")" + lln + R"("}],"description_text" : ")" + dt +
                   R"(","description_color" : ")" + color + R"(","condition_text" : ")" + ct + "\"}";
    }

     resTemp += "]}";

    *resString = resTemp;
}

void Db_server::get_id_slot(const QString &user, QString *id, bool *hasError) {
    *hasError = false;

    getAuctionIdQuery.clear();

    if(!getAuctionIdQuery.exec("SELECT auction.id FROM item\n"
                               "inner join auction on auction.item_id=item.id inner join user on item.user_id=user.id\n"
                               "WHERE user.id = '" + user + "' ORDER BY auction.id DESC LIMIT 1"))
    {
        std::cout << "[Database::getAuctionId]  Error: " << getAuctionIdQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    getAuctionIdQuery.next();

    *id = getAuctionIdQuery.value(0).toString();
}

void Db_server::add_auction_slot(const QMap<QString,QString> &parameters, const QVariantList &tags, const QVariantList &images, bool *hasError){
    *hasError = false;

    addAuctionQuery.clear();

    std::lock_guard<std::mutex> m(db_m);

    if(!addAuctionQuery.exec("INSERT INTO item_description (title, condition_id, color, text) VALUES ('" +
                                parameters["title"] + "', '" + parameters["condition"] + "', '" + parameters["color"]
                                + "', '" + parameters["description"] + "')"))
    {
        std::cout << "[Database::addAuction1]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    addAuctionQuery.clear();

    if(!addAuctionQuery.exec("SELECT id FROM item_description ORDER BY id DESC LIMIT 1"))
    {
        std::cout << "[Database::addAuction2]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    addAuctionQuery.next();

    QString descId = addAuctionQuery.value(0).toString();

    addAuctionQuery.clear();

    if(!addAuctionQuery.exec("INSERT INTO item (user_id, description_id, category_id) VALUES ('"
                                + parameters["user"] + "', '" + descId + "', '" + parameters["categ"] + "')"))
    {
        std::cout << "[Database::addAuction3]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    addAuctionQuery.clear();

    if(!addAuctionQuery.exec("SELECT id FROM item ORDER BY id DESC LIMIT 1"))
    {
        std::cout << "[Database::addAuction4]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    addAuctionQuery.next();

    QString itemId = addAuctionQuery.value(0).toString();

    addAuctionQuery.clear();

    //'YYYY-MM-DD HH:MM' - date format in string
    now = QDateTime::currentDateTime();

    QString temp_date = now.toString(Qt::ISODate).mid(-1,11) + " " + now.time().toString(Qt::ISODate).mid(-1,6);

    if(!addAuctionQuery.exec("INSERT INTO auction (item_id, start_date, end_date, current_price, min_step, "
                             "fix_price) VALUES ('" + itemId + "', '" + temp_date + "', '" + parameters["ed"] +
                             "', '" + parameters["cp"] + "', '" + parameters["mins"] + "', '0')"))
    {
        std::cout << "[Database::addAuction5]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    addAuctionQuery.clear();
    foreach(QVariant image, images) {
        if(!addAuctionQuery.exec("INSERT INTO image (content, item_id) values ('" + image.toString() + "', '" + itemId + "')"))
        {
            std::cout << "[Database::addAuction6]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
            *hasError = true;
            return;
        }        
    }

    QString tagId;
    foreach(QVariant tag, tags) {
        if(!addAuctionQuery.exec("INSERT INTO item_tag (tag_name) values ('" + tag.toString() + "')"))
        {
            std::cout << "[Database::addAuction7]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
            *hasError = true;
            return;
        }   
        addAuctionQuery.clear();
        if(!addAuctionQuery.exec("SELECT id FROM item_tag ORDER BY id DESC LIMIT 1"))
        {
            std::cout << "[Database::addAuction8]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
            *hasError = true;
            return;
        }  
        addAuctionQuery.next();
        tagId = addAuctionQuery.value(0).toString();
        std::cout << "tag: "<< tagId.toStdString() << "item" << itemId.toStdString() <<std::endl;
        addAuctionQuery.clear();
        if(!addAuctionQuery.exec("INSERT INTO tag_item_relation (tag_id, item_id) values ('" + tagId + "', '" + itemId + "')"))
        {
            std::cout << "[Database::addAuction9]  Error: " << addAuctionQuery.lastError().text().toStdString() << std::endl;
            *hasError = true;
            return;
        }   
        addAuctionQuery.clear(); 
    }
}

void Db_server::check_bid_slot(const QString &auction, int currentP, bool *ok, bool *hasError) {
    *hasError = false;
    *ok = false;

    checkBidQuery.clear();

    if(!checkBidQuery.exec("select current_price from auction where id = " + auction))
    {
        std::cout << "[Database::checkBid]  Error: " << checkBidQuery.lastError().text().toStdString() << std::endl;
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

    std::lock_guard<std::mutex> m(db_m);

    if(!setBidQuery.exec("UPDATE auction SET current_price = " + QString::number(currentP) +
                            ", last_licit_user_id = " + user + " WHERE id = " + auction))
    {
        std::cout << "[Database::setBid]  Error: " << setBidQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }
}

void Db_server::add_rating_slot(const QString &id, bool *hasError) {
    *hasError = false;

    addRatingQuery.clear();

    std::lock_guard<std::mutex> m(db_m);

    if(!addRatingQuery.exec("SELECT user_id, last_licit_user_id FROM auction inner join item on auction.item_id=item.id Where auction.id=" + id))
    {
        std::cout << "[Database::addRating]  Error: " << addRatingQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    addRatingQuery.next();

    QString from = addRatingQuery.value(0).toString(), to = addRatingQuery.value(1).toString();

    addRatingQuery.clear();

    if(!addRatingQuery.exec("INSERT INTO rating (user_id, rater_user_id, is_rated, auction_id) VALUES (" +
                            from + ", " + to + ", " + QString::number(0) + ", " + id + ")"))
    {
        std::cout << "[Database::addRating]  Error: " << addRatingQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }
}

void Db_server::set_rating_slot(int rateId, int positive, const QString &msg, bool *hasError) {
    *hasError = false;

    setRatingQuery.clear();

    QDateTime CT = QDateTime::currentDateTime();

    std::lock_guard<std::mutex> m(db_m);

    if(!setRatingQuery.exec("UPDATE rating SET is_positive = " + QString::number(positive) + ", description = '" + msg +
                            "', rating_date = '" + CT.toString(Qt::ISODate).mid(-1,11) + " " +
                            CT.time().toString(Qt::ISODate).mid(-1,6) + "', is_rated = 1 WHERE id = " + QString::number(rateId)))
    {
        std::cout << "[Database::setRating1]  Error: " << setRatingQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }
}

void Db_server::read_closes_slot(QMap<QString, QString> *closes, const QString &date) {

    readClosesQuery.clear();
    std::cout << "db_read" << std::endl;
    if(!readClosesQuery.exec("select id, end_date from auction"))
    {
        std::cout << "[Database::readCloses]  Error: " << readClosesQuery.lastError().text().toStdString() << std::endl;
        return;
    }

    while (readClosesQuery.next()) {

        if (date < readClosesQuery.value(1).toString())
        {
            //id, end_date
            closes->insert(readClosesQuery.value(0).toString(), readClosesQuery.value(1).toString());
            std::cout << readClosesQuery.value(0).toString().toStdString() << " " << readClosesQuery.value(1).toString().toStdString() << std::endl;
        }


    }
    std::cout << "db_read end" << std::endl;
}

void Db_server::get_close_data_slot(const QString &id, QString &lluser, QString &auuser, QString &currentP, QString &title, bool *hasError) {
    *hasError = false;
    getCloseQuery.clear();

    if(!getCloseQuery.exec("SELECT auction.last_licit_user, item.user_id, auction.current_price, item_description.title FROM "
                           "auction inner join item on auction.item_id=item.id inner join item_description on item_description.id=item.description_id"
                           "WHERE auction.id=" + id))
    {
        std::cout << "[Database::getCloseData]  Error: " << getCloseQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    getCloseQuery.next();

    lluser = getCloseQuery.value(0).toString();
    auuser = getCloseQuery.value(1).toString();
    currentP = getCloseQuery.value(2).toString();
    title = getCloseQuery.value(3).toString();
}

void Db_server::get_email_slot(const QString &user, QString &email, bool *hasError) {
    *hasError = false;
    getCloseQuery.clear();

    if(!getCloseQuery.exec("SELECT e-mail FROM user WHERE id=" + user))
    {
        std::cout << "[Database::getEmail]  Error: " << getCloseQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    getCloseQuery.next();

    email = getCloseQuery.value(0).toString();
}

void Db_server::get_rate_slot(const QString &user, QString &p, QString &n, bool *hasError) {
    *hasError = false;
    getRateQuery.clear();

    if(!getRateQuery.exec("SELECT COUNT(*) FROM rating WHERE user_id='" + user + "' AND is_positive=1"))
    {
        std::cout << "[Database::getRate1]  Error: " << getRateQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    getRateQuery.next();

    p = getRateQuery.value(0).toString();

    getRateQuery.clear();

    if(!getRateQuery.exec("SELECT COUNT(*) FROM rating WHERE user_id='" + user + "' AND is_positive=0"))
    {
        std::cout << "[Database::getRate2]  Error: " << getRateQuery.lastError().text().toStdString() << std::endl;
        *hasError = true;
        return;
    }

    getRateQuery.next();

    n = getRateQuery.value(0).toString();
}

void Db_server::get_pending_ratings_slot(int id, QJsonDocument* resJson, bool* ok, bool* hasError) {
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
        getPendingRatingsQuery.clear();

        if (!getPendingRatingsQuery.exec("select rating.id, rating.user_id, user.user_name, rating.auction_id, item_description.title from rating "
                                            "inner join auction on auction.id=rating.auction_id "
                                            "inner join item on item.id=auction.item_id "
                                            "inner join item_description on item.description_id = item_description.id "
                                            "inner join user on rating.user_id = user.id "
                                            "where rating.rater_user_id = " + temp + " and rating.is_rated = 0"))
        {
            std::cout << "[Database::getPendingRatings]  Error: " << getPendingRatingsQuery.lastError().text().toStdString() << std::endl;
            *hasError = true;
            return;
        }

        QJsonArray ratings;
        while (getPendingRatingsQuery.next()) {
            QJsonObject rating;
            rating.insert("ratingId", QJsonValue(getPendingRatingsQuery.value(0).toString()));
            rating.insert("userId", QJsonValue(getPendingRatingsQuery.value(1).toString()));
            rating.insert("userName", QJsonValue(getPendingRatingsQuery.value(2).toString()));
            rating.insert("auctionId", QJsonValue(getPendingRatingsQuery.value(3).toString()));
            rating.insert("auctionTitle", QJsonValue(getPendingRatingsQuery.value(4).toString()));
            ratings.append(QJsonValue(rating));
        }

        resJson->setArray(ratings);

        *ok = true;
        return;
    }
    if (!checkIdQuery.value(0).toInt())
    {
        return;
    }
    std::cout << "[Database::getPendingRatings]  Error: count > 1\n";
    std::cout << "SELECT COUNT(*) FROM user WHERE id LIKE :id\n";
    *hasError = true;
}

void Db_server::get_all_ratings_slot(int id, QJsonDocument* resJson, bool* ok, bool* hasError) {
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
        getAllRatingsQuery.clear();

        if (!getAllRatingsQuery.exec("select user.user_name, rater_user_id, is_positive, description, rating_date from rating "
                                        "inner join user on user.id=rating.rater_user_id "
                                        "where user_id = "+ temp +" and is_rated = 1"))
        {
            std::cout << "[Database::getAllRatings]  Error: " << getPendingRatingsQuery.lastError().text().toStdString() << std::endl;
            *hasError = true;
            return;
        }

        QJsonArray ratings;
        while (getAllRatingsQuery.next()) {
            QJsonObject rating;
            rating.insert("rater_username", QJsonValue(getAllRatingsQuery.value(0).toString()));
            rating.insert("rater_id", QJsonValue(getAllRatingsQuery.value(1).toString()));
            rating.insert("is_positive", QJsonValue(getAllRatingsQuery.value(2).toString()));
            rating.insert("description", QJsonValue(getAllRatingsQuery.value(3).toString()));
            rating.insert("rating_date", QJsonValue(getAllRatingsQuery.value(4).toString()));
            ratings.append(QJsonValue(rating));
        }

        resJson->setArray(ratings);

        *ok = true;
        return;
    }
    if (!checkIdQuery.value(0).toInt())
    {
        return;
    }
    std::cout << "[Database::getAllRatings]  Error: count > 1\n";
    std::cout << "SELECT COUNT(*) FROM user WHERE id LIKE :id\n";
    *hasError = true;
}