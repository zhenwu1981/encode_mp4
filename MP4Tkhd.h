#pragma once

#include "MP4Box.h"

class MP4Tkhd : public MP4Box
{
public:
	MP4Tkhd();
	virtual ~MP4Tkhd();

	void createMP4Tkhd(unsigned char ucVersion, unsigned char* ucFlag, uint32 uiCreationTime, uint32 uiModificationTime
		, uint32 uiTrackID, uint32 uiDuration, uint16 usVolume, uint32 uiWidth, uint32 uiHeight);

	void writeFile(FILE* fd);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiCreationTime;
	uint32	m_uiModificationTime;
	uint32	m_uiTrackID;
	uint32	m_uiReserved;
	uint32	m_uiDuration;
	uint32	m_uiReserved1[2];
	uint16	m_usLayer;
	uint16	m_usAlternateGroup;
	uint16	m_usVolume;
	uint16	m_uiReserved2;
	uint32	m_uiMatrix[9];
	uint32	m_uiWidth;
	uint32	m_uiHeight;
};

