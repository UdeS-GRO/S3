#ifndef YOURMAINWINDOW_H
#define YOURMAINWINDOW_H

#include "mainwindow.h"
#include "robotdiag.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

class YourMainWindow : public MainWindow {
public:
    static const int UPDATE_RATE_MS = 1000;

    float t_ = 0.0;

    YourMainWindow()
        : MainWindow("/dev/ttyACM0", UPDATE_RATE_MS) // port name, update rate
    {
        robotdiag::init();
    }

    ~YourMainWindow()
    {
        robotdiag::stop_and_join();
    }

    // Available functions

    // sendMessage(QString JSONstring); send JSON messages to the arduino
    // setUpdateRate(int rateMs); change preriodic loop frequency

    void onMessageReceived(QString msg) override {

        //Function executed on message received
        qDebug() << "Message received from arduino" << msg;

        // Décodage.
        double t = 0.0; // timestamp
        double p = 0.0; // position
        double v = 0.0; // velocity
        double c = 0.0; // command.

        QJsonDocument jsonResponse = QJsonDocument::fromJson(msg.toUtf8());
        if(!jsonResponse.isEmpty()){
            QJsonObject jsonObj = jsonResponse.object();

            t = jsonObj["ts"].toDouble();
            p = jsonObj["cur_pos"].toDouble();
            v = jsonObj["cur_vel"].toDouble();
            c = jsonObj["cur_cmd"].toDouble();
        }

        robotdiag::RobotState evt;
        evt.id      = 0;  // Moteur réel.
        evt.t       = t;
        evt.cur_pos = p;
        evt.cur_vel = v;
        evt.cur_cmd = c;
        robotdiag::push_event(evt);
    }

    void onPeriodicUpdate() override {

        //Main periodic loop
        //qDebug() << "Periodic loop (nothing for now)";

    }
};

#endif // YOURMAINWINDOW_H
