
#include "MP4Edts.h"

MP4Elst::MP4Elst()
{

}

MP4Elst::~MP4Elst()
{

}

void MP4Elst::createMP4Elst(unsigned int uiTotalTime)
{
	m_ucVersion = 0;
	memset(m_ucFlag, 0, 3);

	m_iEntryCount = 1;

	setSize(20);
	setType("elst");
}

void MP4Elst::setTotalDuration(uint32 uiDuration)
{
	m_stElst[m_iEntryCount-1].m_iTotalTime = uiDuration;
	m_stElst[m_iEntryCount-1].m_iMediaTime = 0;
	m_stElst[m_iEntryCount-1].m_sMediaRateInteger = 1;
	m_stElst[m_iEntryCount-1].m_sMediaRateFraction = 0;
}

void MP4Elst::setSampleDuration(uint32 uiDuration)
{
	m_stElst[m_iEntryCount-1].m_iTotalTime = uiDuration;
	m_stElst[m_iEntryCount-1].m_iMediaTime = 0xFFFFFFFF;
	m_stElst[m_iEntryCount-1].m_sMediaRateInteger = 1;
	m_stElst[m_iEntryCount-1].m_sMediaRateFraction = 0;
	m_iEntryCount ++;
    setSize(32);
}

void MP4Elst::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;
	uint16 sTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_iEntryCount);
	fwrite(&iTemp, 4, 1, fd);
	for (int i = 0; i < m_iEntryCount; ++i)
	{
		iTemp = htonl(m_stElst[i].m_iTotalTime);
		fwrite(&iTemp, 4, 1, fd);
		iTemp = htonl(m_stElst[i].m_iMediaTime);
		fwrite(&iTemp, 4, 1, fd);

		sTemp = htons(m_stElst[i].m_sMediaRateInteger);
		fwrite(&sTemp, 2, 1, fd);
		sTemp = htons(m_stElst[i].m_sMediaRateFraction);
		fwrite(&sTemp, 2, 1, fd);
	}
}

MP4Edts::MP4Edts()
{
}


MP4Edts::~MP4Edts()
{
}

void MP4Edts::createMP4Edts()
{
	int iLength = m_stElst.getSize();

	setSize(iLength);
	setType("edts");
}

void MP4Edts::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	m_stElst.writeFile(fd);
}
