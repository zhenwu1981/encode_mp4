
#include "MP4Minf.h"


MP4Minf::MP4Minf()
{
}


MP4Minf::~MP4Minf()
{
}

void MP4Minf::createMP4Minf(int iType)
{
	m_iType = iType;
	uint64 ullLen = 0;
	if (0 == m_iType)
	{
		ullLen = m_stVmhd.getSize() + m_stDinf.getSize() + m_stStbl.getSize();
	} 
	else
	{
		ullLen = m_stSmhd.getSize() + m_stDinf.getSize() + m_stStbl.getSize();
	}

	setSize(ullLen);
	setType("minf");

	printf("minf : %d \n", getSize());
}

void MP4Minf::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	if (0 == m_iType)
	{
		m_stVmhd.writeFile(fd);
	} 
	else
	{
		m_stSmhd.writeFile(fd);		
	}

	m_stDinf.writeFile(fd);
	m_stStbl.writeFile(fd);

	printf("writeFile minf : %d \n", getSize());
}
