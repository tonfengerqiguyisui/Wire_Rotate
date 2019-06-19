#include "maindialog.h"
#include "ui_maindialog.h"


MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    p.initFromConfig();

    this->showFullScreen();
    setWindowFlags(Qt::WindowCloseButtonHint); //隐藏标题栏问号
    setWindowFlag(Qt::FramelessWindowHint);     //设置窗体的标识，此处设置窗体为一个没有面板边框和标题栏的窗体
    this->setObjectName("dialog");    //这句话一定要有，不然，整个界面上的控件背景都跟界面背景一样
    this->setStyleSheet("QDialog#dialog{border-image:url(2.jpg)}");
    //ui->pushButton->setStyleSheet(“border-image:url(me.png)”); 按钮添加背景图片
    //利用painEvent显示，会卡顿
//    ca =new CameraDisplay(20,this);
//    ui->horizontalLayout->addWidget(ca);

    //调用开启相机自带的窗口，不卡顿，但窗口适应有些问题
    cam.Camera(ui->widget);
//    cam.Trigger(ui->widget);

    ui->lcdNumber_2->display("90°");
    ui->lcdNumber->display("-180°");

    //设置晶体管控件QLCDNumber能显示的位数
    ui->lcdNumber_3->setDigitCount(8);
      //设置显示的模式为十进制
    ui->lcdNumber_3->setMode(QLCDNumber::Dec);
      //设置显示方式
    ui->lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    //新建一个QTimer对象
    timer = new QTimer();
    //设置定时器每个多少毫秒发送一个timeout()信号
    timer->setInterval(1000);
    //启动定时器
    timer->start();

//    QImage *img=new QImage("./00.jpg");
//    QPixmap pixmap("00.jpg");
//    ui->label_7->setPixmap(pixmap);
    //slot
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(fun()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(debug()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(password()));
    connect(ui->pushButton_6, SIGNAL(clicked(bool)), this, SLOT(password1()));
    connect(ui->pushButton_8, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->pushButton_7, SIGNAL(clicked(bool)), this, SLOT(historyimage()));
    connect(ui->pushButton_9, SIGNAL(clicked(bool)), this, SLOT(grab()));
    connect(ui->pushButton_10, SIGNAL(clicked(bool)), this, SLOT(modbus()));
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

MainDialog::~MainDialog()
{
    delete ui;
}

//获取图片像素
//{
//QPainter painter(this);

// srcImage = new QImage("Image\\test.jpg");
// if (srcImage->isNull())
//     return;
// int srcH = srcImage->height();
// int srcW = srcImage->width();
// //显示源图像
// painter.drawImage(srcH, srcW, *srcImage, 0, 0);

// destImage = new QImage(srcW, srcH, srcImage->format());
// //扫描源图像素，实现翻转
// for (int line=0; line<srcW; line++)
//     for (int row=0; row<srcH; row++)
//     {
//         QRgb value = srcImage->pixel(row, line);
//         destImage->setPixel(line, row,value);
//     }

// painter.drawImage(srcW, srcH, *destImage, 200, 200);
// }


    //局部放大图片
//1.       setMouseTracking（）; 打开鼠标移动跟踪
//2.       局部放大图片的方法
//void Widget::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this);
//    painter.drawPixmap(0,0,background);
//    painter.drawPixmap(x+20,y+20,pixmap);
//}
//void Widget::mouseMoveEvent(QMouseEvent *event)
//{
//    x = event->x();
//    y = event->y();
//    //pixmap.fill(QColor(255,255,255,100));
//    mypixmap = mypixmap.grabWidget(this,x,y,10,10);
//    width = mypixmap.width();
//    height = mypixmap.height();
//    pixmap = mypixmap.scaled(width * 5,height * 5，Qt::KeepAspectRatio);         //适应横纵比


////    QPainter painter(&pixmap);
////    painter.setPen(QColor(255,0,0));
////painter.drawText(20,40,QString("%1").arg(x) + "," + QString("%1").arg(y));
//    update();
//}

void MainDialog::fun()
{
//    cam.Trigger(ui->widget);
}
void MainDialog::historyimage()
{
    w1.hisupdate();
    w1.show();
}
void MainDialog::debug()
{
    w3.show();
}
void MainDialog::password()
{
    w2.setflag(0);
    w2.show();
}
void MainDialog::password1()
{
    w2.setflag(1);
    w2.show();
}
void MainDialog::grab()
{
//    QImage img;QString filename;QString path=image_path;
//    QString str=QString::number(i);
//    img = cam.GetMatImage();
//    filename = filename.append(path + "90°-" + str +".jpg");
//    img.save(filename, "JPG", 100);
//    i++;
    QString str1=p.readhis();
    int num2 = str1.toInt();
    num++; num2++;
    str1=QString::number(num2);
    p.sethis(str1);
    num1=QString::number(num);  //QString::fromLocal8Bit  QStringLiteral
    ui->label_5->setText(num1);
    ui->label_6->setText(str1);
    this->update();
}
void MainDialog::onTimerOut()
{
  //获取系统当前时间
  QTime time = QTime::currentTime();
  //设置晶体管控件QLCDNumber上显示的内容
  ui->lcdNumber_3->display(time.toString("hh:mm:ss"));
}
void MainDialog::modbus()
{
    w4.show();
}