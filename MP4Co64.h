#pragma once

#include "MP4Box.h"

//chunk offset 64
class MP4Co64 : public MP4Box
{
public:
	MP4Co64();
	virtual ~MP4Co64();

	void createMP4Co64();

	void writeFile(FILE* fd);

	void setChunkOffset(uint64 iOffset);

private:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiEntryCount;
	uint64*	m_puiChunkOffset;
};

