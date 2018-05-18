# include <iostream>
# include "opencv2/core/core.hpp"

# include "opencv2/highgui/highgui.hpp"

# include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
Mat nImg;

void openImg(const char* filename)
{
	//Mat nImg;

	nImg = imread(filename, CV_LOAD_IMAGE_COLOR); //CV_LOAD_IMAGE_GRAYSCALE 
												  //create a new window
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", nImg);

	waitKey(0);
	destroyWindow("Display window"); //destroy the window

	nImg.release();

}
void drawImg()
{
	/* create an image */
	Mat img(cvSize(200, 100), CV_8UC3, Scalar::all(0));

	/* draw a green line */
	line(img,                         /* the dest image */
		cvPoint(10, 10),             /* start point */
		cvPoint(150, 80),            /* end point */
		cvScalar(0, 255, 0, 0),      /* the color; green */
		1, 8, 0);                    /* thickness, line type, shift */

									 /* draw a blue box */
	rectangle(img,                    /* the dest image */
		cvPoint(20, 15),        /* top left point */
		cvPoint(100, 70),       /* bottom right point */
		cvScalar(255, 0, 0, 0), /* the color; blue */
		1, 8, 0);               /* thickness, line type, shift */

								/* draw a red circle */
	circle(img,                       /* the dest image */
		cvPoint(110, 60), 35,      /* center point and radius */
		cvScalar(0, 0, 255, 0),    /* the color; red */
		1, 8, 0);                  /* thickness, line type, shift */

								   /* display the image */

	imshow("Draw", img);
	waitKey(0);
	destroyWindow("Draw");
	img.release();

}
void addText()
{

	string text = "Funny text inside the box";
	int fontFace = CV_FONT_HERSHEY_SIMPLEX;  //FONT_HERSHEY_SCRIPT_SIMPLEX
	double fontScale = 1.5;
	int thickness = 3;

	Mat img(600, 800, CV_8UC3, Scalar::all(0));

	int baseline = 0;
	Size textSize = getTextSize(text, fontFace,
		fontScale, thickness, &baseline);
	baseline += thickness;

	// center the text
	Point textOrg((img.cols - textSize.width) / 2,
		(img.rows + textSize.height) / 2);

	// draw the box
	rectangle(img, textOrg + Point(0, baseline),
		textOrg + Point(textSize.width, -textSize.height),
		Scalar(0, 0, 255));
	// ... and the baseline first
	line(img, textOrg + Point(0, thickness),
		textOrg + Point(textSize.width, thickness),
		Scalar(0, 0, 255));

	// then put the text itself
	putText(img, text, textOrg, fontFace, fontScale,
		Scalar::all(255), thickness, 8);

	//namedWindow("Text", CV_WINDOW_AUTOSIZE);
	imshow("Text", img);
	waitKey(0);
	destroyWindow("Text");
	img.release();
}
void keybd(const char* filename)
{
	Mat img0;
	int key;
	img0=imread(filename, CV_LOAD_IMAGE_COLOR);

	/* create a copy */
	Mat img1 = nImg.clone();

	/* display original image */
	//namedWindow("image", CV_WINDOW_AUTOSIZE);
	imshow("image", nImg);

	while (1) {
		/* wait for keyboard input */
		key = waitKey(0);

		/* 'q' pressed, quit the program */
		if (key == 'q') break;

		switch (key) {
			/* '1' pressed, display the original image */
		case '1':
			imshow("image", img1);
			break;

			/* '2' pressed, flip the image horizontally */
		case '2':
			flip(img1, nImg, 1);
			imshow("image", nImg);
			break;

			/* '3' pressed, flip the image vertically */
		case '3':
			flip(img1, nImg, 0);
			imshow("image", nImg);
			break;
			img0=imread(filename, CV_LOAD_IMAGE_COLOR);
		}
	}
	/* free memory */
	//destroyWindow("image");
	img0.release();
	img1.release();
}

void mouseHandler(int event, int x, int y, int flags, void *param)
{
	Mat img1;
	switch (event) {
		/* left button down */
	case CV_EVENT_LBUTTONDOWN:
		cout << "Left button down (" << x << "," << y << ")" << endl;  //(%d, %d).\n", x, y);
		break;

		/* right button down */
	case CV_EVENT_RBUTTONDOWN:
		//fprintf(stdout, "Right button down (%d, %d).\n", x, y);
		cout << "Right button down (" << x << "," << y << ")" << endl;
		break;

		/* mouse move */
	case CV_EVENT_MOUSEMOVE:
		/* draw a rectangle */
		img1 = nImg.clone();  //cvCloneImage(img0);

		
		
		/*rectangle(img1,
			cvPoint(x - 15, y + 15),
			cvPoint(x + 15, y + 15),
			cvScalar(0, 0, 255, 0), 2, 8, 0);*/ 
		imshow("image", img1);
		break;
	}
}
void onmouse(int event, int x, int y, int flags, void* param)  //draw circle around cursor, display coordinates and RGB value
{
	char text[100], coords[100];
	Mat img1;
	img1 = nImg.clone();
	if (event == CV_EVENT_MOUSEMOVE)
	{
		Vec3b p = img1.at<Vec3b>(y, x);
		
		sprintf_s(text, "R=%d, G=%d, B=%d", p[2], p[1], p[0]);
		sprintf_s(coords, "x=%d, y=%d", x, y);
		circle(img1,
			cvPoint(x - 10, y + 10), 10,  /* center point & radius */
			cvScalar(0, 0, 255, 0),    /* circle color; red */
			1, 3, 0);
	}
	
		

	putText(img1, text, Point(5, 15), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 0));
	putText(img1, coords, Point(5, 25), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(255, 255, 0));
	imshow("image", img1);



}
int main(int argc, char** argv)
{
	namedWindow("image", CV_WINDOW_AUTOSIZE);
	
	Mat img = imread("C:\Users\Tyler\source\repos\DIP_A1\DIP_A1\picture\preview.jpg");


	if (argc != 2)
	{
		cout << ("File name is not specifed") << endl;
		return -1;
	}

	//cout << "before draw" << endl;

	drawImg();
	//cout << "before text" << endl;
	addText();

	//keybd(argv[1]);

	openImg(argv[1]);
	//cout << "before image" << endl;

	nImg = imread(argv[1], CV_LOAD_IMAGE_COLOR); //CV_LOAD_IMAGE_GRAYSCALE 
	imshow("image", nImg);
	int key;


	/* create a copy */
	Mat img1 = nImg.clone();

	/* display original image */
	//namedWindow("image", CV_WINDOW_AUTOSIZE);
	setMouseCallback("image", mouseHandler, NULL);
	setMouseCallback("image", onmouse, 0);

	while (1) {
		/* wait for keyboard input */
		key = waitKey(0);

		/* 'q' pressed, quit the program */
		if (key == 'q') break;
	
		switch (key) {
			/* '1' pressed, display the original image */
		case '1':
			imshow("image", img1);
			break;

			/* '2' pressed, flip the image horizontally */
		case '2':
			flip(img1, nImg, 1);
			imshow("image", nImg);
			break;

			/* '3' pressed, flip the image vertically */
		case '3':
			flip(img1, nImg, 0);
			imshow("image", nImg);
			break;
		}
	}

	/* free memory */
	//destroyWindow("image");
	nImg.release();
	img1.release();


	return 0;
}