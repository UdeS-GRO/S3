#ifndef PLOT_H
#define PLOT_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPen>

class Plot: public QObject
{
    Q_OBJECT

public:
    Plot();
    void setColor(int,int,int);
    void setDataLen(int);
    void addData(double);
    void draw(QGraphicsScene *);
    void setGain(double);

private:
    double gain = 1;
    int dataBufferLen;
    QVector<double> data;
    QPen pen;


};


#endif // PLOT_H
