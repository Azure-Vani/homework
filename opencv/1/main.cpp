#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

int main(int argc, char **argv)
{
	IplImage *colorImage = cvLoadImage("images/lena.jpg", 1);
	IplImage *blueImage = cvCreateImage(cvSize(colorImage->width, colorImage->height), IPL_DEPTH_8U, 3);
	IplImage *redImage = cvCreateImage(cvSize(colorImage->width, colorImage->height), IPL_DEPTH_8U, 3);
	IplImage *greenImage = cvCreateImage(cvSize(colorImage->width, colorImage->height), IPL_DEPTH_8U, 3);

	for (int h=0; h<colorImage->height; h++)
	{
		for (int w=0; w<colorImage->width; w++) //G,B,R三通道数据交错存放
		{
			uchar b = ((uchar*)(colorImage->imageData + h*colorImage->widthStep))[w*3];
			uchar g =((uchar*)(colorImage->imageData + h*colorImage->widthStep))[w*3+1];
			uchar r =((uchar*)(colorImage->imageData + h*colorImage->widthStep))[w*3+2];

			((uchar*)(blueImage->imageData + h*blueImage->widthStep))[w * 3] = (uchar)b;
			((uchar*)(greenImage->imageData + h*greenImage->widthStep))[w * 3 + 1] = (uchar)g;
			((uchar*)(redImage->imageData + h*redImage->widthStep))[w * 3 + 2] = (uchar)r;
		}
	}

	cvNamedWindow("blue", 1);
	cvShowImage("blue", blueImage);

	cvNamedWindow("green", 1);
	cvShowImage("green", greenImage);

	cvNamedWindow("red", 1);
	cvShowImage("red", redImage);

	cvWaitKey(0);
	cvReleaseImage(&colorImage);
	cvReleaseImage(&blueImage);
	cvReleaseImage(&redImage);
	cvReleaseImage(&greenImage);
}

