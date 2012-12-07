#include "snowwid.h"
#include <QWidget>
 #include <QDesktopWidget>
#include <QTimer>
#include <QApplication>
 #include <QDebug>

snowwid::snowwid(QWidget *parent) :
    QWidget(parent)
{

    timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    wid=new QDesktopWidget();

}
void snowwid::setSnowSize(int max,int min)
{
     maxSize=max;
      minSize=min;
}

void snowwid::setSnowNember(int num)
{
    numSnow=num;
}

void snowwid::setSnowOnTop(bool top)
{
    onTop=top;
}

void  snowwid::updat()
{

     topScreen=wid->availableGeometry(this).top();
     botScreen=wid->availableGeometry(this).bottom();
     leftScreen=wid->availableGeometry(this).left();
     rightScreen=wid->availableGeometry(this).right();


    QPixmap pix(":/snowflake.png");

    for (int i=0;i<numSnow;i++){
        int size=maxSize;
        int minsise=minSize;
        int rndsize=rand() % ++size;
        int rnd=rightScreen;
        int rndX=rand() % ++rnd;
        int rny=botScreen;
        int rndy=rand() % ++rny;
        int k=300;
        dx[i]=rand() % ++k;
        xp[i]=2;
        snow[i]=new  Object;
        if(onTop==true){
            snow[i]->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
        }else{
            snow[i]->setWindowFlags(Qt::WindowStaysOnBottomHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
        }
 snow[i]->setAttribute(Qt::WA_X11NetWmWindowTypeDock);
        snow[i]->setGeometry(rndX,rndy,rndsize+minsise,rndsize+minsise);
        snow[i]->setPixmap(pix);

        snow[i]->show();


    }
 oldNum=numSnow;
timer->start();
  qDebug() << "Animation Autumn is Snow:"<< "Number :"+QString::number(numSnow)+" timeInterval:"+QString::number(timer->interval());
}
 void snowwid::deletAll()
 {
     timer->stop();
         for (int i=0;i<oldNum;i++){
             snow[i]->deleteLater();
             snow[i]->close();

         }

 }

void  snowwid::updateTime()
{

    int rnx=rightScreen-25;
    int rnw=2;

    for (int i=0;i<numSnow;i++){
         qApp->processEvents();
        dx[i]++;
        int k=100;
        int low=rand() % ++k;
        if( dx[i]>=low+100){

            dx[i]=rand() % ++k;
           xp[i]=-xp[i];
        }

        int xx=rand() % ++rnw;
        int xy=rand() % ++rnw;
         int rndw=xx-xy;
         if(rndw==0)rndw=1;
        int rndX=rand() % ++rnx;
        if (snow[i]->pos().x()<=leftScreen-snow[i]->width()){
           xp[i]=2;
         //   xp[i]= rightScreen-snow[i]->width()-2;
        }
        if (snow[i]->pos().x()>=rightScreen){
          xp[i]=-2;

        }
        if (snow[i]->pos().y()>=botScreen-snow[i]->height()){
            int size=maxSize;
            int minsise=minSize;
            int rndsize=rand() % ++size;
            snow[i]->setGeometry(rndX,topScreen,rndsize+minsise,rndsize+minsise);
        }else{
            snow[i]->move(snow[i]->pos().x()+xp[i],snow[i]->pos().y()+2);
        }
    }

}
