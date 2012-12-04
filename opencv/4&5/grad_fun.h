#pragma once

#include "highgui.h"
#include "cv.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

int get_img_ele(IplImage* img, int x, int y);          // get_img_ele������ȡimgͼ���е�y�У���x������ֵ
void set_img_ele(IplImage* img, int x, int y, int ele);// set_img_ele��������imgͼ���е�y�У���x������ֵ

IplImage* fst_order_deri_x(IplImage* src);// fst_order_deri_x��������srcͼ����x����������������ֵ�����ͼ���з���
IplImage* fst_order_deri_y(IplImage* src);// fst_order_deri_y��������srcͼ����y����������������ֵ�����ͼ���з���
IplImage* gradient(IplImage* src);//�����ݶ�

IplImage* snd_order_deri_x(IplImage* src);  // snd_order_deri_x��������srcͼ����x������׵�����IplImage* snd_order_deri_y(IplImage* src);// snd_order_deri_y��������srcͼ����y������׵�������������ֵ�����ͼ���з���
IplImage* snd_order_deri_y(IplImage* src);  // snd_order_deri_y��������srcͼ����y������׵�������������ֵ�����ͼ���з���
IplImage* snd_order_deri_x_y(IplImage* src);// snd_order_deri_y��������srcͼ����y������׵�������������ֵ�����ͼ���з���

IplImage* _detHessian(IplImage*, IplImage*, IplImage*);
IplImage* detHessian(IplImage*);
IplImage* smoothHessian(IplImage*);
