#include "widget.h"
#include "ui_widget.h"
#include <QDesktopWidget>
#include <QTimer>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include <QFileDialog>
#include <QPainter>
#include <QSettings>
#include <QDir>
#include <QProcess>
 #include <QDebug>
Widget::Widget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Widget)
{

    ui->setupUi(this);
    ui->listWidget->setViewMode(QListView::IconMode);
        ui->listWidget->setIconSize(QSize(64, 64));
        ui->listWidget->setMovement(QListView::Static);
        ui->listWidget->setMaximumWidth(128);
        ui->listWidget->setSpacing(12);
    Snowwid=new snowwid;
    Rain=new rain;
    Autumn=new autumn;
    Etoile=new etoile;
    Fanous=new fanous;
     Butterfly=new butterfly;
isTuxActive=false;
 QPixmap p(style()->standardPixmap(QStyle::SP_BrowserReload));
//    ui->pushButtonUpdate->setIcon(QIcon(p));

    ////----------------
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    startStopAction = new QAction(tr("&Stop"), this);

    connect(startStopAction, SIGNAL(triggered()), this, SLOT(startStopAnimation()));
    connect(this, SIGNAL(runing()), this, SLOT(animationisActive()));
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
onTopAction=new QAction(tr("&On top"), this);
onTopAction->setCheckable(true);
connect(onTopAction, SIGNAL(toggled(bool)), ui->checkBoxOnTop, SLOT(setChecked(bool)));
connect( ui->checkBoxOnTop, SIGNAL(toggled(bool)), onTopAction, SLOT(setChecked(bool)));
connect(onTopAction, SIGNAL(toggled(bool)), this, SLOT(startCurentTheme()));
    snowAction = new QAction(QIcon(QPixmap(":/snowicon.png")),tr("&Snow"), this);
    autumnAction= new QAction(QIcon(QPixmap(":/autuIcon.png")),tr("&Autumn"), this);
    rainAction= new QAction(QIcon(QPixmap(":/rain.png")),tr("&Rain"), this);
    starsAction= new QAction(QIcon(QPixmap(":/starIcon.png")),tr("&Stars"), this);
    butterflyAction= new QAction(QIcon(QPixmap(":/papillon_2.png")),tr("&Butterfly"), this);
     tuxAction= new QAction(QIcon(QPixmap(":/tuxicon.png")),tr("&Tux"), this);
    updatAnimation= new QAction(QIcon(p),tr("&Update"), this);

    QActionGroup *gp=new QActionGroup(this);
    snowAction->setActionGroup(gp);
    autumnAction->setActionGroup(gp);
    rainAction->setActionGroup(gp);
    starsAction->setActionGroup(gp);
    butterflyAction->setActionGroup(gp);
 tuxAction->setActionGroup(gp);

    snowAction->setCheckable(true);
    autumnAction->setCheckable(true);
    rainAction->setCheckable(true);
    starsAction->setCheckable(true);
    butterflyAction->setCheckable(true);
   tuxAction->setCheckable(true);

   connect(snowAction, SIGNAL(toggled(bool)), this, SLOT(actveTheme(bool)));
   connect(autumnAction, SIGNAL(toggled(bool)), this, SLOT(actveTheme(bool)));
   connect(rainAction, SIGNAL(toggled(bool)), this, SLOT(actveTheme(bool)));
   connect(starsAction, SIGNAL(toggled(bool)), this, SLOT(actveTheme(bool)));
   connect(butterflyAction, SIGNAL(toggled(bool)), this, SLOT(actveTheme(bool)));
    connect(tuxAction, SIGNAL(toggled(bool)), this, SLOT(actveTheme(bool)));
    connect(updatAnimation, SIGNAL(triggered()), this, SLOT( startCurentTheme()));
QMenu *menuGroup= new QMenu(trUtf8("Effect"),this);
menuGroup->addAction(snowAction);
menuGroup->addAction(rainAction);
menuGroup->addAction(autumnAction);
menuGroup->addAction(starsAction);
menuGroup->addAction(butterflyAction);
menuGroup->addAction(tuxAction);
   trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(updatAnimation);
    trayIconMenu->addSeparator();
    trayIconMenu->addMenu(menuGroup);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(startStopAction);
     trayIconMenu->addAction(onTopAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QPixmap(":/snowicon48.png"));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    loadSetting();


   // const QStringList args = QCoreApplication::arguments();

//    if (args.count() == 2){
//     QString   temeIndex = args.at(1);
//      qDebug() << "temeIndex:"<< temeIndex;
//        if (temeIndex=="0" || temeIndex=="-s")curTheme=0;
//        if (temeIndex=="1" || temeIndex=="-r")curTheme=1;
//        if (temeIndex=="2" || temeIndex=="-a" )curTheme=2;
//        if (temeIndex=="3" || temeIndex=="-t")curTheme=3;
//        if (temeIndex=="4" || temeIndex=="-b")curTheme=4;
//    }
    qDebug() << "curTheme:"<< curThemeStr;

    startCurentTheme();
    trayIcon->show();

}

Widget::~Widget()
{
    saveSetting();

      qDebug() << "close app ";
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    if(QLocale::system().language()==QLocale::Arabic){
       this->setLayoutDirection(Qt::RightToLeft);
         qApp->setLayoutDirection(Qt::RightToLeft);
    }

    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::WinIdChange:

        break;
    default:
        break;
    }
}
void Widget::closeEvent(QCloseEvent *event)
{
    hide();

    event->ignore();
}
void Widget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        startCurentTheme();
         break;
    case QSystemTrayIcon::DoubleClick:
        this->showNormal();
        break;
    case QSystemTrayIcon::MiddleClick:
        //showMessage();
        break;
    default:
        ;
    }
}



void  Widget::startSnow()
{
    if( Snowwid->timer->isActive()){
        Snowwid->deletAll();
    }

    Snowwid->setSnowSize(ui->spinBoxMaxSize->value(),ui->spinBoxMinSize->value());

    Snowwid->timer->setInterval(ui->spinBox->value());
    Snowwid->setSnowNember(ui->spinBoxNum->value());
    Snowwid->setSnowOnTop(ui->checkBoxOnTop->checkState());
        Snowwid->updat();


    emit runing();
}

void  Widget::startRain()
{
    if( Rain->timer->isActive()){
        Rain->deletAll();
    }

    //Rain->maxSize=ui->spinBoxMaxSizeRain->value();
    //Rain->minSize=ui->spinBoxMinSizeRain->value();
    Rain->setRainDuration(ui->spinBoxTimeRain->value());
    Rain->setRainNember(ui->spinBoxNumRain->value());
    Rain->setCloudVisible(ui->checkBoxClodRain->checkState());
    Rain->setRainOnTop(ui->checkBoxOnTop->checkState());
        Rain->starNew();
    //}

    emit runing();
}

void  Widget::startAutumn()
{
    if( Autumn->timer->isActive()){
        Autumn->deletAll();
    }

    Autumn->setAutumnSize(ui->spinBoxMaxSizeAutumn->value(),ui->spinBoxMinSizeAutumn->value());
    Autumn->timer->setInterval(ui->spinBoxTimeAutumn->value());
    Autumn->setAutumnNember(ui->spinBoxNumAutumn->value());
    Autumn->setAutumnOnTop(ui->checkBoxOnTop->checkState());
    // if(ui->radioButtonAutumn->isChecked()){
    Autumn->updat();
    //}

    emit runing();
}

void  Widget::startStars()
{
    if( Etoile->timer->isActive()){
        Etoile->deletAll();
        Fanous->timer->stop();
        Fanous->setVisible(false);
    }

    Etoile->setStarSize(ui->spinBoxMaxSizeEtoile->value(),ui->spinBoxMinSizeEtoile->value());
    Etoile->setStarNember(ui->spinBoxNumEtoile->value());
Etoile->setStarOnTop(ui->checkBoxOnTop->checkState());
        Etoile->startNew();
    startFanous();
   // }

   emit runing();
}

void Widget::startFanous()
{
    if(ui->fanosGroupBox->isChecked()==false){
        Fanous->timer->stop();
        Fanous->setVisible(false);
        return;
    }
    QPixmap pix(":/lun.png");
    int framNum=10;

    //Fanous->move(50,50);
    if(QFile::exists(ui->fanosLineEdit->text() )){
        pix.load(ui->fanosLineEdit->text());
        framNum=ui->fanosSpinBox->value();
    }
    Fanous->setPixmap(pix);
    Fanous->setframeNum(framNum);
    Fanous->timer->start();
    Fanous->show();
}
void  Widget::startTux()
{
 tuxNum=ui->spinBoxTux->value();
    for(int i=0;i<ui->spinBoxTux->value();i++){
        Tux[i]=new Penguin;
       Tux[i]->setTuxOnTop(ui->checkBoxOnTop->checkState());

    }

      isTuxActive=true;
   //   qDebug()<<"isTuxActive"<<isTuxActive;
}

void  Widget::startButterfly()
{
    if( Butterfly->timer->isActive()){
      Butterfly->deletAll();
    }
    Butterfly->setButterflyNember(ui->spinBoxNumButter->value());
 Butterfly->setButterflyOnTop(ui->checkBoxOnTop->checkState());
    Butterfly->startButterfly();
}

void Widget::startStopAnimation()
{
    if (isRuning==true){
        if( Rain->timer->isActive())Rain->deletAll();
        if( Snowwid->timer->isActive()) Snowwid->deletAll();
        if( Autumn->timer->isActive()) Autumn->deletAll();
        if( Etoile->timer->isActive()){
            Etoile->deletAll();
            Fanous->timer->stop();
            Fanous->setVisible(false);
        }
        if( Butterfly->timer->isActive())  Butterfly->deletAll();
        if( isTuxActive==true){
            for(int i=0;i<tuxNum;i++){

                    Tux[i]->deletAll();
               Tux[i]->deleteLater();
                   // Tux[i]->close();

            }
            tuxNum=0;
        }

        startStopAction->setText(tr("&Start"));
        startStopAction->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        isRuning=false;
         qDebug() << "Animation is Stoped: "<< curThemeStr;
    }else{
        startCurentTheme();
    }
}
void Widget::startCurentTheme()
{
    if( Rain->timer->isActive())Rain->deletAll();
    if( Snowwid->timer->isActive()) Snowwid->deletAll();
    if( Autumn->timer->isActive()) Autumn->deletAll();
    if( Etoile->timer->isActive()){
        Etoile->deletAll();
        Fanous->timer->stop();
        Fanous->setVisible(false);
    }

  if( Butterfly->timer->isActive())  Butterfly->deletAll();
  if(  isTuxActive==true){
  //      qDebug()<<"isTuxActive--here"<<isTuxActive;
      for(int i=0;i<tuxNum;i++){
 //qDebug()<<"isTuxActive--here"<<i;
              Tux[i]->deletAll();
              Tux[i]->deleteLater();
              Tux[i]->close();

      }
       tuxNum=0;
         isTuxActive=false;
  }
    //  qDebug()<<"isTuxActive"<<isTuxActive;

    switch (curTheme) {
    case 0:
        startSnow();
        break;
    case 1:
      startRain();
        break;
    case 2:
        startAutumn();
        break;
    case 3:
        startStars();
        break;
    case 4:
      startButterfly();
        break;
    case 5 :
      startTux();
        break;
    default:
        break ;
    }
emit runing();
setTheme(curTheme);
      qDebug() << "curTheme: "<< QString::number(curTheme);
}

void  Widget::animationisActive()
{
   isRuning=true;
   startStopAction->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
   startStopAction->setText(tr("&Stop"));

}
void Widget::setTheme(int theme)
{
    curTheme=theme;
//ui->listWidget->setCurrentRow(curTheme);
  //  ui->comboBoxEffect->setCurrentIndex(curTheme);
            switch (theme) {
            case 0:
                curThemeStr="Snow";
                snowAction->setChecked(true);
                trayIcon->setIcon(QPixmap(":/snowicon.png"));
                 break;
            case 1:
                curThemeStr="Rain";
                rainAction->setChecked(true);
                 trayIcon->setIcon(QPixmap(":/rain.png"));
                break;
            case 2:
                curThemeStr="Autumn";
                autumnAction->setChecked(true);
                 trayIcon->setIcon(QPixmap(":/autuIcon.png"));
                break;
            case 3:
                curThemeStr="Stars";
                starsAction->setChecked(true);
                  trayIcon->setIcon(QPixmap(":/starIcon.png"));
                break;
            case 4:
                curThemeStr="butterfly";
                butterflyAction->setChecked(true);
                trayIcon->setIcon(QPixmap(":/papillon_2.png"));
                break;
            case 5:
                curThemeStr="Tux";
              tuxAction->setChecked(true);
              trayIcon->setIcon(QPixmap(":/tuxicon.png"));
                break;
            default:
               break ;
            }
}

void Widget::loadSetting()
{

    //QSettings settings(QDir::homePath()+"/.snowrain.conf",QSettings::IniFormat);
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
                            QApplication::applicationName(), QApplication::applicationName());
    settings.beginGroup("snow");
    ui->spinBox->setValue(settings.value("snowtimer",100).toInt());
    ui->spinBoxNum->setValue(settings.value("snownumber",15).toInt());
    ui->spinBoxMinSize->setValue(settings.value("snownminsize",3).toInt());
    ui->spinBoxMaxSize->setValue(settings.value("snownmaxsize",25).toInt());
    settings.endGroup();

    settings.beginGroup("rain");
    ui->spinBoxTimeRain->setValue(settings.value("Raintimer",100).toInt());
    ui->spinBoxNumRain->setValue(settings.value("Rainnumber",20).toInt());
       ui->checkBoxClodRain->setChecked(settings.value("Raincloud",true).toBool());
    settings.endGroup();

    settings.beginGroup("autumn");
    ui->spinBoxTimeAutumn->setValue(settings.value("autumntimer",100).toInt());
    ui->spinBoxNumAutumn->setValue(settings.value("autumnnumber",10).toInt());
    ui->spinBoxMinSizeAutumn->setValue(settings.value("autumnminsize",25).toInt());
    ui->spinBoxMaxSizeAutumn->setValue(settings.value("autumnmaxsize",35).toInt());
    settings.endGroup();
    settings.beginGroup("stars");
    ui->spinBoxNumEtoile->setValue(settings.value("starsnumber",25).toInt());
    ui->spinBoxMinSizeEtoile->setValue(settings.value("starsminsize",3).toInt());
    ui->spinBoxMaxSizeEtoile->setValue(settings.value("starsmaxsize",15).toInt());
    ui->fanosGroupBox->setChecked(settings.value("fanousVisible",true).toBool());
    ui->fanosLineEdit->setText(settings.value("pixFilename","").toString());
    ui->fanosSpinBox->setValue(settings.value("pixFrames",1).toInt());
    int xp=settings.value("xpos",0).toInt();
    int yp=settings.value("ypos",0).toInt();
    if(xp>=QApplication::desktop()->geometry().right())xp=0;
    if(yp>=QApplication::desktop()->geometry().bottom())yp=0;
    Fanous->xpos=xp;
    Fanous->ypos=yp;
    settings.endGroup();

    settings.beginGroup("butterfly");
    ui->spinBoxNumButter->setValue(settings.value("butterflynumber",5).toInt());
   settings.endGroup();

    settings.beginGroup("tux");
    ui->spinBoxTux->setValue(settings.value("tuxnumber",3).toInt());
     settings.endGroup();

      //----------------------------------------------------------------------
    settings.beginGroup("theme");
    setTheme(settings.value("curenttheme",0).toInt());
    ui->checkBoxOnTop->setChecked(settings.value("themeOnTop",false).toBool());
    settings.endGroup();

}

void Widget::saveSetting()//حفظ الاعدادات الى ملف
{
 //   QSettings settings(QDir::homePath()+"/.snowrain.conf", QSettings::IniFormat);
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope,
                            QApplication::applicationName(), QApplication::applicationName());
    settings.beginGroup("theme");
    settings.setValue("curenttheme",ui->stackedWidget->currentIndex());
    settings.setValue("themeOnTop", ui->checkBoxOnTop->isChecked());
    settings.endGroup();

    settings.beginGroup("snow");
    settings.setValue("snowtimer", ui->spinBox->value());
    settings.setValue("snownumber", ui->spinBoxNum->value());
    settings.setValue("snownminsize",ui->spinBoxMinSize->value());
    settings.setValue("snownmaxsize", ui->spinBoxMaxSize->value());
    settings.endGroup();

    settings.beginGroup("rain");
    settings.setValue("Raintimer", ui->spinBoxTimeRain->value());
    settings.setValue("Rainnumber", ui->spinBoxNumRain->value());
    settings.setValue("Raincloud",ui->checkBoxClodRain->isChecked());
    //  settings.setValue("autumnmaxsize", ui->spinBoxMaxSizeAutumn->value());
    settings.endGroup();

    settings.beginGroup("autumn");
    settings.setValue("autumntimer", ui->spinBoxTimeAutumn->value());
    settings.setValue("autumnnumber", ui->spinBoxNumAutumn->value());
    settings.setValue("autumnminsize",ui->spinBoxMinSizeAutumn->value());
    settings.setValue("autumnmaxsize", ui->spinBoxMaxSizeAutumn->value());
    settings.endGroup();

    settings.beginGroup("stars");
    settings.setValue("starsnumber", ui->spinBoxNumEtoile->value());
    settings.setValue("starsminsize",ui->spinBoxMinSizeEtoile->value());
    settings.setValue("starsmaxsize", ui->spinBoxMaxSizeEtoile->value());

    settings.setValue("fanousVisible",ui->fanosGroupBox->isChecked());
    settings.setValue("pixFilename", ui->fanosLineEdit->text());
    settings.setValue("pixFrames", ui->fanosSpinBox->value());
    settings.setValue("xpos", Fanous->xpos);
    settings.setValue("ypos", Fanous->ypos);
    settings.endGroup();

    settings.beginGroup("butterfly");
    settings.setValue("butterflynumber", ui->spinBoxNumButter->value());
    settings.endGroup();

    settings.beginGroup("tux");

      settings.setValue("tuxnumber", ui->spinBoxTux->value());
     settings.endGroup();

    qDebug() << "seting saved ";
}

void Widget::on_fanosToolButton_clicked()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Open Image..."),
                                              QString(), tr("image-Files (*.png *.PNG);;All Files (*)"));


    if (!fn.isEmpty())
        ui->fanosLineEdit->setText(fn);
}




void Widget::actveTheme(bool )
{
    if (snowAction->isChecked()){
        ui->listWidget->setCurrentRow(0);
    //    ui->comboBoxEffect->setCurrentIndex(0);
        ui->stackedWidget->setCurrentIndex(0);
        curTheme=0;

    }
    if (rainAction->isChecked()){
         ui->listWidget->setCurrentRow(1);
       //ui->comboBoxEffect->setCurrentIndex(1);
        ui->stackedWidget->setCurrentIndex(1);
        curTheme=1;

    }
    if (autumnAction->isChecked()){
         ui->listWidget->setCurrentRow(2);
  //      ui->comboBoxEffect->setCurrentIndex(2);
        ui->stackedWidget->setCurrentIndex(2);
        curTheme=2;

    }
    if (starsAction->isChecked()){
         ui->listWidget->setCurrentRow(3);
    //    ui->comboBoxEffect->setCurrentIndex(3);
        ui->stackedWidget->setCurrentIndex(3);
        curTheme=3;

    }
    if (butterflyAction->isChecked()){
 ui->listWidget->setCurrentRow(4);
      //  ui->comboBoxEffect->setCurrentIndex(4);
        ui->stackedWidget->setCurrentIndex(4);
        curTheme=4;

    }
    if (tuxAction->isChecked()){
         ui->listWidget->setCurrentRow(5);
  //      ui->comboBoxEffect->setCurrentIndex(5);
        ui->stackedWidget->setCurrentIndex(5);
        curTheme=5;

    }
       startCurentTheme();
}



void Widget::on_buttonBox_clicked(QAbstractButton* button)
{
    int row=ui->listWidget->currentRow();
    curTheme=row;
    if(ui->buttonBox->standardButton(button)==QDialogButtonBox::Apply)
    {

        if(row==curTheme){
            startCurentTheme();
        }else{
            curTheme=row;
         setTheme(row);
        }
        saveSetting();
    }
    if(ui->buttonBox->standardButton(button)==QDialogButtonBox::Ok)
    {
        if(row==curTheme){
            startCurentTheme();
        }else{
            curTheme=row;
         setTheme(row);
        }
        saveSetting();
        hide();
    }
    if(ui->buttonBox->standardButton(button)==QDialogButtonBox::Cancel)
    {
        hide();
    }
    if(ui->buttonBox->standardButton(button)==QDialogButtonBox::RestoreDefaults)
    {
       QDir dir;
     QString filename= QDir::homePath()+"/.snowrain.conf";
    if (dir.remove(filename)==true)
        loadSetting();
     qDebug()<< "settings restored";
    }
}
void Widget::restoreDefault()
{
    QDir dir;
  QString filename= QDir::homePath()+"/.snowrain.conf";
  if (dir.remove(filename)==true)
   qDebug()<< "settings restored";

}

void Widget::on_listWidget_currentRowChanged(int )
{

 //
 //   ui->stackedWidget->setCurrentIndex(currentRow);

}

void Widget::on_listWidget_activated(const QModelIndex &index)
{
    int row=index.row();

        curTheme=row;
     setTheme(row);



}
