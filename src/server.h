#ifndef _SERVER_H
#define _SERVER_H
int server(int port);
void *server_handle_request(void *arg);
#endif