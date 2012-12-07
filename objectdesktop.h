#ifndef OBJECTDESKTOP_H
#define OBJECTDESKTOP_H

#include <QObject>

class ObjectDesktop : public QObject
{
public:
    ObjectDesktop();
  void  showSnow(int max,int min,int interval,int number,bool ontop);
   void  showRin(int interval,int number,bool ontop,bool obj);
      void  showButterfly(int number,bool ontop);
        void  showAutumn(int max,int min,int interval,int number,bool ontop);
           void  showTux(int number,bool ontop);
              void  showStars(int number,bool ontop,bool obj);
};

#endif // OBJECTDESKTOP_H
