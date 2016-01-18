#ifndef CHINESECALENDAR_H
#define CHINESECALENDAR_H

#include <QString>
#include <QStringList>
#include <QDate>
#include <QDateTime>

class ChineseCalendar
{
public:
    ChineseCalendar(QDate dt= QDate::currentDate());//用公历日期初始化
    ChineseCalendar(int cy, int cm, int cd, bool leapMonthFlag);//用农历日期初始化

    static int GetConstellation(int month, int day); //星座
    static int GetAnimal(int year); //属相
    static int Getgan(int year);
    static int Getzhi(int year);
    static QDate lunarToSolar(int year, int month, int day, bool leapMonthFlag);
    static bool solarToLunar(QDate dt, int &lyear, int &lmonth, int &lday, bool &isleapmonth);

public:
    QDate _date;

    int _cYear;  //农历年
    int _cMonth; //农历月份
    int _cDay; //农历当月第几天

    int sterm; //节气
    int animal; //生肖
    int gan;   //天干
    int zhi;   //地支
    int constellation; //星座

    bool _cIsLeapMonth; //当月是否闰月
    bool _cIsLeapYear; //当年是否有闰月

public:
    static bool CheckDateLimit(QDate dt);
    static int GetChineseYearDays(int year);
    static int GetChineseLeapMonthDays(int year);
    static int GetChineseLeapMonth(int year);
    static int GetChineseMonthDays(int year, int month);
    static bool BitTest32(int num, int bitpostion);
    static bool CheckChineseDateLimit(int year, int month, int day, bool leapMonth);

    void otherInfo();

    int ChineseTwentyFourDay();


};




#endif // CHINESECALENDAR_H
