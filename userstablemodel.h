#ifndef USERSTABLEMODEL_H
#define USERSTABLEMODEL_H
#include "filereader.h"
#include <algorithm>
class UsersTableModel:public QAbstractTableModel
{

private:
    int m_RowsCount;
    int m_ColumnsCount;
    QHash<QModelIndex,QVariant> m_hash;
    QVector<QStringList> *m_UserData;
    std::unique_ptr<FileReader> m_File;
    QString fileDir;

    QString m_value_find;
    void setRowCount();
    void setColumnCount();
    QString cutExtension(QString& dir);
public:
    UsersTableModel(QObject* pobj = 0);
    ~UsersTableModel();

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setFileDir(QString& dir);
    void updateData();
    void updateTable();
    void findValue(const QString& value);
};

#endif // USERSTABLEMODEL_H
