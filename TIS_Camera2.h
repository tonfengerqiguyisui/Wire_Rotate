/*********************************************************************************
  *Copyright(C)
  *ClassName:  TIS_Camera
  *Author:  豹�
  *Version: 1.0
  *Date:  2019.7.12
  *Description: ӳ���������,���ڲ������
                ���õ���ģʽ�����Բ���ʵ�������󣬱�֤��ֻ��һ��������󣬲�ͬ���ڲ���ͬһ�������
  *Others:  //��������˵��
  *Function List:  Camera(QWidget *win) //���ֱ����ʾʵʱͼ�� �贫����ʾWidget�ľ��
  *                Trigger(QWidget *win) //Ӳ����ģʽ
  *                CameraInit() //�����ʼ��������������ò�����������
  *                bool Valid() //�ж����״̬����Ϊtrue
  *                Mat GetMatImage();//ץͼ
  *History:  //�޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸��߼��޸����ݼ��
**********************************************************************************/

// TIS_Camera.h: interface for the TIS_Camera class.
//
//////////////////////////////////////////////////////////////////////
#include "tisudshl.h"
#include "Listener2.h"//�ص�ͷ�ļ�
#include<opencv2\opencv.hpp>
#include <QtGui>
#include <QObject>

//���ϻ᲻��������
//#if !defined(AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_)
//#define AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_

//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000



using namespace cv;
using namespace DShowLib;

class TIS_Camera2 : public QObject
{
    Q_OBJECT

public:
    TIS_Camera2();
     ~TIS_Camera2();

    //ʵ�ֵ���ģʽ����ʹ�������������ܹ�ʹ�� ��֤�˲�ͬ��֮��ʹ����ͬһ�����󣬱������ź���۵Ĵ��ݣ����������߼��Ĺ�ͨ
    static TIS_Camera2 *Instance(){
        if (!_instance) {
            _instance = new TIS_Camera2;
        }
        return _instance;
    }

     Listener2 *pListener1; //�ص�����
	
	 //�������ȡͼ��ӿڶ���
//     DShowLib::Grabber *Grab1;
     DShowLib::Grabber Grab1;
	 tFrameHandlerSinkPtr pSink;
	 tIVCDPropertyInterfacePtr	 pItf;	
	 tIVCDPropertyItemsPtr		 pProps;
	 Grabber::tVidFmtListPtr  pVidCapDevList;
	 
    void Camera(QWidget *win); // xiangji zhijie xianshi
    void Trigger(QWidget *win); //wai bu chufa
    void CameraInit();//�����ʼ��
//	void CameraShowImage();//ʵʱ��ʾͼƬ
//	void CamBin(int Bvalue);//Binning��
    bool Valid(); //detect  camera statute
    Mat GetMatImage();//��ȡͼƬͼƬ
//	void CameraClose();//�ر����
//	void CameraStart();//��ʼȡͼ
//	void CameraStop();//ֹͣȡͼ
//	void Camerapropery();//�������

    QImage cvMat2QImage(const cv::Mat& mat, bool clone = true, bool rb_swap = true);
	/**
	* @brief �� OpenCV �� cv::Mat ����ͼ��ת��Ϊ QImage ����
	* @param mat ��ת����ͼ��֧�� CV_8UC1��CV_8UC3��CV_8UC4 ����OpenCV ����������
	* @param clone true ��ʾ�� Mat �������ڴ棬�������ɵ� mat ����Ӱ��ԭʼͼ��false ����� mat �����ڴ�
	* @param rb_swap ֻ��� CV_8UC3 ��ʽ����� true ������ R �� B RGB->BGR����������ڴ�Ļ�ԭʼͼ��Ҳ�ᷢ���仯
	* @return ת����� QImage ͼ��
	*/

signals:
     void ini();
private:

     static TIS_Camera2 *_instance;       //ʵ������
    Mat m_getmat;
    QImage m_qimg;


};

//#endif // !defined(AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_)
