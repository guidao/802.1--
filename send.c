//#include "network.h"
#include "send.h"

#include "md5.h"

#include <libnet.h>

void init_cap(char *device,char *name,int namelen,char *pwd,int pwdlen)
{
	if(namelen>=100||pwdlen>=100)
	{
		fputs("name or password too long\n",stdout);
		return ;
	}
	
	memcpy(lname,name,namelen);
	memcpy(lpwd,pwd,pwdlen);

	char errbuf[LIBNET_ERRBUF_SIZE]="";
	libnet_t *temp=libnet_init(LIBNET_LINK,device,errbuf);
	if(temp==NULL)
	{
		fputs("libnet",stderr);
		fputs(errbuf,stderr);
	}
	link_l=temp;
}
void send_start()
{
	libnet_ptag_t tag=-1;
	char buf[]={0xff,0xff,0xff,0xff,0xff,0xff};
	tag=libnet_build_802_1x(1,0x01,0,NULL,0,link_l,0);
	if(-1==tag)
	{
		fputs(libnet_geterror(link_l),stderr);
		exit(1);
	}
	tag=libnet_autobuild_ethernet(buf,0x888e,link_l);
	tag=libnet_write(link_l);
	if(-1==tag)
	{
		fputs(libnet_geterror(link_l),stderr);
		exit(1);
	}
}

void send_response(char *dmac,char id)
{
	
	libnet_ptag_t tag;
	int len=strlen(lname);
	if(0==len)
	{
		fputs("name cannot null\n",stderr);
		exit(1);
	}
	char *buf=malloc(len+5);
	if(buf==NULL)
	{
		fputs("malloc error\n",stdout);
		exit(1);
	}
	
	buf[0]=0x02;
	buf[1]=id;
	buf[2]=(len+5)>>8;
	buf[3]=len+11;
	buf[4]=0x01;
	buf[5]=0x15;
	buf[6]=0x04;
	memset(buf+7,0,4);
	memcpy(buf+11,lname,len);
	
	//libnet_cq_remove(link_l);


	tag=libnet_build_802_1x(1,0x00,len+11,buf,len+11,link_l,0);
	if(-1==tag)
	{
		fputs(libnet_geterror(link_l),stderr);
		exit(1);
	}
	tag=libnet_autobuild_ethernet(dmac,0x888e,link_l);
	if(-1==tag)
	{
		fputs(libnet_geterror(link_l),stderr);
		exit(1);
	}
	tag=libnet_write(link_l);
	if(-1==tag)
	{
		fputs("libnet",stdout);
		fputs(libnet_geterror(link_l),stderr);
		exit(1);
	}
	
	libnet_clear_packet(link_l);

}

void send_md5(char *buf,int len,char *dmac,char id)
{
	char temp[22];
	
	md5_sum(buf,len);

	temp[0]=0x02;
	temp[1]=id;
	temp[2]=0x00;
	temp[3]=0x16;
	temp[4]=0x04;
	temp[5]=0x10;
	memcpy(temp+6,buf,16);
	
	libnet_ptag_t tag;
	tag=libnet_build_802_1x(1,0x00,22,temp,22,link_l,0);
	if(-1==tag)
	{
		fputs(libnet_geterror(link_l),stderr);
		exit(1);
	}
	
	tag=libnet_autobuild_ethernet(dmac,0x888e,link_l);
	if(-1==tag)
	{
		fputs(libnet_geterror(link_l),stderr);
		exit(1);
	}
	
	tag=libnet_write(link_l);
	if(-1==tag)
	{
		fputs(libnet_geterror(link_l),stderr);
		exit(1);
	}
}

