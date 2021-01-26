#include "tablemodel.h"

TableModel::TableModel(int nRows, int nColumns, QObject *pobj)
                    :QAbstractTableModel(pobj)

{
    //LoadJson();
    //std::sort(m_list.begin(),m_list.end());
    setRowCount();
    setColumnCount();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    return (role == Qt::DisplayRole || role == Qt::EditRole)
                        ? m_hash.value(index, QVariant(m_list.at(index.row()).at(index.column())))
                        : QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole){
        m_hash[index] = value;
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return m_nRows;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return m_nColumns;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags_ = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags_ | Qt::ItemIsEditable):flags_;
}

bool TableModel::setFileDir(const QString &dir)
{
    if(LoadJson(dir))
        return true;
    return false;
}

bool TableModel::LoadJson(const QString& dir)
{
    QFile jsonFile(dir);

   if(!jsonFile.open(QIODevice::ReadOnly)){ // Try Catch
       QMessageBox::critical(0,"Permission denied","Failed to open file:");
         return false;

      }
      QByteArray saveData = jsonFile.readAll();
      jsonFile.close();
      QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
      this->jsonObject = jsonDocument.object();
      if(this->jsonObject.empty())
      {
          QMessageBox::warning(0,"Json file Error","File does not match\nOr Json syntax error ");
          return true;
      }
      Convert();
      return true;

}

void TableModel::Convert()
{
     QList<QVariant> List_ = jsonObject.toVariantMap()["users"].toList();
     if(List_.empty())
     {
         QMessageBox::warning(0,"File has no users attribute  ","Please check the file");
         return;
     }
     QList<QVariant>::iterator begin_iter = List_.begin();
     QStringList temp_strList;
     m_list.clear();

     while (begin_iter != List_.end()) {
         QMap<QString,QVariant> tempIter = begin_iter->toMap();
         if(tempIter["username"].toString().length() > 0){
             temp_strList.push_back(tempIter["username"].toString());
             temp_strList.push_back(tempIter["lastname"].toString());
             temp_strList.push_back(QString::number(tempIter["age"].toInt()));
             temp_strList.push_back(tempIter["address"].toString());
             m_list.push_back(temp_strList);
             temp_strList.clear();
         }
         begin_iter++;
     }
     setRowCount();
     setColumnCount();
}

void TableModel::setRowCount()
{
    m_nRows = m_list.size();
}

void TableModel::setColumnCount()
{
    if(!m_list.empty())
        m_nColumns = m_list.at(0).size();
}

