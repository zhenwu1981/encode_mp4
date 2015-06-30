
#include "MP4Ctts.h"


MP4Ctts::MP4Ctts()
{
	m_pstOffsetBox = NULL;
}


MP4Ctts::~MP4Ctts()
{
	SAFE_FREE_BLOCK(m_pstOffsetBox);
}

void MP4Ctts::createMP4Ctts(unsigned char ucVersion)
{
	m_ucVersion = 0;
	memset(m_ucFlag, 0, 3);
	m_uiEntryCount = 0;
	m_pstOffsetBox = NULL;

	setSize(8);
	setType("ctts");
}

void MP4Ctts::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_uiEntryCount);
	fwrite(&iTemp, 4, 1, fd);
	for (int i = 0; i < m_uiEntryCount; i++)
	{
		CompositionOffsetBox& stBox = m_pstOffsetBox[i];

		iTemp = htonl(stBox.m_uiSampleCount);
		fwrite(&iTemp, 4, 1, fd);
		iTemp = htonl(stBox.m_uiSampleOffset);
		fwrite(&iTemp, 4, 1, fd);
	}
}

void MP4Ctts::setSampleDuration(uint32 uiDuration)
{
	if (NULL == m_pstOffsetBox)
	{
		m_pstOffsetBox = (CompositionOffsetBox*)malloc(sizeof(CompositionOffsetBox));
		m_pstOffsetBox->m_uiSampleCount = 1;
		m_pstOffsetBox->m_uiSampleOffset = uiDuration;

		m_uiEntryCount = 1;

		uint64 ullLen = getSize();
		ullLen += 8;
		setSize1(ullLen);
	}
	else
	{
		if (m_pstOffsetBox[m_uiEntryCount - 1].m_uiSampleOffset == uiDuration)
		{
			m_pstOffsetBox[m_uiEntryCount - 1].m_uiSampleCount += 1;
		}
		else
		{
			m_uiEntryCount += 1;
			m_pstOffsetBox = (CompositionOffsetBox*)realloc(m_pstOffsetBox, m_uiEntryCount*sizeof(CompositionOffsetBox));
			m_pstOffsetBox[m_uiEntryCount - 1].m_uiSampleCount = 1;
			m_pstOffsetBox[m_uiEntryCount - 1].m_uiSampleOffset = uiDuration;

			uint64 ullLen = getSize();
			ullLen += 8;
			setSize1(ullLen);
		}
	}
}
