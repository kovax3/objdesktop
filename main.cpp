#include <QtGui/QApplication>
#include "widget.h"
#include "penguin.h"
#include<QDebug>
#include "objectdesktop.h"
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
    a.setApplicationName("objdesktop");
    a.setOrganizationName("Abou zakaria");
    a.setApplicationVersion("0.1");
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/img/snowicon48.png")), QIcon::Normal, QIcon::Off);
   a.setWindowIcon(icon);
   QString locale = QLocale::system().name();
//qDebug() << "language:"<< locale;
//! [2]
   QTranslator translator;
//! [2] //! [3]
   translator.load(QString(":/objdesktop_") + locale);


   a.installTranslator(&translator);

   QString translatorFileName = QLatin1String("qt_");
   translatorFileName += QLocale::system().name();
     QTranslator *translatorsys = new QTranslator(&a);
   if (translatorsys->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
       a.installTranslator(translatorsys);
    const QStringList args = QCoreApplication::arguments();

    if (args.count() >1){

        QString   goPos1 = args.at(1);

        if (goPos1.toLower()==("-help")){
            QString txt=QString(QObject::trUtf8(
                                    "objdesktop Version : %1 \n"
                                    "Usage: objdesktop [type] [Options]\n"
                                    "type:\n"
                                    "-help              Show help about options.\n"
                                    "-s                 Run snow Animation .\n"
                                    "-a                 Run Autumn Animation .\n"
                                    "-b                 Run Butterfly Animation.\n"
                                    "-r                 Run Rain Animation.\n"
                                    "-e                 Run Stars Animation .\n"
                                    "-t                 Run tux Animation .\n"
                                    "-o                 setting dialog .\n"
                                    "-d                 restore deault settings .\n"
                                    "Options:\n"
                                    "objdesktop -s -max <int> -min <int> -time <int> -num <int> -top \n"
                                    "objdesktop -a -max <int> -min <int> -time <int> -num <int> -top \n"
                                    "objdesktop -b -num <int> -time <int> -top \n"
                                     "objdesktop -r -num <int> -time <int> -obj -top \n"
                                    "objdesktop -e -max <int> -min <int> -num <int> -obj -top \n"
                                   "objdesktop -t -num <int>  -top \n"
                                    "\n"
                                    "-max   <int>           Maximum size .\n"
                                    "-min   <int>           Minimum size .\n"
                                    "-time  <int>           Timer intervale Animation in milliseconds.\n"
                                    "-num   <int>           Objects numbers.\n"
                                    "-top                   Top most .\n"
                                     "-obj                   Show object in rain or stars .\n"
                                    "\n"
                                    "Timer intervale descripton:\n"
                                    "in snow and Autumn maximum is:1000 minimum is :50 default is: 100\n"
                                    "in  rain maximum is:200 minimum is :50 default is: 100\n"
                                    "\n"
                                    "Maximum Maximum numbers descripton:\n"
                                    "in snow and Autumn Maximum 100 Minimum 1 numbers<=100 \n "
                                    "in rain numbers<=100 \n "
                                    "in stars Maximum 30 Minimum 1 numbers<= 100 \n "
                                    "in Butterfly and tux  numbers <=10 \n "
                                    )).arg(a.applicationVersion());
            qDebug()<<txt;
            return 0;
        }else  if (goPos1.toLower()==("-o")){
            Widget w;
            w.show();
            return a.exec();
        }else  if (goPos1.toLower()==("-d")){
            Widget w;
            w.restoreDefault();
            return (0);

        }else{
            int type=0; QString max="25";QString min="3";QString interval="100";QString number="25";
            bool ontop=false; bool obj=false;

            for (int i=0;i<args.count();i++){
                //type
                QString   goPos = args.at(i);
                if(goPos=="-s")type=0;//snow
                if(goPos=="-a")type=1;//autumn
                if(goPos=="-b")type=2;//butterfly
                if(goPos=="-r")type=3;//rain
                if(goPos=="-e")type=4;//stars
                 if(goPos=="-t")type=5;//tux
                //options
                if(goPos=="-max")max=(args.at(i+1));
                if(goPos=="-min")min=(args.at(i+1));
                if(goPos=="-time")interval=(args.at(i+1));
                if(goPos=="-num")number=(args.at(i+1));
                if(goPos=="-top")ontop=true;
                if(goPos=="-obj")obj=true;
            }
            ObjectDesktop Ob;
            if(type==0) {//snow
                Ob.showSnow(max.toInt(),min.toInt(),interval.toInt(),number.toInt(),ontop);
          }  else if(type==1) {//autumn
                    Ob. showAutumn( max.toInt(), min.toInt(), interval.toInt(), number.toInt(), ontop);
           }  else if(type==2) {//butterfly
               Ob.showButterfly( number.toInt(), ontop);
            }else if(type==3) {//rain
               Ob. showRin(interval.toInt(),number.toInt(),obj, ontop);
            }else if(type==4) {//stars
               Ob.showStars(number.toInt(),ontop,obj);
            }else if(type==5) {//tux
                Ob.showTux(number.toInt(),ontop);
            }

            return a.exec();

        }


    }

    Widget w;
 w.hide();
  //  w.show();
    return a.exec();
}
