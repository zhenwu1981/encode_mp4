
#include "MP4Moov.h"


MP4Moov::MP4Moov()
{
	m_iTrakSize = 0;
}


MP4Moov::~MP4Moov()
{
}

void MP4Moov::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	m_stMvhd.writeFile(fd);
	for (int i = 0; i < m_iTrakSize; i++)
	{
		m_stTrak[i].writeFile(fd);
	}

	printf("writeFile moov : %d \n", getSize());
}

void MP4Moov::createMP4Moov()
{
	uint64 iLen = m_stMvhd.getSize();
	for (int i = 0; i < m_iTrakSize; i++)
	{
		iLen += m_stTrak[i].getSize();
	}

	setSize(iLen);
	setType("moov");

	printf("moov : %d \n", getSize());

}
