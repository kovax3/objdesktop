#ifndef SNOWWID_H
#define SNOWWID_H
#include <QWidget>
#include <QTimer>
#include "object.h"
#include <QDesktopWidget>


class snowwid : public QWidget {
    Q_OBJECT
public:
    snowwid(QWidget *parent = 0);
     QTimer *timer;

private:

    QDesktopWidget *wid;
       enum {num=100};
     Object *snow[num];
    int dx[num], xp[num];
    int maxSize,minSize;
    int numSnow;
    bool onTop;
    int topScreen;
    int botScreen;
    int leftScreen;
    int rightScreen;
 int oldNum;
private slots:

    void updateTime();


public slots:
    void updat();
    void deletAll();
    void setSnowSize(int max,int min);
    void setSnowNember(int num);
    void setSnowOnTop(bool top);

};
#endif // SNOWWID_H
