#ifndef ASSINGMENTLISTMODEL_H
#define ASSINGMENTLISTMODEL_H

#include <QAbstractListModel>
#include <QDateTime>
#include <stdio.h>


using namespace std;


enum Roles {
    assingmentNameRole = Qt::UserRole + 1,
    courseNameRole,
    assingmentDueDateRole
};

class AssingmentListModel : public QAbstractListModel
{
public:
    AssingmentListModel();
    ~AssingmentListModel();

    void addData(const QString &assingmentName, const QString &courseName, const QDateTime &assingmentDueDate);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;


protected:
    QHash<int, QByteArray> roleNames() const;

private:
    class AssingmentInfo {
    public:
        QString assingmentName;
        QString courseName;
        QDateTime assingmentDueDate;
    };
    QVector<AssingmentInfo*> m_data;

};

#endif // ASSINGMENTLISTMODEL_H
