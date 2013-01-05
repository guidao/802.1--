#ifndef RECV_H
#define RECV_H

#include <pcap.h>
#include <string.h>

static char errbuf[PCAP_ERRBUF_SIZE];
static char dmac[6];
static int flag=0;
pcap_t *pcap;

void print(char *buf);
void init_pcap(const char *device);
void callback(u_char *userarg,const struct pcap_pkthdr* pkthdr,const u_char *packet);
void read_pcap(char *pwd);

#endif // recv.h
