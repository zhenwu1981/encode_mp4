
#include "MP4Mdhd.h"


MP4Mdhd::MP4Mdhd()
{
}


MP4Mdhd::~MP4Mdhd()
{
}

void MP4Mdhd::createMP4Mdhd(unsigned char ucVersion, uint32 uiCreationTime, uint32 uiModificationTime, uint32 uiTimescale, uint32 uiDuration, uint16 usLanguage, uint16 usPreDefined)
{
	m_ucVersion = ucVersion;
	memset(m_ucFlag, 0, 3);
	m_uiCreationTime = uiCreationTime;
	m_uiModificationTime = uiModificationTime;
	m_uiTimescale = uiTimescale;
	m_uiDuration = uiDuration;
	m_usLanguage = usLanguage & 0x7FFF;
	m_usPreDefined = usPreDefined;

	setSize(24);
	setType("mdhd");

	printf("mdhd : %d \n", getSize());
}

/*
unsigned char m_ucVersion;
unsigned char m_ucFlag[3];
uint32	m_uiCreationTime;
uint32	m_uiModificationTime;
uint32	m_uiTimescale;
uint32	m_uiDuration;
uint16	m_usLanguage;
uint16	m_usPreDefined;
*/

void MP4Mdhd::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;
	uint16 sTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_uiCreationTime);
	fwrite(&iTemp, 4, 1, fd);
	iTemp = htonl(m_uiModificationTime);
	fwrite(&iTemp, 4, 1, fd);
	iTemp = htonl(m_uiTimescale);
	fwrite(&iTemp, 4, 1, fd);
	iTemp = htonl(m_uiDuration);
	fwrite(&iTemp, 4, 1, fd);

	sTemp = htons(m_usLanguage);
	fwrite(&sTemp, 2, 1, fd);
	sTemp = htons(m_usPreDefined);
	fwrite(&sTemp, 2, 1, fd);

	printf("writeFile mdhd : %d \n", getSize());
}
