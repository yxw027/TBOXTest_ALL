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
    signal(SIGSEGV, recvSignal);
    QGuiApplication app(argc, argv);
    QFontDatabase::addApplicationFont(FONT_PATH);//添加字体路径
    mainwindow = new MainWindow;
    if(mainwindow != NULL)
    {
        mainwindow->rootContext()->setContextProperty("MainWindow", mainwindow);
        mainwindow->rootContext()->setContextProperty("fontFamily", FONT_NAME);
        QQmlEngine *engine = mainwindow->engine();
        engine->addImageProvider("qrcode", mainwindow->thread_m);
        mainwindow->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
        mainwindow->setFlags(Qt::FramelessWindowHint);
        mainwindow->show();
        mainwindow->init();
        mainwindow->m_pConnectServerTime->start(1000);
    }
    else
    {

    }
    return app.exec();
}
