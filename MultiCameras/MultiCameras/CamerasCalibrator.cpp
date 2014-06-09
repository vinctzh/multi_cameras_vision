#include "CamerasCalibrator.h"
#include <iostream>
using namespace std;

StereoCameras::StereoCameras(int img_width,int img_height)
{
	originSize.height = img_height;
	originSize.width = img_width;
}

void StereoCameras::loadCamParams()
{
	leftCmeraMatrix = (cv::Mat_<double>(3,3)<< 838.19780, 0.0,  351.27524,
		0.0 ,   837.82702 , 260.79723,
		0.0 , 0.0 , 1.0 );
	leftDistCoffs = (cv::Mat_<double>(1,5) << -0.45653 ,  0.23054  , -0.00055  , -0.00328 , 0.00000 );

	rightCameraMatrix = (cv::Mat_<double>(3,3)<<834.58834, 0.0,  337.38447,
		0.0 ,   834.60353 , 256.53388,
		0.0 , 0.0 , 1.0 );
	rightDistCoffs =( cv::Mat_<double>(1,5)<< -0.46956 , 0.32350 , -0.00124 , -0.00125 , 0.00000);

	om = (cv::Mat_<double>(3,1)<<-0.00147  , 0.00636 , -0.00646);
	T = (cv::Mat_<double>(3,1)<<119.36779 ,  -0.10928 , 0.95835);
	cv::Rodrigues(om,R);
}

void StereoCameras::rectifyCameras()
{
	loadCamParams();
	stereoRectify(leftCmeraMatrix,leftDistCoffs,
		rightCameraMatrix,rightDistCoffs,
		originSize,R,T,R_left,R_right,P_left,P_right,Q,
		1024,0,
		rectifiedSize);

	cout<<Q<<endl;

	initUndistortRectifyMap(leftCmeraMatrix,leftDistCoffs,R_left,P_left,originSize,CV_32FC2,mapX_left,mapY_left);
	initUndistortRectifyMap(rightCameraMatrix,rightDistCoffs,R_right,P_right,originSize,CV_32FC2,mapX_right,mapY_right);
}

void StereoCameras::rectifyImages(const cv::Mat& leftImage,const cv::Mat& rightImage, cv::Mat& leftout,cv::Mat& rightout)
{
	cv::remap(leftImage,leftout,mapX_left,mapY_left,cv::INTER_LINEAR);
	cv::remap(rightImage,rightout,mapX_right,mapY_right,cv::INTER_LINEAR);
	cout<<leftout.size()<<endl;
}