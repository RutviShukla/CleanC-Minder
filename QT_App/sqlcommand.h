#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

#ifndef SQLCOMMAND_H
#define SQLCOMMAND_H


class sqlcommand
{
public:
    sqlcommand();

    void createDatabase(QString path);
    void createTable();
    void addData(QString courseID, QString courseName, QString assignmentName, QString date);
    std::vector<QString> getData();
    std::vector<QString> getData(QString dueTime);
    void deleteDatabase();
};

#endif // SQLCOMMAND_H
