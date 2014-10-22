/**************************************
      功能：hfga采集视频程序，用
	        来测试采集视频质量的
			问题
	  时间：2014年10月20日
	  作者：Ethan
	  问题：
**************************************/
#include "header.h"
#include "threadCreate.h"

using namespace std;


int main(int argc , char* argv[])
{
	Para* para=new Para;

	para->capture1=cvCaptureFromCAM(0);
	
	//para->capture2=cvCaptureFromCAM(1);

	ThreadCreate* thread=new ThreadCreate(para);

	delete para;
	
	return 0;
}