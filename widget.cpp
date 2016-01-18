//#include "syszuxpinyin.h"
//#include "syszuxim.h"
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
//    QWSInputMethod* im = new SyszuxIM;
//    QWSServer::setCurrentInputMethod(im);
    mycal = new cal2;
    mybirth = new birthdaymanager;
    mytodo = new todolist;

    leftbar = new QLabel;
    leftbar->setStyleSheet("background-color:black");
    leftbar->setFixedWidth(70);

    birthbtn = new ClickedLabel;
    birthbtn->setAlignment(Qt::AlignCenter);
    birthbtn->setPixmap(QPixmap(":/img/img/birth.png"));
    connect(birthbtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(showbirthmanager()));

    calbtn = new ClickedLabel;
    calbtn->setAlignment(Qt::AlignCenter);
    calbtn->setPixmap(QPixmap(":/img/img/cal.png"));
    connect(calbtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(showcalander()));

    todobtn = new ClickedLabel;
    todobtn->setPixmap(QPixmap(":/img/img/todo.png"));
    todobtn->setAlignment(Qt::AlignCenter);
    connect(todobtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(showtodolist()));

    QVBoxLayout *leftbarlayout = new QVBoxLayout(leftbar);
    leftbarlayout->addStretch();
    leftbarlayout->addWidget(todobtn);
    leftbarlayout->addSpacing(50);
    leftbarlayout->addWidget(calbtn);
    leftbarlayout->addSpacing(50);
    leftbarlayout->addWidget(birthbtn);
    leftbarlayout->addStretch();

    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    mainlayout->addWidget(leftbar);
    mainlayout->addWidget(mytodo);
    mainlayout->addWidget(mycal);
    mainlayout->addWidget(mybirth);
    mainlayout->setSpacing(0);
    mainlayout->setMargin(0);
    mybirth->hide();
    mytodo->hide();
    this->setFixedSize(800,480);
    gettempbirth(QDate::currentDate());
    gettemptodo(QDate::currentDate());

    connect(mycal,SIGNAL(caldaychange(QDate)),this,SLOT(showbirthincal(QDate)));
    connect(mycal,SIGNAL(calmonthchange(QDate)),this,SLOT(setcalBirthmark(QDate)));
    connect(mycal,SIGNAL(calyearchange(QDate)),this,SLOT(gettempbirth(QDate)));

    connect(mybirth,SIGNAL(birthneedtorefresh()),this,SLOT(regetbirth()));
    connect(mytodo,SIGNAL(todoneedfresh()),this,SLOT(regettodo()));
}

Widget::~Widget()
{
    
}

void Widget::showbirthmanager()
{
    mybirth->show();
    mytodo->hide();
    mycal->hide();
}

void Widget::showcalander()
{
    mycal->show();
    mytodo->hide();
    mybirth->hide();
}

void Widget::showtodolist()
{
    mytodo->show();
    mybirth->hide();
    mycal->hide();
}




bool Widget::gettempbirth(QDate date)
{
    tempbirth.clear();
    for(int i=0;i<mybirth->itemlist.count();i++)
    {
        birthdayclass birth = mybirth->item_birth_hash.value(mybirth->itemlist.at(i));
        QDate d;
        if(birth.islunarbirth) d=birth.getNextLunarbirth(date.year(),birth.lmonth,birth.lday,birth.isleaplunarmonth);
        else d = birth.getNextSolarbirth(date.year(),birth.smonth,birth.sday);
        if(d.year()==date.year())
            tempbirth.insert(d.toString("yyyy-M-d"),birth.name);
    }
    setcalBirthmark(date);
    return true;
}

bool Widget::setcalBirthmark(QDate date)
{
    QDate d(date.year(),date.month(),1);
    while(d.month()==date.month())
    {
        if(tempbirth.contains(d.toString("yyyy-M-d"))) mycal->showbirthmark(d);

        d = d.addDays(1);
    }

    showbirthincal(date);
    return true;
}

bool Widget::showbirthincal(QDate date)
{
    if(tempbirth.contains(date.toString("yyyy-M-d")))
    {
        mycal->todaylist->addItem(tempbirth.value(date.toString("yyyy-M-d"))+tr("的生日"));
        return true;
    }
    return false;
}


bool Widget::gettemptodo(QDate date)
{
    temptodo.clear();
    QDate temp(date.year(),date.month(),1);
    while(temp.month()==date.month())
    {

    for(int i=0;i<mytodo->olditemlist.count();i++)
    {
        QDomElement element = mytodo->domElementForItem.value(mytodo->olditemlist.at(i));
        QDate sd = QDate::fromString(element.attribute("startdate"),"yyyy-M-d");
        QDate ed = QDate::fromString(element.attribute("enddate"),"yyyy-M-d");
        if(sd<=temp && ed>=temp)
        {
            temptodo.insert(temp.toString("yyyy-M-d"),element.attribute("title"));
        }
    }
    for(int i=0;i<mytodo->workingitemlist.count();i++)
    {
        QDomElement element = mytodo->domElementForItem.value(mytodo->workingitemlist.at(i));
        QDate sd = QDate::fromString(element.attribute("startdate"),"yyyy-M-d");
        QDate ed = QDate::fromString(element.attribute("enddate"),"yyyy-M-d");
        if(sd<=temp && ed>=temp)
        {
            temptodo.insert(temp.toString("yyyy-M-d"),element.attribute("title"));
        }
    }
    for(int i=0;i<mytodo->comingitemlist.count();i++)
    {
        QDomElement element = mytodo->domElementForItem.value(mytodo->comingitemlist.at(i));
        QDate sd = QDate::fromString(element.attribute("startdate"),"yyyy-M-d");
        QDate ed = QDate::fromString(element.attribute("enddate"),"yyyy-M-d");
        if(sd<=temp && ed>=temp)
        {
            temptodo.insert(temp.toString("yyyy-M-d"),element.attribute("title"));
        }
    }
    temp = temp.addDays(1);
    }
    setcalTodomark(date);
    return true;
}

bool Widget::setcalTodomark(QDate date)
{

    QDate d(date.year(),date.month(),1);
    while(d.month()==date.month())
    {
        QString key = d.toString("yyyy-M-d");
        if(temptodo.contains(key))
            mycal->showtodomark(date);

        d = d.addDays(1);
    }

    showtodoincal(date);
    return true;
}


bool Widget::showtodoincal(QDate date)
{
    QString key = date.toString("yyyy-M-d");
    if(temptodo.contains(key))
    {
        mycal->todaylist->addItem(temptodo.value(key));
        return true;
    }
    return false;
}

void Widget::regetbirth()
{
    gettempbirth(mycal->cur_date);
}

void Widget::regettodo()
{
    gettemptodo(mycal->cur_date);
}
