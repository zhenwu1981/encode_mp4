#pragma once

#include "MP4Box.h"

#include "MP4Vmhd.h"
#include "MP4Smhd.h"
#include "MP4Dinf.h"
#include "MP4Stbl.h"

class MP4Minf : public MP4Box
{
public:
	MP4Minf();
	virtual ~MP4Minf();

	void createMP4Minf(int iType);	//0 video , 1 audio
	void writeFile(FILE* fd);

public:
	int			m_iType;
	MP4Vmhd		m_stVmhd;
	MP4Smhd		m_stSmhd;
	MP4Dinf		m_stDinf;
	MP4Stbl		m_stStbl;
};

