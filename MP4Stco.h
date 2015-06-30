#pragma once

#include "MP4Box.h"

//chunk offset 32
class MP4Stco : public MP4Box
{
public:
	MP4Stco();
	virtual ~MP4Stco();

	void createMP4Stco();
	void writeFile(FILE* fd);

	void setChunkOffset(uint64 iOffset);

private:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiEntryCount;
	uint32*	m_puiChunkOffset;
};

