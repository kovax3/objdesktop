
#include "butterfly.h"
#include <QDesktopWidget>
#include <QDebug>
butterfly::butterfly(QWidget *parent) :
    QWidget(parent)

{

 timer=new QTimer;
  connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
 //chipNum=5;

}
void butterfly::setButterflyNember(int num)
{
    chipNum=num;
}
 void butterfly::setButterflyOnTop(bool top)
 {
     onTop=top;
 }

void butterfly::startButterfly()

{


    QDesktopWidget *wid=new QDesktopWidget();
    topScreen=wid->availableGeometry(this).top();
    botScreen=wid->availableGeometry(this).bottom();
    leftScreen=wid->availableGeometry(this).left();
    rightScreen=wid->availableGeometry(this).right();

    bool setpix=true;
    for(int i=0;i<chipNum;i++){
       chip[i]=new fanous;
       if(onTop==true){
           chip[i]->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
       }else{
           chip[i]->setWindowFlags(Qt::WindowStaysOnBottomHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
       }
        QPixmap pix;
        if(setpix==true){
          pix.load(":/butterfly_1.png");
         // chip[i]->setPixmap(QPixmap(":/butterfly_1.png"));
          setpix=false;

        }else{
          pix.load(":/butterfly_2.png");
          //   chip[i]->setPixmap(QPixmap(":/butterfly_2.png"));
             setpix=true;

        }

chip[i]->setPixmap(pix);
        chip[i]->setframeNum(30);

       
        int x=rand() % ++rightScreen;
        int y=rand() % ++botScreen;
        chip[i]->move(x,y);
       
        chip[i]->setInterval(50);
        chip[i]->setEnabled(false);
        chip[i]->show();

        int k=300;
        dx[i]=rand() % ++k;
        dy[i]=rand() % ++k;
        xpos[i]=3;
        ypos[i]=3;
    }
    oldNum=chipNum;
    timer->start(100);

}


void butterfly::updateTime()
 {


   for (int i=0;i<chipNum;i++){

        dx[i]++;
         dy[i]++;
        int k=200;
        int low=rand() % ++k;
        if( dx[i]>=low+150){
            dx[i]=rand() % ++k;
            xpos[i]=-xpos[i];
        }
        if( dy[i]>=low+100){
            dy[i]=rand() % ++k;
            ypos[i]=-ypos[i];
        }
        if(ypos[i]==-3 && xpos[i]==-3){
            chip[i]->setInterval(200);
            timer->setInterval(50);
        }else{
            chip[i]->setInterval(50);
            timer->setInterval(100);
        }
        int x= chip[i]->pos().x();
        int y= chip[i]->pos().y();


        if (x<=leftScreen-5){
         //  chip[i]->move(rightScreen+2,y);

            xpos[i]=3;
        //   return;
        }
        if (x>=rightScreen-chip[i]->width()){
          //  chip[i]->move(leftScreen+2,y);
            xpos[i]=-3;
          //return;
        }
        if (y<=topScreen){
            // QMessageBox::information(0,"",QString::number(autume[i]->pos().y()));
            //   chip[i]->move(x,botScreen- chip[i]->height()-2);
            ypos[i]=3;
            // return;
        }
        if (y>=botScreen- chip[i]->height()){
            //  chip[i]->move(x,topScreen+2);
            ypos[i]=-3;
            //return;
        }
         chip[i]->move(x+xpos[i],y+ypos[i]);



   }


 }
void butterfly::deletAll()
{
    timer->stop();
   // timer2->stop();
        for (int i=0;i<oldNum;i++){
            chip[i]->deleteLater();
            chip[i]->close();
        }

}
