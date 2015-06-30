#pragma once

#include "MP4Box.h"

class MP4Urn : public MP4Box
{
public:
	MP4Urn();
	virtual ~MP4Urn();

	void createMP4Urn(unsigned char ucVersion, std::string strName, std::string strLocation);

private:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	std::string m_strName;
	std::string m_strLocation;
};

