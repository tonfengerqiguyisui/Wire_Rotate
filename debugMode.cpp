#include "debugMode.h"

debugMode::debugMode(QWidget *parent)
	: QDialog(parent)
{
//	ui.setupUi(this);
	this->setWindowTitle("����ģʽ");
	this->setWindowFlags(Qt::WindowCloseButtonHint); //���ر������ʺ�
	this->setGeometry(widthOfDialog / 5, widthOfDialog / 5, widthOfDialog, widthOfDialog);

	QGridLayout *grid = new QGridLayout;
	grid->addWidget(createStepGroup(), 0, 0);
	grid->addWidget(createOutputGroup(), 1, 0);
	grid->addWidget(createOutput2Group(), 2, 0);
	setLayout(grid);

	// resize(480, 320);
}

void debugMode::on_confirmOutput_clicked() {
	QString temp = this->degreeText->text();
	bool okNow = false;
	int val = temp.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			// ִ��������õĺ���
			qDebug() << "ȷ������Ƕ���ȷ" << "\n";

		}
		else
		{
			// ����
			qDebug() << "����Խ��" << "\n";
			QMessageBox::critical(NULL, "", "����Խ�磬���������루-180��, 180�㣩�������Ƕ�", QMessageBox::Ok, QMessageBox::Ok);
		}
	}
	else
	{
		// ����
		qDebug() << "�������" << "\n";
		QMessageBox::critical(NULL, "", "���������Ч�ַ���С����", QMessageBox::Ok, QMessageBox::Ok);
	}
}

void debugMode::on_degreeText_textChanged(QString text)
{

	if (text.isEmpty()) {
		this->warningMassege->setText("");
		return;
	}

	bool okNow = false;
	int val = text.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			this->warningMassege->setText("");
		}
		else
		{
			this->warningMassege->setText("�����루-180�㣬180�㣩������ֵ");
		}
	}
	else
	{
		this->warningMassege->setText("���������Ч�ַ���С����");
	}
}

void debugMode::on_confirmOutput2_clicked()
{
	QString temp = this->degreeText2->text();
	bool okNow = false;
	int val = temp.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			// ִ��������õĺ���
			qDebug() << "ȷ������Ƕ���ȷ" << "\n";

		}
		else
		{
			// ����
			qDebug() << "����Խ��" << "\n";
			QMessageBox::critical(NULL, "", "����Խ�磬���������루-180��, 180�㣩�������Ƕ�", QMessageBox::Ok, QMessageBox::Ok);
		}
	}
	else
	{
		// ����
		qDebug() << "�������" << "\n";
		QMessageBox::critical(NULL, "", "���������Ч�ַ���С����", QMessageBox::Ok, QMessageBox::Ok);
	}
}

void debugMode::on_degreeText2_textChanged(QString text)
{
	if (text.isEmpty()) {
		this->warningMassege2->setText("");
		return;
	}

	bool okNow = false;
	int val = text.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			this->warningMassege2->setText("");
		}
		else
		{
			this->warningMassege2->setText("�����루-180�㣬180�㣩������ֵ");
		}
	}
	else
	{
		this->warningMassege2->setText("���������Ч�ַ���С����");
	}
}

void debugMode::on_nextStep_clicked()
{
	if (this->cb_cameraGrabber->isChecked()) {
		if (this->cb_calculateDegree->isChecked()) {
			if (this->cb_outputDegree->isChecked()) {

				this->cb_cameraGrabber->setChecked(false);
				this->cb_calculateDegree->setChecked(false);
				this->cb_outputDegree->setChecked(false);

			}
			else{
				this->cb_outputDegree->setChecked(true);
			}
		}
		else {
			this->cb_calculateDegree->setChecked(true);
		}
	}
	else
	{
		this->cb_cameraGrabber->setChecked(true);
	}
}

void debugMode::on_resetButton_clicked()
{
	this->cb_cameraGrabber->setChecked(false);
	this->cb_calculateDegree->setChecked(false);
	this->cb_outputDegree->setChecked(false);
}

void debugMode::on_cb_cameraGrabber_stateChanged(int flag)
{
	if (flag == 0) {
		return;
	}
	else
	{
		// ִ�лص����� -- �ɼ�ͼƬ
		qDebug() << "���ץͼ" << "\n";
	}
}

void debugMode::on_cb_calculateDegree_stateChanged(int flag)
{
	if (flag == 0) {
		return;
	}
	else
	{
		// ִ�лص����� -- ����Ƕ�
		qDebug() << "����Ƕ�" << "\n";
	}
}

void debugMode::on_cb_outputDegree_stateChanged(int flag)
{
	if (flag == 0) {
		return;
	}
	else
	{
		// ִ�лص����� -- ����Ƕ�
		qDebug() << "����Ƕ�" << "\n";
	}
}

// ��������

QGroupBox * debugMode::createStepGroup()
{
	QGroupBox *groupBox = new QGroupBox(tr("�ֲ�����"));

	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// ���ץͼ
	cb_cameraGrabber = new QCheckBox(this);
	cb_cameraGrabber->setText("���ץͼ");
	//cb_cameraGrabber->setMaximumSize(widthD, heightD);
	//cb_cameraGrabber->setSizePolicy(sizePolicy);
	cb_cameraGrabber->setDisabled(true);
	//cb_cameraGrabber->setGeometry(widthOfDialog / 25, widthOfDialog / 25 + 2 * widthOfDialog / 25, widthOfDialog / 5, widthOfDialog / 10);
	connect(cb_cameraGrabber, SIGNAL(stateChanged(int)), this, SLOT(on_cb_cameraGrabber_stateChanged(int)));

	// ����Ƕ�
	cb_calculateDegree = new QCheckBox(this);
	cb_calculateDegree->setText("����Ƕ�");
	cb_calculateDegree->setDisabled(true);
	//cb_calculateDegree->setMaximumSize(widthD, heightD);
	//cb_calculateDegree->setGeometry(widthOfDialog / 25 + widthOfDialog / 5 + 20, widthOfDialog / 25 + 2 * widthOfDialog / 25, widthOfDialog / 5, widthOfDialog / 10);
	connect(cb_calculateDegree, SIGNAL(stateChanged(int)), this, SLOT(on_cb_calculateDegree_stateChanged(int)));

	// ����Ƕ�
	cb_outputDegree = new QCheckBox(this);
	cb_outputDegree->setText("����Ƕ�");
	cb_outputDegree->setDisabled(true);
	//cb_outputDegree->setMaximumSize(widthD, heightD);
	//cb_outputDegree->setGeometry(widthOfDialog / 25 + 2 * widthOfDialog / 5 + 2 * 20, widthOfDialog / 25 + 2 * widthOfDialog / 25, widthOfDialog / 5, widthOfDialog / 10);
	connect(cb_outputDegree, SIGNAL(stateChanged(int)), this, SLOT(on_cb_outputDegree_stateChanged(int)));

	// ��һ��
	nextStep = new QPushButton(this);
	nextStep->setText("��һ��");
	nextStep->setMaximumSize(widthD, heightD);
	
	//sizePolicy.setHorizontalStretch(0);
	//sizePolicy.setVerticalStretch(0);
	//sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
	nextStep->setSizePolicy(sizePolicy);
	//nextStep->setGeometry(widthOfDialog / 20, widthOfDialog / 3, widthOfDialog / 8, widthOfDialog / 16);
	connect(nextStep, SIGNAL(clicked(bool)), this, SLOT(on_nextStep_clicked()));

	// ����
	resetButton = new QPushButton(this);
	resetButton->setText("����");
	resetButton->setMaximumSize(widthD, heightD);
	resetButton->setSizePolicy(sizePolicy);
	//resetButton->setGeometry(widthOfDialog / 5, widthOfDialog / 3, widthOfDialog / 8, widthOfDialog / 16);
	connect(resetButton, SIGNAL(clicked(bool)), this, SLOT(on_resetButton_clicked()));

	// �Ű�
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(cb_cameraGrabber);
	hbox->addWidget(cb_calculateDegree);
	hbox->addWidget(cb_outputDegree);
	//hbox->addStretch(1);

	QHBoxLayout *hbox2 = new QHBoxLayout;
	hbox2->addWidget(nextStep);
	//hbox2->addStretch(1);
	hbox2->addWidget(resetButton);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addLayout(hbox);
	vbox->addLayout(hbox2);
	groupBox->setLayout(vbox);

	return groupBox;
}

QGroupBox * debugMode::createOutputGroup()
{
	QGroupBox *groupBox = new QGroupBox(tr("�������"));

	// ��������ת�Ƕ�
	inputDegrees = new QLabel(this);
	inputDegrees->setText("��������ת�Ƕ�(/��):");
	//inputDegrees->setGeometry(widthOfDialog / 25, widthOfDialog / 2 + widthOfDialog / 16, widthOfDialog / 4, widthOfDialog / 16);

	// ��ת�Ƕ��ı�
	degreeText = new QLineEdit(this);
	degreeText->setText("");
	degreeText->setMaxLength(7);
	//degreeText->setGeometry(widthOfDialog / 25 + widthOfDialog / 4, widthOfDialog / 2 + widthOfDialog / 16, widthOfDialog / 8, widthOfDialog / 16);
	connect(degreeText, SIGNAL(textChanged(QString)), this, SLOT(on_degreeText_textChanged(QString)));
	// degreeText->setLineWidth(4);

	// ʵʱ�����ת�Ƕ��ı��������ֵ -- ���������������
	warningMassege = new QLabel(this);
	warningMassege->setText("");
	warningMassege->setStyleSheet("color: rgb(255, 0, 0); font: 10pt;");
	//warningMassege->setGeometry(widthOfDialog / 25 + widthOfDialog / 4 + widthOfDialog / 8 + 10, widthOfDialog / 2 + widthOfDialog / 16, 200, widthOfDialog / 16);
	  
	// ȷ�����
	confirmOutput = new QPushButton(this);
	confirmOutput->setText("ȷ�����");
	confirmOutput->setMaximumSize(widthD, heightD);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	confirmOutput->setSizePolicy(sizePolicy);
	//confirmOutput->setGeometry(widthOfDialog / 25 , widthOfDialog / 2 + widthOfDialog / 8, widthOfDialog / 8, widthOfDialog / 16);
	connect(confirmOutput, SIGNAL(clicked(bool)), this, SLOT(on_confirmOutput_clicked()));
	
	
	// �Ű�
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(inputDegrees);
	hbox->addWidget(degreeText);
	// hbox->addStretch(1);
	hbox->addWidget(warningMassege);
	// hbox->addStretch(1);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addLayout(hbox);
	QHBoxLayout *hbox4v = new QHBoxLayout;
	hbox4v->addStretch(0);
	hbox4v->addWidget(confirmOutput);
	hbox4v->addStretch(0);
	vbox->addLayout(hbox4v);
	groupBox->setLayout(vbox);

	return groupBox;
}

QGroupBox * debugMode::createOutput2Group()
{
	QGroupBox *groupBox = new QGroupBox(tr("ƫת�Ƕȵ���"));

	// ��������ת�Ƕ�
	inputDegrees2 = new QLabel(this);
	inputDegrees2->setText("������Ƕ�(/��):");
	//inputDegrees->setGeometry(widthOfDialog / 25, widthOfDialog / 2 + widthOfDialog / 16, widthOfDialog / 4, widthOfDialog / 16);

	// ��ת�Ƕ��ı�
	degreeText2 = new QLineEdit(this);
	degreeText2->setText("");
	degreeText2->setMaxLength(7);
	//degreeText->setGeometry(widthOfDialog / 25 + widthOfDialog / 4, widthOfDialog / 2 + widthOfDialog / 16, widthOfDialog / 8, widthOfDialog / 16);
	connect(degreeText2, SIGNAL(textChanged(QString)), this, SLOT(on_degreeText2_textChanged(QString)));
	// degreeText->setLineWidth(4);

	// ʵʱ�����ת�Ƕ��ı��������ֵ -- ���������������
	warningMassege2 = new QLabel(this);
	warningMassege2->setText("");
	warningMassege2->setStyleSheet("color: rgb(255, 0, 0); font: 10pt;");
	//warningMassege->setGeometry(widthOfDialog / 25 + widthOfDialog / 4 + widthOfDialog / 8 + 10, widthOfDialog / 2 + widthOfDialog / 16, 200, widthOfDialog / 16);

	// ȷ�����
	confirmOutput2 = new QPushButton(this);
	confirmOutput2->setText("ȷ�����");
	confirmOutput2->setMaximumSize(widthD,heightD);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	confirmOutput2->setSizePolicy(sizePolicy);
	//confirmOutput->setGeometry(widthOfDialog / 25 , widthOfDialog / 2 + widthOfDialog / 8, widthOfDialog / 8, widthOfDialog / 16);
	connect(confirmOutput2, SIGNAL(clicked(bool)), this, SLOT(on_confirmOutput2_clicked()));


	// �Ű�
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(inputDegrees2);
	hbox->addWidget(degreeText2);
	// hbox->addStretch(1);
	hbox->addWidget(warningMassege2);
	// hbox->addStretch(1);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addLayout(hbox);
	QHBoxLayout *hbox4v = new QHBoxLayout;
	hbox4v->addStretch(0);
	hbox4v->addWidget(confirmOutput2);
	hbox4v->addStretch(0);
	vbox->addLayout(hbox4v);
	groupBox->setLayout(vbox);

	return groupBox;
}
