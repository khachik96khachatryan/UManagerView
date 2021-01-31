#ifndef FILEREADER_H
#define FILEREADER_H
#include <QAbstractTableModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

#include "xmlparser.h"
class FileReader
{
private:
    void JsonConvert();
    void sortData();

public:
    FileReader();

    void setCheckJson(bool check);
    bool getCheckJson();

    bool LoadJson(const QString dir);
    bool LoadXML(const QString dir);
    void updateBaseData();

    QVector<QStringList> getData()const;
private:
    QJsonObject jsonObject;
    XMLParser   *xmlObject;
    std::shared_ptr<QVector<QStringList>> m_data;
    bool checkJson;
};

#endif // FILEREADER_H
