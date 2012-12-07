#include "penguin.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QMessageBox>

#include <QDebug>
Penguin::Penguin(QWidget *parent) :
    QWidget(parent)
{
    tuxOb=new fanous(QApplication::desktop()->screen(0));

   // onTop=true;
     timer=new QTimer;
     timerTambler=new QTimer;
timerClimber=new QTimer;
       connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
     connect(timerTambler, SIGNAL(timeout()), this, SLOT(updateTimeTambler()));
   connect(timerClimber, SIGNAL(timeout()), this, SLOT(updateClimberAnnimtion()));
   connect(tuxOb, SIGNAL(isPressed()), this, SLOT(stopAllAnimation()));
       connect(tuxOb, SIGNAL(isReleased()), this, SLOT(tambleAnnimation()));



}

void Penguin::stopAllAnimation()
{
 timer   ->stop();
 timerTambler->stop();
 timerClimber->stop();
 m_isRandom=false;
   m_isSlider=false;
}

 void Penguin::setTuxOnTop(bool top)
 {
     onTop=top;
      startTux();
 }
 void Penguin::startTux()
 {

     QDesktopWidget *wid=new QDesktopWidget();
     topScreen=wid->availableGeometry(this).top();
     botScreen=wid->availableGeometry(this).bottom();
     leftScreen=wid->availableGeometry(this).left();
     rightScreen=wid->availableGeometry(this).right();



        if(onTop==true){
            tuxOb->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
        }else{
            tuxOb->setWindowFlags(Qt::WindowStaysOnBottomHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
        }





     tuxOb->setEnabled(true);
     tuxOb->show();

updatePosition();

 }
 void Penguin::updatePosition()
 {
        tuxOb->setInterval(50);
        int tt=topScreen+100;
        int xx=rightScreen-leftScreen;
     int x=rand() % ++xx;
     int y=rand() % ++tt;
     tuxOb->move(x+leftScreen,y);
       tambleAnnimation();
 }

 void Penguin::tambleAnnimation()
 {

      int numtype=3;
       int type=rand() % ++numtype;
   //    qDebug()<<type;
       tuxOb->setPixmap(QPixmap(":/tux/tumble"+QString::number(type+1)+".png"));
       tuxOb->setframeNum(8);
       tuxOb->setDirection(1);
       tuxOb->setDirectionNum(1);

       timerTambler->start(80);

 }
void Penguin::updateTimeTambler()
{

         int x=tuxOb->pos().x();
         int y=tuxOb->pos().y();
         tuxOb->move(x,y+5);
         if(y>=botScreen-tuxOb->height()){
             timerTambler->stop();
             tuxOb->move(x,botScreen-tuxOb->height());


                  int ts=5;
                  int t=rand() % ++ts;
                  if(t==1){
                    //    tuxOb->setInterval(50);
                        bomberAnimation();
                  }else{
                          tuxOb->setInterval(200);
                        m_isRandom=true;
                      updateWaiterAnnimtion();

                  }

     }

}
void Penguin::updateWaiterAnnimtion()
{
    timer->stop();
    if ( m_isRandom==false)
        return;

    tuxOb->setPixmap(QPixmap(":/tux/waiter.png"));
    tuxOb->setDirection(1);
    tuxOb->setDirectionNum(1);
    tuxOb->setframeNum(6);
       QTimer::singleShot(1000, this, SLOT(randomAnnimation()));
}
void Penguin::bomberAnimation()
{
    timer->stop();

  tuxOb->setInterval(50);
    tuxOb->setPixmap(QPixmap(":/tux/bomber.png"));
    tuxOb->setDirection(1);
    tuxOb->setDirectionNum(1);
    tuxOb->setframeNum(16);
       QTimer::singleShot(800, this, SLOT(updatePosition()));
}

void Penguin::randomAnnimation()
{

  if ( m_isRandom==false)
      return;
    m_isSlider=false;
    timer->stop();
    int types=8;
      int type=rand() % ++types;
//      qDebug()<<"type"<<type;
      int directions=1;
      int direction=rand() % ++directions;
      if(direction==0)    m_direction=1;
      if(direction==1)    m_direction=-1;
 //     qDebug()<<"dierctio"<<direction;
         tuxOb->setDirection(direction+1);

         int ts=10000;
           int randts=rand() % ++ts;
           int sht=randts+10000;


       switch (type) {
       case 0:

           tuxOb->setPixmap(QPixmap(":/tux/basher.png"));
           tuxOb->setDirectionNum(2);
           tuxOb->setframeNum(12);
           m_spid=m_direction;
              QTimer::singleShot(sht, this, SLOT(updateWaiterAnnimtion()));
           timer->start(100);
           break;
       case 1:
           tuxOb->setPixmap(QPixmap(":/tux/boarder.png"));
           tuxOb->setDirectionNum(2);
           tuxOb->setframeNum(1);
           m_isSlider=true;
           if(m_direction==-1){
           m_spid=-5;
             }else{
                m_spid=5;
           }
               QTimer::singleShot(5000, this, SLOT(updateWaiterAnnimtion()));
           timer->start(50);
           break;
       case 2:
           tuxOb->setPixmap(QPixmap(":/tux/bridger.png"));
           tuxOb->setDirectionNum(2);
           tuxOb->setframeNum(15);
           m_spid=m_direction;
              QTimer::singleShot(sht, this, SLOT(updateWaiterAnnimtion()));


           timer->start(400);
           break;
       case 3:
             timer->stop();
           tuxOb->setPixmap(QPixmap(":/tux/digger.png"));
           tuxOb->setDirectionNum(1);
           tuxOb->setframeNum(14);
           m_moveTux=false;
   QTimer::singleShot(sht, this, SLOT(updateWaiterAnnimtion()));
           break;
       case 4:
           tuxOb->setPixmap(QPixmap(":/tux/miner.png"));
           tuxOb->setDirectionNum(2);
           tuxOb->setframeNum(12);
            m_spid=m_direction;
               QTimer::singleShot(sht, this, SLOT(updateWaiterAnnimtion()));
              timer->start(300);
           break;
       case 5:
             timer->stop();
           tuxOb->setPixmap(QPixmap(":/tux/reader.png"));
           tuxOb->setDirectionNum(1);
           tuxOb->setframeNum(12);
            m_spid=m_direction;
           m_moveTux=false;
              QTimer::singleShot(3000, this, SLOT(updateWaiterAnnimtion()));
           break;
       case 6:
           tuxOb->setPixmap(QPixmap(":/tux/slider.png"));
           tuxOb->setDirectionNum(2);
           tuxOb->setframeNum(1);
         m_isSlider=true;
           if(m_direction==-1){
           m_spid=-5;
             }else{
                m_spid=5;
           }
               QTimer::singleShot(5000, this, SLOT(updateWaiterAnnimtion()));
           timer->start(50);
           break;
       case 7:
           tuxOb->setPixmap(QPixmap(":/tux/walker.png"));
           tuxOb->setDirectionNum(2);
           tuxOb->setframeNum(8);
           if(m_direction==-1){
           m_spid=-3;
             }else{
                m_spid=3;
           }
           QTimer::singleShot(sht, this, SLOT(updateWaiterAnnimtion()));
              timer->start(100);
           break;
       case 8:
           timer->stop();
           updateClimberAnnimtion();
               QTimer::singleShot(1000, this, SLOT(updateWaiterAnnimtion()));

           break;
       default:
           break ;
       }


}

void Penguin::updateTime()
{
    int x=m_direction+tuxOb->pos().x()+ m_spid;
    int y=botScreen-tuxOb->height();
    int w=tuxOb->width();

    tuxOb->move(x,y);


    if (x+w>=rightScreen){
      tuxOb->move(rightScreen-w,y);
        timer->stop();
        tuxOb->setPixmap(QPixmap(":/tux/climber.png"));
        tuxOb->setDirection(1);
        tuxOb->setDirectionNum(2);
        tuxOb->setframeNum(8);
    //  QTimer::singleShot(5000, this, SLOT(randomAnnimation()));
        m_isRandom=false;
        if(m_isSlider==true){
            m_isSlider=false;
            bomberAnimation();
        }else{
            timerClimber->start(100);

        }

    }
    if (x<=leftScreen){
        timer->stop();
        tuxOb->move(leftScreen,y);
        tuxOb->setPixmap(QPixmap(":/tux/climber.png"));
        tuxOb->setDirection(2);
        tuxOb->setDirectionNum(2);
        tuxOb->setframeNum(8);
    // QTimer::singleShot(5000, this, SLOT(randomAnnimation()));

        m_isRandom=false;
        if(m_isSlider==true){
             m_isSlider=false;
            bomberAnimation();
        }else{
            timerClimber->start(100);

        }
    }
}

void Penguin::updateClimberAnnimtion()
{
    int x=tuxOb->pos().x();
    int y=tuxOb->pos().y();
    //int w=tuxOb->width();
    tuxOb->move(x,y-2);
    if(y<=topScreen){
        timerClimber->stop();
        tambleAnnimation();
    }
}



void Penguin::deletAll()
 {
stopAllAnimation();

          tuxOb->deleteLater();
     tuxOb->close();

 }
