#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

const int MaxW = 2000;
const int MaxH = 2000;
const int inf = ~0U>>1;

char fileName[] = "lena.jpg";

IplImage *oriImage = 0, *dstImage = 0;

int path[2][MaxH][MaxW], W, H, d[] = {-1, 0, 1};
double energy[MaxH][MaxW], f[2][MaxH][MaxW];
uchar data[MaxH][MaxW][3];

int main(void) {
	oriImage = cvLoadImage(fileName, CV_LOAD_IMAGE_ANYCOLOR);
	if (!oriImage) {
		fprintf(stderr, "Failed to load image..");
		return -1;
	}

	W = oriImage->width, H = oriImage->height;

	for (int h = 0; h < H; h++)
		for (int w = 0; w < W; w++) {
			uchar *p = data[h][w];
			p[0] = ((uchar*)(oriImage->imageData + h * oriImage->widthStep))[w * 3];
			p[1] = ((uchar*)(oriImage->imageData + h * oriImage->widthStep))[w * 3 + 1];
			p[2] = ((uchar*)(oriImage->imageData + h * oriImage->widthStep))[w * 3 + 2];
		}
	int limit = W * H / 3;


	while (W * H > limit) {
		for (int i = 0; i < H - 1; i++)
			for (int j = 0; j < W - 1; j++) {
				energy[i][j] = 0;
				for (int k = 0; k < 3; k++)
					energy[i][j] += sqrt((data[i][j][k] - data[i + 1][j][k]) * (data[i][j][k] - data[i + 1][j][k]) + 
							(data[i][j][k] - data[i][j + 1][k]) * (data[i][j][k] - data[i][j + 1][k]));
			}
		for (int i = 0; i < W - 1; i++) energy[H - 1][i] = energy[H - 2][i];
		for (int i = 0; i < H - 1; i++) energy[i][W - 1] = energy[i][W - 2];
		for (int i = 0; i < H; i++) f[0][i][0] = energy[i][0];
		for (int j = 1; j < W; j++)
			for (int i = 0; i < H; i++) {
				int pos = -1;double best = inf;
				for (int k = 0; k < 3; k++) if (i + d[k] >= 0 && i + d[k] < H && f[0][i + d[k]][j - 1] < best) {
					best = f[0][i + d[k]][j - 1];
					pos = i + d[k];
				}
				f[0][i][j] = best + energy[i][j];
				path[0][i][j] = pos;
			}
		for (int i = 0; i < W; i++) f[1][0][i] = energy[0][i];
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++) {
				int pos = -1;double best = inf;
				for (int k = 0; k < 3; k++) if (j + d[k] >= 0 && j + d[k] < W && f[1][i - 1][j + d[k]] < best) {
					best = f[1][i - 1][j + d[k]];
					pos = j + d[k];
				}
				f[1][i][j] = best + energy[i][j];
				path[1][i][j] = pos;
			}
		double best1 = inf, best2 = inf; int pos1 = -1, pos2 = -1;
		for (int i = 0; i < H; i++) if (f[0][i][W - 1] < best1) pos1 = i, best1 = f[0][i][W - 1];
		for (int i = 0; i < W; i++) if (f[1][H - 1][i] < best2) pos2 = i, best2 = f[1][H - 1][i];
		if (best1 < best2) {
			for (int i = W - 1; i >= 0; i--) {
				for (int j = pos1; j < H - 1; j++) 
					for (int k = 0; k < 3; k++)
						data[j][i][k] = data[j + 1][i][k];
				pos1 = path[0][pos1][i];
			}
			H--;
		} else {
			for (int i = H - 1; i >= 0; i--) {
				for (int j = pos2; j < W - 1; j++)
					for (int k = 0; k < 3; k++)
						data[i][j][k] = data[i][j + 1][k];
				pos2 = path[1][i][pos2];
			}
			W--;
		}
	}

	struct CvSize dstSize;
	dstSize.width = W, dstSize.height = H;

	dstImage = cvCreateImage(dstSize, oriImage->depth, oriImage->nChannels);
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++) {
			uchar *p = data[i][j];
			((uchar*)(dstImage->imageData + i * dstImage->widthStep))[j * 3] = p[0];
			((uchar*)(dstImage->imageData + i * dstImage->widthStep))[j * 3 + 1] = p[1];
			((uchar*)(dstImage->imageData + i * dstImage->widthStep))[j * 3 + 2] = p[2];
		}

	cvNamedWindow("oriImage", 1);
	cvShowImage("oriImage", oriImage);

	cvNamedWindow("dstImage", 1);
	cvShowImage("dstImage", dstImage);

	cvWaitKey(0);

	cvDestroyWindow("oriImage");
	cvDestroyWindow("dstImage");
	cvReleaseImage(&dstImage);
	cvReleaseImage(&oriImage);
	return 0;
}

