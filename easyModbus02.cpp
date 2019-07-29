#include "easyModbus02.h"

easyModbus2::easyModbus2(int numberOfRegister)
{
    // use the user-defined register
    this->numberOfRegister = numberOfRegister;
}

easyModbus2::~easyModbus2()
{
    serialPort.clear();
    serialPort.close();
}

int easyModbus2::initSerialPort()
{
    this->hasMatchPort = false;
    QStringList mPortNameList;  //�����б�
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    if (!portList.empty()) {
        foreach(const QSerialPortInfo &info, portList)
        {
            // qDebug() << "SerialPortList:";
            mPortNameList.push_back(info.portName());
            // qDebug() << "    SerialPortName:" << info.portName();
        }

        for(auto sPortName:mPortNameList){
            this->serialPortName = sPortName;
            serialPort.setPortName(serialPortName);
            serialPort.setBaudRate(QSerialPort::Baud38400);           //���ò����ʺͶ�д����
            serialPort.setDataBits(QSerialPort::Data8);              //����λΪ8λ
            serialPort.setFlowControl(QSerialPort::NoFlowControl);   //��������
            serialPort.setParity(QSerialPort::NoParity);           //��У��λ
            serialPort.setStopBits(QSerialPort::OneStop);            //һλֹͣλ
            if (serialPort.isOpen())                                 //��������Ѿ����� �ȸ����ر���
            {
                serialPort.clear();
                serialPort.close();
            }

            if (!serialPort.open(QIODevice::ReadWrite))              //��ReadWrite ��ģʽ���Դ򿪴���
            {
                continue;
            }
            else
            {
                // ===== Matching Serial Port ======= //
                this->matchMessageSend = QString::fromStdString(fxlib.getWriteMsg(this->numberOfRegister, 0));
                sendMsg(this->matchMessageSend);
                QByteArray receiveByte = readMsg();
                QString receivedMsg = receiveByte.toHex();
                if (receivedMsg == this->matchMessageRight)
                {
                    this->hasMatchPort = true;
                    qDebug() << QObject::tr("Successful Opening of Serial Port: %1").arg(this->serialPortName) << endl;
                    return 1;
                }
            }
        }
    }
    else
    {
        return -1;
    }
    return -1;
}

void easyModbus2::sendMsg(QString input)
{

    QString str = input;
    // === �������� === //
    QByteArray writeData = QByteArray::fromHex(str.toLatin1().data());

    serialPort.clear();
    qint64 bytesWritten = serialPort.write(writeData);

    if(bytesWritten == -1 || bytesWritten != writeData.size() || !serialPort.waitForBytesWritten(300)){
        throw 100;
    }

}

void easyModbus2::sendMsg(int intInput)
{

    if(!this->hasMatchPort){
        throw 100;
    }

    // д�����Ĵ��� ��ʾ����
    QString input;
    if(intInput < 0){
        intInput = abs(intInput);
        input = QString::fromStdString(fxlib.getWriteMsg(this->numberOfRegister, intInput));

    }
    else{
        input = QString::fromStdString(fxlib.getWriteMsg(this->numberOfRegister + 2, intInput));
    }
    sendMsg(input);
    // QString input = QString::fromStdString(LRC::convertIntToModbusString(intInput, this->numberOfRegister));
    // === test receive === //
    // ==== һ��Ҫ��һ�²��ܱ�֤д�룬����ԭ����
//    if(true){
//        QByteArray receiveByte = readMsg();
////        for(int i = 0; i < receiveByte.size();i++){
////            std::cout << (receiveByte[i]);
////        }
//    }

}

QByteArray easyModbus2::readMsg()
{
	QByteArray readData = serialPort.readAll();
    while (serialPort.waitForReadyRead(1000)){
        readData.append(serialPort.readAll());
    }

//	if (serialPort.error() == QSerialPort::ReadError)
//	{
//		qDebug() << QObject::tr("Failed to read from port %1 ,error: %2 ").arg(serialPortName).arg(serialPort.errorString()) << endl;
//	}
//	else if (serialPort.error() == QSerialPort::TimeoutError && readData.isEmpty())
//	{
//		qDebug() << QObject::tr("No data was currently available for reading from port %1").arg(serialPortName) << endl;
//	}
//    else{
//        qDebug() << QObject::tr("Data successfully received from port %1").arg(serialPortName) << endl;
//    }
//    if(!readData.isEmpty()){
//        qDebug() << readData.toHex() << endl;
//        //	QString backdata = readData.toHex();
//        //  qDebug() << readData.toHex();
//    }
	return readData;
}
