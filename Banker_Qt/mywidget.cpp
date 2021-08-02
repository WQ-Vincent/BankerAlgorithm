#include "mywidget.h"

mywidget::mywidget(QWidget *parent)
    : QWidget(parent)
{

}

mywidget::~mywidget()
{

}

void mywidget::mousePressEvent(QMouseEvent *event) //窗口移动事件
{
    if( (event->button() == Qt::LeftButton)){
            m_pressed = true;
            m_movePos = event->globalPos() - this->pos();
    //        event->accept();
        }
        else if(event->button() == Qt::RightButton){
            //如果是右键
            this->hide();

        }

}
void mywidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressed){
            move(event->globalPos() - m_movePos);
    //        event->accept();
        }

}
void mywidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
}
