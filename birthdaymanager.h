//生日管家类
//负责显示、管理生日
#ifndef BRITHDAYMANAGER_H
#define BIRTHDAYMANAGER_H

#include <QWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QDomDocument>
#include <QHash>
#include <QFile>
#include <QDateTime>
#include "birthdayclass.h"
#include "birthitem.h"
#include <QLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QPushButton>
#include "clickedlabel.h"
#include <QList>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QCheckBox>

class birthdaymanager : public QWidget
{
    Q_OBJECT
    
public:
    //widget
    //QTreeWidget *treewidget;
    QLabel *name,*lunarbirth,*solarbirth,*star,*animal,*nextbirth,*todays;
    QLabel *infolabel;

    QScrollArea *listscroll;
    QLabel *listlabel;
    QVBoxLayout *listlayout;

    ClickedLabel *editbtn,*addbtn,*deletebtn;


    //编辑与添加生日界面
    QLabel *ename,*editbg;
    QLineEdit *enameline;
    QCheckBox *lunarbox,*yearbox;
    QSpinBox *yearspinbox;
    QComboBox *monthcom,*daycom;
    ClickedLabel *okbtn,*canclebtn;


    //dom
    QDomDocument dombirth;

    //hash
    //QHash<QTreeWidgetItem*,QDomElement> item_dom_hash;
    //QHash<QTreeWidgetItem*,birthdayclass> item_birth_hash;

    QList<birthitem*> itemlist;
    QHash<birthitem*,QDomElement> item_dom_hash;
    QHash<birthitem*,birthdayclass> item_birth_hash;
    QStringList cnweekname,constellationName,ganStr,zhiStr,animalStr,nStr,monthstring;
    QStringList monthComStr,daycomStr;
    QList<int> monthint;
    QList<int> solarmonthdays;
    int dayint;

    birthitem *cur_item;
    bool editing;

signals:
    void birthneedtorefresh();
public:
    birthdaymanager(QWidget *parent = 0);
    ~birthdaymanager();

    void initBaseDate();
    bool readbirth();
    void sorttree(QTreeWidget *tw);
    void additemtolist(birthitem* item);
    void resizelistlabel();
    void write();
public slots:
    //void showdetail(QTreeWidgetItem *item);
    void showdetail(birthitem *item);
    void delCurItem();
    bool addBirth();
    void canclebtnOnclicked();
    void okbtnOnclicked();
    void editbtnOnclicked();
    void yearchanged();
    void monthchanged();
    void hasyearchanged();
    void islunarchanged();
    void freshitem(birthitem *item,birthdayclass &birth);
};

#endif // BIRTHDAYMANAGER_H
