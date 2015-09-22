
#include "MP4Stbl.h"


MP4Stbl::MP4Stbl()
{
}


MP4Stbl::~MP4Stbl()
{
}

void MP4Stbl::createMP4Stbl(int type)
{
	m_iType = type;

	uint64 ullLen = 0;

	if (0 == m_iType)
	{
		ullLen = m_stStsd.getSize() + m_stStts.getSize() + m_stStsz.getSize() + m_stStsc.getSize() + m_stStco.getSize() + m_stStss.getSize() +m_stCtts.getSize();
	}
	else
	{
		ullLen = m_stStsd.getSize() + m_stStts.getSize() + m_stStsz.getSize() + m_stStsc.getSize() + m_stStco.getSize();
	}

	setSize(ullLen);
	setType("stbl");

	printf("stbl : %d \n", getSize());
}

void MP4Stbl::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);

	m_stStsd.writeFile(fd);
	m_stStts.writeFile(fd);
	if (0 == m_iType)
	{
		m_stStss.writeFile(fd);
	}
	m_stStsc.writeFile(fd);
	m_stStsz.writeFile(fd);
	m_stStco.writeFile(fd);
	if (0 == m_iType)
	{
		m_stCtts.writeFile(fd);
	}

	printf("writeFile stbl : %d \n", getSize());
}
