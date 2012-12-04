#include "grad_fun.h"

// get_img_ele函数获取img图像中第y行，第x列像素值
int get_img_ele(IplImage* img, int x, int y)
{
	if (img == 0)
	{
		printf("Image null\n");
		exit(1);
	}
	if (img->nChannels != 1)
	{
		printf("Gray scale image needed as input\n");
		exit(1);
	}
	uchar* ptr = (uchar*)(img->imageData + y * img->widthStep);
	return ptr[x];
}

// set_img_ele函数设置img图像中第y行，第x列像素值
void set_img_ele(IplImage* img, int x, int y, int ele)
{
	if (img == 0)
	{
		printf("Image null\n");
		exit(1);
	}
	if (img->nChannels != 1)
	{
		printf("Gray scale image needed as input\n");
		exit(1);
	}
	uchar* ptr = (uchar*)(img->imageData + y * img->widthStep);
	ptr[x] = ele;
}


// fst_order_deri_x函数计算src图像中x方向导数，并将导数值存放在图像中返回
 IplImage* fst_order_deri_x(IplImage* src)
{
	if (src == 0)
	{
		printf("Null source image\n");
		exit(1);
	}
	if (src->nChannels != 1)
	{
		printf("Gray scale image needed as input\n");
		exit(1);
	}
	//得到输入图像的宽(x方向)、高(y方向)
	int width	= src->width;
	int height	= src->height;

	//将x方向梯度值保存在图像des的矩阵中
	//des图像大小、每个像素的字节数、通道数与输入图像src完全相同
	IplImage* des = cvCreateImage( cvSize(width, height), src->depth, src->nChannels);

	//x方向梯度计算式：des(i,j)=src(i,j+1)-src(i,j)，第一维是行，第二维是列
	//仅仅使用强度，则忽略符号，des(i,j)=|des(i,j)|
	//为图像中每一个像素计算x方向梯度，注意最后c的范围是[0, width-2]
	//这是因为最后一列元素右边没有元素，因此无法计算导数，可以赋默认值0

	/************************************************************************/
	/* Task:请补全下面三行注释对应的程序                                    */
	/************************************************************************/
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width-1; c++)
		{
			int dev;
			//求src(r,c)处的x方向导数
			dev = get_img_ele(src, c+1, r) - get_img_ele(src, c, r);
			//取dev的绝对值
			dev = dev > 0 ? dev : -dev;
			//将求得的导数值放到图像des的对应像素中
			set_img_ele(des, c, r, dev);
		}
	}
	return des;
}

// fst_order_deri_y函数计算src图像中y方向导数，并将导数值存放在图像中返回
IplImage* fst_order_deri_y(IplImage* src)
{
	if (src == 0)
	{
		printf("Null source image\n");
		exit(1);
	}
	if (src->nChannels != 1)
	{
		printf("Gray scale image needed as input\n");
		exit(1);
	}
	//得到输入图像的宽(x方向)、高(y方向)
	int width	= src->width;
	int height	= src->height;

	//将y方向梯度值保存在图像des中
	//des图像大小、每个像素的字节数、通道数与输入图像src完全相同
	IplImage* des = cvCreateImage( cvSize(width, height), src->depth, src->nChannels);

	//y方向梯度计算式：des(i,j)=src(i+1,j)-src(i,j)
	//仅仅使用强度，则忽略符号，des(i,j)=|des(i,j)|
	//为图像中每一个像素计算y方向梯度，注意最后r的范围是[0, height-2]
	//这是因为最后一行下边没有元素，因此无法计算导数，可以赋默认值0

	/************************************************************************/
	/* Task:请补全下面三行注释对应的程序                                    */
	/************************************************************************/
	for (int r = 0; r < height-1; r++)
	{
		for (int c = 0; c < width; c++)
		{
			int dev;
			//求src(r,c)处的y方向导数,存入dev
			dev = get_img_ele(src, c, r + 1) - get_img_ele(src, c, r);
			//取dev的绝对值
			dev = dev < 0 ? -dev : dev;
			//将导数值放到图像des中
			set_img_ele(des, c, r, dev);
		}
	}
	return des;
}



// snd_order_deri_x函数计算src图像中x方向二阶导数，并将导数值存放在图像中返回
IplImage* snd_order_deri_x(IplImage* src)
{
	if (src == 0)
	{
		printf("Null source image\n");
		exit(1);
	}
	if (src->nChannels != 1)
	{
		printf("Gray scale image needed as input\n");
		exit(1);
	}
	//得到输入图像的宽(x方向)、高(y方向)
	int width	= src->width;
	int height	= src->height;

	//将x方向二阶导数值保存在图像des中
	//des图像大小、每个像素的字节数、通道数与输入图像src完全相同
	IplImage* des = cvCreateImage( cvSize(width, height), src->depth, src->nChannels);

	//x方向二阶导数计算式：des(i,j)=src(i, j+2) + src(i, j) - 2 * src(i, j+1)
	//仅仅使用强度，则忽略符号，des(i,j)=|des(i,j)|
	//为图像中每一个像素计算x方向二阶偏导，注意最后c的范围是[0, width-3]
	//这是因为最后两列右边没有多于两列元素，因此无法计算二阶导数，可以赋默认值0

	/************************************************************************/
	/* Task:请补全下面三行注释对应的程序                                    */
	/************************************************************************/
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width-2; c++)
		{
			//求src(r,c)处的x方向导数
			int dev = get_img_ele(src, c+2, r) + get_img_ele(src, c, r) - 2 * get_img_ele(src, c+1, r);
			//取dev的绝对值
			dev = dev > 0 ? dev : -dev;
			//将导数值放到图像des中
			set_img_ele(des, c, r, dev);
		}
	}
	return des;
}

// snd_order_deri_y函数计算src图像中y方向二阶导数，并将导数值存放在图像中返回
IplImage* snd_order_deri_y(IplImage* src)
{
	if (src == 0)
	{
		printf("Null source image\n");
		exit(1);
	}
	if (src->nChannels != 1)
	{
		printf("Gray scale image needed as input\n");
		exit(1);
	}
	//得到输入图像的宽(x方向)、高(y方向)
	int width	= src->width;
	int height	= src->height;

	//将y方向二阶导数值保存在图像des中
	//des图像大小、每个像素的字节数、通道数与输入图像src完全相同
	IplImage* des = cvCreateImage( cvSize(width, height), src->depth, src->nChannels);

	//y方向二阶偏导计算式：des(i,j)=src(i+2,j)+src(i,j)-2*src(i+1,j)
	//仅仅使用强度，则忽略符号，des(i,j)=|des(i,j)|
	//为图像中每一个像素计算y方向二阶导数，注意最后r的范围是[0, height-3]
	//这是因为最后两行下边没有多于两行的元素，因此无法计算二阶导数，可以赋默认值0

	/************************************************************************/
	/* Task:请补全下面三行注释对应的程序                                    */
	/************************************************************************/

	for (int r = 0; r < height-2; r++)
	{
		for (int c = 0; c < width; c++)
		{
			//求src(r,c)处的y方向二阶导数
			int dev = get_img_ele(src, c, r + 2) + get_img_ele(src, c, r) - 2 * get_img_ele(src, c, r + 1);
			//结果取绝对值
			dev = dev < 0 ? -dev : dev;
			//将导数值放到图像des中
			set_img_ele(des, c, r, dev);
		}
	}
	return des;
}

// snd_order_deri_y函数计算src图像中y方向二阶导数，并将导数值存放在图像中返回
IplImage* snd_order_deri_x_y(IplImage* src)
{
	if (src == 0)
	{
		printf("Null source image\n");
		exit(1);
	}
	if (src->nChannels != 1)
	{
		printf("Gray scale image needed as input\n");
		exit(1);
	}

	/************************************************************************/
	/* Task:请补全下面两行注释对应的程序                                    */
	/************************************************************************/

	IplImage* dev_x;
	IplImage* dev_x_y;
	//1.为src图像计算x方向导数，保存在dev_x中
	dev_x = fst_order_deri_x(src);
	//2.为dev_x图像计算y方向导数，保存在dev_x_y中
	dev_x_y = fst_order_deri_y(dev_x);

	cvReleaseImage(&dev_x);
	return dev_x_y;
}

IplImage* gradient(IplImage* src)
{
	if (src == 0)
	{
		printf("Null source image\n");
		exit(1);
	}
	if (src->nChannels != 1)
	{
		printf("Gray scale image needed as input\n");
		exit(1);
	}
	//得到输入图像的宽(x方向)、高(y方向)
	int width	= src->width;
	int height	= src->height;

	//上机时下面代码会去掉，保留注释
	//计算x方向梯度
	IplImage* dx = fst_order_deri_x(src);

	//计算y方向梯度
	IplImage* dy = fst_order_deri_y(src);

	//将梯度值sqrt(dx^2+dy^2)保存在下面这个图像中
	//图像大小、每个像素的字节数、通道数与输入图像相同
	IplImage* des = cvCreateImage( cvSize(width, height), src->depth, src->nChannels);

	/************************************************************************/
	/* Task:请补全下面五行注释对应的程序                                    */
	/************************************************************************/
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			int dev_x; //x方向导数
			int dev_y; //y方向导数
			int grad;  //梯度值
			//计算x方向导数
			dev_x = get_img_ele(dx, c, r);
			//计算y方向导数
			dev_y = get_img_ele(dy, c, r);
			//计算梯度值
			grad = sqrt((double)(dev_x * dev_x + dev_y * dev_y));
			//对梯度取绝对值
			grad = grad < 0 ? -grad : grad;
			//将梯度值写到des图像中的对应位置
			set_img_ele(des, c, r, grad);
		}
	}
	return des;
}

IplImage* _detHessian(IplImage* src_x, IplImage* src_y, IplImage* src_xy) {
	int height = src_x->height;
	int width = src_x->width;

	IplImage *des = cvCreateImage(cvSize(height, width), src_x->depth, src_x->nChannels);

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++) {
			int tmp = get_img_ele(src_x, c, r) * get_img_ele(src_y, c, r) - get_img_ele(src_xy, c + 1, r) * get_img_ele(src_xy, c + 1, r);
			tmp = tmp < 0 ? -tmp : tmp;
			set_img_ele(des, c, r, tmp);
		}
	return des;
}

IplImage* detHessian(IplImage *src) {
	IplImage* src_x = snd_order_deri_x(src);
	IplImage* src_y = snd_order_deri_y(src);
	IplImage* src_xy = snd_order_deri_x_y(src);
	IplImage* des = _detHessian(src_x, src_y, src_xy);
	cvReleaseImage(&src_x);
	cvReleaseImage(&src_y);
	cvReleaseImage(&src_xy);
	return des;
}

IplImage* smoothHessian(IplImage* src) {
	IplImage* hessian_img = detHessian(src);
	IplImage* des_hessian;
	des_hessian = cvCreateImage(cvGetSize(hessian_img), hessian_img->depth, hessian_img->nChannels);
	cvSmooth(hessian_img, des_hessian, CV_MEDIAN);
	cvReleaseImage(&hessian_img);
	return des_hessian;
}

