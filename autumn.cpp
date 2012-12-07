
#include "autumn.h"
#include <QWidget>
 #include <QDesktopWidget>
#include <QTimer>
#include <QApplication>
#include <QMessageBox>
//#include <QtGui>
 #include <QDebug>
autumn::autumn(QWidget *parent) :
    QWidget(parent)

{
    timer = new QTimer();
//timer2 = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
     //connect(timer2, SIGNAL(timeout()), this, SLOT(updateTime2()));
    //wid=new QDesktopWidget();

listpix.append(":/autumn1.png");
listpix.append(":/autumn2.png");
listpix.append(":/autumn3.png");
}
void autumn::setAutumnSize(int max,int min)
{
     maxSize=max;
      minSize=min;
}

void autumn::setAutumnNember(int num)
{
    numAutumn=num;
}

void autumn::setAutumnOnTop(bool top)
{
    onTop=top;
}
void  autumn::updat()
{
    QDesktopWidget *wid=new QDesktopWidget();
    topScreen=wid->availableGeometry(this).top();
    botScreen=wid->availableGeometry(this).bottom();
    leftScreen=wid->availableGeometry(this).left();
    rightScreen=wid->availableGeometry(this).right();
    // QString sst="background-color: rgba(255, 255, 255, 0);";


    bool mv=true;
    for (int i=0;i<numAutumn;i++){
        int p=listpix.count()-1;
        int pat=rand() % ++p;
        QString setpix=listpix.at(pat);
        QPixmap pix(setpix);

        int size=maxSize;
        int minsise=minSize;
        int rndsize=rand() % ++size;
        int rnd=rightScreen;
        int rndX=rand() % ++rnd;
        int rny=botScreen;
        int rndy=rand() % ++rny;
        int k=300;
        dx[i]=rand() % ++k;
        xp[i]=3;
        //   autume[i]=new QLabel();
        object[i]=new Object();
        if(onTop==true){
             object[i]->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
        }else{
            object[i]->setWindowFlags(Qt::WindowStaysOnBottomHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
        }
   object[i]->setAttribute(Qt::WA_X11NetWmWindowTypeDock);
        int rt=360;
        int rot=rand() % ++rt;

        rota[i]=rot;

        QTransform trans;
        trans.rotate(rota[i]);

        object[i]->setGeometry(rndX,rndy,rndsize+minsise,rndsize+minsise);

        object[i]->setPixmap(pix.transformed(trans));


        object[i]->show();

        if(mv==true){
            mv=false;
            npos[i]=1;
        }else{
            npos[i]=-1;
            mv=true;
        }


    }
  oldNum=numAutumn;
    timer->start();
    qDebug() << "Animation Autumn is Runing:"<< "Number :"+QString::number(numAutumn)+" timeInterval:"+QString::number(timer->interval());
    //timer2->start(50);
}
 void autumn::deletAll()
 {
     timer->stop();
    // timer2->stop();
         for (int i=0;i<oldNum;i++){
             object[i]->deleteLater();
             object[i]->close();
         }

 }

void  autumn::updateTime()
{

    for (int i=0;i<numAutumn;i++){
        qApp->processEvents();
        dx[i]++;
        int k=200;
        int low=rand() % ++k;
        if( dx[i]>=low+150){
            dx[i]=rand() % ++k;
            xp[i]=-xp[i];
        }
        int x=object[i]->pos().x();
        int y=object[i]->pos().y();


        if (x<=leftScreen){
            object[i]->move(rightScreen-2,y);
            xp[i]=-3;
            return;
        }
        if (x>=rightScreen){
            object[i]->move(leftScreen+2,y);
            xp[i]=3;
            return;
        }
        if (y<=topScreen){
            // QMessageBox::information(0,"",QString::number(autume[i]->pos().y()));
              object[i]->move(x,botScreen-object[i]->height()-2);
            npos[i]=1;
           //  return;
        }
        if (y>=botScreen){
             object[i]->move(x,topScreen-object[i]->height());
            npos[i]=1;
          return;
        }
        object[i]->move(x+xp[i],y+npos[i]);



    }

}

