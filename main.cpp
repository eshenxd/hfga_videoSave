/**************************************
      ���ܣ�hfga�ɼ���Ƶ������
	        �����Բɼ���Ƶ������
			����
	  ʱ�䣺2014��10��20��
	  ���ߣ�Ethan
	  ���⣺
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