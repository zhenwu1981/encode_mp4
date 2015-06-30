#pragma once
#include <string>
#include <stdio.h>
#include <Winsock2.h>

#include "type.h"

#define SAFE_FREE_BLOCK(x) if(NULL != x) { free(x); }

class MP4Box
{
public:
	MP4Box();
	virtual ~MP4Box();

	void setSize(uint64 uiSize);
	void setSize1(uint64 uiSize);
	uint64 getSize();

	void setType(std::string strType);
	std::string getType();

	void writeFile(FILE* fd);

public:
	uint32	m_uiSize;
	unsigned char	m_ucType[4];
	uint64  m_ullLargesize;
};

