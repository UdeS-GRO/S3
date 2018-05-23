#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <QFile>
#include <QTime>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>

class CsvWriter: public QObject
{
    Q_OBJECT

public:
    CsvWriter();
    ~CsvWriter();
    void write(QJsonObject);
    void close();

private:
    void setHeader(QJsonObject);
    QString folder = "/home/pi/Desktop/";
    QString filename = "Data.csv";
    QFile file;
    QTextStream outStream;
    bool firstLine = true;
};
#endif // CSVWRITER_H
