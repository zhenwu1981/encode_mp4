
#include "MP4Stsz.h"


MP4Stsz::MP4Stsz()
{
	m_puiEntrySize = NULL;
}


MP4Stsz::~MP4Stsz()
{
	SAFE_FREE_BLOCK(m_puiEntrySize);
}

void MP4Stsz::createMP4Stsz()
{
	m_ucVersion = 0;
	memset(m_ucFlag, 0, 3);
	m_uiSampleSize = 0;
	m_uiSampleCount = 0;
	m_puiEntrySize = NULL;

	setSize(12);
	setType("stsz");

	printf("stsz : %d \n", getSize());
}

/*
unsigned char m_ucVersion;
unsigned char m_ucFlag[3];
uint32	m_uiSampleSize;
uint32	m_uiSampleCount;
uint32*	m_puiEntrySize;
*/

void MP4Stsz::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;
	uint16 sTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_uiSampleSize);
	fwrite(&iTemp, 4, 1, fd);
	if (0 == m_uiSampleSize)
	{
		iTemp = htonl(m_uiSampleCount);
		fwrite(&iTemp, 4, 1, fd);

		for (int i = 0; i < m_uiSampleCount; i++)
		{
			iTemp = htonl(m_puiEntrySize[i]);
			fwrite(&iTemp, 4, 1, fd);
		}
	}

	printf("writeFile stsz : %d , m_uiSampleSize %d , m_uiSampleCount : %d \n", getSize(), m_uiSampleSize, m_uiSampleCount);
}

void MP4Stsz::setSampleLength(int iSize)
{
	m_uiSampleCount += 1;

	if (NULL == m_puiEntrySize)
	{
		m_puiEntrySize = (uint32*)malloc(sizeof(uint32));
	} 
	else
	{
		m_puiEntrySize = (uint32*)realloc(m_puiEntrySize,m_uiSampleCount*sizeof(uint32));
	}

	m_puiEntrySize[m_uiSampleCount - 1] = iSize;

	uint64 ullLen = getSize();
	ullLen += 4;
	setSize1(ullLen);

	//printf("stsz : %d ,", getSize());
}
