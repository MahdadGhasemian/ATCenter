#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QMainWindow>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QGuiApplication>


class Serial
{
public:
    Serial();
    ~Serial();
    bool SerialClose(void);
    bool SerialConnect(int port,quint32 baudrate);
    void SerialPortInfo(void);
    void SendChar(char data);
    void Puts(quint8 *data, int count);
    char GetChar(void);
    int GetS(QByteArray *data);
    void WaitForReadyRead(void);
    QSerialPortInfo Serialinfos[10];
    int NumOfSerial;
    QSerialPort serial;
    int openPort;

};

#endif // SERIAL_H
