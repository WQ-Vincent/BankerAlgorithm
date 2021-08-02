#ifndef MYWIDGET_H
#define MYWIDGET_H
#include "mainwindow.h"

class mywidget : public QWidget
{
    Q_OBJECT

public:
    mywidget(QWidget *parent = nullptr);
    ~mywidget();

private slots:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool     m_pressed;
    QPoint   m_movePos;
};

#endif // MYWIDGET_H
