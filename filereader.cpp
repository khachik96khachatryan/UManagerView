#include "filereader.h"
FileReader::FileReader(): m_data(new QVector<QStringList>())
                        ,xmlObject(new XMLParser)
{
}

void FileReader::setCheckJson(bool check)
{
    checkJson = check;
}

bool FileReader::getCheckJson()
{
    return checkJson;
}
bool FileReader::LoadJson(const QString dir)
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
          return false;
      }
      return true;
}

bool FileReader::LoadXML(const QString dir)
{
    QFile file_(dir);
    if(!file_.open(QIODevice::ReadOnly)){ // Try Catch
        QMessageBox::critical(0,"Permission denied","Failed to open file:");
        return false;
      }
       QXmlInputSource source(&file_);
       QXmlSimpleReader reader;
       reader.setContentHandler(xmlObject);
       reader.parse(source);

}

void FileReader::updateBaseData()
{
    if(getCheckJson()){
        JsonConvert();
        xmlObject->clear_();
    }
    else{
        *m_data = xmlObject->getAssoc();
    }

     sortData();
}

void FileReader::JsonConvert()
{
    QList<QVariant> List_ = jsonObject.toVariantMap()["users"].toList();
         if(List_.empty())
         {
             QMessageBox::warning(0,"File has no users attribute  ","Please check the file");
             return;
         }
         QList<QVariant>::iterator begin_iter = List_.begin();
         QStringList temp_strList;
         m_data->clear();

         while (begin_iter != List_.end()) {
             QMap<QString,QVariant> tempIter = begin_iter->toMap();
             if(tempIter["username"].toString().length() > 0){
                 temp_strList.push_back(tempIter["username"].toString());
                 temp_strList.push_back(tempIter["lastname"].toString());
                 temp_strList.push_back(QString::number(tempIter["age"].toInt()));
                 temp_strList.push_back(tempIter["address"].toString());
                 m_data->push_back(temp_strList);
                 temp_strList.clear();
             }
             begin_iter++;
         }
}
void FileReader::sortData()
{
    if(m_data->empty())
            return;
        std::sort(m_data->begin(),m_data->end(),[](QStringList strList,QStringList strList1)
                                                {
                                                    QString str = strList.at(0);
                                                    QString str1 = strList1.at(0);
                                                    return (str.toLower() < str1.toLower());
                                                });
}

QVector<QStringList> FileReader::getData() const
{
    return *(this->m_data);
}

