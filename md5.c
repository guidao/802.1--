#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "md5.h"

void  md5_sum(char *buf,int len)
{
	char md5_str[32]="";
	FILE *p=fopen("temp.temp","wb");
	
	fwrite(buf,len,1,p);
	fclose(p);

	system("md5sum -b temp.temp>temp");
	p=fopen("temp","r");
	
	fread(md5_str,32,1,p);
	fclose(p);
	int i=0;
	for(i=0;i<16;++i)
	{	
		sscanf(md5_str+2*i,"%02x",&buf[i]);
	}
	
}
