#pragma once

#include "MP4Box.h"

struct CompositionOffsetBox
{
	uint32	m_uiSampleCount;
	uint32	m_uiSampleOffset;
};

//PTS ¼ä¸ô
class MP4Ctts : public MP4Box
{
public:
	MP4Ctts();
	virtual ~MP4Ctts();

	void createMP4Ctts(unsigned char ucVersion);
	void writeFile(FILE* fd);

	void setSampleDuration(uint32 uiDuration);

private:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiEntryCount;
	CompositionOffsetBox* m_pstOffsetBox;
};

