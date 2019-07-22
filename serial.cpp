#include "serial.h"

Serial::Serial()
{
    SerialPortInfo();
}

Serial::~Serial()
{
    SerialClose();
}
void Serial::SerialPortInfo(void)
{
    int i=0;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        Serialinfos[i++]=info;

    }
    NumOfSerial = i;
    return;
}
/*********************************************************************
 * @auther
 * @brief
 * @description
 * @param[in]		None.
 * @param[out]		None.
 * @return
 *
 **********************************************************************/

bool Serial::SerialConnect(int port,quint32 baudrate)
{
    openPort = port;
    serial.setPort(Serialinfos[port]);

    if (serial.open(QIODevice::ReadWrite))
    {
        serial.setBaudRate(baudrate);
        serial.setDataBits(QSerialPort::Data8);
        serial.setFlowControl(QSerialPort::NoFlowControl);
        serial.setParity(QSerialPort::NoParity);
       // portMode = SERIALCOM;
       return true;
    }
    else
    {
        serial.close();
        return false;
    }


}
/*********************************************************************
 * @auther
 * @brief
 * @description
 * @param[in]		None.
 * @param[out]		None.
 * @return
 *
 **********************************************************************/
bool Serial::SerialClose(void)
{
    serial.close();
   return true;
}

/*********************************************************************
 * @auther
 * @brief           send char
 * @description
 * @param[in]		None.
 * @param[out]		None.
 * @return
 *
 **********************************************************************/
void Serial::SendChar(char data)
{
    //serial.waitForBytesWritten(10);
    serial.write(&data,1);

}

/*********************************************************************
 * @auther
 * @brief           puts
 * @description
 * @param[in]		None.
 * @param[out]		None.
 * @return
 *
 **********************************************************************/
void Serial::Puts(quint8 *data, int count)
{
    QByteArray buffer;
    int i;

    for(i=0;i<count;i++)
        buffer[i] = *(data+i);


    //serial.waitForBytesWritten(10);
    serial.write(buffer,count);

}

/*********************************************************************
 * @auther
 * @brief           get char
 * @description
 * @param[in]		None.
 * @param[out]		None.
 * @return
 *
 **********************************************************************/
char Serial::GetChar(void)
{
  char ch;
  serial.waitForReadyRead(100);
  serial.read(&ch,1);
  return ch;
}

/*********************************************************************
 * @auther
 * @brief           get's
 * @description
 * @param[in]		None.
 * @param[out]		None.
 * @return
 *
 **********************************************************************/
int Serial::GetS(QByteArray *data)
{
    serial.waitForReadyRead(100);
    int i = serial.bytesAvailable();
    *data = serial.readAll();
    return i;
}

/*********************************************************************
 * @auther
 * @brief           wait for ready read
 * @description
 * @param[in]		None.
 * @param[out]		None.
 * @return
 *
 **********************************************************************/
void Serial::WaitForReadyRead(void)
{
  serial.waitForReadyRead(10000);
}

