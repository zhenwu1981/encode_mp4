
#include "MP4Stsc.h"


MP4Stsc::MP4Stsc()
{
    m_stChunkBox = NULL;
}


MP4Stsc::~MP4Stsc()
{
    if (NULL != m_stChunkBox)
    {
        free(m_stChunkBox);
    }
}

void MP4Stsc::createMP4Stsc()
{
	m_ucVersion = 0;
	memset(m_ucFlag, 0, 3);
	m_uiEntryCount = 0;
	m_stChunkBox = NULL;

	setSize(8);
	setType("stsc");

	printf("stsc : %d \n", getSize());
}

void MP4Stsc::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_uiEntryCount);
	fwrite(&iTemp, 4, 1, fd);
	for (int i = 0; i < m_uiEntryCount; i++)
	{
		SampleToChunkBox& stBox = m_stChunkBox[i];

		iTemp = htonl(stBox.m_uiFirstChunk);
		fwrite(&iTemp, 4, 1, fd);
		iTemp = htonl(stBox.m_uiSamplesPerChunk);
		fwrite(&iTemp, 4, 1, fd);
		iTemp = htonl(stBox.m_uiSampleDescriptionIndex);
		fwrite(&iTemp, 4, 1, fd);
	}

	printf("writeFile stsc : %d , m_uiEntryCount : %d \n", getSize(), m_uiEntryCount);
}

void MP4Stsc::setSmapleToChunk(uint32 uiSampleId, uint32 uiChunkId, uint32 uiSamplesPerChunk)
{
	if (NULL == m_stChunkBox)
	{
		m_uiEntryCount += 1;
		m_stChunkBox = (SampleToChunkBox*)malloc(sizeof(SampleToChunkBox));
		m_stChunkBox[m_uiEntryCount - 1].m_uiFirstChunk = uiChunkId;
		m_stChunkBox[m_uiEntryCount - 1].m_uiSamplesPerChunk = uiSamplesPerChunk;
		m_stChunkBox[m_uiEntryCount - 1].m_uiSampleDescriptionIndex = 1;
		
		uint64 ullLen = getSize();
		ullLen += 12;
		setSize1(ullLen);
	}
	else
	{
		if (m_stChunkBox[m_uiEntryCount - 1].m_uiSamplesPerChunk != uiSamplesPerChunk)
		{
			m_uiEntryCount += 1;
			m_stChunkBox = (SampleToChunkBox*)realloc(m_stChunkBox, m_uiEntryCount*sizeof(SampleToChunkBox));
			m_stChunkBox[m_uiEntryCount - 1].m_uiFirstChunk = uiChunkId;
			m_stChunkBox[m_uiEntryCount - 1].m_uiSamplesPerChunk = uiSamplesPerChunk;
			m_stChunkBox[m_uiEntryCount - 1].m_uiSampleDescriptionIndex = 1;

			uint64 ullLen = getSize();
			ullLen += 12;
			setSize1(ullLen);
		}
	}

	//printf("stsc : %d ,", getSize());
}
