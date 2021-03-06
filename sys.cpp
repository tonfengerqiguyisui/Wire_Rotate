﻿#include "sys.h"
#include "ui_sys.h"

Sys::Sys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sys)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowCloseButtonHint); //隐藏标题栏问号
    setWindowTitle(QString::fromLocal8Bit("系统设置"));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(Password()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(PicNum()));
    connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(close()));

    ui->lineEdit_3->setPlaceholderText(QString::fromLocal8Bit("建议设置为100到1000之间"));//设置无输入时的提示信息
}

Sys::~Sys()
{
    delete ui;
}

void Sys::Password()
{
    if (ui->lineEdit->text() == ui->lineEdit_2->text())
    {
        p.setpass(ui->lineEdit->text());
        QMessageBox::warning(this,QString::fromLocal8Bit("成功"),QString::fromLocal8Bit("密码已修改"),QMessageBox::Yes);
        qDebug() <<  p.readpass();
    }
    else
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("确认密码不一致！"),QMessageBox::Yes);
        //清除内容并定位光标
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit->setFocus();
    }
}

void Sys::PicNum()
{
    if(ui->lineEdit_3->text() ==  "")
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("错误"),QString::fromLocal8Bit("图片数量不能为空"),QMessageBox::Yes);
    }
    else
    {
        int tmp = ui->lineEdit_3->text().toInt();
        if(tmp < 100)
        {
            p.setpic("100");
            QMessageBox::warning(this,QString::fromLocal8Bit("成功"),QString::fromLocal8Bit("图片数量小于100，自动设置为100"),QMessageBox::Yes);
        }
        else
        {
        p.setpic(ui->lineEdit_3->text());
        QMessageBox::warning(this,QString::fromLocal8Bit("成功"),QString::fromLocal8Bit("图片数量已修改"),QMessageBox::Yes);
        //qDebug() <<  p.readpic();
        }
    }
}
