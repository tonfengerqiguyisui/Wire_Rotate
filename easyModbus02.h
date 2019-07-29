#pragma once
#include <QDebug>
#include <QSerialPort>
#include <QtSerialPort\qserialport.h>
#include <QtSerialPort\qserialportinfo.h>
#include <QString>
#include <string>
#include <iostream>
#include <FxPlc.h>
//#pragma comment(lib,"FxPlc.lib")

/**
* @brief        ��ASCII�ı�����PLC����ͨѶ
*               �����ԭ��
*               1.��Ĺ��캯����ΪeasyModbus2(int) ������ָ��д��Ĵ���
*               2.int initSerialPort() -- �Զ���Ⲣ��ʼ�����ڲ����س�ʼ�����ڵ�״̬
*               3.sengMsg ������Ϣ������
*               4.readMsg ��ȡ����
* @author        George
* @date          2019-07-04
*/

class easyModbus2
{
public:
    easyModbus2() = default;
    easyModbus2(int numberOfRegister);
    ~easyModbus2();

    int initSerialPort();
	void sendMsg(QString  input);           //��������
    void sendMsg(int intInput);             //�������νǶ�����
    QByteArray readMsg();                   //��������

private:

    bool hasMatchPort = false;

	QSerialPort serialPort;      //������
	QString serialPortName;      //�򿪵Ĵ���

    // ==== The setting of modbus ===== //
    //// == register == ////
    int numberOfRegister = 2000;

    //// == Matching message == ////
    QString matchMessageSend = ""; // int 0

    QString matchMessageRight = "06"; // ������Ϣ��ȷ��ĵ��»ظ�

    FxLib fxlib;
};

