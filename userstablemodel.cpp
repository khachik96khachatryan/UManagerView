#include "userstablemodel.h"

void UsersTableModel::setRowCount()
{
    if(m_UserData->empty())
    {
        this->m_RowsCount = 0;
        return;
    }

    this->m_RowsCount = m_UserData->size();
}

void UsersTableModel::setColumnCount()
{
    if(m_UserData->empty())
    {
        this->m_ColumnsCount = 0;
        return;
    }
    this->m_ColumnsCount = (m_UserData->at(0)).size();
}
UsersTableModel::UsersTableModel(QObject *pobj):QAbstractTableModel(pobj)
                                               ,m_File(new FileReader())
                                               ,m_UserData(new QVector<QStringList>)
{
    /*m_File->LoadJson("/home/linux/Documents/git/UManager/json.json");
    m_File->updateBaseData();*/
   // updateData();
    setRowCount();
    setColumnCount();
}

UsersTableModel::~UsersTableModel()
{
    delete m_UserData;
}

QVariant UsersTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
            return QVariant();
        }
        return (role == Qt::DisplayRole)
                        ? m_hash.value(index, QVariant(m_UserData->at(index.row()).at(index.column())))
                        : QVariant();
}

bool UsersTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole){
        m_hash[index] = value;
        emit dataChanged(index,index);
        return true;
    }
    return false;
}
int UsersTableModel::rowCount(const QModelIndex &) const
{
    return this->m_RowsCount;
}
int UsersTableModel::columnCount(const QModelIndex &) const
{
    return this->m_ColumnsCount;
}
Qt::ItemFlags UsersTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags_ = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags_ | Qt::ItemIsEditable):flags_;
}
QVariant UsersTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical && role == Qt::DisplayRole)
        {
                return ++section;
        }
        if (role == Qt::DisplayRole)
        {
             if (orientation == Qt::Horizontal) {
                switch (section)
                {
                case 0:
                    return QString("Name");
                case 1:
                    return QString("Lastname");
                case 2:
                    return QString("Age");
                case 3:
                    return QString("Address");
                }
            }
        }
        return QVariant();
}
void UsersTableModel::setFileDir(QString &dir)
{
    if(m_File->LoadJson(dir)){
        m_File->updateBaseData();
        setRowCount();
        setColumnCount();
        return;
    }
}

void UsersTableModel::updateData()
{
    *m_UserData = m_File->getData();
    setRowCount();
    setColumnCount();
    emit layoutChanged();
}
void UsersTableModel::updateTable()
{
    setRowCount();
    setColumnCount();
    emit layoutChanged();
}
void UsersTableModel::findValue(const QString &value)
{
    if(value.length() == 0){
        updateData();
        return;
    }
    QVector<QStringList> copy_(m_File->getData());
    m_UserData->clear();
    auto iter_temp = copy_.begin();
    QString temp_value;
    while (iter_temp != copy_.end()) {
        temp_value = iter_temp->at(0);
        if(temp_value.toLower().contains(value.toLower()))
        {
            m_UserData->push_back(*iter_temp);
        }
        iter_temp++;
    }
}
