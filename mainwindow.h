#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QtCore/QCoreApplication>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTextStream>
#include "QScrollBar"
#include "delay.h"


#define TIMER_TIMEOUT                   40

#define COLOR_A1                        0x00CCCC
#define COLOR_A2                        0x009999


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void update1();

    void Refresh_Port();

    void readData1();

    void on_ClearEditor_clicked();

    void on_OpenPort1_clicked();

    void on_RefreshPort_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_listWidget_2_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *ser1;
    QSerialPortInfo Serialinfos[10];
    QTimer *timer1;
    QByteArray dataE1;
    int showComInfoEn;
    quint64 SequenceNumber;
    QByteArray atList1;
    QByteArray atList2;
};

#endif // MAINWINDOW_H
