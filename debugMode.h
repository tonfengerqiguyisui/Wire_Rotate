#pragma once

#include <QtWidgets/QDialog>
//#include "ui_debugMode.h"
#include <QPushButton>
#include <QLabel>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QDebug>
#include <QRadioButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QMessageBox>
#include <QSizePolicy>

// #include <QSpacerItem>

// ֧������
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif


class debugMode : public QDialog
{
	Q_OBJECT

public:
	debugMode(QWidget *parent = Q_NULLPTR);

private slots:
// ��һ��
void on_nextStep_clicked();
void on_resetButton_clicked();
// �ڶ���
void on_confirmOutput_clicked();
void on_degreeText_textChanged(QString text);

// ������
void on_confirmOutput2_clicked();
void on_degreeText2_textChanged(QString text);

private:
// ���ץͼ�Ļص�����
void on_cb_cameraGrabber_stateChanged(int flag);
// ����ǶȵĻص�����
void on_cb_calculateDegree_stateChanged(int flag);
// ����ǶȵĻص�����
void on_cb_outputDegree_stateChanged(int flag);

private:
//	Ui::debugModeClass ui;

	// �ֲ�������
	QGroupBox *createStepGroup();
	// ��ת�Ƕȵ�����
	QGroupBox *createOutputGroup();
	// ƫת�Ƕȵ�����
	QGroupBox *createOutput2Group();

	int widthOfDialog = 500;

	QLabel *debugInStep;

	//========== ״̬��ʾ ================//
	QCheckBox *cb_cameraGrabber;
	QCheckBox *cb_calculateDegree;
	QCheckBox *cb_outputDegree;
	QPushButton *nextStep;
	QPushButton *resetButton;

	// �ڶ���GroupBox
	QLabel *debugInOutput;
	QLabel *inputDegrees;
	QLabel *warningMassege;
	QLineEdit *degreeText;
	QPushButton *confirmOutput;

	// ������GroupBox
	QLabel *debugInOutput2;
	QLabel *inputDegrees2;
	QLabel *warningMassege2;
	QLineEdit *degreeText2;
	QPushButton *confirmOutput2;

    const int widthD = 120;
    const int heightD = 50;

};
