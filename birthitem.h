//自定义控件，继承自QLabel
//生日管家左侧列表的item控件，能够在一个控件里同时显示姓名、下个生日日期、距离下个生日的天数等信息，并能够响应点击事件

#ifndef BIRTHITEM_H
#define BIRTHITEM_H

#include <QLabel>

class birthitem : public QLabel
{
    Q_OBJECT
public:
    explicit birthitem(QWidget *parent = 0);
    void setnormal();
    void setselect();

public:
    QLabel *name,*nextbirth,*days;
    int daysnum;

signals:
    void clicked(birthitem* thisitem);
    
public slots:

    
protected:
    void mouseReleaseEvent( QMouseEvent* );
};

#endif // BIRTHITEM_H
