#include "base.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include"server.h"
#include"file.h"

int server(int port)
{
	int iListenSocket,iAcceptSocket;
	int iRet;

	iListenSocket = socket (AF_INET, SOCK_STREAM, IPPROTO_IP);
	if(iListenSocket == -1)
	{
		printf("create Listen Socket failed!\n");
		return ERR_FAIL;
	}
	printf("create iListenSocket %d ok!\n",iListenSocket);
	struct sockaddr_in stServerListenAddress = {0};
	stServerListenAddress.sin_family = AF_INET;
	stServerListenAddress.sin_port = htons(port);
	stServerListenAddress.sin_addr.s_addr = inet_addr("192.168.0.182");
	iRet = bind(iListenSocket, ( __SOCKADDR_ARG)&stServerListenAddress, sizeof(struct sockaddr_in));
	if(iRet == -1)
	{
		close(iListenSocket);
		printf("bind port %d fail!\n",port);
		return ERR_FAIL;
	}
	printf("bind port %d ok!\n",port);
	iRet = listen(iListenSocket,5);
	if(iRet == -1)
	{
		printf("listen failed",80);
		close(iListenSocket);
		return ERR_FAIL;
	}
	printf("build listen ok!\n");
	
	while (1)
	{
		memset(&stServerListenAddress,0,sizeof(stServerListenAddress));
		socklen_t uiAddrLength = sizeof(stServerListenAddress);
		printf("listening ....!\n");
		iAcceptSocket = accept(iListenSocket,(__SOCKADDR_ARG)&stServerListenAddress,&uiAddrLength);
		printf("a new client %s connect !\n",inet_ntoa(stServerListenAddress.sin_addr));
		pthread_t pthread = 0;

		iRet = pthread_create (&pthread,NULL,server_handle_request,(void *)&iAcceptSocket);
		if(0 != iRet)
		{
			printf("create pthread server_handle_request failed!\n");
			close(iListenSocket);
			return ERR_FAIL;
		}
		int *piRet = NULL;
		pthread_join(pthread,(void *)&piRet);
		if(NULL != piRet)
		{
			if(ERR_OK!= *piRet)
			{
				break;
			}
		}
	}
	close(iListenSocket);
	printf("close iListenSocket %d ok!\n",iListenSocket);
	return ERR_OK;
}
void *server_handle_request(void *arg)
{
	int *piRet = malloc(sizeof(int));
	*piRet = ERR_OK;
	int iAcceptSocket = *(int *)arg;
	char *fileName = GetDataFromSocket(iAcceptSocket);
	if(STR_HEAD_EQUA(fileName,"exit"))
	{
		*piRet = ERR_EXIT;
	}
	char *Data = GetTextFile(fileName);
	send(iAcceptSocket,Data,strlen(Data),0);
	
	return (void *)piRet;
}