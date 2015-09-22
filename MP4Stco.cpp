
#include "MP4Stco.h"


MP4Stco::MP4Stco()
{
    m_puiChunkOffset = NULL;
}


MP4Stco::~MP4Stco()
{
    if (NULL != m_puiChunkOffset)
    {
        free(m_puiChunkOffset);
    }
}

void MP4Stco::createMP4Stco()
{
	m_ucVersion = 0;
	memset(m_ucFlag, 0, 3);
	m_uiEntryCount = 0;
	m_puiChunkOffset = NULL;

	setSize(8);
	setType("stco");

	printf("stco : %d \n", getSize());
}

void MP4Stco::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_uiEntryCount);
	fwrite(&iTemp, 4, 1, fd);
	for (int i = 0; i < m_uiEntryCount; i++)
	{
		iTemp = htonl(m_puiChunkOffset[i]);
		fwrite(&iTemp, 4, 1, fd);
	}

	printf("writeFile stco : %d , m_uiEntryCount %d  \n", getSize(), m_uiEntryCount);
}

void MP4Stco::setChunkOffset(uint64 iOffset)
{
	m_uiEntryCount += 1;

	if (NULL == m_puiChunkOffset)
	{
		m_puiChunkOffset = (uint32*)malloc(sizeof(uint32));
	}
	else
	{
		m_puiChunkOffset = (uint32*)realloc(m_puiChunkOffset, m_uiEntryCount*sizeof(uint32));
	}

	m_puiChunkOffset[m_uiEntryCount - 1] = iOffset;

	uint64 ullLen = getSize();
	ullLen += 4;
	setSize1(ullLen);

	//printf("stco : %d ,", getSize());
}
