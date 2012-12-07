#ifndef PENGUIN_H
#define PENGUIN_H
#include "fanous.h"
#include <QWidget>
#include <QTimer>
class Penguin : public QWidget
{
    Q_OBJECT
public:
    explicit Penguin(QWidget *parent = 0);
bool onTop;
  protected:

  private:
QTimer *timer;
QTimer *timerTambler;

QTimer *timerClimber;
int m_spid;
bool m_moveTux;
bool m_isRandom;
bool m_isSlider;
int m_direction;
    fanous *tuxOb;

//int TuxNum;
// int oldNum;
 int topScreen;
 int botScreen;
 int leftScreen;
 int rightScreen;
  public slots:
    void startTux();
     void updatePosition();
    void deletAll();

    void setTuxOnTop(bool top);
  private slots:
    void stopAllAnimation();
void tambleAnnimation();
void updateTimeTambler();
void updateTime();
void updateClimberAnnimtion();
void updateWaiterAnnimtion();
void bomberAnimation();
void randomAnnimation();
};

#endif // PENGUIN_H
