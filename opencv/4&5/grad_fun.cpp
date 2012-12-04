#include "grad_fun.h"

// get_img_ele������ȡimgͼ���е�y�У���x������ֵ
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

// set_img_ele��������imgͼ���е�y�У���x������ֵ
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


// fst_order_deri_x��������srcͼ����x����������������ֵ�����ͼ���з���
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
	//�õ�����ͼ��Ŀ�(x����)����(y����)
	int width	= src->width;
	int height	= src->height;

	//��x�����ݶ�ֵ������ͼ��des�ľ�����
	//desͼ���С��ÿ�����ص��ֽ�����ͨ����������ͼ��src��ȫ��ͬ
	IplImage* des = cvCreateImage( cvSize(width, height), src->depth, src->nChannels);

	//x�����ݶȼ���ʽ��des(i,j)=src(i,j+1)-src(i,j)����һά���У��ڶ�ά����
	//����ʹ��ǿ�ȣ�����Է��ţ�des(i,j)=|des(i,j)|
	//Ϊͼ����ÿһ�����ؼ���x�����ݶȣ�ע�����c�ķ�Χ��[0, width-2]
	//������Ϊ���һ��Ԫ���ұ�û��Ԫ�أ�����޷����㵼�������Ը�Ĭ��ֵ0

	/************************************************************************/
	/* Task:�벹ȫ��������ע�Ͷ�Ӧ�ĳ���                                    */
	/************************************************************************/
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width-1; c++)
		{
			int dev;
			//��src(r,c)����x������
			dev = get_img_ele(src, c+1, r) - get_img_ele(src, c, r);
			//ȡdev�ľ���ֵ
			dev = dev > 0 ? dev : -dev;
			//����õĵ���ֵ�ŵ�ͼ��des�Ķ�Ӧ������
			set_img_ele(des, c, r, dev);
		}
	}
	return des;
}

// fst_order_deri_y��������srcͼ����y����������������ֵ�����ͼ���з���
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
	//�õ�����ͼ��Ŀ�(x����)����(y����)
	int width	= src->width;
	int height	= src->height;

	//��y�����ݶ�ֵ������ͼ��des��
	//desͼ���С��ÿ�����ص��ֽ�����ͨ����������ͼ��src��ȫ��ͬ
	IplImage* des = cvCreateImage( cvSize(width, height), src->depth, src->nChannels);

	//y�����ݶȼ���ʽ��des(i,j)=src(i+1,j)-src(i,j)
	//����ʹ��ǿ�ȣ�����Է��ţ�des(i,j)=|des(i,j)|
	//Ϊͼ����ÿһ�����ؼ���y�����ݶȣ�ע�����r�ķ�Χ��[0, height-2]
	//������Ϊ���һ���±�û��Ԫ�أ�����޷����㵼�������Ը�Ĭ��ֵ0

	/************************************************************************/
	/* Task:�벹ȫ��������ע�Ͷ�Ӧ�ĳ���                                    */
	/************************************************************************/
	for (int r = 0; r < height-1; r++)
	{
		for (int c = 0; c < width; c++)
		{
			int dev;
			//��src(r,c)����y������,����dev
			dev = get_img_ele(src, c, r + 1) - get_img_ele(src, c, r);
			//ȡdev�ľ���ֵ
			dev = dev < 0 ? -dev : dev;
			//������ֵ�ŵ�ͼ��des��
			set_img_ele(des, c, r, dev);
		}
	}
	return des;
}



// snd_order_deri_x��������srcͼ����x������׵�������������ֵ�����ͼ���з���
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
	//�õ�����ͼ��Ŀ�(x����)����(y����)
	int width	= src->width;
	int height	= src->height;

	//��x������׵���ֵ������ͼ��des��
	//desͼ���С��ÿ�����ص��ֽ�����ͨ����������ͼ��src��ȫ��ͬ
	IplImage* des = cvCreateImage( cvSize(width, height), src->depth, src->nChannels);

	//x������׵�������ʽ��des(i,j)=src(i, j+2) + src(i, j) - 2 * src(i, j+1)
	//����ʹ��ǿ�ȣ�����Է��ţ�des(i,j)=|des(i,j)|
	//Ϊͼ����ÿһ�����ؼ���x�������ƫ����ע�����c�ķ�Χ��[0, width-3]
	//������Ϊ��������ұ�û�ж�������Ԫ�أ�����޷�������׵��������Ը�Ĭ��ֵ0

	/************************************************************************/
	/* Task:�벹ȫ��������ע�Ͷ�Ӧ�ĳ���                                    */
	/************************************************************************/
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width-2; c++)
		{
			//��src(r,c)����x������
			int dev = get_img_ele(src, c+2, r) + get_img_ele(src, c, r) - 2 * get_img_ele(src, c+1, r);
			//ȡdev�ľ���ֵ
			dev = dev > 0 ? dev : -dev;
			//������ֵ�ŵ�ͼ��des��
			set_img_ele(des, c, r, dev);
		}
	}
	return des;
}

// snd_order_deri_y��������srcͼ����y������׵�������������ֵ�����ͼ���з���
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
	//�õ�����ͼ��Ŀ�(x����)����(y����)
	int width	= src->width;
	int height	= src->height;

	//��y������׵���ֵ������ͼ��des��
	//desͼ���С��ÿ�����ص��ֽ�����ͨ����������ͼ��src��ȫ��ͬ
	IplImage* des = cvCreateImage( cvSize(width, height), src->depth, src->nChannels);

	//y�������ƫ������ʽ��des(i,j)=src(i+2,j)+src(i,j)-2*src(i+1,j)
	//����ʹ��ǿ�ȣ�����Է��ţ�des(i,j)=|des(i,j)|
	//Ϊͼ����ÿһ�����ؼ���y������׵�����ע�����r�ķ�Χ��[0, height-3]
	//������Ϊ��������±�û�ж������е�Ԫ�أ�����޷�������׵��������Ը�Ĭ��ֵ0

	/************************************************************************/
	/* Task:�벹ȫ��������ע�Ͷ�Ӧ�ĳ���                                    */
	/************************************************************************/

	for (int r = 0; r < height-2; r++)
	{
		for (int c = 0; c < width; c++)
		{
			//��src(r,c)����y������׵���
			int dev = get_img_ele(src, c, r + 2) + get_img_ele(src, c, r) - 2 * get_img_ele(src, c, r + 1);
			//���ȡ����ֵ
			dev = dev < 0 ? -dev : dev;
			//������ֵ�ŵ�ͼ��des��
			set_img_ele(des, c, r, dev);
		}
	}
	return des;
}

// snd_order_deri_y��������srcͼ����y������׵�������������ֵ�����ͼ���з���
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
	/* Task:�벹ȫ��������ע�Ͷ�Ӧ�ĳ���                                    */
	/************************************************************************/

	IplImage* dev_x;
	IplImage* dev_x_y;
	//1.Ϊsrcͼ�����x��������������dev_x��
	dev_x = fst_order_deri_x(src);
	//2.Ϊdev_xͼ�����y��������������dev_x_y��
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
	//�õ�����ͼ��Ŀ�(x����)����(y����)
	int width	= src->width;
	int height	= src->height;

	//�ϻ�ʱ��������ȥ��������ע��
	//����x�����ݶ�
	IplImage* dx = fst_order_deri_x(src);

	//����y�����ݶ�
	IplImage* dy = fst_order_deri_y(src);

	//���ݶ�ֵsqrt(dx^2+dy^2)�������������ͼ����
	//ͼ���С��ÿ�����ص��ֽ�����ͨ����������ͼ����ͬ
	IplImage* des = cvCreateImage( cvSize(width, height), src->depth, src->nChannels);

	/************************************************************************/
	/* Task:�벹ȫ��������ע�Ͷ�Ӧ�ĳ���                                    */
	/************************************************************************/
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			int dev_x; //x������
			int dev_y; //y������
			int grad;  //�ݶ�ֵ
			//����x������
			dev_x = get_img_ele(dx, c, r);
			//����y������
			dev_y = get_img_ele(dy, c, r);
			//�����ݶ�ֵ
			grad = sqrt((double)(dev_x * dev_x + dev_y * dev_y));
			//���ݶ�ȡ����ֵ
			grad = grad < 0 ? -grad : grad;
			//���ݶ�ֵд��desͼ���еĶ�Ӧλ��
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

