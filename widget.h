#ifndef WIDGET_H
#define WIDGET_H
#include "snowwid.h"
#include "rain.h"
#include "autumn.h"
#include "etoile.h"
#include "fanous.h"
#include "butterfly.h"
#include "penguin.h"
#include <QWidget>
#include <QDesktopWidget>
#include <QModelIndex>
#include <QAbstractButton>
#include <QSystemTrayIcon>

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void setTheme(int theme);
   void startCurentTheme();
   void restoreDefault();
protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);

signals:
    void runing();

private:
    Ui::Widget *ui;

    snowwid *Snowwid;
    rain *Rain;
    autumn *Autumn;
    etoile *Etoile;
    fanous *Fanous;

    butterfly *Butterfly;
    enum {num=10};
 Penguin *Tux[num];
    bool isTuxActive;
   int tuxNum;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *startStopAction;
    QAction *restoreAction;
    QAction *updatAnimation;
    QAction *quitAction;
    QAction *onTopAction;
    QAction *snowAction;
    QAction *autumnAction;
    QAction *rainAction;
    QAction *starsAction;
     QAction *butterflyAction;
       QAction *tuxAction;
    bool isRuning;
    int curTheme;
    QString curThemeStr;
private slots:



    void on_buttonBox_clicked(QAbstractButton* button);


    void on_fanosToolButton_clicked();




void actveTheme(bool );

    void startSnow();
    void startAutumn();
    void startStars();
    void startRain();
    void startFanous();
    void startButterfly();
void  startTux();
    void startStopAnimation();

    void animationisActive();


    void loadSetting();
    void saveSetting();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_listWidget_currentRowChanged(int );
    void on_listWidget_activated(const QModelIndex &index);
};

#endif // WIDGET_H
