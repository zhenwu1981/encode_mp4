#pragma once

#include "MP4Box.h"

#include "MP4Stsd.h"
#include "MP4Stts.h"
#include "MP4Ctts.h"
#include "MP4Stsz.h"
#include "MP4Stsc.h"
#include "MP4Stco.h"
#include "MP4Co64.h"
#include "MP4Stss.h"

class MP4Stbl : public MP4Box
{
public:
	MP4Stbl();
	virtual ~MP4Stbl();

	void createMP4Stbl(int type);

	void writeFile(FILE* fd);

public:
	int m_iType;

	MP4Stsd		m_stStsd;
	MP4Stts		m_stStts;
	MP4Ctts		m_stCtts;
	MP4Stsz		m_stStsz;
	MP4Stsc		m_stStsc;
	MP4Stco		m_stStco;
	MP4Co64		m_stCo64;
	MP4Stss		m_stStss;
};

