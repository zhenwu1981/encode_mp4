#pragma once

#include "MP4Box.h"

class MP4Mdhd : public MP4Box
{
public:
	MP4Mdhd();
	virtual ~MP4Mdhd();

	void createMP4Mdhd(unsigned char ucVersion, uint32 uiCreationTime, uint32 uiModificationTime, uint32 uiTimescale, uint32 uiDuration
		, uint16 usLanguage, uint16 usPreDefined);

	void writeFile(FILE* fd);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiCreationTime;
	uint32	m_uiModificationTime;
	uint32	m_uiTimescale;
	uint32	m_uiDuration;
	uint16	m_usLanguage;
	uint16	m_usPreDefined;
};

