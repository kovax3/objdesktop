
#include "fanous.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QMessageBox>

#include <QDebug>
fanous::fanous(QWidget *parent) :
    QWidget(parent)

{
   interval=300;
  this->setPalette(Qt::transparent);
 // this->setEnabled(false);
   this->setWindowFlags(Qt::WindowStaysOnBottomHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
   this->setAttribute(Qt::WA_DeleteOnClose,true);
    //this->setAttribute(Qt::WA_X11DoNotAcceptFocus,true);
 this->setAttribute(Qt::WA_X11NetWmWindowTypeUtility,true);
  this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    this->setAttribute(Qt::WA_NoSystemBackground,true);
    this->setAttribute(Qt::WA_PaintOnScreen,false);
this->setAttribute(Qt::WA_X11NetWmWindowTypeDock);
    this->setAttribute(Qt::WA_TranslucentBackground,true);

   this->setAttribute(Qt::WA_X11NetWmWindowTypeSplash,true);
   this->setFocusPolicy(Qt::NoFocus);
   timer=new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(interval);
    b=false;
    curFrame=0;
    xpos=0;
    ypos=0;
    direction=1;
 directionNum=1;
}

void fanous::closeEvent(QCloseEvent *)
{
    this->timer->stop();
}

void fanous::paintEvent(QPaintEvent * /* event */)
{


    QPainter painter(this);
painter.eraseRect(this->rect());
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

   int w=pix.width()/numFrame;
    int x=w*curFrame;
    int h= pix.height()/directionNum;
int y;
if(directionNum==1){
    y=0;
}else{
      y=(pix.height()/direction-h);
}

    this->resize(w,h);
        QRect source(x, y, w, h);

 painter.drawPixmap(this->rect(), pix,source);

}

 void  fanous::setPixmap(QPixmap pix)
 {
     this->pix=pix;
     update();
 }
void fanous::setframeNum(int  num)
{
    this->numFrame=num;
    update();
}
void fanous::setInterval(int value)
{
    this->interval=value;
    timer->setInterval(value);
    update();
}
 void fanous::setDirection(int val)
 {
     direction=val;
       update();
 }
  void fanous::setDirectionNum(int  num)
  {
      directionNum=num;
      update();
  }

void fanous::updateTime()
{
  //   this->move(xpos,ypos);
    curFrame++;
    if(curFrame>=numFrame)
        curFrame=0;

    update();
}

void fanous::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton ) {
        wx = QCursor::pos().x()-this->pos().x();
        wy= QCursor::pos().y()-this->pos().y();
        b=true;
        timer->stop();
emit isPressed();
    }
        update();
}
void fanous::mouseMoveEvent(QMouseEvent *)
{
    if (b==true)   {
        this->move(QCursor::pos().x()-wx , QCursor::pos().y()-wy);
    }
    update();
}
void fanous::mouseReleaseEvent ( QMouseEvent * )
{
    b=false;
    xpos=this->pos().x();
    ypos=this->pos().y();
    timer->start(300);
    emit isReleased();
       update();
}

