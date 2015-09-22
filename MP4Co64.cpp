
#include "MP4Co64.h"


MP4Co64::MP4Co64()
{
    m_puiChunkOffset = NULL;
}


MP4Co64::~MP4Co64()
{
    if (NULL != m_puiChunkOffset)
    {
        free(m_puiChunkOffset);
    }
}

void MP4Co64::createMP4Co64()
{
	m_ucVersion = 0;
	memset(m_ucFlag, 0, 3);
	m_uiEntryCount = 0;
	m_puiChunkOffset = NULL;

	setSize(8);
	setType("co64");
}

void MP4Co64::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;
	uint64 ullTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_uiEntryCount);
	fwrite(&iTemp, 4, 1, fd);
	for (int i = 0; i < m_uiEntryCount; i++)
	{
		ullTemp = htonll(m_puiChunkOffset[i]);
		fwrite(&ullTemp, 8, 1, fd);
	}
}

void MP4Co64::setChunkOffset(uint64 iOffset)
{
	m_uiEntryCount += 1;

	if (NULL == m_puiChunkOffset)
	{
		m_puiChunkOffset = (uint64*)malloc(sizeof(uint64));
	}
	else
	{
		m_puiChunkOffset = (uint64*)realloc(m_puiChunkOffset, m_uiEntryCount*sizeof(uint64));
	}

	m_puiChunkOffset[m_uiEntryCount - 1] = iOffset;

	uint64 ullLen = getSize();
	ullLen += 8;
	setSize1(ullLen);
}
