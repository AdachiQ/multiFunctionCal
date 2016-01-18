#ifndef CAL2_H
#define CAL2_H

#include <QWidget>
#include "cal_label.h"
#include "clickedlabel.h"
#include <QDate>
#include <QListWidget>
#include <QDomDocument>
#include <QFile>
#include <QHash>
#include "chinesecalendar.h"
#include <QList>

struct SolarHolidayStruct
{
    int Month;
    int Day;
    QString HolidayName;
    SolarHolidayStruct(int month, int day, QString name)
    {
        Month = month;
        Day = day;
        HolidayName = name;
    }
    SolarHolidayStruct()
    {
        Month = Day = 0;
        HolidayName = "";
    }
};

struct LunarHolidayStruct
{
    int Month;
    int Day;
    QString HolidayName;

    LunarHolidayStruct(int month, int day, QString name)
    {
        Month = month;
        Day = day;
        HolidayName = name;
    }
    LunarHolidayStruct()
    {
        Month = Day = 0;
        HolidayName = "";
    }
};

struct WeekHolidayStruct
{
    int Month;
    int WeekAtMonth;
    int WeekDay;
    QString HolidayName;

    WeekHolidayStruct(int month, int weekAtMonth, int weekDay, QString name)
    {
        Month = month;
        WeekAtMonth = weekAtMonth;
        WeekDay = weekDay;
        HolidayName = name;
    }
    WeekHolidayStruct()
    {
        Month = WeekAtMonth = WeekDay = 0;
        HolidayName = "";
    }
};


class cal2 : public QWidget
{
    Q_OBJECT
    
public:
    cal2(QWidget *parent = 0);
    ~cal2();

    cal_label *labels[42];

    ClickedLabel *pre,*next,*month,*year,*today,pyear,nyear;
    QLabel *weeks[7];

    cal_label *cur_label;
    QDate cur_date;

    QListWidget *todaylist;
    QLabel *righttop;
    QLabel *righttop2;
    QDomDocument holidays;

    void initBasicData();

public slots:
    void preOnClicked();
    void nextOnClicked();
    void todayOnClicked();
    void newCal(QDate newdate = QDate::currentDate());
    void changeday(cal_label *cclabel);
    bool showbirthmark(QDate date);
    bool showtodomark(QDate date);
    //void pyearOnclicked();
    //void nyearOnclicked();
//    bool readholidays();
//    void showholidays();

public:
    QStringList constellationName;
    QStringList SolarTerm;
    QStringList ganStr;
    QStringList zhiStr;
    QStringList animalStr;
    QStringList nStr;
    QStringList monthstring;
    QStringList cnweekname;
    QStringList longEnweekname;

    QList<SolarHolidayStruct> sholidaylist;
    QList<LunarHolidayStruct> lholidaylist;
    QList<WeekHolidayStruct>  wholidaylist;
    QHash<cal_label*,SolarHolidayStruct> sholidayhash;
    QHash<cal_label*,LunarHolidayStruct> lholidayhash;
    QHash<cal_label*,WeekHolidayStruct>  wholidayhash;
    QHash<cal_label*,ChineseCalendar>  label_cal_hash;



signals:
    void caldaychange(QDate newdate);
    void calmonthchange(QDate newdate);
    void calyearchange(QDate newdate);

public:
    bool matchSolarHoliday(ChineseCalendar &cc,cal_label* lal);
    bool matchLunarHoliday(ChineseCalendar &cc,cal_label* lal);
    bool matchWeekHoliday(ChineseCalendar &cc ,cal_label* lal);

};

#endif // CAL2_H
