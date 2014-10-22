#include "faceDetect.h"


using namespace std;

char* cascade_name="face.xml";
CvHaarClassifierCascade* cascade=(CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );;

//cascade_name="face.xml";

//cascade=(CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );

FaceDetector::FaceDetector(IplImage* image)
{
	Frame_num=0;
	
	/*cascade_name="face.xml";

	cascade=(CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );*/

	frame=cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);

	frame_copy=cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);

	frame_copy1=cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);

	cvCopy(image,frame);

	para=new DetectorPara;

	para->window_scale=0.2;

	para->FD_iterations=5;
}

FaceDetector::~FaceDetector()
{
	if(frame)
		cvReleaseImage(&frame);

	if(frame_copy)
		cvReleaseImage(&frame_copy);

	if(frame_copy1)
		cvReleaseImage(&frame_copy1);

	delete para;

	//cascade=NULL;
}

int FaceDetector::facedetect()
{
	cvCopy(frame,frame_copy);

	cvCopy(frame,frame_copy1);

	CvMemStorage* storage=cvCreateMemStorage(0);

	para->area1.x=cvRound(frame_copy->width*para->window_scale);
	para->area1.y=cvRound(frame_copy->height*para->window_scale);
	para->area1.width=cvRound(frame_copy->width*(1-para->window_scale*2));
	para->area1.height=cvRound(frame_copy->height*(1-para->window_scale*2));

	IplImage* img_ROI=cvCreateImage(cvSize(para->area1.width,para->area1.height),
		frame_copy->depth,frame_copy->nChannels);

	CvPoint p1,p2;

	p1.x=para->area1.x;
	p1.y=para->area1.y;

	p2.x=para->area1.x+para->area1.width;
	p2.y=para->area1.y+para->area1.height;

	cvSetImageROI(frame_copy,para->area1);

	cvCopy(frame_copy,img_ROI);



	double Scale=1.3;

	IplImage* gray=cvCreateImage( cvSize(img_ROI->width,img_ROI->height),
		img_ROI->depth, 1 );

	IplImage* small_img = cvCreateImage( cvSize( cvRound (img_ROI->width/Scale),
		cvRound (img_ROI->height/Scale)),
		img_ROI->depth, 1 );

	int i,faces_num;
	//int  x1, y1, x2, y2, w, h;

	cvCvtColor( img_ROI, gray, CV_BGR2GRAY );
	cvResize( gray, small_img, CV_INTER_LINEAR );
	cvEqualizeHist( small_img, small_img );
	cvClearMemStorage( storage );

	CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,
		1.4, para->FD_iterations, CV_HAAR_DO_CANNY_PRUNING,
		cvSize(50, 50) );

	faces_num=faces->total;

	cvReleaseImage( &small_img );
	
	cvReleaseImage( &gray );
	
	cvReleaseImage(&img_ROI);

	cvReleaseMemStorage(&storage);

	return faces_num;
}

