#include "header.h"



struct Para
{
public:
	CvCapture* capture1;
	CvCapture* capture2;
protected:
private:
	
	IplImage *frame1,*frame2;
	IplImage* show_img;
	CvRect area1,area2;
	CvRect regions1,regions2;

};

class ThreadCreate
{
public:
	ThreadCreate(Para*);
	~ThreadCreate();

protected:
private:
	HANDLE hThread1;
	HANDLE hThread2;

	unsigned uiThread1ID;
	unsigned uiThread2ID;

};

static unsigned __stdcall process1(void* pThis );//摄像头1新线程处理函数
static unsigned __stdcall process2(void* pThis );//摄像头2新线程处理函数