
#include "MP4Url.h"


MP4Url::MP4Url()
{
}


MP4Url::~MP4Url()
{
}

void MP4Url::createMP4Url(unsigned char ucVersion, std::string strLocation)
{
	m_ucVersion = ucVersion;
	memset(m_ucFlag, 0, 3);
	m_ucFlag[2] = 1;
	m_strLocation = strLocation;

	int iSize = 4 + m_strLocation.length();
	setSize(iSize);
	setType("url ");

	printf("url : %d \n", getSize());
}

/*
unsigned char m_ucVersion;
unsigned char m_ucFlag[3];
std::string m_strLocation;
*/

void MP4Url::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	fwrite(m_strLocation.c_str(), m_strLocation.length(),1,fd);

	printf("writeFile url : %d \n", getSize());
}
