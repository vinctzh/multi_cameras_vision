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
	cv::Mat R_left;			// 第一个（左）相机的3x3校正变换（旋转矩阵）
	cv::Mat R_right;		// 第二个（右）相机的3x3校正变换（旋转矩阵）
	cv::Mat P_left;			// 校正过的左相机3x4投影矩阵
	cv::Mat P_right;		// 校正过的右相机3x4投影矩阵
	
	cv::Mat Q;				// 深度-视差映射矩阵

	// remap images to distortion images
	cv::Mat mapX_left;
	cv::Mat mapY_left;
	cv::Mat mapX_right;
	cv::Mat mapY_right;

	void loadCamParams();
};