#ifndef FILEREADER_H
#define FILEREADER_H
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
#include <memory>
class FileReader
{
private:
    void JsonConvert();
    void sortData();

public:
    FileReader();

    bool LoadJson(const QString dir);
    void updateBaseData();
    QVector<QStringList> getData()const;
private:
    QJsonObject jsonObject;
    std::shared_ptr<QVector<QStringList>> m_data;
};

#endif // FILEREADER_H
