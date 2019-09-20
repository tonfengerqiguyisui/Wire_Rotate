#include "threeparams2.h"
#include "ui_threeparams2.h"

threeParams2::threeParams2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::threeParams2)
{
    ui->setupUi(this);

    this -> setWindowFlags(Qt::WindowCloseButtonHint); //���ر������ʺ�

    wd_AP = new AdjustParameters2(this);
    connect(this, &threeParams2::paramMinChanged, wd_AP, &AdjustParameters2::setParamMin);
    connect(this, &threeParams2::paramMaxChanged, wd_AP, &AdjustParameters2::setParamMax);
    connect(this, &threeParams2::paramDefaultChanged, wd_AP, &AdjustParameters2::setParamDefault);
    connect(this, &threeParams2::paramWinTitleChanged, wd_AP, &AdjustParameters2::setWinTitle);
    connect(this, &threeParams2::sendCvMat, wd_AP, &AdjustParameters2::setInDisplay);
}

threeParams2::~threeParams2()
{
    delete ui;
}

void threeParams2::on_pb_Yellow_clicked()
{
    QString winTitle = QString::fromLocal8Bit("��ɫͨ����������");
    emit paramWinTitleChanged(winTitle);

    std::vector<int> paramMin(10, 0); //��10��0
    std::vector<int> paramMax = {180, 180, 255, 255, 255, 255, 255, 255, 255, 255};//�����б�

    // === ��ini�ļ��У���ȡ���� === //
    std::vector<int> paramDefault = {120, 40, 0, 255, 25, 255, 0, 255, 0, 100};
    QString channelStr;
    channelStr.sprintf("Yellow");
    fileReader.readIni(channelStr, paramDefault);
    //����(ͼƬ��)
    emit paramMinChanged(paramMin);
    emit paramMaxChanged(paramMax);
    emit paramDefaultChanged(paramDefault);

    //QPixmap inputImg2 = QPixmap::fromImage(QImage(inFrame.data, inFrame.cols,
     //                                               inFrame.rows, inFrame.step, QImage::Format_RGB888).rgbSwapped());
    wd_AP->updataOutDisplay = false;
    if(hasInputImg){
        emit sendCvMat(this->inputImg);
    }

    wd_AP->exec();
}

void threeParams2::on_pb_Green_clicked()
{
    QString winTitle = QString::fromLocal8Bit("��ɫͨ����������");
    emit paramWinTitleChanged(winTitle);

    // qDebug() << "hello" << endl;
    std::vector<int> paramMin(10, 0);
    std::vector<int> paramMax = {180, 180, 255, 255, 255, 255, 255, 255, 255, 255};
    std::vector<int> paramDefault = {45, 100, 70, 255, 25, 255, 0, 255, 0, 255};

    fileReader.readIni(QString("Green"), paramDefault);

    emit paramMinChanged(paramMin);
    emit paramMaxChanged(paramMax);
    emit paramDefaultChanged(paramDefault);
    wd_AP->updataOutDisplay = false;
    if(hasInputImg){
        emit sendCvMat(this->inputImg);
    }

    wd_AP->exec();
}

void threeParams2::on_pb_Blue_clicked()
{
    QString winTitle = QString::fromLocal8Bit("��ɫͨ����������");
    emit paramWinTitleChanged(winTitle);

    std::vector<int> paramMin(10, 0);
    std::vector<int> paramMax = {180, 180, 255, 255, 255, 255, 255, 255, 255, 255};
    std::vector<int> paramDefault = {100, 120, 30, 255, 25, 255, 0, 255, 0, 255};

    fileReader.readIni(QString("Blue"), paramDefault);

    emit paramMinChanged(paramMin);
    emit paramMaxChanged(paramMax);
    emit paramDefaultChanged(paramDefault);

    wd_AP->updataOutDisplay = false;
    if(hasInputImg){
        emit sendCvMat(this->inputImg);
    }

    wd_AP->exec();
}

void threeParams2::on_pb_Brown_clicked()
{
    QString winTitle = QString::fromLocal8Bit("��ɫͨ����������");
    emit paramWinTitleChanged(winTitle);

    std::vector<int> paramMin(10, 0);
    std::vector<int> paramMax = {180, 180, 255, 255, 255, 255, 255, 255, 255, 255};
    std::vector<int> paramDefault = {120, 40, 0, 255, 25, 255, 0, 255, 100, 255};

    fileReader.readIni(QString("Brown"), paramDefault);

    emit paramMinChanged(paramMin);
    emit paramMaxChanged(paramMax);
    emit paramDefaultChanged(paramDefault);

    wd_AP->updataOutDisplay = false;
    if(hasInputImg){
        emit sendCvMat(this->inputImg);
    }

    wd_AP->exec();
}

void threeParams2::write_params(std::vector<std::vector<int>> &params1)
{
    std::vector<int> blueThreshold{ 100, 120, 30, 255, 25, 255, 0, 255, 0, 255 };
    std::vector<int> greenThreshold{ 45, 100, 70, 255, 50, 255, 0, 255, 0, 255 };
    std::vector<int> yellowThreshold{ 120, 40, 0, 255, 50, 255, 0, 255, 0, 100 };
    std::vector<int> brownThreshold{ 120, 40, 0, 255, 40, 255, 0, 255, 101, 255 };


    QString channelStr;
    channelStr.sprintf("Blue");
    fileReader.readIni(channelStr, blueThreshold);

    channelStr.sprintf("Green");
    fileReader.readIni(channelStr, greenThreshold);

    channelStr.sprintf("Yellow");
    fileReader.readIni(channelStr, yellowThreshold);

    channelStr.sprintf("Brown");
    fileReader.readIni(channelStr, brownThreshold);

    params1.push_back(blueThreshold);
    params1.push_back(greenThreshold);
    params1.push_back(yellowThreshold);
    params1.push_back(brownThreshold);
}
