
#include "MP4Smhd.h"


MP4Smhd::MP4Smhd()
{
}


MP4Smhd::~MP4Smhd()
{
}

void MP4Smhd::createMP4Smhd(unsigned char ucVersion)
{
	m_ucVersion = ucVersion;
	memset(m_ucFlag, 0, 3);
	m_usBalance = 0;
	m_usReserved = 0;

	setSize(8);
	setType("smhd");

	printf("mvhd : %d \n", getSize());
}

void MP4Smhd::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint16 sTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	sTemp = htons(m_usBalance);
	fwrite(&sTemp, 2, 1, fd);
	sTemp = htons(m_usReserved);
	fwrite(&sTemp, 2, 1, fd);

	printf("writeFile Smhd : %d \n", getSize());
}
