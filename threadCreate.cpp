#include "threadCreate.h"
#include "faceDetect.h"

using namespace std;

ThreadCreate::ThreadCreate(Para* para)
{

	hThread1=(HANDLE)_beginthreadex(NULL,NULL,process1,para,0,&uiThread1ID);
	//hThread2=(HANDLE)_beginthreadex(NULL,NULL,process2,para,0,&uiThread2ID);

	WaitForSingleObject(hThread1,INFINITE); 
	//WaitForSingleObject(hThread2,INFINITE); //INFINITE表示等待无限长,单位为毫秒


}

ThreadCreate::~ThreadCreate()
{
	CloseHandle(hThread1);
	CloseHandle(hThread2);
}



static unsigned __stdcall process1( void* pThis)
{
	cout<<"thread1 start!"<<endl;

	Para* para=(Para*)pThis;

	//cvGrabFrame(para->capture1);

	//IplImage* frame1=cvQueryFrame(para->capture1);

	CvVideoWriter* writer=0;

	int fps=20;

	SYSTEMTIME sys;

	

	char outfileName[100];

	char strDir_1[50]="../Video/Video1/";

	IplImage* frame1=0;	

	int frame_sum=0;

	while(para->capture1)
	{
	    if(frame_sum==100)
		{
			frame_sum=0;

			cvReleaseVideoWriter(&writer);  

			continue;
		}
		
		/*cvGrabFrame(para->capture1);

		IplImage* frame1=cvRetrieveFrame(para->capture1);*/

		frame1=cvQueryFrame(para->capture1);

		cvShowImage("test",frame1);

		cvWaitKey(2);

		FaceDetector* detector=new FaceDetector(frame1);

		int num=detector->facedetect();//获取检测到人脸数

		if(num!=0&&frame_sum==0)
		{
			GetLocalTime(&sys);

			sprintf(outfileName,"%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s",strDir_1,sys.wYear,"-",sys.wMonth,"-",sys.wDay,"-",
				sys.wHour,"-",sys.wMinute,"-",sys.wSecond,"-",sys.wMilliseconds,".avi");
			
			writer=cvCreateAVIWriter(outfileName,0,fps,cvSize(640,480),1);
		}
	    
		if(writer)
		{
			cvWriteFrame(writer,frame1);

			frame_sum++;
		}
		
		delete detector;
	}

	

	return 0;
}

static unsigned __stdcall process2(void* pThis )
{
	cout<<"thread2 start!"<<endl;

	Para* para=(Para*)pThis;

	cvGrabFrame(para->capture2);

	IplImage* frame2=cvQueryFrame(para->capture2);

	CvVideoWriter* writer=0;

	int fps=20;

	SYSTEMTIME sys;

	int face_count=0;

	char outfileName[100];

	char strDir_1[50]="../Video/Video2/";

	int frame_sum=0;

	while (para->capture2)
	{
		if(frame_sum==100)
		{
			frame_sum=0;

			cvReleaseVideoWriter(&writer);  

			continue;
		}

		
		cvGrabFrame(para->capture2);

		frame2=cvRetrieveFrame(para->capture2);

		cvShowImage("Video2",frame2);

		cvWaitKey(2);

		FaceDetector* detector=new FaceDetector(frame2);

		int num=detector->facedetect();

		if(num!=0&&frame_sum==0)
		{
			GetLocalTime(&sys);

			sprintf(outfileName,"%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s",strDir_1,sys.wYear,"-",sys.wMonth,"-",sys.wDay,"-",
				sys.wHour,"-",sys.wMinute,"-",sys.wSecond,"-",sys.wMilliseconds,".avi");

			writer=cvCreateAVIWriter(outfileName,0,fps,cvSize(640,480),1);
		}

		if(writer)
		{
			cvWriteFrame(writer,frame2);

			frame_sum++;
		}


		delete detector;

	}

	return 0;
}