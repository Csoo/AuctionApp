//
// Created by petras on 2020. 03. 24..
//

#pragma once

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QThread>
#include <QString>

class db_server: public QThread {
public:

    QString check_login(const QString &user, const QString &passw);

protected:

    QSqlDatabase db;
    QString connectionName;
    QString dbName;
};
