#include "MP4Box.h"


MP4Box::MP4Box()
{
}


MP4Box::~MP4Box()
{
}

void MP4Box::setSize(uint64 uiSize)
{
	uiSize += 8;

	if (uiSize > 0xFFFFFFFF)
	{
		uiSize += 8;
		m_uiSize = 1;
		m_ullLargesize = uiSize;
	}
	else
	{
		m_uiSize = (uint32)uiSize;
		m_ullLargesize = 1;
	}
}

uint64 MP4Box::getSize()
{
	if (1 == m_uiSize)
	{
		return m_ullLargesize;
	} 
	else
	{
		return m_uiSize;
	}
}

void MP4Box::setType(std::string strType)
{
	memcpy(m_ucType,strType.c_str(),4);
}

std::string MP4Box::getType()
{
	std::string strType = (char*)m_ucType;
	return strType;
}

void MP4Box::writeFile(FILE* fd)
{
	uint32 uiTemp = htonl(m_uiSize);
	fwrite(&uiTemp, sizeof(uint32), 1, fd);
	fwrite(m_ucType, 4, 1, fd);

	if (1 == m_uiSize)
	{
		uint64 ullTemp = htonll(m_ullLargesize);
		fwrite(&ullTemp,sizeof(uint64),1,fd);
	}
}

void MP4Box::setSize1(uint64 uiSize)
{
	if (uiSize > 0xFFFFFFFF)
	{
		m_uiSize = 1;
		m_ullLargesize = uiSize;
	}
	else
	{
		m_uiSize = (uint32)uiSize;
		m_ullLargesize = 1;
	}
}
