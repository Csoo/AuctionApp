#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QVector>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <auctionitem.h>

class APIrequest : public QObject
{
    Q_OBJECT
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QNetworkRequest request;

    QUrl url;

public:
    explicit APIrequest(QObject *parent = nullptr);

    Q_INVOKABLE int loginRequest(const QString &name, const QString &pw);
    Q_INVOKABLE bool registerRequest(const QString &name, const QString &pw,  const QString &email,  const QString &fullName,  const QString &address,  const QString &phone = "");
    Q_INVOKABLE int addAuctionRequest(int userId, const QString &title, const QString &descriptionText, const QString &color, int currentPrice, int minStep, int categoryId,  int conditionId, QStringList tags, QDate endDate, const QList<QByteArray> &images);
    Q_INVOKABLE int bidRequest(int auctionId, int licitUserId, int currentPrice, int bid);
    Q_INVOKABLE int rateUserRequest(int userIdFrom, int userIdTo, bool isPositive, const QString &message);
    Q_INVOKABLE bool allAuctionRequest();
    QVector<AuctionItem> searchRequest(const QString &searchText, int category_id, const QString &color, int condition_id, int minPrice, int maxPrice, const QStringList &tags);
    QJsonDocument ownProfileRequest(int id);
    QJsonDocument profileRequest(int id);
    QJsonDocument auctionRequest(int id);

signals:
};

#endif // APIREQUEST_H
