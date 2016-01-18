#include <QApplication>
#include "widget.h"
//#include <QWSServer>
#include <QTextCodec>
//#include <QWSInputMethod>
//#include "syszuxpinyin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QTextCodec *codec = QTextCodec::codecForName("GB2312");

//    QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);
    Widget w;
    w.show();
    
    return a.exec();
}
