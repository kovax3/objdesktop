#ifndef AUTUMN_H
#define AUTUMN_H
#include <QWidget>
#include <QTimer>
#include <QDesktopWidget>

#include "object.h"
class autumn : public QWidget {
    Q_OBJECT
public:
    autumn(QWidget *parent = 0);

    QTimer *timer;


protected:

private:
int oldNum;
int maxSize,minSize;
int numAutumn;
bool onTop;
    int topScreen;
    int botScreen;
    int leftScreen;
    int rightScreen;
   QList<QString> listpix;
   // QPixmap pix;
   // QDesktopWidget *wid;
    enum {num=100};
   // QLabel *autume[num];
    Object *object[num];
    int dx[num], xp[num],npos[num];
    int rota[num];
private slots:
    void updateTime();

public slots:
    void updat();
    void deletAll();
    void setAutumnSize(int max,int min);
    void setAutumnNember(int num);
    void setAutumnOnTop(bool top);
};

#endif // AUTUMN_H
