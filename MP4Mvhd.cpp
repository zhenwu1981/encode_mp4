
#include "MP4Mvhd.h"


MP4Mvhd::MP4Mvhd()
{
	memset(m_ucFlag, 0, 3);
}

MP4Mvhd::~MP4Mvhd()
{
}

void MP4Mvhd::createMP4Mvhd(unsigned char ucVersion, uint32 uiCreationTime, uint32 uiModificationTime, uint32 uiTimescale, uint32 uiDuration, uint32 uiRate, uint16 usVolume, uint32 uiNextTrackID)
{
	m_ucVersion = ucVersion;
	memset(m_ucFlag, 0, 3);
	m_uiCreationTime = uiCreationTime;
	m_uiModificationTime = uiModificationTime;
	m_uiTimescale = uiTimescale;
	m_uiDuration = uiDuration;
	m_uiRate = uiRate;
	m_usVolume = usVolume;
	memset(m_ucReserved, 0, 10);
	m_uiMatrix[0] = m_uiMatrix[4] = 0x00010000;
	m_uiMatrix[1] = m_uiMatrix[2] = m_uiMatrix[3] = m_uiMatrix[5] = m_uiMatrix[6] = m_uiMatrix[7] = 0;
	m_uiMatrix[8] = 0x40000000;
	memset(m_uiPreDefined, 0, sizeof(uint32)* 6);
	m_uiNextTrackID = uiNextTrackID;

	setSize(100);
	setType("mvhd");

	printf("mvhd : %d \n", getSize());
}

/*
unsigned char m_ucVersion;
unsigned char m_ucFlag[3];
uint32	m_uiCreationTime;
uint32	m_uiModificationTime;
uint32	m_uiTimescale;
uint32	m_uiDuration;
uint32	m_uiRate;
uint16	m_usVolume;
unsigned char m_ucReserved[10];
uint32	m_uiMatrix[9];
uint32	m_uiPreDefined[6];
uint32  m_uiNextTrackID;
*/

void MP4Mvhd::writeFile(FILE* fd)
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
	iTemp = htonl(m_uiRate);
	fwrite(&iTemp, 4, 1, fd);
	sTemp = htons(m_usVolume);
	fwrite(&sTemp, 2, 1, fd);

	fwrite(m_ucReserved, 10, 1, fd);

	for (int i = 0; i < 9; i++)
	{
		iTemp = htonl(m_uiMatrix[i]);
		fwrite(&iTemp, 4, 1, fd);
	}

	for (int i = 0; i < 6; i++)
	{
		iTemp = htonl(m_uiPreDefined[i]);
		fwrite(&iTemp, 4, 1, fd);
	}

	iTemp = htonl(m_uiNextTrackID);
	fwrite(&iTemp, 4, 1, fd);

	printf("writeFile mvhd : %d \n", getSize());
}
