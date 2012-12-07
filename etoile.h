#ifndef ETOILE_H
#define ETOILE_H
#include "object.h"
#include <QPropertyAnimation>
#include <QWidget>

#include<QTimer>
class etoile : public QWidget {
    Q_OBJECT
public:
    etoile(QWidget *parent = 0);

QTimer *timer;
QTimer *timer2;


protected:

public slots:
void startNew();
void deletAll();
void setStarSize(int max,int min);
void setStarNember(int num);
void setStarOnTop(bool top);

private:
bool onTop;
int maxSize,minSize;
int numStars;

int m_h;
int m_w;
int rotatI;
int starIndex;
int flashIndex;
qreal opacyt;
qreal iop;
    enum {num=100};

    Object *star[num];
    int leftpos;


private slots:
   void updateTime();
    void runEtoile();
    void runFlash();
    void flashPos();
};
#endif // ETOILE_H
