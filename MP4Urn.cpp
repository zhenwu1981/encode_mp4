#include "MP4Urn.h"


MP4Urn::MP4Urn()
{
}


MP4Urn::~MP4Urn()
{
}

void MP4Urn::createMP4Urn(unsigned char ucVersion, std::string strName, std::string strLocation)
{
	m_ucVersion = ucVersion;
	memset(m_ucFlag, 0, 3);
	m_strName = strName;
	m_strLocation = strLocation;

	int iSize = 4 + m_strLocation.length() + m_strName.length();
	setSize(iSize);
	setType("urn");
}
