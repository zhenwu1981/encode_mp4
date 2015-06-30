#pragma once

#include "MP4Box.h"
#include "MP4Tkhd.h"
#include "MP4Mdia.h"
#include "MP4Edts.h"

class MP4Trak : public MP4Box
{
public:
	MP4Trak();
	virtual ~MP4Trak();

	void createMP4Trak();
	void writeFile(FILE* fd);
	
public:
	MP4Tkhd		m_stTkhd;
	MP4Edts		m_stEdts;
	MP4Mdia		m_stMdia;
};

