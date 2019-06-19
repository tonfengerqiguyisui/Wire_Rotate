// TIS_Camera.h: interface for the TIS_Camera class.
//
//////////////////////////////////////////////////////////////////////
#include "tisudshl.h"
#include "Listener1.h"//�ص�ͷ�ļ�
#include<opencv2\opencv.hpp>
#include <QtGui>


#if !defined(AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_)
#define AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



using namespace cv;
using namespace DShowLib;

class TIS_Camera  
{
public:
	TIS_Camera();
	 ~TIS_Camera();

	 
	 Listener1 *pListener1; //�ص�����
	
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
//    QImage GetMatImage();//��ȡͼƬͼƬ
//	void CameraClose();//�ر����
//	void CameraStart();//��ʼȡͼ
//	void CameraStop();//ֹͣȡͼ
//	void Camerapropery();//�������

//    QImage cvMat2QImage(const cv::Mat& mat, bool clone = true, bool rb_swap = true);
	/**
	* @brief �� OpenCV �� cv::Mat ����ͼ��ת��Ϊ QImage ����
	* @param mat ��ת����ͼ��֧�� CV_8UC1��CV_8UC3��CV_8UC4 ����OpenCV ����������
	* @param clone true ��ʾ�� Mat �������ڴ棬�������ɵ� mat ����Ӱ��ԭʼͼ��false ����� mat �����ڴ�
	* @param rb_swap ֻ��� CV_8UC3 ��ʽ����� true ������ R �� B RGB->BGR����������ڴ�Ļ�ԭʼͼ��Ҳ�ᷢ���仯
	* @return ת����� QImage ͼ��
	*/

private:

    Mat m_getmat;
    QImage m_qimg;


};

#endif // !defined(AFX_TIS_CAMERA_H__9AE25ADE_A9E6_4DFD_A8E0_6181580BA1D4__INCLUDED_)
