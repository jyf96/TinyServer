#include"base.h"
#include<sys/socket.h>
#include"file.h"
char Buff[4094];
char *GetNextHead(char *p)
{
	if(p == NULL)
	{
		return NULL;
	}
	while(*p!='\0'&&*p!=' ')
	{
		p++;
	}
	if(*p!=' ')
	{
		return NULL;
	}
	while(*p!='\0'&&*p==' ')
	{
		p++;
	}
	if(*p=='\0')
	{
		return NULL;
	}
	return p;
}
char *GetDataFromSocket(int iAcceptSocket)
{
	memset(Buff,0,sizeof(Buff));
	recv(iAcceptSocket,Buff,sizeof(Buff)-1,MSG_WAITFORONE);
	printf("%s\n",Buff);
	char *p = GetNextHead(Buff);
	printf("%s \n",p);
	return p;
}
char *GetTextFile(char *fileName)
{
	char szFullPathName[4094] = "resources";
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
	f = fopen(szFullPathName,"r");
	if(f!=NULL)
	{
		fread(szFullPathName,sizeof(char),sizeof(szFullPathName)-1,f);
		printf("%s\n",szFullPathName);
		fclose(f);
	}
	else
	{
		printf("no exit file\n");
	}
	memset(Buff,0,sizeof(Buff));
	memcpy(Buff,szFullPathName,strlen(szFullPathName));
	return Buff;
}