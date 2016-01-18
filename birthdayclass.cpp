#include "birthdayclass.h"

birthdayclass::birthdayclass()
{
    name = "";
    islunarbirth = false;
    hasyear = false;
    isleaplunarmonth = false;
    lyear = lmonth = lday = 0;
    syear = smonth = sday = 0;
    animal = 0;
    star = 0;
}

bool birthdayclass::setBirth(QString _name,int _syear,int _smonth,int _sday)
{
    if(QDate(_syear,_smonth,_sday).isNull()) return false;
    if(!ChineseCalendar::CheckDateLimit(QDate(_syear,_smonth,_sday))) return false;

    ChineseCalendar::solarToLunar(QDate(_syear,_smonth,_sday),lyear,lmonth,lday,isleaplunarmonth);

    islunarbirth = false;
    hasyear = true;
    name = _name;
    syear = _syear;
    smonth = _smonth;
    sday = _sday;

    animal = ChineseCalendar::GetAnimal(syear);
    star = ChineseCalendar::GetConstellation(smonth,sday);
    //if(nextbirth.isNull()) return false;
    nextbirth = getNextSolarbirth(QDate::currentDate().year(),smonth,sday);
    daysto = QDate::currentDate().daysTo(nextbirth);
    return true;
}

bool birthdayclass::setBirth(QString _name, int _smonth, int _sday)
{
    islunarbirth = false;
    hasyear = false;
    name = _name;
    syear = 0;
    smonth = _smonth;
    sday = _sday;

    lyear = 0;
    animal = 0;
    star = ChineseCalendar::GetConstellation(smonth,sday);
    //if(nextbirth.isNull()) return false;
    nextbirth = getNextSolarbirth(QDate::currentDate().year(),smonth,sday);
    daysto = QDate::currentDate().daysTo(nextbirth);
    return true;

}

bool birthdayclass::setBirth(QString _name, int _lyear, int _lmonth, int _lday, bool _leap)
{
    if(!ChineseCalendar::CheckChineseDateLimit(_lyear,_lmonth,_lday,_leap))
    {
        return false;
    }

    islunarbirth = true;
    hasyear = true;

    name = _name;
    lyear = _lyear;
    lmonth = _lmonth;
    lday = _lday;
    isleaplunarmonth = _leap;

    QDate solarbirth = ChineseCalendar::lunarToSolar(lyear,lmonth,lday,isleaplunarmonth);

    syear = solarbirth.year();
    smonth = solarbirth.month();
    sday = solarbirth.day();

    animal = ChineseCalendar::GetAnimal(syear);
    star = ChineseCalendar::GetConstellation(smonth,sday);
    nextbirth = getNextLunarbirth(QDate::currentDate().year(),lmonth,lday,isleaplunarmonth);
     //if(nextbirth.isNull()) return false;
    daysto = QDate::currentDate().daysTo(nextbirth);
    return true;

}

bool birthdayclass::setBirth(QString _name, int _lmonth, int _lday, bool _leap)
{
    islunarbirth = true;
    hasyear = false;
    name = _name;
    lyear = 0;
    lmonth = _lmonth;
    lday = _lday;
    isleaplunarmonth = _leap;
    animal = 0;
    star = 0;
    syear = 0;

    nextbirth = getNextLunarbirth(QDate::currentDate().year(),lmonth,lday,isleaplunarmonth);
    // if(nextbirth.isNull()) return false;
    daysto = QDate::currentDate().daysTo(nextbirth);
    return true;
}

void birthdayclass::setRemindtime(int days)
{
    if(nextbirth.isValid())
    {
        remindtime.setDate(nextbirth.addDays(-days));
        remindtime.setTime(QTime(12,0,0));
    }
}

QDate birthdayclass::getNextSolarbirth(int year,int month,int day)
{
    QDate temp(year,month,day);
    if(temp.isValid() && QDate::currentDate().daysTo(temp)>=0) return temp;
    else return getNextSolarbirth(year +1,month,day);
}

QDate birthdayclass::getNextLunarbirth(int year, int month, int day, bool isleaplunarmonth)
{
    QDate temp = ChineseCalendar::lunarToSolar(year,month,day,isleaplunarmonth);
    if(temp.isValid())
    {
        if(temp>=QDate::currentDate()) return temp;
    }

    return ChineseCalendar::lunarToSolar(year+1,month,day,isleaplunarmonth);
}
