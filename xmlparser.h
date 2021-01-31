#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QWidget>
#include <QXmlSimpleReader>
#include <QFile>
#include <QString>
#include <QDir>
#include <QFileDialog>
#include <memory>
#include <QDebug>
#include <QList>
#include <QTableWidgetItem>
#include <set>
#include <vector>

#include <QMessageBox>

class XMLParser:public QXmlDefaultHandler
{
private:
       QString m_strText;

       QVector<QStringList> assoc;
       QStringList strList;
public:
    XMLParser();

    bool startElement(const QString &namespaceURI,
                      const QString &localName,
                      const QString &qName,
                      const QXmlAttributes &atts) override;

    bool characters(const QString &ch)override;

    bool endElement(const QString &namespaceURI,
                    const QString &localName,
                    const QString &qName)override;

    bool fatalError(const QXmlParseException &exception)override;

    const QVector<QStringList>& getAssoc();

    bool isEmpty();
    void clear_();


};

#endif // XMLPARSER_H
