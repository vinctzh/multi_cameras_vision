#include <iostream>
#include <opencv2/opencv.hpp>
#include "CamerasCalibrator.h"
#include "FaceDetector.hpp"
#include "libflandmark/flandmark_detector.h"

using namespace cv;
using namespace std;

#include "Cameras.h"

const int CAMERA_COUNT = 2;

int main()
{
	//Mat frams[CAMERA_COUNT];

	//Cameras cms(CAMERA_COUNT);
	//int camIds[] = {0,/*1,*/2};
	//int flag = cms.OpenMultiCameras(camIds);
	//if ( flag != -1)
	//{
	//	cout<<"Fail to open camera "<<flag;
	//	return -1;
	//}	

	//while (1)
	//{
	//	cms.GetNextMultiFrames(frams);
	//	imshow("Camera 1",frams[0]);
	//	imshow("Camera 2",frams[1]);
	//	//imshow("Camera 3",frams[2]);
	//	if (waitKey(20) == 'q') break;
	//}
		
	StereoCameras stereoCameras(640,480);
	stereoCameras.rectifyCameras();

	cv::Mat leftImage = cv::imread("le1.jpg");
	cv::Mat rightImage =cv::imread("ri1.jpg");

	cv::Mat leftOut,rightOut;
	stereoCameras.rectifyImages(leftImage,rightImage,leftOut,rightOut);

	Mat leftFaceMarked,rightFaceMarked;
	leftOut.copyTo(leftFaceMarked);
	rightOut.copyTo(rightFaceMarked);

	// Flandmark detect feature points
	FLANDMARK_Model * model = flandmark_init("flandmark_model.dat");
	if (model == 0)
	{
		printf("Structure model wasn't created. Corrupted file flandmark_model.dat?\n");
		exit(1);
	}

	int *bbox = (int*)malloc(4*sizeof(int));
	double *landmarks = (double*)malloc(2*model->data.options.M*sizeof(double));

	FaceDetector fd;
	fd.LoadTrainingParams("npd_model_1.mat");
	IplImage* img_1 ;
	img_1 = &IplImage(leftFaceMarked);
	fd.Detect(img_1);
	imshow("facedeted_left",Mat(img_1));
	cout<<fd.faces[0].x<<"  "<<fd.faces[0].y<<" "<<fd.faces[0].height<<" "<<fd.faces[0].width<<endl;

	IplImage* img_1o;
	img_1o = &IplImage(leftOut);
	
	bbox[0] = fd.faces[0].x;
	bbox[1] = fd.faces[0].y;
	bbox[2] = fd.faces[0].x + fd.faces[0].width;
	bbox[3] = fd.faces[0].y + fd.faces[0].height;

	IplImage *flandImg = cvCreateImage(cvSize(img_1o->width,img_1o->height),IPL_DEPTH_8U,1);
	cvConvertImage(img_1o,flandImg);
	cout<<"landmarks for left£º ";

	flandmark_detect(flandImg, bbox, model, landmarks);
	for (int i = 2; i < 2*model->data.options.M; i += 2)
	{
		cvCircle(img_1o, cvPoint(int(landmarks[i]), int(landmarks[i+1])), 3, CV_RGB(255,0,0), CV_FILLED);
		cout<<int(landmarks[i])<<" "<<int(landmarks[i+1])<<endl;
	}
	imshow("flandmark_left",Mat(img_1o));

	IplImage* img_2 ;
	img_2 = &IplImage(rightFaceMarked);
	fd.Detect(img_2);
	imshow("facedeted_right",Mat(img_2));
	cout<<fd.faces[1].x<<"  "<<fd.faces[1].y<<" "<<fd.faces[1].height<<" "<<fd.faces[1].width<<endl;

	IplImage* img_2o;
	img_2o = &IplImage(rightOut);

	bbox[0] = fd.faces[1].x;
	bbox[1] = fd.faces[1].y;
	bbox[2] = fd.faces[1].x + fd.faces[1].width;
	bbox[3] = fd.faces[1].y + fd.faces[1].height;

	IplImage *flandImg_2 = cvCreateImage(cvSize(img_2o->width,img_2o->height),IPL_DEPTH_8U,1);
	cvConvertImage(img_2o,flandImg_2);

	flandmark_detect(flandImg_2, bbox, model, landmarks);
	cout<<"landmarks for right£º ";
	for (int i = 2; i < 2*model->data.options.M; i += 2)
	{
		cvCircle(img_2o, cvPoint(int(landmarks[i]), int(landmarks[i+1])), 3, CV_RGB(255,0,0), CV_FILLED);
		
		cout<<int(landmarks[i])<<" "<<int(landmarks[i+1])<<endl;
	}
	imshow("flandmark_right",Mat(img_2o));

	// imshows
	cv::Mat doubleView(leftOut.rows,2*leftOut.cols,leftOut.type());
	cv::Rect leftROI(0,0,leftOut.cols,leftOut.rows);
	cv::Rect rightROI(leftOut.cols,0,leftOut.cols,leftOut.rows);

	leftOut.copyTo(doubleView(leftROI));
	rightOut.copyTo(doubleView(rightROI));

	cv::Mat doubleviewORG(leftImage.rows,2*leftImage.cols,leftImage.type());
	leftImage.copyTo(doubleviewORG(leftROI));
	rightImage.copyTo(doubleviewORG(rightROI));

	imshow("rectified double view",doubleView);
	imshow("origin double view",doubleviewORG);		
	
	cv::waitKey(0);  
	return 0;
}