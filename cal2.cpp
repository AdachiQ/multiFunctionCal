#include "cal2.h"
cal2::cal2(QWidget *parent)
    : QWidget(parent)
{

    initBasicData();
//--------------------------顶层--------------------------------------------------------------
    QFont font1;
    font1.setPixelSize(15);

    QPalette palette1;
    palette1.setColor(QPalette::WindowText,QColor(155,155,155,255));

    today = new ClickedLabel;
    today->setFont(font1);
    today->setPalette(palette1);
    today->setText(tr("Today"));
    connect(today,SIGNAL(clicked(ClickedLabel*)),this,SLOT(todayOnClicked()));

    pre = new ClickedLabel;
    pre->setFont(font1);
    pre->setPalette(palette1);
    pre->setText(tr("PRE"));
    connect(pre,SIGNAL(clicked(ClickedLabel*)),this,SLOT(preOnClicked()));

    next = new ClickedLabel;
    next->setFont(font1);
    next->setPalette(palette1);
    next->setText(tr("NEXT"));
    connect(next,SIGNAL(clicked(ClickedLabel*)),this,SLOT(nextOnClicked()));

    month = new ClickedLabel;
    month->setFont(font1);
    month->setPalette(palette1);

    year = new ClickedLabel;
    year->setFont(font1);
    year->setPalette(palette1);

    QHBoxLayout *toplayout = new QHBoxLayout;
    toplayout->addWidget(today);
    toplayout->addStretch();
    toplayout->addWidget(pre);
    toplayout->addSpacing(20);
    toplayout->addWidget(month);
    toplayout->addSpacing(5);
    toplayout->addWidget(year);
    toplayout->addSpacing(20);
    toplayout->addWidget(next);
    toplayout->addStretch();

//--------------------------顶层结束----------------------------------------------------------



//---------------------------星期---------------------------------------------------------------
    QString weekstr[7]={"MON","TUE","WED","THU","FRI","SAT","SUN"};
    QHBoxLayout* weeklayout = new QHBoxLayout;
    weeklayout->setSpacing(0);

    QFont font2;
    font2.setPixelSize(15);
    QPalette palette2;
    palette2.setColor(QPalette::WindowText,QColor(155,155,155,255));

    for(int i=0;i<7;i++)
    {
        QLabel* label = new QLabel(tr("%1").arg(weekstr[i]));
        label->setFont(font2);
        label->setPalette(palette2);
        label->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        label->setFixedHeight(20);
        weeklayout->addWidget(label);
    }


    QVBoxLayout *toplayout2 = new QVBoxLayout;
    toplayout2->addLayout(toplayout);
    toplayout2->addLayout(weeklayout);
    QWidget *topwidget = new QWidget;
    topwidget->setLayout(toplayout2);
    topwidget->setFixedHeight(70);
    topwidget->setAutoFillBackground(true);
    QPalette pet;
    pet.setColor(QPalette::Background,QColor(50,58,69));
    topwidget->setPalette(pet);
    topwidget->setFixedHeight(100);
    //topwidget->setStyleSheet("background-color: rgb(50,58,69)");

//---------------------------星期结束---------------------------------------------------------------



//----------------------------月历----------------------------------------------------------------
    QGridLayout* grid = new QGridLayout;
    grid->setSpacing(1);

    int row,col,num;
    for(row=0;row<6;row++)
        for(col=1;col<=7;col++)
        {
            num =row*7+col;
            labels[num] = new cal_label;

            QPalette lpa;
            lpa.setColor(QPalette::WindowText,QColor(200,200,200));
            labels[num]->lunarday->setPalette(lpa);
            connect(labels[num],SIGNAL(clicked(cal_label*)),this,SLOT(changeday(cal_label*)));
            grid->addWidget(labels[num],row,col-1);
        }

    QVBoxLayout* mainlayout = new QVBoxLayout();
    //mainlayout->setSpacing(0);
    mainlayout->addWidget(topwidget);
    mainlayout->addLayout(grid);


    QFont rtfont1;
    rtfont1.setPixelSize(30);
    righttop = new QLabel;
    righttop->setFont(rtfont1);
    righttop->setStyleSheet("color:white;background-color:rgb(20,185,214)");
    righttop->setFixedSize(360,100);
    //righttop->setAlignment(Qt::AlignCenter);
    righttop->setIndent(20);

    righttop2 = new QLabel;
    rtfont1.setPixelSize(20);
    righttop2->setFont(rtfont1);
    righttop2->setFixedHeight(100);
    righttop2->setStyleSheet("color:white;background-color:grey");
    righttop2->setAlignment(Qt::AlignCenter);
    //righttop2->setIndent(30);

    QVBoxLayout *rtlayout = new QVBoxLayout;
    rtlayout->addWidget(righttop);
    rtlayout->addWidget(righttop2);
    rtlayout->setSpacing(0);

//    QLabel *rtwidget = new QLabel;
//    rtwidget->setLayout(rtlayout);
//    rtwidget->setFixedHeight(200);
//    rtwidget->setStyleSheet("background-color:rgb(107,203,202)");
//    //rtwidget->setPalette(pet);

    todaylist = new QListWidget;
    QFont f1;
    f1.setPixelSize(20);
    todaylist->setFont(f1);
    //todaylist->setStyleSheet("background-color:rgb(24,34,144)");

    QVBoxLayout *right1 = new QVBoxLayout;
    right1->addLayout(rtlayout);
    right1->addWidget(todaylist);

    QHBoxLayout *lastlayout = new QHBoxLayout(this);
    lastlayout->setSpacing(1);
    lastlayout->addLayout(mainlayout);
    lastlayout->addLayout(right1);
    lastlayout->setMargin(0);

    newCal();

}

cal2::~cal2()
{
     //delete mycalendat;
}

void cal2::preOnClicked()
{
    newCal(cur_date.addMonths(-1));
    emit calmonthchange(cur_date);
}


void cal2::nextOnClicked()
{
    newCal(cur_date.addMonths(1));
    emit calmonthchange(cur_date);
}

void cal2::todayOnClicked()
{
    QDate temp = cur_date;
    newCal();
    if(temp.year()!=QDate::currentDate().year()) emit calyearchange(cur_date);
    else if(temp.month()!=QDate::currentDate().month()) emit calmonthchange(cur_date);
    else  emit caldaychange(cur_date);

}

void cal2::newCal(QDate newdate)
{

    sholidayhash.clear();
    wholidayhash.clear();
    lholidayhash.clear();
    label_cal_hash.clear();

    cur_date = newdate;

    year->setNum(cur_date.year());
    month->setText(QDate::shortMonthName(cur_date.month()));
    int i;
    for(i=1;i<=42;i++)
    {
        labels[i]->resetall();
        labels[i]->setEnabled(false);
    }


    QDate date(cur_date.year(),cur_date.month(),1);

    int firstday = date.dayOfWeek();
    while(date.month()==cur_date.month())
    {

        ChineseCalendar cncal(date);
        cal_label *templabe = labels[date.day()+firstday-1];
        label_cal_hash.insert(templabe,cncal);
        templabe->setEnabled(true);
        templabe->day->setNum(cncal._date.day());

        templabe->lunarday->setText( nStr[cncal._cDay] );
        if(cncal.sterm!=0)
           templabe->lunarday->setText( SolarTerm[cncal.sterm] );
        if(matchWeekHoliday(cncal,templabe))
        {
            templabe->lunarday->setText(wholidayhash.value(templabe).HolidayName);
            templabe->bholiday->show();
        }
        if(matchSolarHoliday(cncal,templabe))
        {
            templabe->lunarday->setText(sholidayhash.value(templabe).HolidayName);
            templabe->bholiday->show();
        }

        if(matchLunarHoliday(cncal,templabe))
        {
            templabe->lunarday->setText(lholidayhash.value(templabe).HolidayName);
            templabe->bholiday->show();
        }

        date = date.addDays(1);

    }


    cur_label = labels[cur_date.day()+firstday-1];

    changeday(cur_label);
}

void cal2::changeday(cal_label *cclabel)
{
    cur_label->setnormal();
    cclabel->setselect();
    cur_label = cclabel;
    ChineseCalendar temp = label_cal_hash.value(cclabel);
    cur_date = temp._date;
    righttop->setText(tr("%1\n%2-%3  %4").arg(cur_date.year()).arg(cur_date.month()).arg(cur_date.day()).arg(longEnweekname[cur_date.dayOfWeek()]));
    righttop2->setText(tr("%1%2%3年\n%4%5\n%6").arg(ganStr[temp.gan]).arg(zhiStr[temp.zhi]).arg(animalStr[temp.animal])
                       .arg(monthstring[temp._cMonth]).arg(nStr[temp._cDay]).arg(constellationName[temp.constellation]));

    todaylist->clear();
    if(sholidayhash.contains(cur_label)) todaylist->addItem(sholidayhash.value(cur_label).HolidayName);
    if(wholidayhash.contains(cur_label)) todaylist->addItem(wholidayhash.value(cur_label).HolidayName);
    if(lholidayhash.contains(cur_label)) todaylist->addItem(lholidayhash.value(cur_label).HolidayName);

    emit caldaychange(cur_date);
}

//bool cal2::readholidays()
//{
//    QFile file(tr("holidays.xml"));
//    if (!file.open(QFile::ReadOnly | QFile::Text)) {
//        QMessageBox::warning(this, tr("SAX Bookmarks"),
//                             tr("Cannot read file %1")
//                             .arg(file.errorString()));
//        return false;
//    }

//    QString errorStr;
//    int errorLine;
//    int errorColumn;

//    if (!holidays.setContent(&file, true, &errorStr, &errorLine,
//                             &errorColumn)) {
//        QMessageBox::information(window(), tr("DOM Bookmarks"),
//                                 tr("Parse error at line %1, column %2:\n%3")
//                                 .arg(errorLine)
//                                 .arg(errorColumn)
//                                 .arg(errorStr));
//        return false;
//    }
//    file.close();

//    QDomElement root = holidays.documentElement();
//    QDomElement child = root.firstChildElement();
//    while (!child.isNull()) {
//        m_holiday *temp1= new m_holiday;
//        temp1->htype = child.attribute("htype").toInt();
//        temp1->month = child.attribute("month").toInt();
//        temp1->day = child.attribute("day").toInt();
//        temp1->week = child.attribute("week").toInt();
//        temp1->weeknum = child.attribute("weeknum").toInt();
//        temp1->title = child.attribute("title");
//        holidaylist[temp1->month].append(temp1);
//        child = child.nextSiblingElement();
//    }
//}

//void cal2::showholidays()
//{

//    todaylist->clear();

//    if(holidaylist[cur_date.month()].isEmpty()) return;
//    QDate firstday(cur_date.year(),cur_date.month(),1);
//    QListIterator<m_holiday*> it(holidaylist[cur_date.month()]);
//    while(it.hasNext())
//    {
//        m_holiday* h = it.next();
//        if(h->htype == 1)
//        {

//            int n = h->week<firstday.dayOfWeek()?0:1;
//            labels[(h->weeknum-n)*7+h->week]->lunarday->setText(h->title);
//        }
//        else
//        {
//            labels[h->day+firstday.dayOfWeek()-1]->lunarday->setText(h->title);
//        }

//        todaylist->addItem(h->title);
//    }

//}

void cal2::initBasicData()
{

    cnweekname<<"未知"<<"周一"<<"周二"<<"周三"<<"周四"<<"周五"<<"周六"<<"周日";
    longEnweekname<<"unknown"<<"Monday"<<"Tuesday"<<"Wednesday"<<"Thursday"<<"Friday"<<"Saturday"<<"Sunday";

    //星座名称
    constellationName<<"未知"
                      <<"白羊座"<<"金牛座"<<"双子座"<<"巨蟹座"<<"狮子座"<<"处女座"
                      <<"天秤座"<<"天蝎座"<<"射手座"<<"摩羯座"<<"水瓶座"<<"双鱼座";
    //二十四节气
    SolarTerm<<"未知"
             <<"小寒"<<"大寒"<<"立春"<<"雨水"<<"惊蛰"<<"春分"
             <<"清明"<<"谷雨"<<"立夏"<<"小满"<<"芒种"<<"夏至"
             <<"小暑"<<"大暑"<<"立秋"<<"处暑"<<"白露"<<"秋分"
             <<"寒露"<<"霜降"<<"立冬"<<"小雪"<<"大雪"<<"冬至";
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

    sholidaylist
      <<SolarHolidayStruct(1, 1,"元旦")
      <<SolarHolidayStruct(2, 14,"情人节")
      <<SolarHolidayStruct(3, 8,"妇女节")
      <<SolarHolidayStruct(3, 12, "植树节")
      <<SolarHolidayStruct(3, 15,"消费者权益日")
      <<SolarHolidayStruct(4, 1,"愚人节")
      <<SolarHolidayStruct(5, 1,"劳动节")
      <<SolarHolidayStruct(5, 4,"青年节")
      <<SolarHolidayStruct(6, 1,"儿童节")
      <<SolarHolidayStruct(7, 1,"建党节")
      <<SolarHolidayStruct(8, 1,"建军节")
      <<SolarHolidayStruct(9, 10,"教师节")
      <<SolarHolidayStruct(10, 1, "国庆节")
      <<SolarHolidayStruct(12, 24,"平安夜")
      <<SolarHolidayStruct(12, 25,"圣诞节");

    lholidaylist
        <<LunarHolidayStruct(1, 1,"春节")
        <<LunarHolidayStruct(1, 15,"元宵节")
        <<LunarHolidayStruct(5, 5,"端午节")
        <<LunarHolidayStruct(7, 7,"七夕")
        <<LunarHolidayStruct(7, 15,"中元节")
        <<LunarHolidayStruct(8, 15,"中秋节")
        <<LunarHolidayStruct(9, 9,"重阳")
        <<LunarHolidayStruct(12, 8,"腊八节")
        <<LunarHolidayStruct(12, 23,"小年");
        //注意除夕需要其它方法进行计算,因为农历年最后一天可能是29号或30号

    wholidaylist
        <<WeekHolidayStruct(5, 2, 7, "母亲节")
        <<WeekHolidayStruct(6, 3, 7, "父亲节")
        <<WeekHolidayStruct(11, 4, 4, "感恩节");
}


bool cal2::matchSolarHoliday(ChineseCalendar &cc, cal_label *lal)
{
    for(int i=0;i<sholidaylist.count();i++)
     {
         if ((sholidaylist[i].Month == cc._date.month()) && (sholidaylist[i].Day == cc._date.day()))
         {
             sholidayhash.insert(lal,sholidaylist[i]);
             return true;
         }
     }
    return false;
}

bool cal2::matchLunarHoliday(ChineseCalendar &cc,cal_label* lal)
{
    if (cc._cIsLeapMonth == false) //闰月不计算节日
    {

        for(int i=0;i<lholidaylist.count();i++ )
        {
            if ((lholidaylist[i].Month == cc._cMonth) && (lholidaylist[i].Day == cc._cDay))
            {

                lholidayhash.insert(lal,lholidaylist[i]);
                return true;
            }
        }

        //对除夕进行特别处理
        if (cc._cMonth == 12)
        {
            int i = cc.GetChineseMonthDays(cc._cYear, 12); //计算当年农历12月的总天数
            if (cc._cDay == i) //如果为最后一天
            {
                LunarHolidayStruct temp(12,i,"除夕");
                lholidayhash.insert(lal,temp);
                return true;
            }
        }
    }
    return false;
}


bool cal2::matchWeekHoliday(ChineseCalendar &cc ,cal_label* lal)
{
    for(int i=0;i<wholidaylist.count();i++)
    {
       if(cc._date.month() == wholidaylist[i].Month)
        {
            QDate temp = label_cal_hash.value(lal)._date;
            int day_week = QDate(temp.year(),temp.month(),1).dayOfWeek();
            int n = wholidaylist[i].WeekDay<day_week?0:1;
            int day = (wholidaylist[i].WeekAtMonth-n)*7 + wholidaylist[i].WeekDay - day_week + 1;
            if(day == temp.day())
            {
               wholidayhash.insert(lal,wholidaylist[i]);
               return true;
            }
        }
    }
    return false;
}

bool cal2::showbirthmark(QDate date)
{
    if(date.year()!=cur_date.year() || date.month()!=cur_date.month()) return false;
    QDate firstday(date.year(),date.month(),1);
    labels[date.day()+firstday.dayOfWeek()-1]->bbirth->show();
    return true;
}

bool cal2::showtodomark(QDate date)
{
    if(date.year()!=cur_date.year() || date.month()!=cur_date.month()) return false;
    QDate firstday(date.year(),date.month(),1);
    labels[date.day()+firstday.dayOfWeek()-1]->btodo->show();
    return true;
}
