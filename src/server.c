#include "base.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include"server.h"
#include"file.h"
char Buff[1024*10] = {0};
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

		iRet = server_handle_request(iAcceptSocket);
		if(ERR_OK != iRet)
		{
			break;
		}
	}
	close(iListenSocket);
	printf("close iListenSocket %d ok!\n",iListenSocket);
	return ERR_OK;
}
int server_handle_request(int iAcceptSocket)
{
	char szString[20] = {0};
	memset(Buff,0,sizeof(Buff));
	recv(iAcceptSocket,Buff,sizeof(Buff)-1,MSG_WAITFORONE);
	printf("%s\n",Buff);
	char *pcData = Buff;

	//method
	pcData = StringQueuePop(pcData,szString);
	printf("%s\n",szString);

	//filepath
	pcData = StringQueuePop(pcData,szString);
	printf("%s\n",szString);
	if(STR_HEAD_EQUA(szString,"/exit"))
	{
		return ERR_EXIT;
	}
	/*send http response*/
	SendString("HTTP/1.1 200 OK\r\nContent-type : text/htm\r\n\r\n",iAcceptSocket);
	
	/*send body*/
	SendFile(szString,iAcceptSocket);
	
	close(iAcceptSocket);
	return ERR_OK;
}