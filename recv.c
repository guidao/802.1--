#include <pcap.h>
#include <stdio.h>
#include "recv.h"


void init_pcap(const char *device)
{
	pcap_t *temp;
	if(NULL==device)
	{
		char *p=pcap_lookupdev(errbuf);
		if(p==NULL)
		{
			fputs(errbuf,stdout);
			exit(1);
		}
		device=p;
	}
	temp=pcap_open_live(device,200,0,0,errbuf);
	if(temp==NULL)
	{
		fputs(errbuf,stdout);
		exit(0);
	}
	pcap=temp;
}
void callback(u_char* userarg,const struct pcap_pkthdr* pkthdr,const u_char* packet)
{
	u_char *temp=packet;
	u_char id=0;
	temp+=12;
	char buf[26]="";
	if(temp[0]!=0x88||temp[1]!=0x8e)
	{
		return;
	}
	temp+=6;
	id=*(temp+1);
	switch(*temp)
	{
		case 0x01:
			if(*(temp+4)==0x01)
			{
				if(flag==0)
				{
					memcpy(dmac,packet+6,6);
					flag=1;
				}
				send_response(dmac,id);
				fputs("send a response\n",stdout);
			}
			else if(*(temp+4)==0x04)
			{
	
				buf[0]=id;
				memcpy(buf+1,userarg,strlen(userarg));
				memcpy(buf+1+strlen(userarg),temp+6,16);
				
				send_md5(buf,17+strlen(userarg),dmac,id);


			}
			break;
		case 0x03:
			fputs("sucess\n",stdout);
			system("dhclient");
			break;
	}
}
void read_pcap(char *pwd)
{
	send_start();
	int re=pcap_loop(pcap,-1,callback,pwd);
	if(re<0)
	{
		fputs("pcap_loop error\n",stdout);
		exit(1);
	}
}


