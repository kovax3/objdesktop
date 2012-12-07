#ifndef BUTTERFLY_H
#define BUTTERFLY_H
#include <QWidget>
#include <QTimer>
#include "fanous.h"
class butterfly : public QWidget {
    Q_OBJECT
public:
    butterfly(QWidget *parent = 0);
    QTimer *timer;


    private:
   int chipNum;
   bool onTop;
    int topScreen;
    int botScreen;
    int leftScreen;
    int rightScreen;
    enum {num=10};
    fanous *chip[num];
     int dx[num],dy[num], xpos[num],ypos[num];
int oldNum;

private slots:
    void updateTime();

public slots:
void startButterfly();
void deletAll();
void setButterflyNember(int num);
void setButterflyOnTop(bool top);
};
#endif // BUTTERFLY_H
