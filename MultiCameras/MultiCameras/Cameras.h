#pragma  once
#include <opencv2/opencv.hpp>
using namespace cv;

#include <iostream>
using namespace std;

class Cameras
{
public:
	int cm_count;
	VideoCapture** cam_captures;
	Cameras(int cm_c);
	~Cameras();

	int OpenMultiCameras(int *camId);
	bool GetNextMultiFrames(Mat frames[]);
private:
	
	void ReleaseMultiCameras();
	bool IsAllDevicesReady();
};