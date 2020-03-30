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
#include <QDebug>

class db_server: public QThread {
public:

    db_server(const QString& driver, QString connectionName, QString dbName);

    bool init();

public slots:

    void check_login(const QString &user, const QString &passw, bool* ok, bool* hasError);

protected:

    QSqlDatabase db;
    QString connectionName;
    QString dbName;

    QSqlQuery getLoginQuery;
};