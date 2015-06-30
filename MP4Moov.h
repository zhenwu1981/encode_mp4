#pragma once

#include "MP4Box.h"

#include "MP4Mvhd.h"
#include "MP4Trak.h"

class MP4Moov : public MP4Box
{
public:
	MP4Moov();
	virtual ~MP4Moov();

	void createMP4Moov();

	void writeFile(FILE* fd);

public:
	MP4Mvhd		m_stMvhd;
	int			m_iTrakSize;
	MP4Trak		m_stTrak[MAX];
};

