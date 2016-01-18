#include "cal_label.h"

cal_label::cal_label(QWidget *parent, int pixsize) :
    QLabel(parent)
{
    QFont font;

    font.setPixelSize(pixsize);
    day = new QLabel;
    day->setFont(font);
    day->setAlignment(Qt::AlignCenter);

    font.setPixelSize(pixsize-4);
    lunarday = new QLabel;
    lunarday->setFont(font);
    lunarday->setAlignment(Qt::AlignHCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(5);
    layout->addWidget(day);
    layout->addWidget(lunarday);
    this->setMinimumSize(60,50);


    int h = 7;
    bholiday = new QLabel;
    bholiday->setFont(font);
    bholiday->setStyleSheet("background-color:rgba(20,186,214,255)");
    bholiday->setFixedHeight(h);

    bbirth = new QLabel;
    bbirth->setFont(font);
    bbirth->setStyleSheet("background-color:rgba(242,121,53,255)");
    bbirth->setFixedHeight(h);

    btodo = new QLabel;
    btodo->setFont(font);
    btodo->setStyleSheet("background-color:rgba(31,187,166,255)");
    btodo->setFixedHeight(h);

    QHBoxLayout *blayout = new QHBoxLayout;
    blayout->addWidget(bholiday);
    blayout->addWidget(bbirth);
    blayout->addWidget(btodo);
    //blayout->setMargin(0);
    blayout->setSpacing(1);

    layout->addLayout(blayout);
    //layout->setSpacing(0);
    layout->setMargin(0);
}

void cal_label::mouseReleaseEvent(QMouseEvent *evt)
{
    emit clicked(this);
}

void cal_label::resetall()
{
    day->clear();
    lunarday->clear();
    bholiday->hide();
    bbirth->hide();
    btodo->hide();
    setnormal();
}

void cal_label::setnormal()
{
    day->setStyleSheet("color:black");
    lunarday->setStyleSheet("color:grey");
    this->setStyleSheet("background-color:rgb(237,237,229)");
}

void cal_label::setselect()
{
    day->setStyleSheet("color:white");
    lunarday->setStyleSheet("color:white");
    this->setStyleSheet("background-color:rgb(242,112,112)");
}
