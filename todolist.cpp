#include "todolist.h"
#include <QLayout>
#include <QtGui>
#include <QPixmap>
#include <QMessageBox>

todolist::todolist(QWidget *parent)
    : QWidget(parent)
{

    QFont tf;
    tf.setPixelSize(30);
    eventlist1 = new QListWidget;
    eventlist1->setStyleSheet("color:rgb(169,170,171);background-color:white");
    eventlist1->setFont(tf);
    eventlist1->setFrameStyle(0);
    connect(eventlist1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showdetail(QListWidgetItem*)));

    eventlist2 = new QListWidget;
    eventlist2->setFrameStyle(0);
    eventlist2->setFont(tf);
    //eventlist2->setStyleSheet("color:rgb(169,170,171);background-color:rgba(25,42,45,200)");
    eventlist2->setStyleSheet("color:rgb(169,170,171);background-color:white");
    connect(eventlist2,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showdetail(QListWidgetItem*)));

    eventlist3 = new QListWidget;
    eventlist3->setFrameStyle(0);
    eventlist3->setFont(tf);
   // eventlist3->setStyleSheet("color:rgb(169,170,171);background-color:rgba(25,42,45,200)");
    eventlist3->setStyleSheet("color:rgb(169,170,171);background-color:white");
    connect(eventlist3,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showdetail(QListWidgetItem*)));

    toolbox = new QToolBox;
    QFont toolfont;
    toolfont.setPixelSize(30);
    toolbox->setFont(toolfont);
    toolbox->addItem(eventlist1,tr("更早"));
    toolbox->addItem(eventlist2,tr("最近"));
    toolbox->addItem(eventlist3,tr("更多"));
    toolbox->setCurrentIndex(1);
    toolbox->layout()->setSpacing(1);

    QFile file("myqss.qss");
    file.open(QFile::ReadOnly);
    toolbox->setStyleSheet(file.readAll());



    int fsize =30;
    QFont font;
    font.setPixelSize(fsize);
    font.setBold(true);
    stitle = new QLabel;
    stitle->setFont(font);
    stitle->setFixedHeight(100);
    stitle->setStyleSheet("color:white;background-color:rgb(242,112,112)");
    stitle->setIndent(20);

    font.setBold(false);
    font.setPixelSize(fsize-10);

    int indent = 40;
    sstart = new QLabel;
    sstart->setFont(font);
    sstart->setStyleSheet("background-color:rgba(0,0,0,0);color:white");
    sstart->setIndent(indent);


    send = new QLabel;
    send->setFont(font);
    send->setStyleSheet("background-color:rgba(0,0,0,0);color:white");
    send->setIndent(indent);

    splace = new QLabel;
    splace ->setFont(font);
    splace ->setStyleSheet("background-color:rgba(0,0,0,0);color:white");
    splace->setIndent(indent);

    fsize = 20;
    font.setPixelSize(fsize);
    sdetail = new QPlainTextEdit;
    sdetail->setFont(font);
    sdetail->setStyleSheet("background-color:rgba(0,0,0,0);color:white");
    sdetail->setMaximumHeight(50);
    sdetail->setDisabled(true);
    sdetail->setFrameStyle(0);

    QHBoxLayout *sdetaillayout = new QHBoxLayout;
    sdetaillayout->addSpacing(40);
    sdetaillayout->addWidget(sdetail);
    sdetaillayout->addSpacing(10);


    slist = new QListWidget;
    slist->setFont(font);
    slist->setStyleSheet("background-color:rgba(0,0,0,0);color:white");
    slist->setFrameStyle(0);
    connect(slist,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(reverseStepState(QListWidgetItem*)));

    QHBoxLayout *slistlayout = new QHBoxLayout;
    slistlayout->addSpacing(40);
    slistlayout->addWidget(slist);
    slistlayout->addSpacing(10);

    sbtnsbg = new QLabel;
    sbtnsbg->setFixedHeight(50);
    sbtnsbg->setStyleSheet("background-color:rgb(106,106,106)");

    //完成
    delbtn = new ClickedLabel;
    delbtn->setPixmap(QPixmap(":/img/img/trashcan.png"));
    delbtn->setAlignment(Qt::AlignCenter);
    connect(delbtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(delbtnOnclick()));

    //完成
    addbtn = new ClickedLabel;
    addbtn->setPixmap(QPixmap(":/img/img/plus.png"));
    addbtn->setAlignment(Qt::AlignCenter);
    connect(addbtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(addbtnOnclick()));

    //完成
    editbtn = new ClickedLabel;
    editbtn->setPixmap(QPixmap(":/img/img/pencil.png"));
    editbtn->setAlignment(Qt::AlignCenter);
    connect(editbtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(editbtnOnclick()));

    //完成
    setdonebtn = new ClickedLabel;
    setdonebtn->setPixmap(QPixmap(":/img/img/heart1.png"));
    setdonebtn->setAlignment(Qt::AlignCenter);
    connect(setdonebtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(reverseEventState()));

    //完成
    setundobtn = new ClickedLabel;
    setundobtn->setPixmap(QPixmap(":/img/img/heart2.png"));
    setundobtn->setAlignment(Qt::AlignCenter);
    connect(setundobtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(reverseEventState()));

    QHBoxLayout *sbtnslayout = new QHBoxLayout(sbtnsbg);
    sbtnslayout->addWidget(delbtn);
    sbtnslayout->addWidget(addbtn);
    sbtnslayout->addWidget(editbtn);
    sbtnslayout->addWidget(setdonebtn);
    sbtnslayout->addWidget(setundobtn);
    setundobtn->hide();

    sbg =new QLabel;
    sbg->setFixedWidth(360);
    sbg->setStyleSheet("background-color:rgb(48,46,47)");

    QVBoxLayout *sbglayout = new QVBoxLayout(sbg);
    sbglayout->addWidget(stitle);
    sbglayout->addSpacing(20);
    sbglayout->addWidget(sstart);
    sbglayout->addWidget(send);
    sbglayout->addWidget(splace);
    sbglayout->addLayout(sdetaillayout);
    sbglayout->addSpacing(15);
    sbglayout->addLayout(slistlayout);
    sbglayout->addStretch();
    sbglayout->addWidget(sbtnsbg);
    sbglayout->setMargin(0);

    //-----------------------------编辑界面----------------------------------------
    ebg = new QLabel;
    ebg->setStyleSheet("background-color:rgb(48,46,47)");


    QFont efont;

    etitleedit = new QLineEdit;
    etitleedit->setStyleSheet("background-color:rgb(242,112,112);color:white");
    efont.setPixelSize(60);
    etitleedit->setFont(efont);
    etitleedit->setFrame(false);
    etitleedit->setFixedHeight(100);
    //etitleedit->setTextMargins(QMargins(10));

    efont.setPixelSize(20);
    startdatetime = new QDateTimeEdit;
    startdatetime->setDisplayFormat("yyyy-M-d   H:mm:ss");
    startdatetime->setFont(efont);
    startdatetime->setStyleSheet("color:white");
    startdatetime->setFrame(false);

    estart = new QLabel;
    estart->setFont(efont);
    estart->setText(tr("开始时间"));
    estart->setStyleSheet("color:white");
    estart->setIndent(30);


    QHBoxLayout *estartlayout = new QHBoxLayout;
    estartlayout->addSpacing(30);
    estartlayout->addWidget(startdatetime);
    estartlayout->addStretch();


    enddatetime = new QDateTimeEdit;
    enddatetime->setDisplayFormat("yyyy-M-d   H:mm:ss");
    enddatetime->setFont(efont);
    enddatetime->setStyleSheet("color:white");
    enddatetime->setFrame(false);

    eend = new QLabel;
    eend->setFont(efont);
    eend->setText(tr("结束时间"));
    eend->setStyleSheet("color:white");
    eend->setIndent(30);

    QHBoxLayout *eendlayout = new QHBoxLayout;
    eendlayout->addSpacing(30);
    eendlayout->addWidget(enddatetime);
    eendlayout->addStretch();


    eplace = new QLabel;
    eplace->setFont(efont);
    eplace->setText(tr("地点"));
    eplace->setStyleSheet("color:white");
    eplace->setIndent(30);

    eplaceedit = new QLineEdit;
    eplaceedit->setFont(efont);
    eplaceedit->setStyleSheet("color:white;background-color:darkgrey");
    eplaceedit->setFrame(false);
    eplaceedit->setFixedHeight(40);

    QHBoxLayout *eplacelayout = new QHBoxLayout;
    eplacelayout->addSpacing(30);
    eplacelayout->addWidget(eplaceedit);
    //eplacelayout->addSpacing(30);


    edetail = new QPlainTextEdit;
    edetail->setFont(efont);
    edetail->setStyleSheet("color:white;;background-color:grey");
    edetail->setFrameStyle(0);

    QHBoxLayout *edetaillayout = new QHBoxLayout;
    edetaillayout->addSpacing(30);
    edetaillayout->addWidget(edetail);
    //edetaillayout->addSpacing(30);

    QVBoxLayout *leftlayout = new QVBoxLayout;
    leftlayout->addWidget(etitleedit);
    leftlayout->addSpacing(20);

    leftlayout->addWidget(estart);
    leftlayout->addLayout(estartlayout);
    leftlayout->addSpacing(10);

   // leftlayout->addWidget(startdatetime);
    leftlayout->addWidget(eend);
    leftlayout->addLayout(eendlayout);
    //leftlayout->addWidget(enddatetime);
    leftlayout->addSpacing(10);

    leftlayout->addWidget(eplace);
    leftlayout->addSpacing(5);
    leftlayout->addLayout(eplacelayout);
    leftlayout->addLayout(edetaillayout);
    leftlayout->setSpacing(0);

    efont.setPixelSize(60);
    estepedit = new QLineEdit;
    estepedit->setStyleSheet("background-color:rgb(242,112,112);color:white");
    estepedit->setFrame(false);
    estepedit->setFixedSize(260,100);
    //estepedit->setTextMargins(10);
    estepedit->setFont(efont);

    addstepbtn = new ClickedLabel;
    addstepbtn->setStyleSheet("background-color:rgb(147,221,234);color:white;font:100px");
    addstepbtn->setFixedSize(100,100);
    addstepbtn->setAlignment(Qt::AlignCenter);
    addstepbtn->setText("+");
    connect(addstepbtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(addsteptolist()));


    QHBoxLayout *esteplayout = new QHBoxLayout;
    esteplayout->addWidget(estepedit);
    esteplayout->addWidget(addstepbtn);
    esteplayout->setSpacing(0);

    esteplist = new QListWidget;
    esteplist->setStyleSheet("color:white;font:25px");
    esteplist->setFrameStyle(0);
    connect(esteplist,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(esteplistclicked(QListWidgetItem*)));

    QHBoxLayout *esteplistlayout = new QHBoxLayout;
    esteplistlayout->addSpacing(30);
    esteplistlayout->addWidget(esteplist);
    //esteplistlayout->addSpacing(30);

    QVBoxLayout *rightlayout = new QVBoxLayout;
    rightlayout->addLayout(esteplayout);
    rightlayout->addSpacing(5);
    rightlayout->addLayout(esteplistlayout);

    QHBoxLayout *etoplayout = new QHBoxLayout;
    etoplayout->addLayout(leftlayout);
    etoplayout->addLayout(rightlayout);

    bottombg = new QLabel;
    bottombg->setFixedHeight(50);
    bottombg->setStyleSheet("background-color:rgb(106,106,106)");


    okbtn = new ClickedLabel;
    okbtn->setPixmap(QPixmap(":/img/img/checkmark.png"));
    okbtn->setAlignment(Qt::AlignCenter);
    connect(okbtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(okOnclicked()));

    //完成
    canclebtn = new ClickedLabel;
    canclebtn->setPixmap(QPixmap(":/img/img/exit.png"));
    canclebtn->setAlignment(Qt::AlignCenter);
    connect(canclebtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(cancleOnclicked()));

    //完成
    stepdelbtn = new ClickedLabel;
    stepdelbtn->setPixmap(QPixmap(":/img/img/trashcan.png"));
    stepdelbtn->setAlignment(Qt::AlignCenter);
    connect(stepdelbtn,SIGNAL(clicked(ClickedLabel*)),this,SLOT(delstepfromlist()));

    QHBoxLayout *ebtnslayout = new QHBoxLayout(bottombg);
    ebtnslayout->addWidget(okbtn);

    ebtnslayout->addWidget(stepdelbtn);
    ebtnslayout->addWidget(canclebtn);


    QVBoxLayout *emainlayout = new QVBoxLayout(ebg);
    emainlayout->addLayout(etoplayout);
    emainlayout->addWidget(bottombg);
    emainlayout->setMargin(0);

    //-------------------------------编辑界面结束---------------------------------

    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    mainlayout->addWidget(toolbox);
    mainlayout->addWidget(sbg);
    mainlayout->addWidget(ebg);
    mainlayout->setMargin(0);
    mainlayout->setSpacing(1);
    //sbg->hide();
    //toolbox->hide();

    setundobtn->hide();
    setdonebtn->show();
    ebg->hide();
    readtodos();

    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(checkdatechange()));
    timer->start(5000);
    olddatetime = QDateTime::currentDateTime();
}

todolist::~todolist()
{
    
}


bool todolist::readtodos()
{
    QFile file(QDir::currentPath()+"/xml/todolist.xml");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("待办事项"),
                             tr("无法读取文件 %1")
                             .arg(file.errorString()));
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!todos.setContent(&file, true, &errorStr, &errorLine,
                                &errorColumn)) {
        QMessageBox::information(window(), tr("待办事项"),
                                 tr("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
        return false;
    }
    file.close();

    eventlist1->clear();
    eventlist2->clear();
    eventlist3->clear();

    QDomElement root = todos.documentElement();
    QDomElement child = root.firstChildElement();
    while (!child.isNull())
    {
        parseEvents(child);
        child = child.nextSiblingElement();
    }

    additemstoEventlist1();
    additemstoEventlist2();
    additemstoEventlist3();
    if(!workingitemlist.isEmpty())
    {
        cur_item = workingitemlist.first();
        toolbox->setCurrentIndex(1);
    }
    else if(!comingitemlist.isEmpty())
    {
        cur_item = comingitemlist.first();
        toolbox->setCurrentIndex(2);
    }
    else if(!olditemlist.isEmpty())
    {
        cur_item = olditemlist.first();
        toolbox->setCurrentIndex(0);
    }
    else cur_item = NULL;
    showdetail(cur_item);
    connect(eventlist1,SIGNAL(itemClicked(QListWidgetItem*)),
            this,SLOT(showdetail(QListWidgetItem*)));

    connect(eventlist2,SIGNAL(itemClicked(QListWidgetItem*)),
            this,SLOT(showdetail(QListWidgetItem*)));

    connect(eventlist3,SIGNAL(itemClicked(QListWidgetItem*)),
            this,SLOT(showdetail(QListWidgetItem*)));

}

void todolist::parseEvents(const QDomElement &element)
{
    QListWidgetItem *item = new QListWidgetItem;

//    if(element.attribute("done")=="true")
//        item1->setCheckState(Qt::Checked);
//    else
//        item1->setCheckState(Qt::Unchecked);
    domElementForItem.insert(item,element);
    item->setText(element.attribute("title"));
    addItemtolist(item);
}



void todolist::showdetail(QListWidgetItem *item)
{
    if(!item)
    {
        stitle->setText(tr("当前列表无内容"));
        sstart->clear();
        send->clear();
        splace->clear();
        sdetail->hide();
        slist->hide();
        return;
    }
    QDomElement element = domElementForItem.value(item);

    stitle->setText(element.attribute("title"));

    sstart->setText(tr("<strong>开始时间</strong>：%1 %2").arg(element.attribute("startdate")).arg(element.attribute("starttime")));
    send->setText(tr("<strong>结束时间</strong>：%1 %2").arg(element.attribute("enddate")).arg(element.attribute("endtime")));

    //待删除


    splace->setText(tr("<strong>地点</strong>：%1").arg(element.attribute("place")));

    sdetail->setPlainText(element.attribute("detail"));
    if(sdetail->toPlainText().isEmpty()) sdetail->hide();
    else sdetail->show();

    if(element.attribute("done")=="true")
    {
        setundobtn->show();
        setdonebtn->hide();
    }
    else
    {
        setundobtn->hide();
        setdonebtn->show();
    }
    slist->clear();
    stepdomforitem.clear();

    QDomElement child = element.firstChildElement();
    if(!child.isNull())
    {
        slist->show();
        while(!child.isNull())
        {
            QListWidgetItem *listitem = new QListWidgetItem;
            listitem->setText(child.attribute("title"));
            stepdomforitem.insert(listitem,child);

            if(child.attribute("done")=="true")
                listitem->setCheckState(Qt::Checked);
            else
                listitem->setCheckState(Qt::Unchecked);

            slist->addItem(listitem);
            child = child.nextSiblingElement();
        }
    }
    else slist->hide();

    cur_item = item;
}

void todolist::reverseStepState(QListWidgetItem* item)
{
    //QMessageBox::information(window(),tr("changed"),tr("checkstatechanged"));
    QDomElement element = stepdomforitem.value(item);
    if(item->checkState()==Qt::Checked)
        element.setAttribute("done","true");
    else
        element.setAttribute("done","false");

    write();
}


void todolist::reverseEventState()
{
    if(!cur_item) return;

    QDomElement element = domElementForItem.value(cur_item);
    if(element.attribute("done")=="false")
    {
        element.setAttribute("done","true");
        setdonebtn->hide();
        setundobtn->show();
    }
    else
    {
        element.setAttribute("done","false");
        setdonebtn->show();
        setundobtn->hide();
    }

    write();
}




void todolist::delbtnOnclick()
{

    if(cur_item)
    {
        QDomElement element = domElementForItem.take(cur_item);
        todos.documentElement().removeChild(element);
        write();
        if(olditemlist.contains(cur_item))
        {
            olditemlist.removeOne(cur_item);
            delete cur_item;
            if(olditemlist.isEmpty()) cur_item = NULL;
            else cur_item = olditemlist[0];
        }
        else if(workingitemlist.contains(cur_item))
        {
            workingitemlist.removeOne(cur_item);
            delete cur_item;
            if(workingitemlist.isEmpty()) cur_item = NULL;
            else cur_item = workingitemlist[0];
        }
        else
        {
            comingitemlist.removeOne(cur_item);
            delete cur_item;
            if(comingitemlist.isEmpty()) cur_item = NULL;
            else cur_item = comingitemlist[0];
        }
        showdetail(cur_item);
        emit todoneedfresh();

    }
}

void todolist::addbtnOnclick()
{
    timer->stop();
    eventediting = false;
    stepediting = false;
    etitleedit->clear();
    eplaceedit->clear();
    edetail->clear();
    estepedit->clear();
    esteplist->clear();
    startdatetime->setDate(QDate::currentDate());
    startdatetime->setTime(QTime::currentTime());
    enddatetime->setDate(QDate::currentDate());
    enddatetime->setTime(QTime::currentTime());
    sbg->hide();
    toolbox->hide();
    ebg->show();
}

void todolist::editbtnOnclick()
{
    if(cur_item)
    {
        if(domElementForItem.contains(cur_item))
        {
            timer->stop();
            QDomElement element = domElementForItem.value(cur_item);
            etitleedit->setText(element.attribute("title"));
            eplaceedit->setText(element.attribute("place"));
            edetail->setPlainText(element.attribute("detail"));
            QDate d;
            QTime t;
            d = d.fromString(element.attribute("startdate"),"yyyy-M-d");
            t = t.fromString(element.attribute("starttime"),"H:mm");
            startdatetime->setDate(d);
            startdatetime->setTime(t);

            d = d.fromString(element.attribute("enddate"),"yyyy-M-d");
            t = t.fromString(element.attribute("endtime"),"H:mm");
            enddatetime->setDate(d);
            enddatetime->setTime(t);
            QDomElement child = element.firstChildElement();
            esteplist->clear();
            while(!child.isNull())
            {
                esteplist->addItem(child.attribute("title"));
                child = child.nextSiblingElement();
            }

            ebg->show();
            sbg->hide();
            toolbox->hide();
            eventediting = true;
            stepediting = false;

        }

    }

}

void todolist::write()
{
    QFile file(QDir::currentPath()+"/xml/todolist.xml");
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("待办事项"),
                             tr("无法写入 %1\n%2.")
                             .arg(QDir::currentPath()+"\\xml\\todolist.xml")
                             .arg(file.errorString()));
        return;
    }
    QTextStream out(&file);
    todos.save(out, 4);
}



void todolist::addsteptolist()
{
    if(estepedit->text().isEmpty()) return;
    if(stepediting)
    {
        esteplist->currentItem()->setText(estepedit->text());
    }
    else
    {
        esteplist->addItem(estepedit->text());
        estepedit->clear();
    }
    stepediting = false;

}


void todolist::delstepfromlist()
{
    if(esteplist->count()!=0)
    {
        QListWidgetItem *item = esteplist->currentItem();
        delete item;
        estepedit->clear();
    }
}

void todolist::cancleOnclicked()
{
    ebg->hide();
    sbg->show();
    toolbox->show();
    timer->start(5000);
}

void todolist::okOnclicked()
{

    if(etitleedit->text().isEmpty()) return;
    if(startdatetime->dateTime()>enddatetime->dateTime()) return;

    QDomElement element = todos.createElement("event");
    element.setAttribute("done","false");
    element.setAttribute("title",etitleedit->text());
    element.setAttribute("place",eplaceedit->text());
    element.setAttribute("detail",edetail->toPlainText());
    element.setAttribute("startdate",startdatetime->date().toString("yyyy-M-d"));
    element.setAttribute("starttime",startdatetime->time().toString("H:mm"));
    element.setAttribute("enddate",enddatetime->date().toString("yyyy-M-d"));
    element.setAttribute("endtime",enddatetime->time().toString("H:mm"));
    if(esteplist->count()!=0)
    {

        for(int i=0;i<esteplist->count();i++)
        {
            QDomElement child = todos.createElement("item");

            child.setAttribute("title",esteplist->item(i)->text());

            child.setAttribute("done","false");
            element.appendChild(child);
        }
    }
    QListWidgetItem * newitem = new QListWidgetItem;
    newitem->setText(etitleedit->text());
    domElementForItem.insert(newitem,element);

    if(eventediting)
    {
        QDomElement oldelement = domElementForItem.take(cur_item);
        todos.documentElement().removeChild(oldelement);

        if(olditemlist.contains(cur_item))
        {
            olditemlist.removeOne(cur_item);
            delete cur_item;
        }
        else if(workingitemlist.contains(cur_item))
        {
            workingitemlist.removeOne(cur_item);
            delete cur_item;
        }
        else
        {
            comingitemlist.removeOne(cur_item);
            delete cur_item;
        }


    }
    todos.documentElement().appendChild(element);
    write();

    addItemtolist(newitem);
    additemstoEventlist1();
    additemstoEventlist2();
    additemstoEventlist3();
    showdetail(newitem);
    cur_item = newitem;
    ebg->hide();
    sbg->show();
    toolbox->show();
    timer->start(5000);
    emit todoneedfresh();
}

int todolist::addItemtolist(QListWidgetItem *item)
{
    if(!item) return 0;
    QDomElement element = domElementForItem.value(item);
    QDate sdate;
    sdate = sdate.fromString(element.attribute("startdate"),"yyyy-M-d");

    QDate edate;
    edate = edate.fromString(element.attribute("enddate"),"yyyy-M-d");

    if(edate<QDate::currentDate())
    {
        addItemtoOldlist(item);
        return 1;
    }
    else if(sdate>QDate::currentDate().addDays(6))
    {
        addItemtoCominglist(item);
        return 3;
    }
    else
    {
        addItemtoWorkinglist(item);
        return 2;
    }
}

void todolist::addItemtoOldlist(QListWidgetItem *item)
{
    if(!item) return;
    if(!olditemlist.isEmpty())
    {
        QDomElement element1 = domElementForItem.value(item);
        QString dtStr = element1.attribute("startdate")+ " " + element1.attribute("starttime");
        QDateTime itemdt;
        itemdt = itemdt.fromString(dtStr,"yyyy-M-d H:mm");

        for(int i=0;i<olditemlist.count();i++)
        {

            QDomElement element2 = domElementForItem.value(olditemlist[i]);
            dtStr = element2.attribute("startdate")+ " " + element1.attribute("starttime");
            QDateTime dt;
            dt = dt.fromString(dtStr,"yyyy-M-d H:mm");
            if(itemdt<=dt)
            {
                olditemlist.insert(i,item);
                return;
            }

        }

    }
    olditemlist.append(item);
}

void todolist::addItemtoCominglist(QListWidgetItem *item)
{
    if(!item) return;
    if(!comingitemlist.isEmpty())
    {
        QDomElement element1 = domElementForItem.value(item);
        QString dtStr = element1.attribute("startdate")+ " " + element1.attribute("starttime");
        QDateTime itemdt;
        itemdt = itemdt.fromString(dtStr,"yyyy-M-d H:mm");

        for(int i=0;i<comingitemlist.count();i++)
        {

            QDomElement element2 = domElementForItem.value(comingitemlist.at(i));
            dtStr = element2.attribute("startdate")+ " " + element1.attribute("starttime");
            QDateTime dt;
            dt = dt.fromString(dtStr,"yyyy-M-d H:mm");
            if(itemdt<=dt)
            {
                comingitemlist.insert(i,item);
                return;
            }

        }

    }
    comingitemlist.append(item);
}


void todolist::addItemtoWorkinglist(QListWidgetItem *item)
{
    if(!item) return;
    if(!workingitemlist.isEmpty())
    {
        QDomElement element1 = domElementForItem.value(item);
        QString dtStr = element1.attribute("startdate")+ " " + element1.attribute("starttime");
        QDateTime itemsdt;
        itemsdt = itemsdt.fromString(dtStr,"yyyy-M-d H:mm");

        dtStr = element1.attribute("enddate")+ " " + element1.attribute("endtime");
        QDateTime itemedt;
        itemedt = itemedt.fromString(dtStr,"yyyy-M-d H:mm");

        for(int i=0;i<workingitemlist.count();i++)
        {
            QDomElement element2 = domElementForItem.value(workingitemlist.at(i));
            dtStr = element2.attribute("startdate")+ " " + element1.attribute("starttime");
            QDateTime sdt2;
            sdt2 = sdt2.fromString(dtStr,"yyyy-M-d H:mm");

            dtStr = element2.attribute("enddate")+ " " + element1.attribute("endtime");
            QDateTime edt22;
            edt22 = edt22.fromString(dtStr,"yyyy-M-d H:mm");

            if(itemsdt.date()<QDate::currentDate())
            {
                if(edt22.date()<QDate::currentDate())
                {
                    if(itemedt<=edt22)
                    {
                        workingitemlist.insert(i,item);
                        return;
                    }
                }
                else
                {
                    workingitemlist.insert(i,item);
                    return;
                }
            }
            else
            {
                if(itemsdt<sdt2)
                {
                    workingitemlist.insert(i,item);
                    return;
                }
            }
        }

    }
    workingitemlist.append(item);

}

void todolist::additemstoEventlist2()
{
    for(int i=0;i<eventlist2->count();i++)
        eventlist2->takeItem(i);
    for(int i=0;i<workingitemlist.count();i++)
        eventlist2->addItem(workingitemlist.at(i));
}

void todolist::additemstoEventlist1()
{
    for(int i=0;i<eventlist1->count();i++)
        eventlist1->takeItem(i);
    for(int i=0;i<olditemlist.count();i++)
        eventlist1->addItem(olditemlist.at(i));
}

void todolist::additemstoEventlist3()
{
    for(int i=0;i<eventlist3->count();i++)
        eventlist3->takeItem(i);
    for(int i=0;i<comingitemlist.count();i++)
        eventlist3->addItem(comingitemlist.at(i));
}

void todolist::esteplistclicked(QListWidgetItem* item)
{
    estepedit->setText(item->text());
    stepediting = true;
}

void todolist::freshlist()
{


}

void todolist::checkdatechange()
{
    for(int i=0;i<workingitemlist.count();i++)
    {
        QDomElement element = domElementForItem.value(workingitemlist[i]);
        QString str = element.attribute("enddate") + " " + element.attribute("endtime");
        QDateTime dt = QDateTime::fromString(str,"yyyy-M-d H:mm");
        if(dt.date()<QDate::currentDate())
        {
            QListWidgetItem *item = workingitemlist.takeAt(i);
            addItemtoOldlist(item);
            additemstoEventlist1();
        }
        else if(dt==QDateTime::currentDateTime())
        {
            //提醒时间到了
            freshlist();
        }
    }
    for(int i=0;i<comingitemlist.count();i++)
    {
        QDomElement element = domElementForItem.value(comingitemlist[i]);
        QString str = element.attribute("enddate");
        QDate dt = QDate::fromString(str,"yyyy-M-d");
        if(dt<QDate::currentDate().addDays(6))
        {
            QListWidgetItem *item = comingitemlist.takeAt(i);
            addItemtoWorkinglist(item);
            additemstoEventlist2();
        }
        else return;
    }
}
