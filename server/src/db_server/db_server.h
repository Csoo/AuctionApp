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

    void check_login_slot(const QString &user, const QString &passw, bool* ok, bool* hasError);
    void check_reg_slot(const QString &email, const QString &user, int* ok, bool* hasError);

    void add_user_slot(const QString &email, const QString &user, const QString &fullName, const QString &passw, const QString &add, const QString &phone, bool* hasError);

protected:

    QSqlDatabase db;
    QString connectionName;
    QString dbName;

    QSqlQuery getLoginQuery;
};