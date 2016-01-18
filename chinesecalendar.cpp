#include "chinesecalendar.h"


//基本常量
static int MinYear = 1900;
static int MaxYear = 2050;
static QDate MinDay(1900, 1, 30);
static QDate MaxDay(2049, 12, 31);
static int GanZhiStartYear = 1864; //干支计算起始年
static QDate GanZhiStartDay(1899, 12, 22);//起始日
static int AnimalStartYear = 1900; //1900年为鼠年

//阴历数据结构如下，共使用17位数据
// 第17位：表示闰月天数，0表示29天   1表示30天
// 第16位-第5位（共12位）表示12个月，其中第16位表示第一月，如果该月为30天则为1，29天为0
// 第4位-第1位（共4位）表示闰月是哪个月，如果当年没有闰月，则置0
static int LunarDateArray[] = {
    0x04BD8,0x04AE0,0x0A570,0x054D5,0x0D260,0x0D950,0x16554,0x056A0,0x09AD0,0x055D2,
    0x04AE0,0x0A5B6,0x0A4D0,0x0D250,0x1D255,0x0B540,0x0D6A0,0x0ADA2,0x095B0,0x14977,
    0x04970,0x0A4B0,0x0B4B5,0x06A50,0x06D40,0x1AB54,0x02B60,0x09570,0x052F2,0x04970,
    0x06566,0x0D4A0,0x0EA50,0x06E95,0x05AD0,0x02B60,0x186E3,0x092E0,0x1C8D7,0x0C950,
    0x0D4A0,0x1D8A6,0x0B550,0x056A0,0x1A5B4,0x025D0,0x092D0,0x0D2B2,0x0A950,0x0B557,
    0x06CA0,0x0B550,0x15355,0x04DA0,0x0A5B0,0x14573,0x052B0,0x0A9A8,0x0E950,0x06AA0,
    0x0AEA6,0x0AB50,0x04B60,0x0AAE4,0x0A570,0x05260,0x0F263,0x0D950,0x05B57,0x056A0,
    0x096D0,0x04DD5,0x04AD0,0x0A4D0,0x0D4D4,0x0D250,0x0D558,0x0B540,0x0B6A0,0x195A6,
    0x095B0,0x049B0,0x0A974,0x0A4B0,0x0B27A,0x06A50,0x06D40,0x0AF46,0x0AB60,0x09570,
    0x04AF5,0x04970,0x064B0,0x074A3,0x0EA50,0x06B58,0x055C0,0x0AB60,0x096D5,0x092E0,
    0x0C960,0x0D954,0x0D4A0,0x0DA50,0x07552,0x056A0,0x0ABB7,0x025D0,0x092D0,0x0CAB5,
    0x0A950,0x0B4A0,0x0BAA4,0x0AD50,0x055D9,0x04BA0,0x0A5B0,0x15176,0x052B0,0x0A930,
    0x07954,0x06AA0,0x0AD50,0x05B52,0x04B60,0x0A6E6,0x0A4E0,0x0D260,0x0EA65,0x0D530,
    0x05AA0,0x076A3,0x096D0,0x04BD7,0x04AD0,0x0A4D0,0x1D0B6,0x0D250,0x0D520,0x0DD45,
    0x0B5A0,0x056D0,0x055B2,0x049B0,0x0A577,0x0A4B0,0x0AA50,0x1B255,0x06D20,0x0ADA0,
    0x14B63};

ChineseCalendar::ChineseCalendar(QDate dt)
{

    int i;
    int leap;
    int temp;
    int offset;

    //CheckDateLimit(dt);

    _date = dt;

    //农历日期计算部分
    leap = 0;
    temp = 0;

    offset = MinDay.daysTo(_date);

    for (i = MinYear; i <= MaxYear; i++)
    {
        temp = GetChineseYearDays(i);  //求当年农历年天数
        if (offset - temp < 1)
            break;
        else
        {
            offset = offset - temp;
        }
    }
    _cYear = i;


    leap = GetChineseLeapMonth(_cYear);//计算该年闰哪个月
    //设定当年是否有闰月
    if (leap > 0)
    {
        _cIsLeapYear = true;
    }
    else
    {
        _cIsLeapYear = false;
    }


    _cIsLeapMonth = false;
    for (i = 1; i <= 12; i++)
    {
        //闰月
        if ((leap > 0) && (i == leap + 1) && (_cIsLeapMonth == false))
        {
            _cIsLeapMonth = true;
            i = i - 1;
            temp = GetChineseLeapMonthDays(_cYear); //计算闰月天数
        }
        else
        {
            _cIsLeapMonth = false;
            temp = GetChineseMonthDays(_cYear, i);//计算非闰月天数
        }

        offset = offset - temp;
        if (offset <= 0) break;
    }

    offset = offset + temp;
    _cMonth = i;
    _cDay = offset;

    otherInfo();
}


ChineseCalendar::ChineseCalendar(int cy, int cm, int cd, bool leapMonthFlag)
{
    int i, leap, Temp, offset;

    //CheckChineseDateLimit(cy, cm, cd, leapMonthFlag);

    _cYear = cy;
    _cMonth = cm;
    _cDay = cd;

    offset = 0;

    for (i = MinYear; i < cy; i++)
    {
        Temp = GetChineseYearDays(i); //求当年农历年天数
        offset = offset + Temp;
    }

    leap = GetChineseLeapMonth(cy);// 计算该年应该闰哪个月
    if (leap != 0)
    {
        _cIsLeapYear = true;
    }
    else
    {
        _cIsLeapYear = false;
    }


    if (cm != leap)
    {
        _cIsLeapMonth = false;  //当前日期并非闰月
    }
    else
    {
        _cIsLeapMonth = leapMonthFlag;  //使用用户输入的是否闰月月份
    }


    if ((_cIsLeapYear == false) || //当年没有闰月
            (cm < leap)) //计算月份小于闰月
    {

        for (i = 1; i < cm; i++)
        {
            Temp = GetChineseMonthDays(cy, i);//计算非闰月天数
            offset = offset + Temp;
        }

        //检查日期是否大于最大天
        if (cd > GetChineseMonthDays(cy, cm))
        {
            //QMessageBox::warning(this,tr("错误"),tr("非法农历日期"));
        }
        offset = offset + cd; //加上当月的天数

    }
    else   //是闰年，且计算月份大于或等于闰月
    {

        for (i = 1; i < cm; i++)
        {
            Temp = GetChineseMonthDays(cy, i); //计算非闰月天数
            offset = offset + Temp;
        }

        if (cm > leap) //计算月大于闰月
        {
            Temp = GetChineseLeapMonthDays(cy);   //计算闰月天数
            offset = offset + Temp;               //加上闰月天数

            if (cd > GetChineseMonthDays(cy, cm))
            {
                //QMessageBox::warning(this,tr("错误"),tr("非法农历日期"));
            }
            offset = offset + cd;
        }
        else  //计算月等于闰月
        {
            //如果需要计算的是闰月，则应首先加上与闰月对应的普通月的天数
            if (_cIsLeapMonth == true) //计算月为闰月
            {
                Temp = GetChineseMonthDays(cy, cm); //计算非闰月天数
                offset = offset + Temp;
            }

            if (cd > GetChineseLeapMonthDays(cy))
            {
                //QMessageBox::warning(this,tr("错误"),tr("非法农历日期"));
            }
            offset = offset + cd;
        }
    }

    _date = MinDay.addDays(offset);

    otherInfo();

}

bool ChineseCalendar::CheckDateLimit(QDate dt)
{
    if ((dt < MinDay) || (dt > MaxDay))
    {
        return false;
    }
    return true;
}

int ChineseCalendar::GetChineseYearDays(int year)
{
    int i, f, sumDay, info;

    sumDay = 348; //29天 X 12个月
    i = 0x8000;
    info = LunarDateArray[year - MinYear] & 0x0FFFF;
    //0x04BD8  & 0x0FFFF 中间12位，即4BD，每位代表一个月，为1则为大月，为0则为小月
    //计算12个月中有多少天为30天
    for (int m = 0; m < 12; m++)
    {
        f = info & i; // 0x04BD8  & 0x0FFFF  & 0x8000[1000 0000 0000 0000]
        if (f != 0)
        {
            sumDay++;
        }
        i = i >> 1;
    }
    return sumDay + GetChineseLeapMonthDays(year);
}


//传回农历 y年闰月的天数
int ChineseCalendar::GetChineseLeapMonthDays(int year)
{
    if (GetChineseLeapMonth(year) != 0)
    {
        //前4位，即0在这一年是润年时才有意义，它代表这年润月的大小月。
        if ((LunarDateArray[year - MinYear] & 0x10000) != 0)
        {   //为1则润大月
            return 30;
        }
        else
        {   //为0则闰小月
            return 29;
        }
    }
    else
    {
        return 0;
    }
}


//传回农历 y年闰哪个月 1-12 , 没闰传回 0
int ChineseCalendar::GetChineseLeapMonth(int year)
{
    //最后4位，即8，代表这一年的润月月份，为0则不润。首4位要与末4位搭配使用
    return LunarDateArray[year - MinYear] & 0xF;
}


//传回农历 y年m月的总天数
int ChineseCalendar::GetChineseMonthDays(int year, int month)
{   //0X0FFFF[0000 {1111 1111 1111} 1111]
    if (BitTest32((LunarDateArray[year - MinYear] & 0x0000FFFF), (16 - month)))
    {
        return 30;
    }
    else
    {
        return 29;
    }
}


// 测试某位是否为真
bool ChineseCalendar::BitTest32(int num, int bitpostion)
{

    if ((bitpostion > 31) || (bitpostion < 0))
        //throw;
        return false;

    int bit = 1 << bitpostion;

    if ((num & bit) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


bool ChineseCalendar::CheckChineseDateLimit(int year, int month, int day, bool leapMonth)
{
    if ((year < MinYear) || (year > MaxYear))
    {
        //QMessageBox::warning(this,tr("错误"),tr("超出可转换的日期"));
        return false;

    }
    if ((month < 1) || (month > 12))
    {
        //QMessageBox::warning(this,tr("错误"),tr("非法农历日期"));
        return false;
    }
    if ((day < 1) || (day > 30)) //中国的月最多30天
    {
        //QMessageBox::warning(this,tr("错误"),tr("非法农历日期"));
        return false;
    }

    int leap = GetChineseLeapMonth(year);// 计算该年应该闰哪个月
    if ((leapMonth == true) && (month != leap))
    {
        //QMessageBox::warning(this,tr("错误"),tr("非法农历日期"));
        return false;
    }
    return true;
}


int ChineseCalendar::ChineseTwentyFourDay() //返回节气
{

    return 0;
}


//返回星座
int ChineseCalendar::GetConstellation(int month,int day)
{
    //2012年是闰年
    QDate mojie(2012,1,19); //摩羯座终止日10
    QDate shuiping(2012,2,18); //水瓶座终止日11
    QDate shuangyu(2012,3,20); //双鱼12
    QDate baiyang(2012,4,19); //白羊1
    QDate jinniu(2012,5,20); //金牛2
    QDate shuangzi(2012,6,21); //双子3
    QDate juxie(2012,7,22); //巨蟹4
    QDate shizi(2012,8,22); //狮子5
    QDate chunv(2012,9,22); //处女6
    QDate tiancheng(2012,10,23); //天秤7
    QDate tianxie(2012,11,22); //天蝎8
    QDate sheshou(2012,12,21); //射手9

    QDate mday(2012,month,day);
    if(mday<=mojie) return 10;
    else if(mday<=shuiping) return 11;
    else if(mday<=shuangyu) return 12;
    else if(mday<=baiyang) return 1;
    else if(mday<=jinniu) return 2;
    else if(mday<=shuangzi) return 3;
    else if(mday<=juxie) return 4;
    else if(mday<=shizi) return 5;
    else if(mday<=chunv) return 6;
    else if(mday<=tiancheng) return 7;
    else if(mday<=tianxie) return 8;
    else if(mday<=sheshou) return 9;
    else return 10;

}


//返回生肖
int ChineseCalendar::GetAnimal(int year)
{

    int offset = year - AnimalStartYear; //阳历计算
    //int offset = this._cYear - AnimalStartYear;　农历计算
    return (offset % 12)+1;
}


int ChineseCalendar::Getgan(int year)
{
    return (year - GanZhiStartYear) % 60 %10+1;
}

int ChineseCalendar::Getzhi(int year)
{
    return (year - GanZhiStartYear) % 60 %12+1;
}

void ChineseCalendar::otherInfo()
{
    animal = GetAnimal(_date.year());
    gan = Getgan(_cYear);
    zhi = Getzhi(_cYear);
    sterm = ChineseTwentyFourDay();
    constellation = GetConstellation(_date.month(),_date.day());
}

QDate ChineseCalendar::lunarToSolar(int year, int month, int day, bool leapMonthFlag)
{
    int i, leap, Temp, offset;
    bool isleapyear,isleapmonth;

    if(!CheckChineseDateLimit(year,month,day,leapMonthFlag))
    {
        QDate da(2013,2,29);
        return da;
    }

    offset = 0;

    for (i = MinYear; i < year; i++)
    {
        Temp = GetChineseYearDays(i); //求当年农历年天数
        offset = offset + Temp;
    }

    leap = GetChineseLeapMonth(year);// 计算该年应该闰哪个月
    if (leap != 0)
    {
        isleapyear = true;
    }
    else
    {
        isleapyear = false;
    }


    if (month != leap)
    {
        isleapmonth = false;  //当前日期并非闰月
    }
    else
    {
        isleapmonth = leapMonthFlag;  //使用用户输入的是否闰月月份
    }


    if ((isleapyear == false) || //当年没有闰月
            (month < leap)) //计算月份小于闰月
    {

        for (i = 1; i < month; i++)
        {
            Temp = GetChineseMonthDays(year, i);//计算非闰月天数
            offset = offset + Temp;
        }

        //检查日期是否大于最大天
        if (day > GetChineseMonthDays(year, month))
        {
            //QMessageBox::warning(this,tr("错误"),tr("非法农历日期"));
        }
        offset = offset + day; //加上当月的天数

    }
    else   //是闰年，且计算月份大于或等于闰月
    {

        for (i = 1; i < month; i++)
        {
            Temp = GetChineseMonthDays(year, i); //计算非闰月天数
            offset = offset + Temp;
        }

        if (month > leap) //计算月大于闰月
        {
            Temp = GetChineseLeapMonthDays(year);   //计算闰月天数
            offset = offset + Temp;               //加上闰月天数

            if (day > GetChineseMonthDays(year, month))
            {
                //QMessageBox::warning(this,tr("错误"),tr("非法农历日期"));
            }
            offset = offset + day;
        }
        else  //计算月等于闰月
        {
            //如果需要计算的是闰月，则应首先加上与闰月对应的普通月的天数
            if (isleapmonth == true) //计算月为闰月
            {
                Temp = GetChineseMonthDays(year, month); //计算非闰月天数
                offset = offset + Temp;
            }

            if (day > GetChineseLeapMonthDays(year))
            {
                //QMessageBox::warning(this,tr("错误"),tr("非法农历日期"));
            }
            offset = offset + day;
        }
    }

    return MinDay.addDays(offset);
}

bool ChineseCalendar::solarToLunar(QDate dt, int &lyear, int &lmonth, int &lday, bool &isleapmonth)
{
    int i;
    int leap;
    int temp;
    int offset;

    if(!CheckDateLimit(dt)) return false;

    //农历日期计算部分
    leap = 0;
    temp = 0;

    offset = MinDay.daysTo(dt);

    for (i = MinYear; i <= MaxYear; i++)
    {
        temp = GetChineseYearDays(i);  //求当年农历年天数
        if (offset - temp < 1)
            break;
        else
        {
            offset = offset - temp;
        }
    }
    lyear = i;


    leap = GetChineseLeapMonth(lyear);//计算该年闰哪个月
    //设定当年是否有闰月
    bool isleapyear;
    if (leap > 0)
    {
        isleapyear = true;
    }
    else
    {
        isleapyear = false;
    }


    isleapmonth = false;
    for (i = 1; i <= 12; i++)
    {
        //闰月
        if ((leap > 0) && (i == leap + 1) && (isleapmonth == false))
        {
            isleapmonth = true;
            i = i - 1;
            temp = GetChineseLeapMonthDays(lyear); //计算闰月天数
        }
        else
        {
            isleapmonth = false;
            temp = GetChineseMonthDays(lyear, i);//计算非闰月天数
        }

        offset = offset - temp;
        if (offset <= 0) break;
    }

    offset = offset + temp;
    lmonth = i;
    lday = offset;
    return true;
}

