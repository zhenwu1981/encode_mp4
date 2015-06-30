#pragma once

#include "MP4Box.h"

#include "MP4Mdhd.h"
#include "MP4Hdlr.h"
#include "MP4Minf.h"

class MP4Mdia : public MP4Box
{
public:
	MP4Mdia();
	virtual ~MP4Mdia();

	void createMP4Mdia();
	void writeFile(FILE* fd);

public:
	MP4Mdhd		m_stMdhd;
	MP4Hdlr		m_stHdlr;
	MP4Minf		m_stMinf;
};

