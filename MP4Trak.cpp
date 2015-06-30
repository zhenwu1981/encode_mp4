
#include "MP4Trak.h"


MP4Trak::MP4Trak()
{
}


MP4Trak::~MP4Trak()
{
}

void MP4Trak::createMP4Trak()
{
	uint64 iLen = m_stMdia.getSize() + m_stTkhd.getSize() + m_stEdts.getSize();
	setSize(iLen);
	setType("trak");

	printf("trak : %d \n", getSize());
}

void MP4Trak::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);

	m_stTkhd.writeFile(fd);
	m_stEdts.writeFile(fd);
	m_stMdia.writeFile(fd);

	printf("writeFile trak : %d \n", getSize());
}
