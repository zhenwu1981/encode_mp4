#ifndef MP4_TYPE_H
#define MP4_TYPE_H

#define uint32	unsigned int
#define uint64	unsigned long long
#define uint16	unsigned short
#define int16	unsigned short
#define uint8	unsigned char

#define MAX		100

#include <sys/timeb.h>
#include <arpa/inet.h>
#include <string.h>

uint64 MP4GetAbsTimestamp();

#if __linux__
unsigned long long htonll(unsigned long long host);
#endif

#endif
