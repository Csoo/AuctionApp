#include "apirequest.h"
#include <QDebug>

using json = nlohmann::json;

APIrequest::APIrequest(QObject *parent) :
    QObject(parent),
    manager(new QNetworkAccessManager(this)),
    url(QUrl("http://81.183.216.27:3000"))
{

}

bool APIrequest::loginRequest(const QString &name, const QString &pw)
{
    url.setPath("/login");
    request.setUrl(url);

    request.setRawHeader("user", name.toUtf8());
    request.setRawHeader("password", pw.toUtf8());
    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&loop, SLOT(quit()));

    qDebug() << url.toString() << " / " << name.toUtf8() << pw.toUtf8() << endl;

    reply = manager->get(request);
    loop.exec();

     qDebug() << reply->errorString() << endl;

    return reply->readAll() == "true";
}
