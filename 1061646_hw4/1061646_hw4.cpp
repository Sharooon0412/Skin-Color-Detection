/*利用你所學的顏色的知識，撰寫一個程式來偵測一張輸入照片中的皮膚區域並將其標
示出。*/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>

using namespace cv;
using namespace std;

Mat Skin(Mat& hsv_img, Mat& Bgra_img, Mat& Ycrcb_img, Mat& image1)
{
	Mat dstImg = image1;
	//轉換成HSV, BGRA, YCrCb圖
	cvtColor(image1, hsv_img, cv::COLOR_BGR2HSV);
	cvtColor(image1, Bgra_img, cv::COLOR_BGR2BGRA);
	cvtColor(image1, Ycrcb_img, cv::COLOR_BGR2YCrCb);

	int h = 0;
	int s = 1;
	int v = 2;

	int A = 3;
	int R = 2;
	int G = 1;
	int B = 0;

	int Y = 0;
	int Cr = 1;
	int Cb = 2;

	for (int i = 0; i < hsv_img.rows; i++)
	{
		for (int j = 0; j < hsv_img.cols; j++)
		{
			uchar* dstt = dstImg.ptr<uchar>(i, j);
			uchar* src = hsv_img.ptr<uchar>(i, j);
			uchar* Bgra = Bgra_img.ptr<uchar>(i, j);
			uchar* Ycrcb = Ycrcb_img.ptr<uchar>(i, j);

			if ((0 <= src[h] && src[h] <= 25) && (58 <= src[s] && src[s] <= 173)
				&& Bgra[R] > 95 && Bgra[G] > 40 and Bgra[B] > 20
				&& Bgra[R] > Bgra[G] && Bgra[R] > Bgra[B] && abs(Bgra[R] - Bgra[G]) > 15 && Bgra[A] > 15)
			{
				dstt[0] = 255;
				dstt[1] = 255;
				dstt[2] = 255;
				//cout << "pp\n ";
			}
			else if (Bgra[R] > 95 && Bgra[G] > 40 && Bgra[B] > 20
				&& Bgra[R] > Bgra[G] && Bgra[R] > Bgra[B] && abs(Bgra[R] - Bgra[G]) > 15 && Bgra[A] > 15
				&& Ycrcb[Cr] > 135 && Ycrcb[Cb] > 85 && Ycrcb[Y] > 80
				&& Ycrcb[Cr] <= (1.5862 * Ycrcb[Cb]) + 20 && Ycrcb[Cr] >= (0.3448 * Ycrcb[Cb]) + 76.2069
				&& Ycrcb[Cr] >= (-4.5652 * Ycrcb[Cb]) + 234.5652 && Ycrcb[Cr] <= (-1.15 * Ycrcb[Cb]) + 301.75
				&& Ycrcb[Cr] <= (-2.2857 * Ycrcb[Cb]) + 432.85)
			{
				dstt[0] = 255;
				dstt[1] = 255;
				dstt[2] = 255;
				//cout << "xx\n ";
			}
			else
			{
				dstt[0] = 0;
				dstt[1] = 0;
				dstt[2] = 0;
				//cout << "aa\n ";
			}
		}
		cout << hsv_img.rows << " ";
		cout << i << "\n";
	}
	return dstImg;
}

int main()
{
	Mat image1 = imread("SkinDetection.jpg");
	//Mat image1 = cv::imread("2.jpg");
	Mat dstImg = image1;
	Mat hsv_img;
	Mat Bgra_img;
	Mat Ycrcb_img;

	imshow("原圖", image1);
	imshow("膚色", Skin(hsv_img, Bgra_img, Ycrcb_img,image1));
	cv::waitKey();

	return 0;
}