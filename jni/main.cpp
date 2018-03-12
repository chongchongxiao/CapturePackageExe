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
using namespace std;

void myCallback(u_char * uchar, const struct pcap_pkthdr *  packet,const u_char * data);
string getTime();

int main()
{
	string filename="/sdcard/wifi/log/logFile";
	ofstream writer((filename+".tmp").c_str(),ios::app);
	char error_buffer2[100];
	setuid(0);
    pcap_t* pPcap_t=pcap_open_live("wlan0",65535,0,-1,error_buffer2);
    if(getuid()!=0)
	{
		writer<<getTime()<<"未使用root权限运行，应用程序停止运行！"<<endl;
		exit(-1);
	}
    if(!pPcap_t)
    {
        writer<<getTime()<<"wlan0 open failed"<<endl;
        exit(-1);
    }
    writer<<getTime()<<"wlan0 open successful"<<endl;
    unsigned char error_buffer1[100];
    writer.close();
    int n= pcap_loop(pPcap_t,10,myCallback,error_buffer1);
    return true;
}

void myCallback(u_char * uchar, const struct pcap_pkthdr *  packet,const u_char * data)
{
	bpf_u_int32 length=     packet->caplen;
	bpf_u_int32 plen=   packet->len;
	string filename="/sdcard/wifi/data/myFile";
	ofstream writer((filename+".tmp").c_str(),ios::app);
	writer<<getTime()<<"the cap len: "<<length<<"the pcaket len: "<<plen<<endl;
	writer.close();
}

string getTime()
{
    time_t tt = time(NULL);//这句返回的只是一个时间cuo
    tm* t= localtime(&tt);
    char str[50];
    memset(str,'\0',50);
    sprintf(str,"%d-%02d-%02d %02d:%02d:%02d  ",
    t->tm_year + 1900,
    t->tm_mon + 1,
    t->tm_mday,
    t->tm_hour,
    t->tm_min,
    t->tm_sec);
    return string(str);
}
