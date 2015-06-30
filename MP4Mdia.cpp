
#include "MP4Mdia.h"


MP4Mdia::MP4Mdia()
{
}


MP4Mdia::~MP4Mdia()
{
}

void MP4Mdia::createMP4Mdia()
{
	uint64 iLen = m_stMdhd.getSize() + m_stHdlr.getSize() + m_stMinf.getSize();
	setSize(iLen);
	setType("mdia");

	printf("mdia : %d \n", getSize());
}

void MP4Mdia::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	m_stMdhd.writeFile(fd);
	m_stHdlr.writeFile(fd);
	m_stMinf.writeFile(fd);

	printf("writeFile mdia : %d \n", getSize());
}
