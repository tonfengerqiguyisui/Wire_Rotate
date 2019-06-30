#include "debugmode.h"

debugMode::debugMode(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    setWindowFlags(Qt::WindowCloseButtonHint); //���ر������ʺ�
	// ���ź�����
	// connect(ui.pb_nextStep, SIGNAL(clicked()), this, SLOT(on_pb_nextStep_clicked()));

	// ============= ״ָ̬ʾ������ ==================//
	vStateWidget.resize(numberOfLight);
	for (int i = 0; i < numberOfLight; i++) {
		vStateWidget.at(i) = new stateWidget();
	}

	vStateWidget.at(0) = dynamic_cast<stateWidget*>(ui.wd_cameraGrabber);
	vStateWidget.at(1) = dynamic_cast<stateWidget*>(ui.wd_calculateDegree);
	vStateWidget.at(2) = dynamic_cast<stateWidget*>(ui.wd_outputDegree);

	vStateWidget.at(0)->lightTextStr = "���ץͼ";
	vStateWidget.at(1)->lightTextStr = "����Ƕ�";
	vStateWidget.at(2)->lightTextStr = "����Ƕ�";

	// ui.lb_cameraGrabber->setAlignment(Qt::AlignCenter);

	for (int i = 0; i < numberOfLight; i++) {
		vStateWidget.at(i)->turnOn();
	}

}

void debugMode::on_pb_nextStep_clicked()
{
	this->stateNumber += 1;
	this->stateNumber %= (this->numberOfLight + 1);

	if (this->stateNumber == 0) {
		for (int i = 0; i < this->numberOfLight; i++) {
            vStateWidget.at(i)->m_color = Qt::blue;
			vStateWidget.at(i)->turnOn();
			vStateWidget.at(i)->update();
		}
	}
	else {
		for (int i = 0; i < this->stateNumber; i++) {
			vStateWidget.at(i)->m_color = Qt::green;
			vStateWidget.at(i)->turnOn();
			vStateWidget.at(i)->update();
		}
	}

	// qDebug() << this->stateNumber << endl;
	if (this->stateNumber == 1) {
		// ִ��=���ץͼ=��=�ص�����=
        emit grab_signal();

	}
	else if (this->stateNumber == 2) {
		// ִ��=����Ƕ�=��=�ص�����=
        emit caculate();
	}
	else if (this->stateNumber == 3) {
		// ִ��=����Ƕ�=��=�ص�����=
        emit outcome();
	}

}

void debugMode::on_pb_reset_clicked()
{
	for (int i = 0; i < this->numberOfLight; i++) {
        vStateWidget.at(i)->m_color = Qt::blue;
		vStateWidget.at(i)->turnOn();
		vStateWidget.at(i)->update();
	}
	this->stateNumber = 0;
}

void debugMode::on_pb_confirmOutputO_clicked()
{
	QString temp = ui.le_inputDegreeO->text();
	bool okNow = false;
	int val = temp.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			// ִ��������õĺ���
			// =�ص�����= ������ǶȵĻص�������
            emit out(val);
			qDebug() << "ȷ������Ƕ���ȷ" << "\n";
		}
		else
		{
			// ����
			qDebug() << "����Խ��" << "\n";
			QMessageBox::critical(NULL, "", ("����Խ�磬���������루-180��, 180�㣩�������Ƕ�"), QMessageBox::Ok, QMessageBox::Ok);
		}
	}
	else
	{
		// ����
		qDebug() << "�������" << "\n";
		QMessageBox::critical(NULL, "", "���������Ч�ַ���С����", QMessageBox::Ok, QMessageBox::Ok);
	}
}

void debugMode::on_le_inputDegreeO_textChanged(const QString &arg1)
{
	if (arg1.isEmpty()) {
		ui.lb_warningMsg->setText("");
		return;
	}

	bool okNow = false;
	int val = arg1.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			ui.lb_warningMsg->setText("");
		}
		else
		{
			//ui.lb_warningMsg->setText("-180, 180");
			ui.lb_warningMsg->setText("�����루-180��, 180�㣩������ֵ");
		}
	}
	else
	{
		ui.lb_warningMsg->setText("���������Ч�ַ���С����");
	}
}

void debugMode::on_le_inputDegreeT_textChanged(const QString &arg1)
{
	if (arg1.isEmpty()) {
		ui.lb_warningMsg_2->setText("");
		return;
	}

	bool okNow = false;
	int val = arg1.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			ui.lb_warningMsg_2->setText("");
		}
		else
		{
			// ui.lb_warningMsg_2->setText("-180, 180");
			ui.lb_warningMsg->setText("�����루-180��, 180�㣩������ֵ");
		}
	}
	else
	{
		ui.lb_warningMsg_2->setText("���������Ч�ַ���С����");
	}
}

void debugMode::on_pb_confirmOutputT_clicked()
{
	QString temp = ui.le_inputDegreeT->text();
	bool okNow = false;
	int val = temp.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			// ===============ִ��������õĺ���
			// =�ص�����= ��ƫת�ǶȵĻص�������
            emit deflection(val);
			qDebug() << "ȷ������Ƕ���ȷ" << "\n";


		}
		else
		{
			// ����
			qDebug() << "����Խ��" << "\n";
			QMessageBox::critical(NULL, "", QObject::trUtf8("����Խ�磬���������루-180��, 180�㣩�������Ƕ�"), QMessageBox::Ok, QMessageBox::Ok);
		}
	}
	else
	{
		// ����
		qDebug() << "�������" << "\n";
		QMessageBox::critical(NULL, "", "���������Ч�ַ���С����", QMessageBox::Ok, QMessageBox::Ok);
	}
}
