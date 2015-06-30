
#include "MP4Dref.h"


MP4Dref::MP4Dref()
{
}


MP4Dref::~MP4Dref()
{
}

void MP4Dref::createMP4Dref(unsigned char ucVersion)
{
	m_ucVersion = ucVersion;
	memset(m_ucFlag, 0, 3);
	m_uiEntryCount = 1;

	uint64 ullLen = 8 + m_stUrl.getSize();

	setSize(ullLen);
	setType("dref");

	printf("dref : %d \n", getSize());
}

/*
unsigned char m_ucVersion;
unsigned char m_ucFlag[3];
uint32	m_uiEntryCount;
MP4Url	m_stUrl;
*/

void MP4Dref::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_uiEntryCount);
	fwrite(&iTemp, 4, 1, fd);

	m_stUrl.writeFile(fd);

	printf("writeFile dref : %d \n", getSize());
}
