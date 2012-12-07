#ifndef FANOUS_H
#define FANOUS_H
#include <QWidget>
#include <QTimer>


class fanous : public QWidget {
    Q_OBJECT
public:
    fanous(QWidget *parent = 0);
  QTimer *timer;
int xpos;
int ypos;
int interval;
signals:
void isPressed();
void isReleased();

protected:
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *t);
    void mousePressEvent ( QMouseEvent * ) ;
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent ( QMouseEvent * event ) ;
private:
    bool b;
    int wx;
    int wy;
    int direction;
    QPixmap pix;
    int numFrame;
    int directionNum;
    int curFrame;
public slots:
    void setPixmap(QPixmap pix);
    void setframeNum(int  num);
     void setDirectionNum(int  num);
    void setInterval(int  value);
    void setDirection(int val);

private slots:
    void  updateTime();
};
#endif // FANOUS_H
