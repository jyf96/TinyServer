#ifndef _BASE_H
#define _BASE_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum err_t{
	ERR_FAIL = -1,
	ERR_OK = 0,
	ERR_EXIT = 1,
	ERR_MAX
}ERR_T;

#endif