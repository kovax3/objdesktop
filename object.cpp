#include "object.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
Object::Object(QWidget *parent) :
    QWidget(parent)

{
   this->setPalette(Qt::transparent);
  this->setEnabled(false);
   this->setWindowFlags(Qt::WindowStaysOnBottomHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);//
  this->setAttribute(Qt::WA_DeleteOnClose,true);
  this->setAttribute(Qt::WA_X11DoNotAcceptFocus,true);
 //this->setAttribute(Qt::WA_X11NetWmWindowTypeUtility,true);
   this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
     this->setAttribute(Qt::WA_NoSystemBackground,true);
     this->setAttribute(Qt::WA_PaintOnScreen,false);

     this->setAttribute(Qt::WA_TranslucentBackground,true);

    this->setFocusPolicy(Qt::NoFocus);
}


void Object::paintEvent(QPaintEvent * /* event */)
{
    QPixmap originalPixmap;
   originalPixmap = QPixmap::grabWindow(QApplication::desktop()->winId(),this->pos().x(),this->pos().y(),this->geometry().width(),this->geometry().height());

      QPainter painter(this);
     painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

//     painter.translate(50, 50);
//    painter.rotate(60.0);
//    painter.scale(0.7, 0.7);
  //  painter.translate(-50, -50);
//  painter.drawPixmap(this->rect(),originalPixmap);
      painter.drawPixmap(this->rect(), pix);
}

 void  Object::setPixmap(QPixmap pix)
 {
     this->pix=pix;
      update();
 }


