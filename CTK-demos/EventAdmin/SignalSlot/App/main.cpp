﻿#include <QCoreApplication>
#include <QtDebug>

#include <ctkPluginFrameworkLauncher.h>
#include <ctkPluginContext.h>
#include <ctkPluginException.h>

int main(int argc, char *argv[])
{
    qDebug()<<"---main start---";
    QCoreApplication app(argc, argv);

    // 获取事件管理插件org_commontk_eventadmind.dll所在位置
    QString eventAdminPath = QCoreApplication::applicationDirPath() + "/lib";
    // 在插件的搜索路径列表中添加一条路径
    ctkPluginFrameworkLauncher::addSearchPath(eventAdminPath);

    // 设置并启动 CTK 插件框架
    bool ret = ctkPluginFrameworkLauncher::start("org.commontk.eventadmin");
    qDebug()<<"plugin org_commontk_eventadmind.dll start: "<<ret;

    // 获取插件上下文（即插件运行环境）
    ctkPluginContext* context = ctkPluginFrameworkLauncher::getPluginContext();

    // 获取插件所在位置
    QString path = QCoreApplication::applicationDirPath() + "/plugins";
    // 启动插件 BlogEventHandlerUsingSlots
    try {
        QSharedPointer<ctkPlugin> plugin = context->installPlugin(QUrl::fromLocalFile(path + "/BlogEventHandlerUsingSlots.dll"));
        plugin->start();
        qDebug() << "BlogEventHandlerUsingSlots start ...";
    } catch (const ctkPluginException &e) {
        qDebug() << "Failed to start BlogEventHandlerUsingSlots" << e.what();
    }

    // 启动插件 BlogManagerUsingSignals
    try {
        QSharedPointer<ctkPlugin> plugin = context->installPlugin(QUrl::fromLocalFile(path + "/BlogManagerUsingSignals.dll"));
        plugin->start();
        qDebug() << "BlogManagerUsingSignals start ...";
    } catch (const ctkPluginException &e) {
        qDebug() << "Failed to start BlogManagerUsingSignals" << e.what();
    }

    // 停止插件
    ctkPluginFrameworkLauncher::stop();

    return app.exec();
}
