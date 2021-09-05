#include"base.h"
#include"server.h"
int main(char argc,char *argv[])
{
	printf("%s\n",argv[0]);
	int iRet = 0;
	iRet = server(5001);
	if(ERR_OK != iRet)
	{
		printf("server exit %d\n",iRet);
	}
	return 0;
}