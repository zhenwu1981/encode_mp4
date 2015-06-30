#pragma once

#include "MP4Box.h"


//I ֡
class MP4Stss : public MP4Box
{
public:
	MP4Stss();
	virtual ~MP4Stss();

	void createMP4Stss();

	void writeFile(FILE* fd);

	void setIFrameIndex(uint32 uiIndex);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiEntryCount;
	uint32*	m_puiSampleNumber;
};

