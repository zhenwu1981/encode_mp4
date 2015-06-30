
#include "MP4Stss.h"


MP4Stss::MP4Stss()
{
	m_puiSampleNumber = NULL;
}


MP4Stss::~MP4Stss()
{
	SAFE_FREE_BLOCK(m_puiSampleNumber);
}

void MP4Stss::createMP4Stss()
{
	m_ucVersion = 0;
	memset(m_ucFlag, 0, 3);
	m_uiEntryCount = 0;
	m_puiSampleNumber = NULL;

	setSize(8);
	setType("stss");

	printf("stss : %d \n", getSize());
}

/*
unsigned char m_ucVersion;
unsigned char m_ucFlag[3];
uint32	m_uiEntryCount;
uint32*	m_puiSampleNumber;
*/

void MP4Stss::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_uiEntryCount);
	fwrite(&iTemp, 4, 1, fd);
	for (int i = 0; i < m_uiEntryCount; i++)
	{
		iTemp = htonl(m_puiSampleNumber[i]);
		fwrite(&iTemp, 4, 1, fd);
	}

	printf("writeFile stss : %d , m_uiEntryCount : %d \n", getSize(), m_uiEntryCount);
}

void MP4Stss::setIFrameIndex(uint32 uiIndex)
{
	m_uiEntryCount += 1;

	if (NULL == m_puiSampleNumber)
	{
		m_puiSampleNumber = (uint32*)malloc(sizeof(uint32));
	}
	else
	{
		m_puiSampleNumber = (uint32*)realloc(m_puiSampleNumber, m_uiEntryCount*sizeof(uint32));
	}

	m_puiSampleNumber[m_uiEntryCount - 1] = uiIndex;

	uint64 ullLen = getSize();
	ullLen += 4;
	setSize1(ullLen);

	//printf("stss : %d ,", getSize());
}
