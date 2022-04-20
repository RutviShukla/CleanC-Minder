#include "sqlcommand.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QtSql>
#include <QQmlContext>
#include <QtDebug>
#include <QFileInfo>
#include <QtQuick/QQuickWindow>
#include <QtQml>
#include <QDateTime>
#include <qqml.h>
#include <QQuickView>
#include <QAbstractListModel>
#include <QQmlListProperty>
#include <QDateTime>
#include "windows.h"
#include "backend.h"
#include "assingmentlistmodel.h"
#include "filterproxymodel.h"

using namespace std;


int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    QEventLoop eventLoop;

    BackEnd object;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QString course_url = "https://ufl.instructure.com/api/v1/courses?enrollment_state=active&access_token="+object.access_token;

     // make the get request to active courses
    QUrl active_courses(course_url);
    QNetworkRequest request(active_courses);
    QNetworkReply *reply = mgr.get(request);
    eventLoop.exec();

    QMap<QString,QString> courseData;

    if (reply ->error() == QNetworkReply::NoError)
    {
        QString strReply = reply -> readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonArray courses_json_array = jsonResponse.array();
        for(int i=0; i<courses_json_array.size(); i++)
        {
              QJsonObject jsonObj = courses_json_array.at(i).toObject();
              QString courseName = jsonObj.find("name").value().toString();
              int courseID = jsonObj.find("id").value().toInt();

              QString course_id_string = QString :: number(courseID);
              courseData[course_id_string] = courseName;

              QString parameters = "/assignments?per_page=100&access_token="+object.access_token;
              QString courseURL= "https://ufl.instructure.com/api/v1/courses/"+course_id_string+parameters;

              QUrl complete_url(courseURL);
              object.request = QNetworkRequest(complete_url);
              object.request_vec.push_back(object.request);
         }

         for (qsizetype i=0; i < object.request_vec.size();i++)
         {
             QEventLoop eventLoop2;
             QNetworkAccessManager a_mgr;
             QObject::connect(&a_mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop2, SLOT(quit()));
             QNetworkRequest request(object.request_vec[i]);
             QNetworkReply *a_reply = a_mgr.get(request);
             eventLoop2.exec();

             if (a_reply ->error() == QNetworkReply::NoError)
             {
                 int ass_course_id;
                 QString strReply = a_reply -> readAll();
                 QJsonDocument assignment_jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
                 QJsonArray assignment_json_array = assignment_jsonResponse.array();

                 for(int i=0; i<assignment_json_array.size(); i++)
                 {
                     QJsonObject jsonObj2 = assignment_json_array.at(i).toObject();
                     QString assignmentName = jsonObj2.find("name").value().toString();
                     ass_course_id = jsonObj2.find("course_id").value().toInt();
                     QString dueDate = jsonObj2.find("due_at").value().toString();

                     object.listCourses.push_back(QString :: number(ass_course_id));
                     object.course_ID.push_back(QString :: number(ass_course_id));
                     object.due_dates.push_back(dueDate);
                     object.assignment_names.push_back(assignmentName);
                 }
             }
                  delete a_reply;
         }
     }
     delete reply;

    AssingmentListModel listModel;

    sqlcommand sqlData;

    //QString path2 = QDir :: current().currentPath()  + "/Resources/Database/qt.assignments";
    //qDebug() << path2;
    //QString path = "C:/Users/Thicctoria/Desktop/CEN3031-Group5/MainApp/QT_App/Resources/Database/qt.assignments";
    //sqlData.createDatabase(path);
    //sqlData.createTable();
    for(qsizetype i =0; i< object.listCourses.size(); i++)
    {
        QDateTime dateTime = QDateTime :: fromString(object.due_dates[i],"yyyy-MM-ddThh:mm:ssZ");
        object.due_dates[i] = dateTime.toString("yyyy-MM-dd:hh:mm:ss");
        QDateTime date = QDateTime :: fromString(object.due_dates[i],"yyyy-MM-dd:hh:mm:ss");
        if(courseData.count(object.listCourses[i]))
        {
            replace(object.listCourses.begin(), object.listCourses.end(), object.listCourses[i],courseData.value(object.listCourses[i]));
        }

         listModel.addData(object.assignment_names[i], object.listCourses[i], date);
         //sqlData.addData(object.course_ID[i],object.listCourses[i],object.assignment_names[i],object.due_dates[i]);
         //qDebug() << "CourseID: " << object.course_ID[i] << "CourseName: " << object.listCourses[i] << "Assignment_Name: " << object.assignment_names[i] << "Due Date: " << object.due_dates[i];
    }

    FilterProxyModel filterModel;
    filterModel.setSourceModel(&listModel);
    filterModel.setFilterRole(assingmentNameRole);
    filterModel.setSortRole(assingmentNameRole);


//


//        //EXAMPLE CODE TO DRAW FROM/COMMENT IF NECESSARY

//             sqlData.addData("Cen 3101", "Intro to Software Engineering", "Spring Review", "2021-01-30T00:12:00.000");
//             vector<QString> v1 = sqlData.getData();
//             for(unsigned int x = 0; x < v1.size(); x++){
//             qDebug() << v1.at(x);
//               }
//             sqlData.deleteDatabase();


    QQmlApplicationEngine engine;

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("filterModel", &filterModel);


    const QUrl url(u"qrc:/main.qml"_qs);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
