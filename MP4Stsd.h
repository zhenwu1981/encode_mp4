#pragma once

#include "MP4Box.h"

#define MAX 16

class AVCConfigurationBox :public MP4Box
{
public:
	AVCConfigurationBox ();
	virtual ~AVCConfigurationBox();

	void createAVCConfigurationBox(uint8 ucAVCProfileIndication, uint8 ucProfileCompatibility, uint8 ucAVCLevelIndication
		, uint8 ucLengthSizeMinusOne, std::string strSPS , std::string strPPS);

	void writeFile(FILE* fd);

public:
	uint8	m_ucConfigurationVersion;
	uint8	m_ucAVCProfileIndication;	//sps[1]
	uint8	m_ucProfileCompatibility;	//sps[2]
	uint8	m_ucAVCLevelIndication;		//sps[3]
	uint8	m_ucLengthSizeMinusOne;
	uint8	m_ucNumOfSequenceParameterSets;
	uint16	m_usSequenceParameterSetLength;
	std::string m_strSPS;
	uint8	m_ucNumOfPictureParameterSets;
	uint16	m_usPictureParameterSetLength;
	std::string m_strPPS;
};

class  VisualSampleEntry :public MP4Box
{
public:
	VisualSampleEntry();
	virtual ~VisualSampleEntry();

	void createVisualSampleEntry(uint16 usWidth, uint16 usHeight, std::string strCompressorname);

	void writeFile(FILE* fd);

public:
	unsigned char m_ucReserved[6];
	uint16	m_usDataReferenceIndex;
	uint16	m_usPreDefined;
	uint16	m_usReserved;
	uint32	m_uiPreDefined[3];
	uint16	m_usWidth;
	uint16	m_usHeight;
	uint32	m_uiHorizresolution;
	uint32	m_uiVertresolution;
	uint32	m_uiReserved;
	uint16	m_usFrameCount;
	unsigned char m_strCompressorname[32];
	uint16	m_usDepth;
	int16	m_usPreDefined1;

	AVCConfigurationBox		m_stAVCCBox;
};
class SLConfigDescriptor
{
public:
	SLConfigDescriptor();
	virtual ~SLConfigDescriptor();

	void writeFile(FILE* fd);

	uint64 getSize();

public:
	uint8	m_cTag;
	uint8	m_cLength;
	uint8	m_cPredefined;
};

class DecoderSpecificInfo
{
public:
	DecoderSpecificInfo();
	virtual ~DecoderSpecificInfo();

	void createDecoderSpecificInfo(unsigned char* ucData, int len);

	void writeFile(FILE* fd);

	uint64 getSize();

public:
	uint8	m_ctag;
	uint8	m_clength;
	uint8	m_iSpecificInfo[MAX];
};

class DecoderConfigDescriptor 
{
public:
	DecoderConfigDescriptor();
	virtual ~DecoderConfigDescriptor();

	void createDecoderConfigDescriptor(int iMaxBitrate, int iAvgBitrate);

	void writeFile(FILE* fd);

	uint64 getSize();

public:
	uint8	m_ctag;
	uint8	m_clength;
	uint8	m_cObjectProfile;
	uint8	m_cStreamType;
	uint32	m_iBufferSizeDB;
	uint32	m_iMaxBitrate;
	uint32	m_iAvgBitrate;
	DecoderSpecificInfo		m_stDecoderSpecificInfo;
};

class ESDescriptor :public MP4Box
{
public:
	ESDescriptor();
	virtual ~ESDescriptor();

	void createESDescriptor();

	void writeFile(FILE* fd);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint8	m_cTag;
	uint8	m_cLength;
	uint16	m_sESID;
	uint8	m_cFlag;
	DecoderConfigDescriptor		m_stDecoderConfigDescriptor;
	SLConfigDescriptor			m_stSLConfigDescriptor;
};

class  AudioSampleEntry :public MP4Box
{
public:
	AudioSampleEntry();
	virtual ~AudioSampleEntry();

	void createAudioSampleEntry(uint16	usChannelCount, uint16	usSampleSize, uint32	uiSampleRate);

	void writeFile(FILE* fd);

public:
	unsigned char m_ucReserved[6];
	uint16	m_usDataReferenceIndex;
	uint32	m_uiReserved[2];
	uint16	m_usChannelCount;
	uint16	m_usSampleSize;
	uint16	m_usPreDefined;
	uint16	m_usReserved;
	uint32	m_uiSampleRate;

	ESDescriptor	m_stESDescriptor;
};

class MP4Stsd : public MP4Box
{
public:
	MP4Stsd();
	virtual ~MP4Stsd();

	void createMP4Stsd(int iType);	//0 video , 1 audio
	void writeFile(FILE* fd);

public:
	unsigned char m_ucVersion;
	unsigned char m_ucFlag[3];
	uint32	m_uiEntryCount;
	int		m_iType;
	VisualSampleEntry		m_stVideoSamleEntry;
	AudioSampleEntry		m_stAudioSamleEntry;
};

