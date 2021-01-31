#include "widget.h"
#include <QApplication>
#include "filereader.h"
#include "xmlparser.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
/*
    QFile file_("/home/linux/Documents/TextPars/cd.xml");

    XMLParser handler;
    QXmlInputSource source(&file_);
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.parse(source);

*/
    w.show();

    return a.exec();
}
