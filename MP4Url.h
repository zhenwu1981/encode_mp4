#pragma once

#include "MP4Box.h"

class MP4Url : public MP4Box
{
public:
	MP4Url();
	virtual ~MP4Url();

	void createMP4Url(unsigned char ucVersion, std::string strLocation);

	void writeFile(FILE* fd);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	std::string m_strLocation;
};

