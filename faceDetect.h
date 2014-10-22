#include "header.h"


struct DetectorPara
{
	int hour,minute,second;
	int FD_iterations;
	int show_width,show_height;
	int Align_iterations;
	int pic_width,pic_height;
	float window_scale,window_scale1;

	CvCapture* capture1;
	CvCapture* capture2;
	IplImage *frame1,*frame2;
	IplImage* show_img;
	CvRect area1,area2;
	CvRect regions1,regions2;
};

class FaceDetector
{
public:
	FaceDetector(IplImage* img);
	~FaceDetector();

	int facedetect();
protected:
private:
	//char* cascade_name;
	//CvHaarClassifierCascade* cascade;

	int num; //检测到对齐的人脸数
	int Frame_num;
	//int savenum;//已保存的人脸数
	//int a[2];

	DetectorPara* para;

	//SYSTEMTIME sys;

	IplImage* frame;
	IplImage* frame_copy;
	IplImage* frame_copy1;
};