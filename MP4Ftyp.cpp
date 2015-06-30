
#include "MP4Ftyp.h"


MP4Ftyp::MP4Ftyp()
{
}


MP4Ftyp::~MP4Ftyp()
{
}

void MP4Ftyp::createMP4Ftyp(std::string strMajorBrand, uint32 uiMinorVersion, int iCompatibleLength, std::string* pstrCompatibleBrands)
{
	memcpy(m_ucMajorBrand,strMajorBrand.c_str(),4);
	m_uiMinorVersion = uiMinorVersion;
	m_iCompatibleLength = iCompatibleLength;
	for (int i = 0; i < m_iCompatibleLength; i++)
	{
		memcpy(m_pucCompatibleBrands[i], pstrCompatibleBrands[i].c_str(),4);
	}

	unsigned long iLength = 8 + 4 * iCompatibleLength;

	setSize(iLength);
	setType("ftyp");

	printf("ftyp : %d \n", getSize());
}

/*
unsigned char m_ucMajorBrand[4];
uint32 m_uiMinorVersion;
int m_iCompatibleLength;
unsigned char m_pucCompatibleBrands[MAX][4];
*/

void MP4Ftyp::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);

	fwrite(m_ucMajorBrand,4,1,fd);
	uint32 uiTemp = htonl(m_uiMinorVersion);
	fwrite(&uiTemp, 4, 1, fd);
	for (int i = 0; i < m_iCompatibleLength; i++)
	{
		fwrite(m_pucCompatibleBrands[i], 4, 1, fd);
	}

	printf("writeFile ftyp : %d \n", getSize());

	MP4Box stBox;
	stBox.setSize(0);
	stBox.setType("free");
	stBox.writeFile(fd);
}
