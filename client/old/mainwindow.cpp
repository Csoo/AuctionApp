#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QQmlContext>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->quickWidget->rootContext()->setContextProperty("mainWin", this);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/login.qml")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

