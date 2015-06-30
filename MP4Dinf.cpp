
#include "MP4Dinf.h"


MP4Dinf::MP4Dinf()
{
}


MP4Dinf::~MP4Dinf()
{
}

void MP4Dinf::createMP4Dinf()
{
	uint64 ullLen = m_stDref.getSize();

	setSize(ullLen);
	setType("dinf");

	printf("dinf : %d \n", getSize());
}

void MP4Dinf::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	m_stDref.writeFile(fd);

	printf("writeFile dinf : %d \n", getSize());
}
