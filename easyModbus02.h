#pragma once
#include <QDebug>
#include <QSerialPort>
#include <QtSerialPort\qserialport.h>
#include <QtSerialPort\qserialportinfo.h>
#include <QString>
#include <string>
#include "CRC16.h"

//modbus class, which is very different to easyModbus01.h
class easyModbus2
{
public:
    easyModbus2();
    easyModbus2(int a);
    easyModbus2(QString selfDefinedPortName);
    ~easyModbus2();

	void sendMsg(QString  input);           //��������
	void sendMsg(int intInput);            //������������
    QByteArray readMsg();                   //��������

private:

	QSerialPort serialPort;      //������
	QString serialPortName;      //�򿪵Ĵ���
    QString received_Msg;        //���յ�������
    QByteArray receive_byte;     //���յ�������

    QString matchMessageA = "01 06 01 98 00 08 08 1F";
    QString matchMessageB = "01 06 01 98 00 08 08 1F";

    QString matchMessageAA = "3a30313035303530304646303046360D0A";

    QString matchMessageAB = "3a30313035303530304646303046360d0a";


    bool rtuOrAscii = true;
};

