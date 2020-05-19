#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <apirequest.h>
#include <auctionimages.h>
#include <auctionlistmodel.h>
#include <profile.h>
#include <auction.h>
#include <pendingitemlistmodel.h>
#include <ratinglistmodel.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setOrganizationName("AuctionApp");

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    APIrequest req;
    AuctionImages imgs;
    Profile profile;
    AuctionListModel model;
    Auction auction;
    PendingItemListModel pendingModel;
    RatingListModel rateModel;
    engine.rootContext()->setContextProperty("httpRequest", &req);
    engine.rootContext()->setContextProperty("images", &imgs);
    engine.rootContext()->setContextProperty("myProfile", &profile);
    engine.rootContext()->setContextProperty("auctionModel", &model);
    engine.rootContext()->setContextProperty("auctionItem", &auction);
    engine.rootContext()->setContextProperty("pendingModel", &pendingModel);
    engine.rootContext()->setContextProperty("ratingModel", &rateModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
