#include "MP4Vmhd.h"


MP4Vmhd::MP4Vmhd()
{
}


MP4Vmhd::~MP4Vmhd()
{
}

void MP4Vmhd::creatMP4Vmhd(unsigned char ucVersion)
{
	m_ucVersion = ucVersion;
	memset(m_ucFlag, 0, 3);
	m_ucFlag[2] = 1;
	m_usGraphicsmode = 0;
	memset(m_usOpcolor, 0, sizeof(uint16)*3);

	setSize(12);
	setType("vmhd");

	printf("vmhd : %d \n", getSize());
}

/*
unsigned char m_ucVersion;
unsigned char m_ucFlag[3];
uint16	m_usGraphicsmode;
uint16	m_usOpcolor[3];
*/

void MP4Vmhd::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint16 sTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	sTemp = htons(m_usGraphicsmode);
	fwrite(&sTemp, 2, 1, fd);

	for (int i = 0; i < 3;i++)
	{
		sTemp = htons(m_usOpcolor[i]);
		fwrite(&sTemp, 2, 1, fd);
	}

	printf("writeFile vmhd : %d \n", getSize());
}
