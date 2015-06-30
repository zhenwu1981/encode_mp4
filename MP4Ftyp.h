#pragma once

#include "MP4Box.h"

class MP4Ftyp : public MP4Box
{
public:
	MP4Ftyp();
	virtual ~MP4Ftyp();

	void createMP4Ftyp(std::string strMajorBrand, uint32 uiMinorVersion, int iCompatibleLength, std::string* pstrCompatibleBrands);
	void writeFile(FILE* fd);

private:
	unsigned char m_ucMajorBrand[4];
	uint32 m_uiMinorVersion;
	int m_iCompatibleLength;
	unsigned char m_pucCompatibleBrands[MAX][4];
};

