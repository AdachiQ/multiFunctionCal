#ifndef CLICKEDLABEL_H_
#define CLICKEDLABEL_H_
#include <QLabel>
#include <QWidget>

class ClickedLabel : public QLabel
{
    Q_OBJECT
signals:
    void clicked(ClickedLabel* clabel);
public:
    int daynumber;
    ClickedLabel(QWidget *parent=0,int newday = 0): QLabel(parent),m_str("")
    {
        setText(m_str);
        daynumber = newday;
    }
    ~ClickedLabel(){}
protected:
    void mouseReleaseEvent( QMouseEvent* );
private:
    QString m_str;
};
#endif /* CLICKEDLABEL_H_ */
