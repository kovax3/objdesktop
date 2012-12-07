#include "objectdesktop.h"
#include "snowwid.h"
#include "rain.h"
#include "butterfly.h"
#include "autumn.h"
#include "penguin.h"
#include "etoile.h"
#include "fanous.h"
ObjectDesktop::ObjectDesktop()
{

}
   void  ObjectDesktop::showSnow(int max,int min,int interval,int number,bool ontop)
   {
       if(max>100||max<3)max=25;
        if(min>100||min<1)min=1;
        if(interval>1000||interval<50)interval=100;
        if(number>100||number<1)number=10;

           snowwid *Snowwid=new snowwid;
           Snowwid->setSnowSize(max,min);
           Snowwid->timer->setInterval(interval);
           Snowwid->setSnowNember(number);
           Snowwid->setSnowOnTop(ontop);
                Snowwid->updat();

   }
   void  ObjectDesktop::showRin(int interval,int number,bool obj,bool ontop)
   {
       if(interval>200||interval<50)interval=100;
       if(number>100||number<1)number=20;
           rain *Rain=new rain;
           Rain->setRainDuration(interval);
           Rain->setRainNember(number);
           Rain->setCloudVisible(obj);
           Rain->setRainOnTop(ontop);
               Rain->starNew();

   }
   void  ObjectDesktop::showButterfly(int number,bool ontop)
   {
            if(number>10||number<1)number=5;
           butterfly *Butterfly=new butterfly;
           Butterfly->setButterflyNember(number);
        Butterfly->setButterflyOnTop(ontop);
           Butterfly->startButterfly();

   }
   void  ObjectDesktop::showAutumn(int max,int min,int interval,int number,bool ontop)
   {
       if(interval>1000||interval<50)interval=100;
       if(number>100||number<1)number=10;
              if(max>100||max<5)max=35;
               if(min>100||min<1)min=35;
           autumn *Autumn=new autumn;
           Autumn->setAutumnSize(max,min);
           Autumn->timer->setInterval(interval);
           Autumn->setAutumnNember(number);
           Autumn->setAutumnOnTop(ontop);
           // if(ui->radioButtonAutumn->isChecked()){
           Autumn->updat();

   }
   void  ObjectDesktop::showTux(int number,bool ontop)
   {
       if(number<1||number>10)number=3;
       for(int i=0;i<number;i++){
        Penguin   *Tux=new Penguin;
          Tux->setTuxOnTop(ontop);

       }

   }
   void  ObjectDesktop::showStars(int number,bool ontop,bool obj)
   {
         if(number>100||number<1)number=25;
         etoile *stars=new etoile;
         stars->setStarNember(number);
         stars->setStarOnTop(ontop);
         stars->startNew();
         if(obj==true){
             fanous *Fanous=new fanous;
             QPixmap pix(":/lun.png");
             int framNum=10;

             Fanous->setPixmap(pix);
             Fanous->setframeNum(framNum);
             Fanous->timer->start();
             Fanous->show();
         }

   }
