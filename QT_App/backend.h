#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QDateTime>
#include <qqml.h>
#include <QAbstractListModel>
#include <QQmlListProperty>
#include <QtQml/qqml.h>
#include <QNetworkRequest>

class BackEnd
{

private:
    class assignmentsInfo {
    public:
        QString cName;  //course name
        QString aName;  //assignment name
        QDateTime dDate;    //due date
    };

public:
    QVector<QString> listCourses;
    QVector<QString> assignment_names;
    QVector<QString> due_dates;
    QVector<QString> course_ID;
    QNetworkRequest request;
    //QString access_token = "1016~4dnAMKpSxP9OzNoxtJOYw8DAgXz4KSLlshQLRMU2sMQvBMO3wrZZlw4ia2bIJCbt"; // add token
    QString access_token = "1016~Ac0cFcraqlqoE0u654oBA4mqEOXUMzrqSNABV9tAlCpbnRYG2yBam0DhwUnhYbgH";
    QVector<QNetworkRequest> request_vec;

    BackEnd();
};

#endif // BACKEND_H
