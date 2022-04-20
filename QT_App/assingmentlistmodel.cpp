#include "assingmentlistmodel.h"

AssingmentListModel::AssingmentListModel()
{

}

AssingmentListModel::~AssingmentListModel()
{

}

void AssingmentListModel::addData(const QString &assingmentName, const QString &courseName, const QDateTime &assingmentDueDate)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    AssingmentInfo* ass = new AssingmentInfo();
    ass->assingmentName = assingmentName;
    ass->courseName = courseName;
    ass->assingmentDueDate = assingmentDueDate;
    m_data.push_back(ass);
    endInsertRows();
}

int AssingmentListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.size();
}

QVariant AssingmentListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.size())
    return QVariant();

    const QString &assingmentName = m_data[index.row()]->assingmentName;
    const QString &courseName = m_data[index.row()]->courseName;
    const QDateTime &assingmentDueDate = m_data[index.row()]->assingmentDueDate;
    if (role == assingmentNameRole)
        return assingmentName;
    if (role == courseNameRole)
        return courseName;
    if (role == assingmentDueDateRole)
        return assingmentDueDate;

    return QVariant();
}

QHash<int, QByteArray> AssingmentListModel::roleNames() const
{
 QHash<int, QByteArray> roles;
 roles[assingmentNameRole] = "assingment";
 roles[courseNameRole] = "course";
 roles[assingmentDueDateRole] = "dueDate";
 return roles;
}
