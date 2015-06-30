#pragma once

#include "MP4Box.h"


struct  SampleToChunkBox
{
	uint32	m_uiFirstChunk;
	uint32	m_uiSamplesPerChunk;
	uint32	m_uiSampleDescriptionIndex;
};

//sample to chunk
class MP4Stsc : public MP4Box
{
public:
	MP4Stsc();
	virtual ~MP4Stsc();

	void createMP4Stsc();

	void writeFile(FILE* fd);

	void setSmapleToChunk(uint32 uiSampleId, uint32 uiChunkId, uint32 uiSamplesPerChunk);

private:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiEntryCount;
	SampleToChunkBox*	m_stChunkBox;
};

