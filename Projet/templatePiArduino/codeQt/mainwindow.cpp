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


     // Fonctions de connections events/slots
    connectTimers(updateRate);
    connectCheckBoxRead();
    connectElectroaimantButton();
    connectSpinBoxes();
    connectPlotBoxe();  // activation du plot, mettre en commentaire si pas utilise
    // Serial protocole
    serialCom = new SerialProtocol(portName, BAUD_RATE);
    connectSerialPortRead();


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

            //ui->enc_1->setText(QString::number(jsonObj["enc_1"].toDouble()));
            //ui->enc_2->setText(QString::number(jsonObj["enc_2"].toDouble()));
            //ui->encodeur_vex->setText(QString::number(jsonObj["encodeur_vex"].toDouble()));
            ui->pot_vex->setText(QString::number(jsonObj["pot_vex"].toInt()));


            // Plot data
            scene.clear();
            currentPot.addData(jsonObj["pot_vex"].toDouble());
            currentPot.draw(&scene);


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

void MainWindow::connectElectroaimantButton() {
    // Fonction de connection du boutton Send
    connect(ui->electroAimantButtonON, SIGNAL(clicked()), this, SLOT(sendElectoaimantON()));
    connect(ui->electroAimantButtonOFF,SIGNAL(clicked()), this, SLOT(sendElectoaimantOFF()));
}

void MainWindow::connectSpinBoxes() {
    // Fonction des spin boxes
    connect(ui->doubleSpinBoxVitesse, SIGNAL(valueChanged(double)), this, SLOT(sendDesVel(double)));

}

void MainWindow::connectPlotBoxe() {

    ui->graphicsView->setScene(&scene);
    // Plot data
    currentPot.setDataLen(300);
    currentPot.setColor(255,0,0);
    currentPot.setGain(.2);

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

void MainWindow::sendElectoaimantON(){
   // ui->doubleSpinBoxVitesse->setValue(0.0);
    serialCom->sendMessage("{\"aimant\": \"true\"}");
}

void MainWindow::sendElectoaimantOFF(){
   // ui->doubleSpinBoxVitesse->setValue(0.0);
    serialCom->sendMessage("{\"aimant\": \"false\"}");
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
