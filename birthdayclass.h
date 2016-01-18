//生日类，包含姓名、出生年月日等信息


#ifndef BIRTHDAYCLASS_H
#define BIRTHDAYCLASS_H
#include <QString>
#include <QDateTime>
#include "chinesecalendar.h"

class birthdayclass
{
public:
    birthdayclass();
//    birthdayclass(QString _name,int _syear,int _smonth,int _sday);
//    birthdayclass(QString _name,int _smonth, int _sday);
//    birthdayclass(QString _name, int _lyear, int _lmonth, int _lday, bool _leap);
//    birthdayclass(QString _name,int _lmonth, int _lday, bool _leap);

    bool setBirth(QString _name,int _syear,int _smonth,int _sday);
    bool setBirth(QString _name,int _smonth, int _sday);
    bool setBirth(QString _name, int _lyear, int _lmonth, int _lday, bool _leap);
    bool setBirth(QString _name,int _lmonth, int _lday, bool _leap);

    void setRemindtime(int days);
    QDate getNextSolarbirth(int year,int month,int day);
    QDate getNextLunarbirth(int year,int month,int day,bool isleaplunarmonth);
public:
    QString name;
    int star;
    int animal;

    bool islunarbirth;
    int lyear,lmonth,lday;
    bool isleaplunarmonth,hasyear;
    int syear,smonth,sday;
    QDateTime remindtime;
    QDate nextbirth;
    int daysto;
};


#endif // BIRTHDAYCLASS_H
