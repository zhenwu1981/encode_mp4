#pragma once

#include "MP4Box.h"

class MP4Elst : public MP4Box
{
public:
	MP4Elst();
	~MP4Elst();

	void createMP4Elst(unsigned int uiTotalTime);

	void writeFile(FILE* fd);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];

	uint32	m_iEntryCount;
	uint32  m_iTotalTime;
	uint32	m_iMediaTime;
	uint16	m_sMediaRateInteger;
	uint16	m_sMediaRateFraction;
};


class MP4Edts : public MP4Box
{
public:
	MP4Edts();
	~MP4Edts();

	void createMP4Edts();

	void writeFile(FILE* fd);
public:
	MP4Elst	m_stElst;
};

