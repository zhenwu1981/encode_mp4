#pragma once

#include "MP4Box.h"

class MP4Hdlr : public MP4Box
{
public:
	MP4Hdlr();
	virtual ~MP4Hdlr();

	void createMP4Hdlr(uint32 uiPreDefined, uint32 uiHandlerType, std::string strName);
	void writeFile(FILE* fd);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiPreDefined;
	uint32	m_uiHandlerType;
	uint32	m_uiReserved[3];
	std::string m_strName;
};

