#include "xmlparser.h"

XMLParser::XMLParser()
{

}

bool XMLParser::startElement(const QString &,
                             const QString &,
                             const QString &qName,
                             const QXmlAttributes &atts)
{
    for (int i = 0; i < atts.count(); ++i) {
           if(atts.localName(i) == "number"){
               qDebug() << "Atts: "<<atts.value(i)<<"   q -> "<<qName;
           }
       }
    return true;
}

bool XMLParser::characters(const QString &ch)
{
    m_strText = ch;
    return true;
}

bool XMLParser::endElement(const QString &,
                           const QString &,
                           const QString &qName)
{

    if(qName != "note" && qName != "xml"){
         //  qDebug()<<"TagName: "<<qName<<"\t Text: "<<m_strText;
           strList<<m_strText;
        }
    else{
        if(!strList.empty())
        {
            assoc.push_back(strList);
            strList.clear();
        }
    }
    return true;
}

bool XMLParser::fatalError(const QXmlParseException &exception)
{
    qDebug() << "Line:"
    << exception.lineNumber()
    << ", Column:" << exception.columnNumber()
    << ", Message:" << exception.message();
    return false;
}

const QVector<QStringList>& XMLParser::getAssoc()
{
    if(!assoc.empty())
        return this->assoc;

    return QVector<QStringList>();
}

bool XMLParser::isEmpty()
{
    return (assoc.empty())?true:false;
}

void XMLParser::clear_()
{
    assoc.clear();
}
