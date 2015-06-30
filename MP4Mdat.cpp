
#include "MP4Mdat.h"


MP4Mdat::MP4Mdat()
{
}


MP4Mdat::~MP4Mdat()
{
}

void MP4Mdat::createMP4Mdat()
{
	setSize(1);
	setType("mdat");
}

void MP4Mdat::writeFile(FILE* fd)
{
	int iSize = 1;
	uint32 uiTemp = htonl(iSize);
	fwrite(&uiTemp, sizeof(uint32), 1, fd);
	fwrite(m_ucType, 4, 1, fd);
}
