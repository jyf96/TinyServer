#ifndef __FILE_H
#define __FILE_H
#define STR_HEAD_EQUA(Buff,str) (0 == strncmp(Buff,str,sizeof(str)-1))
char *StringQueuePop(char *pcHead,char szOutString[20]);
void SendFile(char *fileName,int iAcceptSocket);
#endif