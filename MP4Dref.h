#pragma once

#include "MP4Box.h"

#include "MP4Url.h"

class MP4Dref : public MP4Box
{
public:
	MP4Dref();
	virtual ~MP4Dref();

	void createMP4Dref(unsigned char ucVersion);

	void writeFile(FILE* fd);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiEntryCount;
	MP4Url	m_stUrl;
	//MP4Box*	m_stDataEntry[MAX];	// MP4Url , MP4Urn
};

