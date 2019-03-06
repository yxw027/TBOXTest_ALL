#include <QGuiApplication>
#include <QDebug>
#include <QString>
#include <QSize>
#include <QCoreApplication>
#include "mainwindow.h"

MainWindow* mainwindow = NULL;

void recvSignal(int sig)
{
    //qDebug()<<"recvSignal!!!";
}

int main(int argc, char *argv[])
{
    system("echo 0 > /sys/class/gpio/gpio112/value");
    system("echo 1 > /sys/class/gpio/gpio101/value");
    system("echo 1 > /sys/class/gpio/gpio6/value");
    signal(SIGSEGV, recvSignal);
    QGuiApplication app(argc, argv);
    QFontDatabase::addApplicationFont(FONT_PATH);//添加字体路径
    mainwindow = new MainWindow;
    mainwindow->m_pCallInterface->pickdown();
    mainwindow->rootContext()->setContextProperty("MainWindow", mainwindow);
    mainwindow->rootContext()->setContextProperty("fontFamily", FONT_NAME);
    QQmlEngine *engine = mainwindow->engine();
    engine->addImageProvider("qrcode", mainwindow->thread_m);
    mainwindow->m_pInitTimer->start(1000);
    //mainwindow->init();
    mainwindow->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    mainwindow->setFlags(Qt::FramelessWindowHint);
    mainwindow->show();
    mainwindow->m_pConnectServerTime->start(1000);
    return app.exec();
}
