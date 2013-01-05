cc=gcc -Wall `libnet-config --defines`  
dd=`libnet-config --libs` -lpcap
myclient : md5.o send.o recv.o main.o
	$(cc) -o myclient $^ $(dd)
md5.o : md5.h md5.c
	$(cc) -c $^ $(dd)

send.o : md5.h send.h send.c
	$(cc) -c $^	$(dd)
	
recv.o : send.h recv.h recv.c
	$(cc) -c $^	$(dd)

main.o : main.c
