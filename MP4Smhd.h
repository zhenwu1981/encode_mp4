#pragma once

#include "MP4Box.h"

class MP4Smhd : public MP4Box
{
public:
	MP4Smhd();
	virtual ~MP4Smhd();

	void createMP4Smhd(unsigned char ucVersion);

	void writeFile(FILE* fd);

private:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint16	m_usBalance;
	uint16	m_usReserved;
};

