#pragma once

#include "MP4Box.h"

struct TimeToSampleBox
{
	uint32	m_uiSampleCount;
	uint32	m_uiSampleDelta;
};

//Ê±¼ä¼ä¸ô
class MP4Stts : public MP4Box
{
public:
	MP4Stts();
	virtual ~MP4Stts();

	void createMP4Stts(unsigned char ucVersion);
	void writeFile(FILE* fd);

	void setSampleDuration(uint32 uiDuration);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiEntryCount;
	TimeToSampleBox* m_pstSampleBox;
};

