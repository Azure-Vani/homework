/*
任务1：
目标：
阅读理解函数 get_img_ele(); set_img_ele();的功能。
阅读理解掌握离散图像中x方向一阶、二阶偏导数（dx2）的计算方式,补充完成y方向一阶、二阶偏导数函数。
（函数定义在文件：snd_order_gradient.cpp中。）

运行并显示结果，理解这些数学量的物理意义。

参考资料：
1.离散图像二阶导数dx^2, dy^2, dxdy
http://hi.baidu.com/shareshow/blog/item/34abdf544725cf54d109069b.html/cmtid/7718f40398ef4f793912bb9e

*/
#include "grad_fun.h"
#include "highgui.h"
#include "cv.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;



int main()
{
	char img_file[] = "1.jpg";  //显示原图
	IplImage* image = cvLoadImage(img_file, CV_LOAD_IMAGE_GRAYSCALE);
	cvNamedWindow("show_src");
	cvShowImage("show_src", image);
	cvWaitKey(0);
	

	IplImage* xdev1 = fst_order_deri_x(image);  //显示一阶x偏导结果
	cvNamedWindow("show_x1");
	cvShowImage("show_x1", xdev1);
	cvWaitKey(0);

	IplImage* ydev1 = fst_order_deri_y(image);  //显示一阶x偏导
	cvNamedWindow("show_y1");
	cvShowImage("show_y1", ydev1);
	cvWaitKey(0);

	IplImage* xdev2 = snd_order_deri_x(image);//显示二阶x偏导
	cvNamedWindow("show_x2");
	cvShowImage("show_x2", xdev2);
	cvWaitKey(0);


	IplImage* ydev2 = snd_order_deri_y(image);//显示二阶y偏导
	cvNamedWindow("show_y2");
	cvShowImage("show_y2", ydev2);
	cvWaitKey(0);

	IplImage* xydev2 = snd_order_deri_x(image);//显示二阶xy偏导
	cvNamedWindow("show_xy");
	cvShowImage("show_xy", xydev2);
	cvWaitKey(0);

	IplImage* hessian_img = detHessian(image);
	cvNamedWindow("show_hessian");
	cvShowImage("show_hessian", hessian_img);
	cvWaitKey(0);


	IplImage* des_hessian = smoothHessian(image);
	cvNamedWindow("show_smoothHessian");
	cvShowImage("show_smoothHessian", des_hessian);
	cvWaitKey(0);

	cvReleaseImage(&des_hessian);
	cvReleaseImage(&hessian_img);
	cvReleaseImage(&image);
	cvReleaseImage(&xdev1);
	cvReleaseImage(&ydev1);
	cvReleaseImage(&xdev2);
	cvReleaseImage(&ydev2);
	cvReleaseImage(&xydev2);
}
