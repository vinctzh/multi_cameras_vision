#include <opencv2/opencv.hpp>

class StereoCameras
{
public:
	StereoCameras(int img_width,int img_height);
	
	void rectifyCameras();
	void rectifyImages(const cv::Mat& leftImage,const cv::Mat& rightImage, cv::Mat& leftout,cv::Mat& rightout);

private:
	cv::Size originSize;
	cv::Size rectifiedSize;
	// Params calculated from stereo calibration
	cv::Mat leftCmeraMatrix;
	cv::Mat leftDistCoffs;

	cv::Mat rightCameraMatrix;
	cv::Mat rightDistCoffs;

	cv::Mat om;
	cv::Mat T;
	cv::Mat R;

	// Params for rectify
	cv::Mat R_left;			// ��һ�����������3x3У���任����ת����
	cv::Mat R_right;		// �ڶ������ң������3x3У���任����ת����
	cv::Mat P_left;			// У�����������3x4ͶӰ����
	cv::Mat P_right;		// У�����������3x4ͶӰ����
	
	cv::Mat Q;				// ���-�Ӳ�ӳ�����

	// remap images to distortion images
	cv::Mat mapX_left;
	cv::Mat mapY_left;
	cv::Mat mapX_right;
	cv::Mat mapY_right;

	void loadCamParams();
};