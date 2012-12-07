#include "rain.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QApplication>
 #include <QDebug>
 #include <QBitmap>
 #include <QLabel>

         #include <QHBoxLayout>
rain::rain(QWidget *parent) :
    QWidget(parent)

{
 timer = new QTimer();
 cloud = new Object;

 cloud->setGeometry(leftpos-50,0,650,100);
 cloud->setPixmap(QPixmap(":/cloud2.png"));
       duration=50;//defaut animation duration
       objectsCount=35; //defaut number objects
       cloudVisible=true;//defaut
       connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

}
void rain::setCloudVisible(bool visible)
{
    cloudVisible=visible;
         cloud->setVisible(visible);
}

void rain::setRainNember(int num)
{

   objectsCount=num;

}
   void rain::setRainDuration(int dr)
   {
      duration=dr;
   }

void rain::setRainOnTop(bool top)
{
    onTop=top;
}

void rain::starNew()
{

    wid=new QDesktopWidget ;
    int w=wid->availableGeometry(this).right();
    leftpos=(w/2)-300;

    QPixmap pix(":/drop-l.png");

    int posx=600/objectsCount;
    for (int i=0;i<objectsCount;i++){
        int w=5;
        int dw=rand() % ++w;
        int t=500;
        int rndT=rand() % ++t;

        Object  *cloudRain= new Object;
        if(onTop==true){
            cloudRain->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
        }else{
            cloudRain->setWindowFlags(Qt::WindowStaysOnBottomHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
        }
cloudRain->setAttribute(Qt::WA_X11NetWmWindowTypeDock);
        cloudRain->setGeometry(i*posx+leftpos,rndT+10,dw+3,15);
        cloudRain->setPixmap(pix);
       listObject.append(cloudRain);

       int s=15;
        int sp=rand() % ++s;
       lisTspeed.append(sp);

        cloudRain->show();
    }
    if (cloudVisible==true){
           cloud->setVisible(true);

 //   cloud->setMask(QRegion(this->rect()));

        cloud->show();
    }else{
           cloud->setVisible(false);
    }
    timer->start(duration);
       qDebug() << "Animation Autumn is Rain:"<< "Number :"+QString::number(objectsCount)+" timeInterval:"+QString::number(duration);
//    timer2->start(duration-20);
//    timer3->start(duration-30);
    //  QMessageBox::information(0,"",QString::number(listAnimation.count()));
}


void rain::updateTime()
{
    if (cloudVisible==true){

  cloud->move(leftpos-50,10);

    }
    for (int i=0;i<objectsCount;i++){
        int x=listObject.at(i)->pos().x();
        int y=listObject.at(i)->pos().y();
        int b=10;
        int dy=rand() % ++b;
        int speed=lisTspeed.at(i)+7;
        listObject.at(i)->move(x,y+speed);
        if (y>=590){
            lisTspeed.takeAt(i);
            lisTspeed.insert(i,dy);
            y=10;
            int w=5;
            int dw=rand() % ++w;
            listObject.at(i)->resize(dw+3,15);
             int posx=600/objectsCount;
           listObject.at(i)-> move(i*posx+leftpos,10);

        }



    }
}
void rain::deletAll()
{
    timer->stop();
    for (int i=0;i<objectsCount;i++){


     //   listObject.at(i)->deleteLater();
     listObject.at(i)->close();
        //  listW.takeAt(i);

    }
    listObject.clear();
lisTspeed.clear();
    if (cloudVisible==true){
 // cloud->deleteLater();
        cloud->setVisible(false);

    }

}
