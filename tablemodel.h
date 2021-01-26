#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>
#include <set>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>


class TableModel:public QAbstractTableModel
{
private:
    int m_nRows;
    int m_nColumns;
    QHash<QModelIndex,QVariant> m_hash;
    QVector<QStringList> m_list;
public:
    TableModel(int nRows,int nColumns, QObject* pobj = 0);
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setFileDir(const QString& dir);

private:

    bool LoadJson(const QString& dir = "/home/linux/Documents/git/UManager/json.json");
    void Convert();
    void setRowCount();
    void setColumnCount();
    QJsonObject jsonObject;

signals:
    void update_data();
};

#endif // TABLEMODEL_H
