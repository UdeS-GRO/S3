#ifndef SERIALPROTOCOL_H
#define SERIALPROTOCOL_H

#include <QObject>
#include <QSerialPort>
class SerialProtocol : public QObject{

    Q_OBJECT

public:
    explicit SerialProtocol(QString , qint32 );
    ~SerialProtocol();
    void sendMessage(QString msg);

signals:
    void newMessage(QString msg);

private slots:
    void readReceivedMsg();

private:
    void connectSignals();
    QSerialPort* serial_;
    QString msgBuffer = "";
};

#endif // SERIALPROTOCOL_H
