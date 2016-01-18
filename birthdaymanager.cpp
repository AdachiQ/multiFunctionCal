#include "birthdaymanager.h"
#include <QPropertyAnimation>
#include <QtGui>
#include <QMessageBox>

birthdaymanager::birthdaymanager(QWidget *parent)
    : QWidget(parent)
{
    QFont font;
    font.setPixelSize(50);

    //---------------------------列表---------------------------------------------------
    listlabel = new QLabel;
    //listlabel->setStyleSheet("background-color:blue");

    listlayout = new QVBoxLayout(listlabel);
    listscroll = new QScrollArea;
    listscroll->setWidget(listlabel);
    listscroll->setMinimumSize(340,470);
    listlabel->setMinimumSize(listscroll->size());
    listscroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listscroll->setStyleSheet("background-color:rgb(99,180,122)");
    listlayout->setMargin(0);
    listlayout->setSpacing(1);

//-------------------------------------列表结束--------------------------------------

    //---------------------------------详情---------------------------------------------
    name = new QLabel;
    name->setStyleSheet("color:white;background-color:black");
    name->setFont(font);
    name->setAlignment(Qt::AlignCenter);
    name->setFixedHeight(100);


    int indent = 60;
    lunarbirth = new QLabel;
    lunarbirth->setStyleSheet("color:white");
    font.setPixelSize(20);
    lunarbirth->setFont(font);
    lunarbirth->setAlignment(Qt::AlignLeft);
    lunarbirth->setIndent(indent);

    solarbirth = new QLabel;
    solarbirth->setStyleSheet("color:white");
    solarbirth->setFont(font);
    solarbirth->setAlignment(Qt::AlignLeft);
    solarbirth->setIndent(indent);

    animal = new QLabel;
    animal->setStyleSheet("color:white");
    animal->setFont(font);
    animal->setAlignment(Qt::AlignLeft);
    animal->setIndent(indent);

    star = new QLabel;
    star->setStyleSheet("color:white");
    star->setFont(font);
    star->setAlignment(Qt::AlignLeft);
    star->setIndent(indent);

    nextbirth = new QLabel;
    nextbirth ->setStyleSheet("color:white");
    //font.setPixelSize(25);
    nextbirth ->setFont(font);
    nextbirth ->setAlignment(Qt::AlignLeft);
    nextbirth->setIndent(indent);

    todays = new QLabel;
    todays->setStyleSheet("color:white");
    //font.setBold(true);
    todays ->setFont(font);
    todays ->setAlignment(Qt::AlignLeft);
    todays->setIndent(indent);

    addbtn = new ClickedLabel;
    addbtn->setPixmap(QPixmap(":/img/img/plus.png"));
    addbtn->setAlignment(Qt::AlignCenter);
    connect(addbtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(addBirth()));

    deletebtn = new ClickedLabel;
    deletebtn->setPixmap(QPixmap(":/img/img/trashcan.png"));
    deletebtn->setAlignment(Qt::AlignCenter);
    connect(deletebtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(delCurItem()));

    editbtn = new ClickedLabel;
    editbtn->setPixmap(QPixmap(":/img/img/pencil.png"));
    editbtn->setAlignment(Qt::AlignCenter);
    connect(editbtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(editbtnOnclicked()));

    QLabel *bottom = new QLabel;
    bottom->setStyleSheet("background-color:rgb(25,216,190)");
    bottom->setFixedHeight(50);

    QHBoxLayout *btnslayout = new QHBoxLayout(bottom);
    btnslayout->addWidget(deletebtn);
    btnslayout->addWidget(editbtn);
    btnslayout->addWidget(addbtn);
    btnslayout->setMargin(0);

    QVBoxLayout *infolayout = new QVBoxLayout;
    infolayout->addWidget(name);
    infolayout->addSpacing(50);
    infolayout->addWidget(lunarbirth);
    infolayout->addWidget(solarbirth);
    infolayout->addWidget(animal);
    infolayout->addWidget(star);
    infolayout->addSpacing(20);
    infolayout->addWidget(nextbirth);
    infolayout->addWidget(todays);
    infolayout->addStretch();
    infolayout->addWidget(bottom);
    infolayout->setMargin(0);

    infolabel = new QLabel;
    infolabel->setStyleSheet("background-color:rgb(31,186,165)");
    infolabel->setLayout(infolayout);
    infolabel->setFixedWidth(360);

    //------------------------------详情结束-------------------------------------


    //------------------------------编辑-----------------------------------
    editbg = new QLabel;
    editbg->setStyleSheet("background-color:rgb(152,87,77)");

    QHBoxLayout *inputlayout = new QHBoxLayout;
    ename = new QLabel;
    ename->setText(tr("姓名"));
    ename->setStyleSheet("color:white");
    ename->setFixedWidth(100);
    ename->setAlignment(Qt::AlignRight);
    QFont efont;
    efont.setPixelSize(40);
    ename->setFont(efont);

    enameline = new QLineEdit;
    enameline->setFont(efont);
    enameline->setStyleSheet("color:white;background-color:rgba(0,0,0,0)");
    enameline->setFixedWidth(150);

    inputlayout->addStretch();
    inputlayout->addWidget(ename);
    inputlayout->addSpacing(20);
    inputlayout->addWidget(enameline);
    inputlayout->addStretch();

    lunarbox = new QCheckBox;
    lunarbox->setText(tr("农历"));
    lunarbox->setStyleSheet("color:white");
    connect(lunarbox,SIGNAL(stateChanged(int)),this,SLOT(islunarchanged()));

    yearbox = new QCheckBox;
    yearbox->setText(tr("设置年份"));
    yearbox->setStyleSheet("color:white");
    yearbox->setChecked(true);
    connect(yearbox,SIGNAL(stateChanged(int)),this,SLOT(hasyearchanged()));

    QHBoxLayout *statelayout = new QHBoxLayout;
    statelayout->addStretch();
    statelayout->addWidget(lunarbox);
    statelayout->addSpacing(50);
    statelayout->addWidget(yearbox);
    statelayout->addStretch();


    QFont ymdfont;
    ymdfont.setPixelSize(25);
    yearspinbox = new QSpinBox;
    yearspinbox->setRange(1900,2050);
    yearspinbox->setMinimumSize(80,40);
    yearspinbox->setStyleSheet("color:white;background-color:grey");
    yearspinbox->setFont(ymdfont);
    yearspinbox->setFrame(false);
    connect(yearspinbox,SIGNAL(editingFinished()),this,SLOT(yearchanged()));

    monthcom = new QComboBox;
    monthcom->setMinimumSize(80,40);
    monthcom->setStyleSheet("color:white;background-color:grey");
    monthcom->setFont(ymdfont);
    monthcom->setFrame(false);
    connect(monthcom,SIGNAL(currentIndexChanged(int)),this,SLOT(monthchanged()));

    daycom = new QComboBox;
    daycom ->setMinimumSize(80,40);
    daycom ->setStyleSheet("color:white;background-color:grey");
    daycom ->setFont(ymdfont);
    daycom ->setFrame(false);

    QHBoxLayout *ymdlayout = new QHBoxLayout;
    ymdlayout->addStretch();
    ymdlayout->addWidget(yearspinbox);
    ymdlayout->addWidget(monthcom);
    ymdlayout->addWidget(daycom);
    ymdlayout->addStretch();


    QLabel *editbtnbg = new QLabel;
    editbtnbg->setStyleSheet("background-color:rgb(220,132,118)");
    editbtnbg->setFixedHeight(50);

    okbtn = new ClickedLabel;
    okbtn->setPixmap(QPixmap(":/img/img/checkmark.png"));
    okbtn->setAlignment(Qt::AlignCenter);
    connect(okbtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(okbtnOnclicked()));

    canclebtn = new ClickedLabel;
    canclebtn->setPixmap(QPixmap(":/img/img/exit.png"));
    canclebtn->setAlignment(Qt::AlignCenter);
    connect(canclebtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(canclebtnOnclicked()));

    QHBoxLayout *oclayout = new QHBoxLayout(editbtnbg);
    oclayout->addWidget(okbtn);
    oclayout->addWidget(canclebtn);


    QVBoxLayout *editbglayout = new QVBoxLayout(editbg);
    editbglayout->addStretch();
    editbglayout->addLayout(inputlayout);
    editbglayout->addLayout(statelayout);
    editbglayout->addLayout(ymdlayout);
    editbglayout->addStretch();
    editbglayout->addWidget(editbtnbg);
    editbglayout->setMargin(0);

    //-------------------------------编辑结束----------------------------

    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    mainlayout->addWidget(listscroll);
    mainlayout->addWidget(infolabel);
    mainlayout->addWidget(editbg);
    //editbg->setFixedWidth(0);
    //mainlayout->addLayout(infolayout);
    mainlayout->setSpacing(1);
    mainlayout->setMargin(0);

    //listwidget->setMaximumWidth(300);

    initBaseDate();
    readbirth();


}

birthdaymanager::~birthdaymanager()
{
    
}


bool birthdaymanager::readbirth()
{
    QFile file(QDir::currentPath()+"/xml/birthday.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("生日管家"),
                             tr("无法打开文件 %1")
                             .arg(file.errorString()));
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!dombirth.setContent(&file, true, &errorStr, &errorLine,
                             &errorColumn)) {
        QMessageBox::information(window(), tr("生日管家"),
                                 tr("错误信息:第%1行,第%2列:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
        return false;
    }
    file.close();

    QDomElement root = dombirth.documentElement();
    QDomElement child = root.firstChildElement();

    itemlist.clear();
    item_birth_hash.clear();
    item_dom_hash.clear();

    while (!child.isNull())
    {
       // QTreeWidgetItem *item = new QTreeWidgetItem(treewidget);
        birthitem *item = new birthitem;
        birthdayclass b;
        if(child.attribute("islunar")=="true")
       {
           int m = child.attribute("lmonth").toInt();
           int d = child.attribute("lday").toInt();
           bool leap = child.attribute("leap")=="true";
           if(child.attribute("hasyear")=="true")
           {
               int y = child.attribute("lyear").toInt(); 
               if(!b.setBirth(child.attribute("name"),y,m,d,leap)) continue;
           }
           else
           {
               if(!b.setBirth(child.attribute("name"),m,d,leap)) continue;
           }
       }
       else
       {
           int m = child.attribute("smonth").toInt();
           int d = child.attribute("sday").toInt();
           if(child.attribute("hasyear")=="true")
           {
               int y = child.attribute("syear").toInt();
               if(!b.setBirth(child.attribute("name"),y,m,d))continue;
           }
           else
           {
               if(!b.setBirth(child.attribute("name"),m,d))continue;
           }
       }

        item->daysnum = b.daysto;
       additemtolist(item);
       item_dom_hash.insert(item,child);
       item_birth_hash.insert(item,b);

       item->name->setText(b.name);
       item->nextbirth->setText(b.nextbirth.toString("yyyy-MM-dd"));
       if(b.daysto==0) item->days->setText(tr("今天"));
       else item->days->setText(tr("还有%1天").arg(b.daysto));

       connect(item,SIGNAL(clicked(birthitem*)),this,SLOT(showdetail(birthitem*)));
       child = child.nextSiblingElement();
    }

    for(int i=0;i<itemlist.count();i++)
        listlayout->addWidget(itemlist.at(i));

    resizelistlabel();
    if(itemlist.isEmpty()) cur_item = NULL;
    else cur_item = itemlist.first();
    showdetail(cur_item);
    emit birthneedtorefresh();
    return true;
}

void birthdaymanager::initBaseDate()
{
    cnweekname<<"未知"<<"周一"<<"周二"<<"周三"<<"周四"<<"周五"<<"周六"<<"周日";

    //星座名称
    constellationName<<"未知"
                      <<"白羊座"<<"金牛座"<<"双子座"<<"巨蟹座"<<"狮子座"<<"处女座"
                      <<"天秤座"<<"天蝎座"<<"射手座"<<"摩羯座"<<"水瓶座"<<"双鱼座";
    //天干
    ganStr<<"未知"<<"甲"<<"乙"<<"丙"<<"丁"<<"戊"<<"己"<<"庚"<<"辛"<<"壬"<<"癸";
    //地支
    zhiStr<<"未知"<<"子"<<"丑"<<"寅"<<"卯"<<"辰"<<"巳"<<"午"<<"未"<<"申"<<"酉"<<"戌"<<"亥";
    //生肖
    animalStr<<"未知"<<"鼠"<<"牛"<<"虎"<<"兔"<<"龙"<<"蛇"<<"马"<<"羊"<<"猴"<<"鸡"<<"狗"<<"猪";

    //农历日文字
    nStr<<"未知"
        <<"初一"<<"初二"<<"初三"<<"初四"<<"初五"<<"初六"<<"初七"<<"初八"<<"初九"<<"初十"
        <<"十一"<<"十二"<<"十三"<<"十四"<<"十五"<<"十六"<<"十七"<<"十八"<<"十九"<<"廿十"
        <<"廿一"<<"廿二"<<"廿三"<<"廿四"<<"廿五"<<"廿六"<<"廿七"<<"廿八"<<"廿九"<<"三十";
    //农历月文字
    monthstring<<"未知"
               <<"正月"<<"二月"<<"三月"<<"四月"<<"五月"<<"六月"
               <<"七月"<<"八月"<<"九月"<<"十月"<<"冬月"<<"腊月";

    monthComStr<<"1月"<<"2月"<<"3月"<<"4月"<<"5月"<<"6月"
               <<"7月"<<"8月"<<"9月"<<"10月"<<"11月"<<"12月";
    monthint<<1<<2<<3<<4<<5<<6<<7<<8<<9<<10<<11<<12;
    solarmonthdays<<31<<28<<31<<30<<31<<30<<31<<31<<30<<31<<30<<31;

}



void birthdaymanager::showdetail(birthitem *item)
{

    if(!item) return;
    cur_item->setnormal();
    cur_item = item;
    cur_item->setselect();
    birthdayclass b = item_birth_hash.value(item);
    name->setText(b.name);
    star->setText(tr("<strong>星座:</strong>%1").arg(constellationName[b.star]));
    animal->setText(tr("<strong>生肖:</strong>%1").arg(animalStr[b.animal]));
    if(!b.hasyear)
    {
        if(b.islunarbirth)
        {
            lunarbirth->show();
            solarbirth->hide();
            if(b.isleaplunarmonth)
                lunarbirth->setText(tr("<strong>农历生日</strong>:闰%1%2").arg(monthstring[b.lmonth])
                                                       .arg(nStr[b.lday]));
            else
                lunarbirth->setText(tr("<strong>农历生日</strong>:%1%2").arg(monthstring[b.lmonth])
                                                       .arg(nStr[b.lday]));

        }
        else
        {
            lunarbirth->hide();
            solarbirth->show();
            solarbirth->setText(tr("<strong>公历生日</strong>:%1-%2").arg(b.smonth).arg(b.sday));
        }
    }
    else
    {
        if(b.isleaplunarmonth)
            lunarbirth->setText(tr("<strong>农历生日</strong>:%1年闰%2%3").arg(b.lyear)
                                                   .arg(monthstring[b.lmonth])
                                                   .arg(nStr[b.lday]));
        else
            lunarbirth->setText(tr("<strong>农历生日</strong>:%1年%2%3").arg(b.lyear)
                                                   .arg(monthstring[b.lmonth])
                                                   .arg(nStr[b.lday]));
        solarbirth->setText(tr("<strong>公历生日</strong>:%1-%2-%3").arg(b.syear).arg(b.smonth).arg(b.sday));
    }
    nextbirth->setText(tr("<strong>下个生日</strong>:%1").arg(b.nextbirth.toString("yyyy-MM-dd")));

    if(b.daysto==0)
    {
        todays->setText(tr("<strong>今天！</strong>"));
    }
    else
    {
        todays->setText(tr("<strong>还有</strong>:%1天").arg(b.daysto));
    }

}

void birthdaymanager::additemtolist(birthitem *item)
{
    //if(itemlist.isEmpty()) itemlist.append(item);
    for(int i=0;i<itemlist.count();i++)
    {
        if(item->daysnum<=itemlist.at(i)->daysnum)
        {
            itemlist.insert(i,item);
            return;
        }
    }
    itemlist.append(item);
}

void birthdaymanager::delCurItem()
{
    if(cur_item)
    {
        QDomElement element = item_dom_hash.value(cur_item);
        item_dom_hash.remove(cur_item);
        dombirth.documentElement().removeChild(element);
        write();

        item_birth_hash.remove(cur_item);

        listlayout->removeWidget(cur_item);
        itemlist.removeOne(cur_item);
        delete cur_item;
        if(itemlist.isEmpty()) cur_item = NULL;
        else cur_item = itemlist.first();
        showdetail(cur_item);
        resizelistlabel();
        emit birthneedtorefresh();
    }
}

void birthdaymanager::write()
{
    QFile file(QDir::currentPath()+"/xml/birthday.xml");
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return;
    }
    QTextStream out(&file);
    dombirth.save(out, 4);
}

bool birthdaymanager::addBirth()
{
//    QPropertyAnimation pa(infolabel,"size");
//    pa.setEndValue(QSize(0,400));

//    QPropertyAnimation pb(editbg,"size");
//    pb.setEndValue(QSize(300,400));

//    pa.setDuration(200);
//    pb.setDuration(200);
//    pa.start();
//    pb.start();
    disconnect(yearbox,SIGNAL(stateChanged(int)),this,SLOT(hasyearchanged()));
    disconnect(lunarbox,SIGNAL(stateChanged(int)),this,SLOT(islunarchanged()));
    infolabel->hide();
    editbg->show();
    listscroll->hide();
    enameline->clear();
    lunarbox->setChecked(false);
    yearbox->setChecked(true);
    yearspinbox->setValue(QDate::currentDate().year());
    yearchanged();
    connect(yearbox,SIGNAL(stateChanged(int)),this,SLOT(hasyearchanged()));
    connect(lunarbox,SIGNAL(stateChanged(int)),this,SLOT(islunarchanged()));
    editing = false;
    return true;

}

void birthdaymanager::canclebtnOnclicked()
{
    infolabel->show();
    editbg->hide();
    listscroll->show();
}

void birthdaymanager::okbtnOnclicked()
{
    if(enameline->text()=="")return;

    birthdayclass b;
    if(lunarbox->checkState()==Qt::Checked)
    {
        int m = monthint.at(monthcom->currentIndex());
        bool leap;
        if(m<0)
        {
            m = -m;
            leap = true;
        }
        else leap = false;

        if(yearbox->checkState()==Qt::Checked)
        {
            b.setBirth(enameline->text(),yearspinbox->value(),m,daycom->currentIndex()+1,leap);
        }
        else
        {
            b.setBirth(enameline->text(),m,daycom->currentIndex()+1,leap);
        }
    }
    else
    {
        if(yearbox->checkState()==Qt::Checked)
            b.setBirth(enameline->text(),yearspinbox->value(),
                       monthcom->currentIndex()+1,daycom->currentIndex()+1);
        else
            b.setBirth(enameline->text(),monthcom->currentIndex()+1,daycom->currentIndex()+1);
    }

    QDomElement element = dombirth.createElement("birthday");
    element.setAttribute("hasyear",b.hasyear?"true":"false");
    element.setAttribute("islunar",b.islunarbirth?"true":"false");
    element.setAttribute("leap",b.isleaplunarmonth?"true":"false");
    element.setAttribute("name",b.name);
    element.setAttribute("syear",b.syear);
    element.setAttribute("smonth",b.smonth);
    element.setAttribute("sday",b.sday);
    element.setAttribute("lyear",b.lyear);
    element.setAttribute("lmonth",b.lmonth);
    element.setAttribute("lday",b.lday);

    if(editing && cur_item)
    {
        item_birth_hash.remove(cur_item);
        item_birth_hash.insert(cur_item,b);

        itemlist.removeOne(cur_item);
        additemtolist(cur_item);

        QDomElement t = item_dom_hash.take(cur_item);
        item_dom_hash.insert(cur_item,element);
        dombirth.documentElement().replaceChild(element,t);
        freshitem(cur_item,b);
        showdetail(cur_item);
    }
    else
    {
        birthitem *newitem = new birthitem;
        freshitem(newitem,b);

        item_birth_hash.insert(newitem,b);
        item_dom_hash.insert(newitem,element);
        dombirth.documentElement().appendChild(element);
        additemtolist(newitem);
        connect(newitem,SIGNAL(clicked(birthitem*)),this,SLOT(showdetail(birthitem*)));
        cur_item = newitem;

        showdetail(cur_item);

    }


    for(int i=0;i<itemlist.count();i++)
        listlayout->removeWidget(itemlist[i]);
    for(int i=0;i<itemlist.count();i++)
        listlayout->addWidget(itemlist[i]);


    resizelistlabel();
    editbg->hide();
    infolabel->show();
    listscroll->show();


    write();
    emit birthneedtorefresh();
}

void birthdaymanager::yearchanged()
{
    if(yearspinbox->value()<1900 || yearspinbox->value()>2050) return;
    monthint.clear();
    monthint<<1<<2<<3<<4<<5<<6<<7<<8<<9<<10<<11<<12;
    monthComStr.clear();

    if(lunarbox->checkState()==Qt::Checked)
    {

        if(yearbox->checkState()==Qt::Checked)
        {

            monthComStr<<"正月"<<"二月"<<"三月"<<"四月"<<"五月"<<"六月"
                         <<"七月"<<"八月"<<"九月"<<"十月"<<"冬月"<<"腊月";

            int i = ChineseCalendar::GetChineseLeapMonth(yearspinbox->value());
            if(i!=0)
            {

                monthint.insert(i,-i);
                QString str = tr("闰") + monthComStr[i-1];
                monthComStr.insert(i,str);
            }

        }
        else
        {
            monthint.clear();
            monthint<<1<<-1<<2<<-2<<3<<-3<<4<<-4<<5<<-5<<6<<-6
                   <<7<<-7<<8<<-8<<9<<-9<<10<<-10<<11<<-11<<12<<-12;
            monthComStr<<"正月"<<"闰正月"<<"二月"<<"闰二月"<<"三月"<<"闰三月"
                      <<"四月"<<"闰四月"<<"五月"<<"闰五月"<<"六月"<<"闰六月"
                      <<"七月"<<"闰七月"<<"八月"<<"闰八月"<<"九月"<<"闰九月"
                      <<"十月"<<"闰十月"<<"冬月"<<"闰冬月"<<"腊月"<<"闰腊月";
        }
    }
    else
    {
        monthComStr<<"1月"<<"2月"<<"3月"<<"4月"<<"5月"<<"6月"<<"7月"<<"8月"<<"9月"<<"10月"<<"11月"<<"12月";
    }
    monthcom->clear();
    monthcom->addItems(monthComStr);
}


void birthdaymanager::monthchanged()
{
    int month = monthcom->currentIndex();
    if(month==-1)return;
    daycomStr.clear();

    if(lunarbox->checkState()==Qt::Checked)
    {
        if(yearbox->checkState()==Qt::Checked)
        {
            if(monthint.at(month)<0)
               dayint = ChineseCalendar::GetChineseLeapMonthDays(yearspinbox->value());
            else dayint = ChineseCalendar::GetChineseMonthDays(yearspinbox->value(),month+1);
        }
        else dayint = 30;
        for(int i=1;i<=dayint;i++)
        {
            daycomStr.append(nStr[i]);
        }
    }

    else
    {

        if(yearbox->checkState()==Qt::Checked)
            dayint = QDate::isLeapYear(yearspinbox->value())?29:28;
        else dayint = 29;
        for(int i=1;i<=dayint;i++)
            daycomStr.append(QString::number(i));

    }
    daycom->clear();
    daycom->addItems(daycomStr);
}



void birthdaymanager::hasyearchanged()
{
    if(yearbox->checkState()==Qt::Checked)
    {
        yearspinbox->setEnabled(true);
    }
    else
    {
        yearspinbox->setEnabled(false);
    }
    yearchanged();

}

void birthdaymanager::islunarchanged()
{
    yearchanged();
}

void birthdaymanager::freshitem(birthitem *item, birthdayclass &birth)
{
    if(item)
    {
        item->name->setText(birth.name);
        item->nextbirth->setText(birth.nextbirth.toString("yyyy-MM-dd"));
        item->daysnum = birth.daysto;
        if(item->daysnum==0) item->days->setText(tr("今天"));
        else item->days->setText(tr("还有：%1天").arg(item->daysnum));
    }
}

void birthdaymanager::editbtnOnclicked()
{
    if(cur_item)
    {
        editing = true;

        birthdayclass b = item_birth_hash.value(cur_item);
        enameline->setText(b.name);
        lunarbox->setChecked(b.islunarbirth);
        yearbox->setChecked(b.hasyear);
        infolabel->hide();
        editbg->show();
        listscroll->hide();
    }
}

void birthdaymanager::resizelistlabel()
{
    listlabel->setFixedSize(listscroll->width(),listlayout->count()*101);
}
