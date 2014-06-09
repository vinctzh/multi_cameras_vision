#include "Cameras.h"

Cameras::Cameras(int cm_c)
{
	this->cm_count = cm_c;
	cam_captures = (VideoCapture**)malloc(cm_c*sizeof(VideoCapture*));
}

int Cameras::OpenMultiCameras(int *camIds)
{
	for (int i=0;i<cm_count;i++)
	{
		cam_captures[i] = new VideoCapture(camIds[i]);
		if (!cam_captures[i]->isOpened())
			return i;
		cout<<"Camera "<<i<<" "<<cam_captures[i]->get(CV_CAP_PROP_FRAME_HEIGHT)<<" "<<cam_captures[i]->get(CV_CAP_PROP_FRAME_WIDTH)<<endl;
		/*	cam_captures[i]->set(CV_CAP_PROP_FRAME_HEIGHT,960);
		cam_captures[i]->set(CV_CAP_PROP_FRAME_WIDTH,1280);*/
	
	}
	return -1;
}

void Cameras::ReleaseMultiCameras()
{
	for (int i=0;i<cm_count;i++)
	{
		if (cam_captures[i]!=NULL || cam_captures[i]->isOpened())
		{
			cam_captures[i]->release();
			cam_captures[i] = NULL;
		}
	}
}

bool Cameras::IsAllDevicesReady()
{
	for (int i=0;i<cm_count;i++)
	{
		if (cam_captures[i]==NULL || !cam_captures[i]->isOpened())
		{
			try
			{
				cam_captures[i]->open(i);
			}
			catch (Exception* e)
			{
				
			}
			if (!cam_captures[i]->isOpened())	return false;

		}
	}
	return true;
}

bool Cameras::GetNextMultiFrames(Mat frames[])
{
	if (!IsAllDevicesReady())
		return false;

	for (int i=0;i<cm_count;i++)
	{
		if (! cam_captures[i]->read(frames[i]))
			return false;
	}

	return true;
}

Cameras::~Cameras()
{
	ReleaseMultiCameras();
	free(cam_captures);
}