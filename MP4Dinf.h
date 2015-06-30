#pragma once

#include "MP4Box.h"

#include "MP4Dref.h"

class MP4Dinf : public MP4Box
{
public:
	MP4Dinf();
	virtual ~MP4Dinf();

	void createMP4Dinf();
	void writeFile(FILE* fd);

public:
	MP4Dref		m_stDref;
};

