#ifndef OBJECT_H
#define OBJECT_H

#include <QWidget>



class Object : public QWidget {
    Q_OBJECT
public:
    Object(QWidget *parent = 0);


protected:
 void paintEvent(QPaintEvent *event);

private:
QPixmap pix;

public slots:
    void setPixmap(QPixmap pix);

};

#endif // OBJECT_H
