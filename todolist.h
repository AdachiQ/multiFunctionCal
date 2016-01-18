#ifndef TODOLIST_H
#define TODOLIST_H

#include "clickedlabel.h"
#include <QWidget>
#include <QLabel>
#include <QDateTime>
#include <QDomDocument>
#include <QListWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QHash>
#include <QDateTimeEdit>
#include <QToolBox>
#include <QList>

#include <QTimer>
class todolist : public QWidget
{
    Q_OBJECT
    
public:
    todolist(QWidget *parent = 0);
    ~todolist();

    int addItemtolist(QListWidgetItem*item);
    void addItemtoOldlist(QListWidgetItem*item);
    void addItemtoWorkinglist(QListWidgetItem*item);
    void addItemtoCominglist(QListWidgetItem*item);
    void additemstoEventlist1();
    void additemstoEventlist2();
    void additemstoEventlist3();


public:
    QListWidget *eventlist1,*eventlist2,*eventlist3;
    QToolBox *toolbox;
    bool eventediting,stepediting;
    QTimer *timer;
    QDateTime olddatetime;
    //显示详情界面
    QLabel *sbg;
    QLabel *stitle;
    QLabel *sstart;
    QLabel *send;
    QLabel *splace;
    QListWidget *slist;
    ClickedLabel *delbtn,*addbtn,*setdonebtn,*setundobtn,*editbtn;
    QLabel *sbtnsbg;
    QPlainTextEdit *sdetail;


    //编辑详情界面
    QLabel *ebg;
    QLineEdit *etitleedit,*eplaceedit;
    QLabel *eplace;
    QLabel *estart;
    QLabel *eend;
    QDateTimeEdit *startdatetime;
    QDateTimeEdit *enddatetime;
    QPlainTextEdit *edetail;
    QListWidget *esteplist;
    QLineEdit *estepedit;
    ClickedLabel *addstepbtn,*okbtn,*canclebtn,*stepdelbtn;
    QLabel *bottombg;


    QListWidgetItem *cur_item;
    QDomDocument todos;

    QList<QListWidgetItem *> olditemlist;
    QList<QListWidgetItem *> workingitemlist;
    QList<QListWidgetItem *> comingitemlist;

    QHash<QListWidgetItem *, QDomElement> domElementForItem;
    QHash<QListWidgetItem *, QDomElement> stepdomforitem;

public slots:
    void showdetail(QListWidgetItem *item);

    void reverseStepState(QListWidgetItem* item);
    void reverseEventState();

    void delbtnOnclick();
    void addbtnOnclick();
    void editbtnOnclick();
    void write();
    void addsteptolist();
    void delstepfromlist();
    void okOnclicked();
    void cancleOnclicked();
    void esteplistclicked(QListWidgetItem *item);
    void freshlist();
    void checkdatechange();
public:
    bool readtodos();
    void updatetodos();
    void parseEvents(const QDomElement &element);

signals:
    void todoneedfresh();
};

#endif // TODOLIST_H
