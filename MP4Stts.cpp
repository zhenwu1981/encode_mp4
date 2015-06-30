
#include "MP4Stts.h"


MP4Stts::MP4Stts()
{
	m_pstSampleBox = NULL;
}


MP4Stts::~MP4Stts()
{
	SAFE_FREE_BLOCK(m_pstSampleBox);
}

void MP4Stts::createMP4Stts(unsigned char ucVersion)
{
	m_ucVersion = 0;
	memset(m_ucFlag, 0, 3);
	m_uiEntryCount = 0;
	m_pstSampleBox = NULL;

	setSize(8);
	setType("stts");

	printf("stts : %d \n", getSize());
}

/*
unsigned char m_ucVersion;
unsigned char m_ucFlag[3];
uint32	m_uiEntryCount;
TimeToSampleBox* m_pstSampleBox;
*/

void MP4Stts::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;
	uint16 sTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_uiEntryCount);
	fwrite(&iTemp, 4, 1, fd);
	for (int i = 0; i < m_uiEntryCount; i++)
	{
		TimeToSampleBox& stBox = m_pstSampleBox[i];
		
		iTemp = htonl(stBox.m_uiSampleCount);
		fwrite(&iTemp, 4, 1, fd);
		iTemp = htonl(stBox.m_uiSampleDelta);
		fwrite(&iTemp, 4, 1, fd);
	}

	printf("writeFile stts : %d , m_uiEntryCount : %d \n", getSize(), m_uiEntryCount);
}

void MP4Stts::setSampleDuration(uint32 uiDuration)
{
	//printf("setSampleDuration : %u \n", uiDuration);
	if (NULL == m_pstSampleBox)
	{
		m_pstSampleBox = (TimeToSampleBox*)malloc(sizeof(TimeToSampleBox));
		m_pstSampleBox->m_uiSampleCount = 1;
		m_pstSampleBox->m_uiSampleDelta = uiDuration;

		m_uiEntryCount = 1;

		uint64 ullLen = getSize();
		ullLen += 8;
		setSize1(ullLen);
	}
	else
	{
		if (m_pstSampleBox[m_uiEntryCount - 1].m_uiSampleDelta == uiDuration)
		{
			m_pstSampleBox[m_uiEntryCount - 1].m_uiSampleCount += 1;
		}
		else
		{
			m_uiEntryCount += 1;
			m_pstSampleBox = (TimeToSampleBox*)realloc(m_pstSampleBox, m_uiEntryCount*sizeof(TimeToSampleBox));
			m_pstSampleBox[m_uiEntryCount - 1].m_uiSampleCount = 1;
			m_pstSampleBox[m_uiEntryCount - 1].m_uiSampleDelta = uiDuration;

			uint64 ullLen = getSize();
			ullLen += 8;
			setSize1(ullLen);
		}
	}

	//printf("stts : %d ,", getSize());
}
