#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtWidgets>
#include <QJsonObject>
#include <QJsonDocument>

MainWindow::MainWindow(QString portName, int updateRate, QWidget *parent) :
    QMainWindow(parent)
{
    // Initialisation du UI
    ui = new Ui::MainWindow;
    ui->setupUi(this);


    ui->graphicsView->setScene(&scene);
    // Fonctions de connections events/slots
    connectTimers(updateRate);
    connectCheckBoxRead();
    connectButtonReset();
    connectSpinBoxes();
    // Serial protocole
    serialCom = new SerialProtocol(portName, BAUD_RATE);
    connectSerialPortRead();

    // Plot data

    desVelPlot.setDataLen(150);
    desVelPlot.setColor(255,0,0);

    desVelPlot.setGain(6);
    curVelPlot.setGain(6);

    curVelPlot.setDataLen(150);
    curVelPlot.setColor(0,0,255);
}

MainWindow::~MainWindow()
{
    updateTimer_.stop();
    delete serialCom;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    sendMessage("{\"read\": \"false\"}"); //Arret de communication periodique de l'arduino
    event->accept();
}

void MainWindow::receiveFromSerial(QString msg) {
    // Fonction appelee lors de reception sur port serie
    // Accumulation des morceaux de message
    msgBuffer += msg;

    if(msgBuffer.endsWith('\n')){
        QJsonDocument jsonResponse = QJsonDocument::fromJson(msgBuffer.toUtf8());
        if(~jsonResponse.isEmpty()){
            QJsonObject jsonObj = jsonResponse.object();

            QString buff = jsonResponse.toJson(QJsonDocument::Indented);
            ui->textBrowser->setText(buff.mid(2,buff.length()-4));
            // Modify line edit
            //ui->accel_x->setText(QString::number(jsonObj["accel_x"].toDouble()));
            //ui->accel_y->setText(QString::number(jsonObj["accel_y"].toDouble()));
            //ui->accel_z->setText(QString::number(jsonObj["accel_z"].toDouble()));
            //ui->gyro_x->setText(QString::number(jsonObj["gyro_x"].toDouble()));
            //ui->gyro_y->setText(QString::number(jsonObj["gyro_y"].toDouble()));
            //ui->gyro_z->setText(QString::number(jsonObj["gyro_z"].toDouble()));
            //ui->mag_x->setText(QString::number(jsonObj["mag_x"].toDouble()));
            //ui->mag_y->setText(QString::number(jsonObj["mag_y"].toDouble()));
            //ui->mag_z->setText(QString::number(jsonObj["mag_z"].toDouble()));
            //ui->heading->setText(QString::number(jsonObj["heading"].toDouble()));
            //ui->temperature->setText(QString::number(jsonObj["temperature"].toDouble()));
            //ui->enc_1->setText(QString::number(jsonObj["enc_1"].toDouble()));
            //ui->enc_2->setText(QString::number(jsonObj["enc_2"].toDouble()));
            //ui->shunt_voltage->setText(QString::number(jsonObj["shunt_voltage"].toDouble()));
            //ui->bus_voltage->setText(QString::number(jsonObj["bus_voltage"].toDouble()));
            //ui->current->setText(QString::number(jsonObj["current"].toDouble()));
            //ui->load_voltage->setText(QString::number(jsonObj["load_voltage"].toDouble()));
            //ui->pot_vex->setText(QString::number(jsonObj["pot_vex"].toInt()));

            ui->curVel->setText(QString::number(jsonObj["cur_vel"].toDouble()));

            // Plot data
            scene.clear();
            curVelPlot.addData(jsonObj["cur_vel"].toDouble());
            desVelPlot.addData(jsonObj["des_vel"].toDouble());

            desVelPlot.draw(&scene);
            curVelPlot.draw(&scene);


            msgReceived_ = msgBuffer;
            onMessageReceived(msgReceived_);
            msgBuffer = "";
        }
    }
}


void MainWindow::connectTimers(int updateRate) {
    // Fonction de connection de timers
    connect(&updateTimer_, &QTimer::timeout, this, [this] {
        onPeriodicUpdate(); // call overriden virtual function
    });
    updateTimer_.start(updateRate);
}

void MainWindow::connectCheckBoxRead() {
    // Fonction de connection de la checkbox
    connect(ui->checkBox, &QCheckBox::toggled, [this](bool state) {
        // Requete d'envoie periodique du Arduino
        if (state){
            serialCom->sendMessage("{\"read\": \"true\"}");
        } else{
            serialCom->sendMessage("{\"read\": \"false\"}");
        }
    });
}
void MainWindow::connectSerialPortRead() {
    // Fonction de connection au message de la classe (serialProtocol)
    connect(serialCom, SIGNAL(newMessage(QString)), this, SLOT(receiveFromSerial(QString)));
}

void MainWindow::connectButtonReset() {
    // Fonction de connection du boutton Send
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetPWM()));
}

void MainWindow::connectSpinBoxes() {
    // Fonction des spin boxes
    connect(ui->doubleSpinBoxVitesse, SIGNAL(valueChanged(double)), this, SLOT(sendDesVel(double)));
    connect(ui->doubleSpinBoxP, SIGNAL(valueChanged(double)), this, SLOT(sendPID()));
    connect(ui->doubleSpinBoxI, SIGNAL(valueChanged(double)), this, SLOT(sendPID()));
    connect(ui->doubleSpinBoxD, SIGNAL(valueChanged(double)), this, SLOT(sendPID()));

}

void MainWindow::sendPID(){

    double PID[3];
    PID[0]= ui->doubleSpinBoxP->value();
    PID[1]= ui->doubleSpinBoxI->value();
    PID[2]= ui->doubleSpinBoxD->value();

    QJsonArray array = {PID[0], PID[1], PID[2]};
    QJsonObject jsonObject
    {
        {"set_PID", array}
    };
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    sendMessage(strJson);
}
void MainWindow::sendDesVel(double value){
    QJsonObject jsonObject
    {
        {"set_des_vel", value}
    };
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    sendMessage(strJson);
}

void MainWindow::resetPWM(){
    ui->doubleSpinBoxVitesse->setValue(0.0);
}


void MainWindow::sendMessage(QString msg) {
    // Fonction d'ecriture sur le port serie
    serialCom->sendMessage(msg);
    qDebug() << msg;
}

void MainWindow::setUpdateRate(int rateMs) {
    // Fonction d'initialisation du Timer
    updateTimer_.start(rateMs);
}
