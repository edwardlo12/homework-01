#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

struct yellow
{
	int MIN_X;
	int MAX_X;
	int MIN_Y;
	int MAX_Y;
};

Mat IMGC;
int col, row;


void onMouse(int Event, int x, int y, int flags, void* param) {
	yellow color;

	//color INIT
	color.MAX_X = 0;
	color.MAX_Y = 0;
	color.MIN_X = col;
	color.MIN_Y = row;

	if (Event == CV_EVENT_LBUTTONDOWN) {
		cout <<"("<<y<<" , "<<x<<") "<<int(IMGC.at<Vec3b>(y, x).val[0]) << " " << int(IMGC.at<Vec3b>(y, x).val[1]) << " " << int(IMGC.at<Vec3b>(y, x).val[2]) << endl;

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				if (IMGC.at<Vec3b>(i, j).val[0] == IMGC.at<Vec3b>(y, x).val[0] && IMGC.at<Vec3b>(i, j).val[1] == IMGC.at<Vec3b>(y, x).val[1] && IMGC.at<Vec3b>(i, j).val[2] == IMGC.at<Vec3b>(y, x).val[2]) {
					//cout << "(" << i << " , " << j << ")" << endl;
					if (i < color.MIN_Y) color.MIN_Y = i;
					if (j < color.MIN_X) color.MIN_X = j;
					if (i > color.MAX_Y) color.MAX_Y = i;
					if (j > color.MAX_X) color.MAX_X = j;

				}
			}
		cout << "MIN_X=" << color.MIN_X << " MIN_Y=" << color.MIN_Y << " MAX_X=" << color.MAX_X << " MAX_Y=" << color.MAX_Y << endl;
		Mat ROI(IMGC, Rect(color.MIN_X, color.MIN_Y, color.MAX_X - color.MIN_X, color.MAX_Y - color.MIN_Y));
		imshow("ROI", ROI);
		imwrite("hw1_roi_image.jpg", ROI);
	}
}

int main()
{
	Mat img;
	img=imread("homework_1_original.bmp",IMREAD_COLOR);
	IMGC = img.clone();

	col = IMGC.cols;
	row = IMGC.rows;
	int flag = 0;
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			//IMGC.at<Vec3b>(i, j) = 0;
			if (IMGC.at<Vec3b>(i, j).val[0] > 150 && IMGC.at<Vec3b>(i, j).val[1] < 15 && IMGC.at<Vec3b>(i, j).val[2] < 15) {
				IMGC.at<Vec3b>(i, j) = { 128,0,128 };
			}

			if (IMGC.at<Vec3b>(i, j).val[0] < 15 && IMGC.at<Vec3b>(i, j).val[1] < 15 && IMGC.at<Vec3b>(i, j).val[2] > 150) {
				IMGC.at<Vec3b>(i, j) = { 200,200,0 };
			}

			if (IMGC.at<Vec3b>(i, j).val[0] < 15 && IMGC.at<Vec3b>(i, j).val[1] > 150 && IMGC.at<Vec3b>(i, j).val[2] < 15) {
				IMGC.at<Vec3b>(i-300, j) = IMGC.at<Vec3b>(i , j);
				IMGC.at<Vec3b>(i, j) = {255,255,255};
			}
		}
	}

	imshow("img", img);
	imshow("IMGC", IMGC);
	setMouseCallback("IMGC", onMouse, NULL);
	imwrite("hw1_changed_image.jpg", IMGC);
	waitKey(1);

	/*for (int i = 0; i < row; i++) 
		for (int j = 0; j < col; j++) {
			if (IMGC.at<Vec3b>(i, j).val[0] == 0 && IMGC.at<Vec3b>(i, j).val[1] == 255 && IMGC.at<Vec3b>(i, j).val[2] == 255) {
				//cout << "(" << i << " , " << j << ")" << endl;
				if (i < y.MIN_Y) y.MIN_Y = i; 
				if (j < y.MIN_X) y.MIN_X = j; 
				if (i > y.MAX_Y) y.MAX_Y = i;
				if (j > y.MAX_X) y.MAX_X = j;
				
			}
		}*/
			

	

	
	
	std::cout << "hello!!!" << std::endl;
	waitKey(0);
	return 0;

}

