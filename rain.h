#ifndef RAIN_H
#define RAIN_H
#include "object.h"
#include <QWidget>
#include <QPropertyAnimation>
#include<QTimer>
#include<QDesktopWidget>
class rain : public QWidget {
    Q_OBJECT
public:
    rain(QWidget *parent = 0);

QTimer *timer;
//QTimer *timer2;
//QTimer *timer3;


protected:


private:
int duration;
int objectsCount;
bool cloudVisible;
bool onTop;
   // enum {num=20};
   // QPropertyAnimation * anim;
 QDesktopWidget *wid;
   // Object *cloud[num];
  QList<Object *> listObject;
   QList<int > lisTspeed;
    int leftpos;

    Object *  cloud ;
private slots:
   void updateTime();

public slots:
   void starNew();
   void deletAll();
   void setCloudVisible(bool visible);
   void setRainNember(int num);
   void setRainOnTop(bool top);
   void setRainDuration(int dr);

};

#endif // RAIN_H
