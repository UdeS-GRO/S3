#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QString portName, int updateRate, QWidget *parent) :
    QMainWindow(parent)
{
    // Initialisation du UI
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    // Fonctions de connections events/slots
    connectTimers(updateRate);
    connectButtons();
    connectSpinBoxes();

    // Serial protocole
    serialCom = new SerialProtocol(portName, BAUD_RATE);
    connectSerialPortRead();

    // Plot data
    potVex.setDataLen(500);
    potVex.setColor(255,0,0);
    potVex.setGain(1);

    /*file.setFileName(filename);
    outStream.setDevice(&file);*/

}

MainWindow::~MainWindow()
{
    updateTimer_.stop();
    delete serialCom;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
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

            // Plot data
            scene.clear();
            potVex.addData((jsonObj["pot_vex"].toDouble()-512.0)/5.0);


            potVex.draw(&scene);

            msgReceived_ = msgBuffer;
            onMessageReceived(msgReceived_);
            if(record){
                writer_->write(jsonObj);
            }
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

void MainWindow::connectSerialPortRead() {
    // Fonction de connection au message de la classe (serialProtocol)
    connect(serialCom, SIGNAL(newMessage(QString)), this, SLOT(receiveFromSerial(QString)));
}

void MainWindow::connectButtons(){
    // Fonction de connection du boutton Send
    connect(ui->pulseButton, SIGNAL(clicked()), this, SLOT(sendPulseStart()));
    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(manageRecording(int)));
}

void MainWindow::connectSpinBoxes() {
    // Fonction des spin boxes
    connect(ui->DurationBox, SIGNAL(valueChanged(int)), this, SLOT(sendPulseSetting()));
    connect(ui->PWMBox, SIGNAL(valueChanged(int)), this, SLOT(sendPulseSetting()));

}

void MainWindow::sendPulseSetting(){
    int PWM_val = ui->PWMBox->value();
    int duration_val = ui->DurationBox->value();
    QJsonObject jsonObject
    {
        {"set_PWM", PWM_val},
        {"set_duration", duration_val}
    };
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    sendMessage(strJson);
}

void MainWindow::sendPulseStart(){
    QJsonObject jsonObject
    {
        {"pulse", "true"}
    };
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    sendMessage(strJson);
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

void MainWindow::manageRecording(int stateButton){
    if(stateButton == 2){
        startRecording();
    }
    if(stateButton == 0){
        stopRecording();
    }
}

void MainWindow::startRecording(){
    record = true;
    writer_ = new CsvWriter();
}

void MainWindow::stopRecording(){
    record = false;
    delete writer_;
}
