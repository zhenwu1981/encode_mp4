
#include "MP4Hdlr.h"


MP4Hdlr::MP4Hdlr()
{
}


MP4Hdlr::~MP4Hdlr()
{
}

void MP4Hdlr::createMP4Hdlr(uint32 uiPreDefined, uint32 uiHandlerType, std::string strName)
{
	m_ucVersion = 0;
	memset(m_ucFlag, 0, 3);
	m_uiPreDefined = uiPreDefined;
	m_uiHandlerType = uiHandlerType;
	memset(m_uiReserved, 0, sizeof(uint32)* 3);
	m_strName = strName;

	int iSize = 24 + strName.length() + 1;
	setSize(iSize);
	setType("hdlr");

	printf("hdlr : %d \n", getSize());
}

/*
unsigned char m_ucVersion;
unsigned char m_ucFlag[3];
uint32	m_uiPreDefined;
uint32	m_uiHandlerType;
uint32	m_uiReserved[3];
std::string m_strName;
*/

void MP4Hdlr::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;
	uint16 sTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_uiPreDefined);
	fwrite(&iTemp, 4, 1, fd);
	iTemp = htonl(m_uiHandlerType);
	fwrite(&iTemp, 4, 1, fd);
	for (int i = 0; i < 3; i++)
	{
		fwrite(&m_uiReserved[i], 4, 1, fd);
	}

	fwrite(m_strName.c_str(), m_strName.length(), 1, fd);
	unsigned char tt = 0;
	fwrite(&tt, 1, 1, fd);

	printf("writeFile hdlr : %d \n", getSize());
}
