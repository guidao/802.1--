#ifndef SEND_H
#define SEND_H
#include <libnet.h>
#include <string.h>

libnet_t *link_l;
char lname[100];
char lpwd[100];


void init_cap(char *device,char *name,int namelen,char *pwd,int pwdlen);
void send_start();
void send_response(char *dmac,char id);
void send_md5(char *buf,int len,char *dmac,char id);

#endif // send.h
