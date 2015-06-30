#pragma once

#include "MP4Box.h"

class MP4Mvhd : public MP4Box
{
public:
	MP4Mvhd();
	virtual ~MP4Mvhd();

	void createMP4Mvhd(unsigned char ucVersion , uint32 uiCreationTime , uint32 uiModificationTime , uint32 uiTimescale , uint32 uiDuration 
		,uint32 uiRate , uint16 usVolume , uint32 uiNextTrackID);

	void writeFile(FILE* fd);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiCreationTime;
	uint32	m_uiModificationTime;
	uint32	m_uiTimescale;
	uint32	m_uiDuration;
	uint32	m_uiRate;
	uint16	m_usVolume;
	unsigned char m_ucReserved[10];
	uint32	m_uiMatrix[9];
	uint32	m_uiPreDefined[6];
	uint32  m_uiNextTrackID;
};

