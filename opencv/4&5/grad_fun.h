#pragma once

#include "highgui.h"
#include "cv.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

int get_img_ele(IplImage* img, int x, int y);          // get_img_ele函数获取img图像中第y行，第x列像素值
void set_img_ele(IplImage* img, int x, int y, int ele);// set_img_ele函数设置img图像中第y行，第x列像素值

IplImage* fst_order_deri_x(IplImage* src);// fst_order_deri_x函数计算src图像中x方向导数，并将导数值存放在图像中返回
IplImage* fst_order_deri_y(IplImage* src);// fst_order_deri_y函数计算src图像中y方向导数，并将导数值存放在图像中返回
IplImage* gradient(IplImage* src);//计算梯度

IplImage* snd_order_deri_x(IplImage* src);  // snd_order_deri_x函数计算src图像中x方向二阶导数，IplImage* snd_order_deri_y(IplImage* src);// snd_order_deri_y函数计算src图像中y方向二阶导数，并将导数值存放在图像中返回
IplImage* snd_order_deri_y(IplImage* src);  // snd_order_deri_y函数计算src图像中y方向二阶导数，并将导数值存放在图像中返回
IplImage* snd_order_deri_x_y(IplImage* src);// snd_order_deri_y函数计算src图像中y方向二阶导数，并将导数值存放在图像中返回

IplImage* _detHessian(IplImage*, IplImage*, IplImage*);
IplImage* detHessian(IplImage*);
IplImage* smoothHessian(IplImage*);
