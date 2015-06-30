#pragma once

#include "MP4Box.h"

class MP4Stsz : public MP4Box
{
public:
	MP4Stsz();
	virtual ~MP4Stsz();

	void createMP4Stsz();

	void writeFile(FILE* fd);

	void setSampleLength(int iSize);

private:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiSampleSize;
	uint32	m_uiSampleCount;
	uint32*	m_puiEntrySize;
};

