#include "easyModbus02.h"

easyModbus2::easyModbus2()
{
    //initialize the first serial port
    // choose the first serialPort
    QStringList mPortNameList;  //�����б�

    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    if (!portList.empty()) {
        foreach(const QSerialPortInfo &info, portList)
        {
            mPortNameList.push_back(info.portName());
            qDebug() << "SerialPortName:" << info.portName();
        }
    }
    else
    {
        qDebug() << "No Available Serial Port" << endl;
    }

    int matchingFlag = false;

    for(auto sPortName:mPortNameList){
        this->serialPortName = sPortName;
        serialPort.setPortName(serialPortName);
        serialPort.setBaudRate(QSerialPort::Baud9600);//���ò����ʺͶ�д����
        serialPort.setDataBits(QSerialPort::Data8);      //����λΪ8λ
        serialPort.setFlowControl(QSerialPort::NoFlowControl);//��������
        serialPort.setParity(QSerialPort::NoParity); //��У��λ
        serialPort.setStopBits(QSerialPort::OneStop);  //һλֹͣλ
        if (serialPort.isOpen())//��������Ѿ����� �ȸ����ر���
        {
            // serialPort.clear();
            serialPort.close();
        }

        if (!serialPort.open(QIODevice::ReadWrite))//��ReadWrite ��ģʽ���Դ򿪴���
        {
            qDebug() << QObject::tr("Failed to open serial port: %1").arg(serialPortName) << endl;

        }
        else
        {
            // Matching Serial Port
            sendMsg(matchMessageA);
            QByteArray receiveByte = readMsg();
            QString receivedMsg = receiveByte.toHex();
            if (receivedMsg == matchMessageB)
            {
                qDebug() << QObject::tr("Successful Opening of Serial Port: %1").arg(serialPortName) << endl;
                matchingFlag = true;
                break;
            }
        }
    }
    if(!matchingFlag){
        qDebug() << QObject::tr("Please check the serial port. No suitable serial port can communicate.") << endl;
    }
}

easyModbus2::easyModbus2(QString selfDefinedPortName)
{

    this->serialPortName = selfDefinedPortName;
    serialPort.setPortName(serialPortName);
    serialPort.setBaudRate(QSerialPort::Baud9600);//���ò����ʺͶ�д����
    serialPort.setDataBits(QSerialPort::Data8);      //����λΪ8λ
    serialPort.setFlowControl(QSerialPort::NoFlowControl);//��������
    serialPort.setParity(QSerialPort::NoParity); //��У��λ
    serialPort.setStopBits(QSerialPort::OneStop);  //һλֹͣλ
    if (serialPort.isOpen())//��������Ѿ����� �ȸ����ر���
    {
        // serialPort.clear();
        serialPort.close();
    }

    if (!serialPort.open(QIODevice::ReadWrite))//��ReadWrite ��ģʽ���Դ򿪴���
    {
        qDebug() << QObject::tr("Failed to open serial port: %1").arg(serialPortName) << endl;

    }
    else
    {
        qDebug() << QObject::tr("Successful Opening of Serial Port: %1").arg(serialPortName) << endl;
    }
}

easyModbus2::~easyModbus2()
{
    serialPort.clear();
    serialPort.close();
}

void easyModbus2::sendMsg(QString input)
{
	QByteArray writeData;

	QString str;
	bool ok;
	char data;
	QStringList list;
	str = input;

	list = str.split(" ");
	for (int i = 0; i < list.count(); i++) {
		if (list.at(i) == " ")
			continue;
		if (list.at(i).isEmpty())
			continue;
		data = (char)list.at(i).toInt(&ok, 16);
		if (!ok)
		{
			qDebug() << "������������" << endl;
		}
		writeData.append(data);
	}
	////��������
	//	serialPort.write(buf);
    //  QByteArray str1=QByteArray::fromHex(str.toLatin1().data());???

	qint64 bytesWritten = serialPort.write(writeData);

	if (bytesWritten == -1)
	{
		qDebug() << QObject::tr("Failed to write the data to port %1 , error:%2").arg(serialPortName).arg(serialPort.errorString()) << endl;
	}
	else if (bytesWritten != writeData.size())
	{
		qDebug() << QObject::tr("Failed to write all the data to port %1 , error:%2").arg(serialPortName).arg(serialPort.errorString()) << endl;
	}
	else if (!serialPort.waitForBytesWritten(5000))
	{
		qDebug() << QObject::tr("Operation timed out or an error occurred for port %1 , error:%2").arg(serialPortName).arg(serialPort.errorString()) << endl;
	}
	//////////////////////��ʾ���͵�����/////////////////////////////////////////////////

	qDebug() << QObject::tr("Data successfully sent to port %1").arg(serialPortName) << endl;

	//////////////////////��ʾ���յ�����/////////////////////////////////////////////////
}

void easyModbus2::sendMsg(int intInput)
{
	QString input = QString::fromStdString(CRC16::convertIntToModbusString(intInput));
	sendMsg(input);
}

QByteArray easyModbus2::readMsg()
{
	QByteArray readData = serialPort.readAll();
	while (serialPort.waitForReadyRead(1000))
		readData.append(serialPort.readAll());
	if (serialPort.error() == QSerialPort::ReadError)
	{
		qDebug() << QObject::tr("Failed to read from port %1 ,error: %2 ").arg(serialPortName).arg(serialPort.errorString()) << endl;
	}
	else if (serialPort.error() == QSerialPort::TimeoutError && readData.isEmpty())
	{
		qDebug() << QObject::tr("No data was currently available for reading from port %1").arg(serialPortName) << endl;
	}
    else{
        qDebug() << QObject::tr("Data successfully received from port %1").arg(serialPortName) << endl;
    }
    if(!readData.isEmpty()){
        qDebug() << readData.toHex() << endl;
        //	QString backdata = readData.toHex();
        qDebug() << readData.toHex();
    }
	return readData;
}
