#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "cal2.h"
#include "todolist.h"
#include "birthdaymanager.h"
#include <QHash>


class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();
    cal2 *mycal;
    birthdaymanager *mybirth;
    todolist *mytodo;
    QLabel *leftbar;
    ClickedLabel *todobtn,*calbtn,*birthbtn;
    QHash<QString,QString> temptodo;
    QHash<QString,QString> tempbirth;
public slots:
    void showbirthmanager();
    void showcalander();
    void showtodolist();

    bool gettemptodo(QDate date);
    bool setcalTodomark(QDate date);
    bool showtodoincal(QDate date);

    bool gettempbirth(QDate date);
    bool setcalBirthmark(QDate date);
    bool showbirthincal(QDate date);

    void regetbirth();
    void regettodo();


};

#endif // WIDGET_H
