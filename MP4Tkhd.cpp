#include "MP4Tkhd.h"


MP4Tkhd::MP4Tkhd()
{
}

MP4Tkhd::~MP4Tkhd()
{
}

void MP4Tkhd::createMP4Tkhd(unsigned char ucVersion, unsigned char* ucFlag, uint32 uiCreationTime, uint32 uiModificationTime, uint32 uiTrackID, uint32 uiDuration, uint16 usVolume, uint32 uiWidth, uint32 uiHeight)
{
	m_ucVersion = ucVersion;
	memcpy(m_ucFlag,ucFlag,3);
	m_uiCreationTime = uiCreationTime;
	m_uiModificationTime = uiModificationTime;
	m_uiTrackID = uiTrackID;
	m_uiReserved = 0;
	m_uiDuration = uiDuration;
	memset(m_uiReserved1, 0, sizeof(uint32)* 2);
	m_usLayer = 0;
	m_usAlternateGroup = 0;
	m_usVolume = usVolume;
	m_uiReserved2 = 0;
	m_uiMatrix[0] = m_uiMatrix[4] = 0x00010000;
	m_uiMatrix[1] = m_uiMatrix[2] = m_uiMatrix[3] = m_uiMatrix[5] = m_uiMatrix[6] = m_uiMatrix[7] = 0;
	m_uiMatrix[8] = 0x40000000;
	m_uiWidth = uiWidth;
	m_uiHeight = uiHeight;

	setSize(84);
	setType("tkhd");

	printf("tkhd : %d \n", getSize());
}

/*
unsigned char m_ucVersion;
unsigned char m_ucFlag[3];
uint32	m_uiCreationTime;
uint32	m_uiModificationTime;
uint32	m_uiTrackID;
uint32	m_uiReserved;
uint32	m_uiDuration;
uint32	m_uiReserved1[2];
uint16	m_usLayer;
uint16	m_usAlternateGroup;
uint16	m_usVolume;
uint16	m_uiReserved2;
uint32	m_uiMatrix[9];
uint32	m_uiWidth;
uint32	m_uiHeight;
*/

void MP4Tkhd::writeFile(FILE* fd)
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
	iTemp = htonl(m_uiTrackID);
	fwrite(&iTemp, 4, 1, fd);
	fwrite(&m_uiReserved, 4, 1, fd);
	iTemp = htonl(m_uiDuration);
	fwrite(&iTemp, 4, 1, fd);
	fwrite(&m_uiReserved1[0], 4, 1, fd);
	fwrite(&m_uiReserved1[1], 4, 1, fd);

	sTemp = htons(m_usLayer);
	fwrite(&sTemp, 2, 1, fd);
	sTemp = htons(m_usAlternateGroup);
	fwrite(&sTemp, 2, 1, fd);
	sTemp = htons(m_usVolume);
	fwrite(&sTemp, 2, 1, fd);
	fwrite(&m_uiReserved2, 2, 1, fd);

	for (int i = 0; i < 9;i ++)
	{
		iTemp = htonl(m_uiMatrix[i]);
		fwrite(&iTemp, 4, 1, fd);
	}

	//!! TODO 16	
	iTemp = htons(m_uiWidth);
	fwrite(&iTemp, 4, 1, fd);
	iTemp = htons(m_uiHeight);
	fwrite(&iTemp, 4, 1, fd);
}
