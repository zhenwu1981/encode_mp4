#pragma once

#include "MP4Box.h"

class MP4Mdat : public MP4Box
{
public:
	MP4Mdat();
	virtual ~MP4Mdat();

	void createMP4Mdat();
	void writeFile(FILE* fd);

};

