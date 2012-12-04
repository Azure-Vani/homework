#include <cv.h>
#include <highgui.h>

char file_name[] = "pollen.tif";

IplImage *oriImage = 0, *dstImage = 0;

int cnt[256];uchar map[256]; double p[256];

int main(void) {
	oriImage = cvLoadImage(file_name, -1);
	if (!oriImage) {
		fprintf(stderr, "Failed to load image..");
		return -1;
	}

	dstImage = cvCreateImage(cvGetSize(oriImage), oriImage->depth, oriImage->nChannels);

	double Sum = 0;
	for (int h = 0; h < oriImage->height; h++)
		for (int w = 0; w < oriImage->width; w++) {
			uchar tmp = ((uchar*)(oriImage->imageData + h * oriImage->widthStep))[w];
			cnt[tmp]++; Sum++;
			((uchar*)(dstImage->imageData + h * dstImage->widthStep))[w] = tmp;
		}

	double Sp = 0;
	for (int i = 0; i < 256; i++) {
		Sp += cnt[i] / Sum;
		map[i] = cvRound(Sp * 255);
	}

	for (int h = 0; h < oriImage->height; h++)
		for (int w = 0; w < oriImage->width; w++) {
			uchar tmp = ((uchar*)oriImage->imageData + h * oriImage->widthStep)[w];
			((uchar*)dstImage->imageData + h * dstImage->widthStep)[w] = map[tmp];
		}


	cvNamedWindow("oriImage", 1);
	cvShowImage("oriImage", oriImage);

	cvNamedWindow("dstImage", 1);
	cvShowImage("dstImage", dstImage);

	cvWaitKey(0);
	cvDestroyWindow("dstImage");
	cvReleaseImage(&dstImage);
	cvReleaseImage(&oriImage);
	return 0;
}

