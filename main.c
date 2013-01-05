#include "recv.h"
#include "send.h"
#include "md5.h"
#include "network.h"


int main(char argc,char *argv[])
{
	if(argc!=4)
	{
		fputs("format error:myclient eth0 username password\n",stderr);
		exit(1);
	}
	init_cap(argv[1],argv[2],strlen(argv[2]),argv[3],strlen(argv[3]));

	init_pcap(argv[1]);

	read_pcap(argv[3]);

}
