//
// Created by lichong on 2017/7/24.
//
#include <iostream>
#include <sys/types.h>
#include <unistd.h>   //getuid()
#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <jni.h>
#include <time.h>
#include "com_example_lichong_capturer_CapturePacket.h"
#define JNI_FALSE 0
#define JNI_TRUE 1
using namespace std;
void myCallback(u_char * uchar, const struct pcap_pkthdr *  packet,const u_char * data)
{
	bpf_u_int32 length=     packet->caplen;
	bpf_u_int32 plen=   packet->len;
	string filename="/sdcard/wifi/data/myFile";
	ofstream writer((filename+".tmp").c_str(),ios::app);
	writer<<"the cap len: "<<length<<"the pcaket len: "<<plen<<endl;
	writer.close();
}


int main()
{


     char error_buffer[100];
	char *device;
   	device= pcap_lookupdev(error_buffer);
	if(device)
	{
		printf("pcap_lookupdev successful\n%s\n",device);
	}else
	{
		printf("fault:\n");
		printf("%s\n",error_buffer);
	}
     char error_buffer2[100];
     pcap_t* pPcap_t=    pcap_open_live("wlan0",65535,0,-1,error_buffer2);
	if(pPcap_t)
	{
		printf("open successful\n");
	}else
	{
		printf("fault:\n");
		printf("%s\n",error_buffer2);
	}
     unsigned char error_buffer1[100];
   int n= pcap_loop(pPcap_t,5,myCallback,error_buffer1);


   printf("%d:%s",n,error_buffer1);

   scanf("%d",&n);

    return 0;
}
