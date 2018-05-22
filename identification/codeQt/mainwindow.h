#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "serialprotocol.h"
#include "plot.h"
#include <QCloseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QFile>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int TIMEOUT_MS = 100; // ms
    int DEFAULT_UPDATE_RATE = 100; // ms
    const qint32 BAUD_RATE = 115200;

    explicit MainWindow(QString portName, int updateRate, QWidget *parent = 0);
    virtual ~MainWindow();
    void closeEvent(QCloseEvent *event) override;

    /* --- FUNCTIONS FOR DERIVED CLASS (TO OVERRIDE OR CALL) --- */

    // can be used in derived class
    void sendMessage(QString msg);
    void setUpdateRate(int rateMs);

    // should be overriden
    virtual void onPeriodicUpdate() {}
    virtual void onMessageReceived(QString /*msg*/) {}

private slots:
    void receiveFromSerial(QString);
    void sendPulseSetting();
    void sendPulseStart();
    void manageRecording(int);

private:
    void connectTimers(int updateRate);
    void connectButtons();
    void connectSerialPortRead();
    void connectSpinBoxes();
    void startRecording();
    void stopRecording();
    void writeFile(QString);

    bool record = false;
    QTimer updateTimer_;
    QString msgReceived_{""};
    QString msgBuffer{""};
    SerialProtocol* serialCom;
    QString filename = "/home/pi/Desktop/Data.txt";
    QFile file;
    QTextStream outStream;



    QGraphicsScene scene;
    Plot potVex;


protected:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
