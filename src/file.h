#ifndef __FILE_H
#define __FILE_H
#define STR_HEAD_EQUA(Buff,str) (0 == strncmp(Buff,str,sizeof(str)-1))
char *GetDataFromSocket(int iAcceptSocket);
char *GetTextFile(char *fileName);
#endif