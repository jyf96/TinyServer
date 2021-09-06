#include"base.h"
#include<sys/socket.h>
#include"file.h"

char *StringQueuePop(char *pcHead,char szOutString[20])
{
	if(pcHead == NULL)
	{
		return NULL;
	}
	char *p = pcHead;
	while(*p == ' ')
	{
		p++;
	}
	pcHead = p;

	while(*p!='\0'&&*p!=' '&&*p!='\n')
	{
		p++;
	}
	memset(szOutString,0,sizeof(char)*20);
	if((p-pcHead)>19)
	{
		memcpy(szOutString,pcHead,sizeof(char)*19);
	}
	else
	{
		memcpy(szOutString,pcHead,sizeof(char)*(p-pcHead));
	}

	while(*p!='\0'&&*p==' ')
	{
		p++;
	}
	return p;
}
void SendFile(char *fileName,int iAcceptSocket)
{
	char szFullPathName[128] = "resources";
	FILE *f = NULL;
	if(STR_HEAD_EQUA(fileName,"/"))
	{
		strcat(szFullPathName,"/index.html");
	}
	else
	{
		strcat(szFullPathName,fileName);
	}
	printf("%s\n",szFullPathName);
	char Buff[4094] = {0};
	f = fopen(szFullPathName,"r");
	if(f!=NULL)
	{
		fread(Buff,sizeof(char),sizeof(Buff)-1,f);
		fclose(f);
	}
	else
	{
		printf("file not exit!\n");
		sprintf(Buff,"file not exit!\n");
	}
	printf("%s\n",Buff);
	send(iAcceptSocket,Buff,strlen(Buff),0);
	return;
}