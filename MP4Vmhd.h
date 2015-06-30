#pragma once

#include "MP4Box.h"

//สำฦต
class MP4Vmhd :public MP4Box
{
public:
	MP4Vmhd();
	virtual ~MP4Vmhd();

	void creatMP4Vmhd(unsigned char ucVersion);
	void writeFile(FILE* fd);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint16	m_usGraphicsmode;
	uint16	m_usOpcolor[3];
};

