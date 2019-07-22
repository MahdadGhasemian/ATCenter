#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->setFixedSize(this->width(), this->height());

    ser1 = new QSerialPort(this);

    Refresh_Port();

    connect(ser1, SIGNAL(readyRead()), this, SLOT(readData1()));

    timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(update1()));

    ui->textEdit->setFontPointSize(9);

    showComInfoEn = ui->checkBox_3->isChecked();

    SequenceNumber = 0;

    QFile file1("atlist1.txt");
    if (!file1.open(QFile::ReadOnly)) {
        ui->textEdit->setTextColor(QColor("black"));
        ui->textEdit->append("Could not open file for reading");
        ui->textEdit->setTextColor(QColor("red"));
        return;
    }
    QByteArray temp1 = file1.readAll();
    atList1.append(temp1);
    ui->listWidget->addItems(QString(temp1.data()).split('\r'));
    file1.close();

    QFile file2("atlist2.txt");
    if (!file2.open(QFile::ReadOnly)) {
        ui->textEdit->setTextColor(QColor("black"));
        ui->textEdit->append("Could not open file for reading");
        ui->textEdit->setTextColor(QColor("red"));
        return;
    }
    QByteArray temp2 = file2.readAll();
    atList2.append(temp2);
    ui->listWidget_2->addItems(QString(temp2.data()).split('\r'));
    file2.close();

}

MainWindow::~MainWindow()
{
    ser1->close();
    delete ui;
}

void MainWindow::update1()
{
    timer1->stop();
    QByteArray data , dataPrint , buffer;
    QTime time;
    data = dataE1;
    dataE1.clear();

    if ( data.size() > 0 )
    {
        if ( showComInfoEn )
        {
            dataPrint.append("ComA (    , ");
            dataPrint.append(QString::number((uchar)SequenceNumber++, 10).leftJustified(4, ' '));
            dataPrint.append(" , ");
            time = QTime::currentTime();
            dataPrint.append(time.toString("hh:mm:ss"));
            dataPrint.append(") ");
        }
        if ( ui->checkBox_2->isChecked())
        {
            QString dataHex;
            int i;
            for (i = 0; i < data.size(); i++)
            {
                if ( !dataHex.isEmpty() )
                    dataHex.append( " , 0x" );
                else
                    dataHex.append( "0x" );
                dataHex.append( QString::number((uchar)data.at(i), 16).rightJustified(2, '0') );
            }
            dataPrint.append(dataHex);
            if ( showComInfoEn )
            {
                buffer.append(QString::number((int)i, 10).leftJustified(3, ' '));
                dataPrint[6] = buffer[0];
                dataPrint[7] = buffer[1];
                dataPrint[8] = buffer[2];
            }
        }
        else
        {
            dataPrint.append(data);
            if ( showComInfoEn )
            {
                buffer.append(QString::number((int)data.size(), 10).leftJustified(3, ' '));
                dataPrint[6] = buffer[0];
                dataPrint[7] = buffer[1];
                dataPrint[8] = buffer[2];
            }
        }
        dataPrint.append('\n');

        ui->textEdit->insertPlainText(dataPrint);
        if ( ui->checkBox->isChecked())
            ui->textEdit->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->maximum());
    }
}

/*!
 * \brief بررسی پورت های موجود
 */
void MainWindow::Refresh_Port()
{

    ui->Port1_Select->clear();

    int i=0;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        Serialinfos[i++]=info;
        ui->Port1_Select->addItem(info.portName() + " : " + info.description());
    }
}

/*!
 * \brief خواندن داده های پورت 1
 */
void MainWindow::readData1()
{
    dataE1.append(ser1->readAll());
    timer1->start(TIMER_TIMEOUT);
}

/*!
 * \brief 1باز یا بسته کردن پورت
 */
void MainWindow::on_OpenPort1_clicked()
{

    if(ui->OpenPort1->text() == "Open")
    {

        ser1->setPort(Serialinfos[ui->Port1_Select->currentIndex()]);

        if (ser1->open(QIODevice::ReadWrite))
        {
            bool ok;
            ser1->setBaudRate(ui->Port1_Buad->currentText().toInt(&ok,10));
            ser1->setDataBits(QSerialPort::Data8);
            ser1->setFlowControl(QSerialPort::NoFlowControl);
            ser1->setParity(QSerialPort::NoParity);

            ui->OpenPort1->setText("Close");
            ui->textEdit->setTextColor(QColor("black"));
            ui->textEdit->append("Open port1\n");
            ui->textEdit->setTextColor(QColor("red"));

        }

    }
    else
    {
        ser1->close();
        ui->OpenPort1->setText("Open");
        ui->textEdit->setTextColor(QColor("black"));
        ui->textEdit->append("Close port1\n");
        ui->textEdit->setTextColor(QColor("red"));
    }

}

/*!
 * \brief پاک کردن صفحه
 */
void MainWindow::on_ClearEditor_clicked()
{
    ui->textEdit->clear();
}


void MainWindow::on_RefreshPort_clicked()
{
    Refresh_Port();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    //if ( ui->checkBox->isChecked())
    //ui->plainTextEdit->verticalScrollBar()->setValue(ui->plainTextEdit->verticalScrollBar()->maximum());
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    showComInfoEn = arg1;
}

void MainWindow::on_pushButton_clicked()
{
    QByteArray temp;

    QFile fileAddress("address.txt");
    if (!fileAddress.open(QFile::ReadWrite)) {
        ui->textEdit->setTextColor(QColor("black"));
        ui->textEdit->append("Could not open file for reading");
        ui->textEdit->setTextColor(QColor("red"));
        return;
    }
    QString path = fileAddress.readAll();
    QString address = QFileDialog::getSaveFileName(this, tr("Save Log's"), path , tr("Document files (*.txt);;All files (*.*)"), 0);

    temp.clear();
    temp.insert(0, address);
    fileAddress.write(temp);
    fileAddress.close();

    QFile file(address);
    if (!file.open(QFile::WriteOnly)) {
        ui->textEdit->setTextColor(QColor("black"));
        ui->textEdit->append("Could not open file for reading");
        ui->textEdit->setTextColor(QColor("red"));
        return;
    }
    file.flush();
    temp.clear();
    temp.insert(0 , ui->textEdit->toPlainText());
    file.write(temp);
    file.close();
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    QString text = ui->listWidget->currentItem()->text();
    QByteArray data(text.toStdString().c_str());

    ui->textEdit->setTextColor(QColor("blue"));
    ui->textEdit->append(text);
    ui->textEdit->setTextColor(QColor("red"));

    data.append('\r');
    data.append('\n');
    ser1->write(data);

}

void MainWindow::on_listWidget_2_doubleClicked(const QModelIndex &index)
{
    QString text = ui->listWidget_2->currentItem()->text();
    QByteArray data(text.toStdString().c_str());

    ui->textEdit->setTextColor(QColor("blue"));
    ui->textEdit->append(text);
    ui->textEdit->setTextColor(QColor("red"));

    data.append('\r');
    data.append('\n');
    ser1->write(data);
}

void MainWindow::on_pushButton_2_clicked()
{
    if ( ui->tabWidget->currentIndex() == 0 )
    {
        ui->listWidget->addItem(ui->lineEdit->text());

        QFile file1("atlist1.txt");
        if (!file1.open(QFile::WriteOnly)) {
            ui->textEdit->setTextColor(QColor("black"));
            ui->textEdit->append("Could not open file for reading");
            ui->textEdit->setTextColor(QColor("red"));
            return;
        }
        atList1.append(ui->lineEdit->text());
        atList1.append('\r');
        file1.write(atList1);
        file1.close();
    }
    else if ( ui->tabWidget->currentIndex() == 1 )
    {
        ui->listWidget_2->addItem(ui->lineEdit->text());

        QFile file2("atlist2.txt");
        if (!file2.open(QFile::WriteOnly)) {
            ui->textEdit->setTextColor(QColor("black"));
            ui->textEdit->append("Could not open file for reading");
            ui->textEdit->setTextColor(QColor("red"));
            return;
        }
        atList2.append(ui->lineEdit->text());
        atList2.append('\r');
        file2.write(atList2);
        file2.close();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString text = ui->lineEdit_2->text();
    QByteArray data(text.toStdString().c_str());

    ui->textEdit->setTextColor(QColor("blue"));
    ui->textEdit->append(text);
    ui->textEdit->setTextColor(QColor("red"));

    ser1->write(data);
}

void MainWindow::on_pushButton_4_clicked()
{
    QByteArray data;

    ui->textEdit->setTextColor(QColor("blue"));
    ui->textEdit->append("Ctrl+Z");
    ui->textEdit->setTextColor(QColor("red"));

    data.append(0x1A);

    ser1->write(data);
}
