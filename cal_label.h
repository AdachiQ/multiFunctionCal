//自定义控件，用于显示月历里某一天的全部信息
//能够显示公历日期、农历日期、传统节日、节气
//能够显示当天是否有生日、节日、待办事项


#ifndef CAL_LABEL_H
#define CAL_LABEL_H

#include <QLabel>
#include <QLayout>

class cal_label : public QLabel
{
    Q_OBJECT
public:
    explicit cal_label(QWidget *parent = 0,int pixsize = 16);
    QLabel *day,*lunarday;
    QLabel *bholiday,*bbirth,*btodo;

signals:
    void clicked(cal_label* cclabel);

public:
    void resetall();
    void setnormal();
    void setselect();

protected:
    void mouseReleaseEvent( QMouseEvent* );
    
public slots:
    
};

#endif // CAL_LABEL_H
