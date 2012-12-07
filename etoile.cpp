
#include "etoile.h"
#include <QDesktopWidget>
#include <QVariant>
#include <QMessageBox>
 #include <QDebug>
 #include <QParallelAnimationGroup>
etoile::etoile(QWidget *parent) :
    QWidget(parent)

{
    timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(runEtoile()));
    minSize=3;
    maxSize=15;
    numStars=25;
    rotatI=0;
}

void etoile::setStarSize(int max,int min)
{
    maxSize=max;
     minSize=min;
}

void etoile::setStarNember(int num)
{
    numStars=num;
}

void etoile::setStarOnTop(bool top)
{
    onTop=top;
}

void etoile::startNew()
{

   // numStars=50;
    QDesktopWidget wid;
    m_w=wid.availableGeometry(this).right();
    m_h=wid.availableGeometry(this).bottom()/2;
    for(int i=0;i<numStars;i++){
        int size=maxSize;
        int minsise=minSize;
        int rndsize=rand() % ++size;
        int rnw=m_w;
        int rndX=rand() % ++rnw;
        int rnh=m_h;
        int rndy=rand() % ++rnh;

        star[i]=new  Object();
        if(onTop==true){
            star[i]->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
        }else{
            star[i]->setWindowFlags(Qt::WindowStaysOnBottomHint|Qt::FramelessWindowHint|Qt::WindowType_Mask);
        }

        star[i]->setGeometry(rndX,rndy,rndsize+minsise,rndsize+minsise);
        star[i]->setPixmap(QPixmap(":/reflet.png"));
        int o=9;
        int rndo=rand() % ++o;
        float flt=rndo;
        float b=10;
        float ff=flt/b;

        // QMessageBox::information(0,"",ff.toString());
        star[i]->setWindowOpacity(ff);
        star[i]->show();

    }
    timer->start(1000);
    qDebug() << "Animation stars is Runing:"<< "Number :"+QString::number(numStars);
}

void etoile::updateTime()
{


    int i=numStars-1;
    int rndI=rand() % ++i;
    starIndex=rndI;
    opacyt=1.0;
    iop=0.1;
    int size=maxSize;
    int minsise=minSize;
    int rndsize=rand() % ++size;
    int rnw=m_w;
    int rndX=rand() % ++rnw;
    int rnh=m_h;
    int rndy=rand() % ++rnh;
    for (int r=0;r<3;r++){
         int i=numStars-1;
        int rndr=rand() % ++i;
        star[rndr]->setWindowOpacity(0.7);
    }

    star[starIndex]->setWindowOpacity(0.9);
    star[starIndex]->setGeometry(rndX,rndy,rndsize+minsise,rndsize+minsise);
  //  qDebug() << "x:"+QString::number(rndX)<< "y :"+QString::number(rndy)<< "w :"+QString::number(rndsize+minsise)<< "h :"+QString::number(rndsize+minsise);


    int p=15;
    int rndp=rand() % ++p;
    if (rndp==5){
        flashIndex=starIndex;
     runFlash();
 }else{
     timer2->start(100);
 }

    //
}
void etoile::runEtoile()
{
       QPixmap pix(":/reflet.png");
         rotatI=rotatI+10;
         if(rotatI>=180){
            rotatI=0;

         }
        QTransform trans;
        trans.rotate(rotatI);
    
        star[starIndex]->setPixmap(pix.transformed(trans));
 opacyt=opacyt-iop;
 star[starIndex]->setWindowOpacity(opacyt);
    if (opacyt==0.1){
//        int o=9;
//        int rndo=rand() % ++o;
//        float flt=rndo;
//        float b=10;
//        float ff=flt/b;
//        if (ff==0)ff=0.5;
//        star[starIndex]->setWindowOpacity(ff);
 timer2->stop();
    }
// star[starIndex]->windowOpacity()

}
void etoile::runFlash()
{


    int i=m_w;
    int rndI=rand() % ++i;
    QParallelAnimationGroup *group = new QParallelAnimationGroup;
     connect(group, SIGNAL(finished()), this, SLOT(flashPos()));
    QPropertyAnimation * anim = new QPropertyAnimation(star[flashIndex], "pos");
    QPropertyAnimation * anim2 = new QPropertyAnimation(star[flashIndex], "windowOpacity");

    anim->setEasingCurve(QEasingCurve::InQuad);
    anim->setEndValue(QPointF(rndI,m_h*2));
    anim->setDuration(750);

   anim2->setStartValue(qreal(1.0));
    anim2->setEndValue(qreal(0.0));
    anim2->setDuration(750);
    group->addAnimation( anim);
    group->addAnimation( anim2);

    group->start();
   // qDebug() << "anim started:"+QString::number(flashIndex);
}
void etoile::flashPos()
{

    int size=maxSize;
    int minsise=minSize;
    int rndsize=rand() % ++size;
    int rnw=m_w;
    int rndX=rand() % ++rnw;
    int rnh=m_h;
    int rndy=rand() % ++rnh;
    star[flashIndex]->setGeometry(rndX,rndy,rndsize+minsise,rndsize+minsise);
}

void etoile::deletAll()
{

    timer->stop();
    timer2->stop();
    for (int i=0;i<numStars;i++){

        star[i]->deleteLater();
        star[i]->close();

    }

}
