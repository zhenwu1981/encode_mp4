
#include "MP4Stsd.h"

VisualSampleEntry::VisualSampleEntry()
{

}

VisualSampleEntry::~VisualSampleEntry()
{

}

void VisualSampleEntry::createVisualSampleEntry(uint16 usWidth, uint16 usHeight, std::string strCompressorname)
{
	memset(m_ucReserved, 0, 6);
	m_usDataReferenceIndex = 1;
	m_usPreDefined = 0;
	m_usReserved = 0;
	memset(m_uiPreDefined, 0, 3 * sizeof(uint32));
	m_usWidth = usWidth;
	m_usHeight = usHeight;
	m_uiHorizresolution = 0x00480000;
	m_uiVertresolution = 0x00480000;
	m_uiReserved = 0;
	m_usFrameCount = 1;
	memset(m_strCompressorname, 0, 32);
	//memcpy(m_strCompressorname, strCompressorname.c_str(), 32);
	m_usDepth = 0x0018;
	m_usPreDefined1 = -1;

	uint64 ullLen = 78 + m_stAVCCBox.getSize();

	setSize(ullLen);
	setType("avc1");

	printf("avc1 : %d \n", getSize());
}

void VisualSampleEntry::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32	uiTemp = 0;
	uint16	usTemp = 0;

	fwrite(m_ucReserved,6,1,fd);
	usTemp = ntohs(m_usDataReferenceIndex);
	fwrite(&usTemp, 2, 1, fd);
	usTemp = ntohs(m_usPreDefined);
	fwrite(&usTemp, 2, 1, fd);
	usTemp = ntohs(m_usReserved);
	fwrite(&usTemp, 2, 1, fd);
	for (int i = 0; i < 3;i++)
	{
		uiTemp = ntohl(m_uiPreDefined[i]);
		fwrite(&uiTemp, 4, 1, fd);
	}
	usTemp = ntohs(m_usWidth);
	fwrite(&usTemp, 2, 1, fd);
	usTemp = ntohs(m_usHeight);
	fwrite(&usTemp, 2, 1, fd);
	uiTemp = ntohl(m_uiHorizresolution);
	fwrite(&uiTemp, 4, 1, fd);
	uiTemp = ntohl(m_uiVertresolution);
	fwrite(&uiTemp, 4, 1, fd);
	uiTemp = ntohl(m_uiReserved);
	fwrite(&uiTemp, 4, 1, fd);
	usTemp = ntohs(m_usFrameCount);
	fwrite(&usTemp, 2, 1, fd);
	fwrite(m_strCompressorname, 32, 1, fd);
	usTemp = ntohs(m_usDepth);
	fwrite(&usTemp, 2, 1, fd);
	usTemp = ntohs(m_usPreDefined1);
	fwrite(&usTemp, 2, 1, fd);

	m_stAVCCBox.writeFile(fd);

	printf("writeFile avc1 : %d \n", getSize());
}

AudioSampleEntry::AudioSampleEntry()
{

}

AudioSampleEntry::~AudioSampleEntry()
{

}

void AudioSampleEntry::createAudioSampleEntry(uint16 usChannelCount, uint16 usSampleSize, uint32 uiSampleRate)
{
	memset(m_ucReserved, 0, 6);
	m_usDataReferenceIndex = 1;
	m_uiReserved[0] = 0;
	m_uiReserved[1] = 0;
	m_usChannelCount = usChannelCount;
	m_usSampleSize = usSampleSize;
	m_usPreDefined = 0;
	m_usReserved = 0;
	m_uiSampleRate = uiSampleRate << 16;

	uint64 ullLen = 28 + m_stESDescriptor.getSize();

	setSize(ullLen);
	setType("mp4a");
}

void AudioSampleEntry::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32	uiTemp = 0;
	uint16	usTemp = 0;

	fwrite(m_ucReserved, 6, 1, fd);
	usTemp = ntohs(m_usDataReferenceIndex);
	fwrite(&usTemp, 2, 1, fd);

	for (int i = 0; i < 2; i++)
	{
		uiTemp = ntohl(m_uiReserved[i]);
		fwrite(&uiTemp, 4, 1, fd);
	}

	usTemp = ntohs(m_usChannelCount);
	fwrite(&usTemp, 2, 1, fd);
	usTemp = ntohs(m_usSampleSize);
	fwrite(&usTemp, 2, 1, fd);
	usTemp = ntohs(m_usPreDefined);
	fwrite(&usTemp, 2, 1, fd);
	usTemp = ntohs(m_usReserved);
	fwrite(&usTemp, 2, 1, fd);

	uiTemp = ntohl(m_uiSampleRate);
	fwrite(&uiTemp, 4, 1, fd);

	m_stESDescriptor.writeFile(fd);
	printf("writeFile avc1 : %d \n", getSize());
}

MP4Stsd::MP4Stsd()
{
}

MP4Stsd::~MP4Stsd()
{
}

void MP4Stsd::createMP4Stsd(int iType)
{
	m_ucVersion = 0;
	memset(m_ucFlag, 0, 3);
	m_uiEntryCount = 1;
	m_iType = iType;

	uint64 ullLen = 8;

	if (0 == iType)
	{
		ullLen += m_stVideoSamleEntry.getSize();
	} 
	else
	{
		ullLen += m_stAudioSamleEntry.getSize();
	}

	setSize(ullLen);
	setType("stsd");

	printf("stsd : %d \n", getSize());
}

void MP4Stsd::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint32 iTemp = 0;

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	iTemp = htonl(m_uiEntryCount);
	fwrite(&iTemp, 4, 1, fd);

	if (0 == m_iType)
	{
		m_stVideoSamleEntry.writeFile(fd);
	} 
	else
	{
		m_stAudioSamleEntry.writeFile(fd);
	}

	printf("writeFile stsd : %d \n", getSize());
}


AVCConfigurationBox::AVCConfigurationBox()
{

}

AVCConfigurationBox::~AVCConfigurationBox()
{

}

void AVCConfigurationBox::createAVCConfigurationBox(uint8 ucAVCProfileIndication, uint8 ucProfileCompatibility, uint8 ucAVCLevelIndication, uint8 ucLengthSizeMinusOne, std::string strSPS, std::string strPPS)
{
	m_ucConfigurationVersion = 1;
	m_ucAVCProfileIndication = ucAVCProfileIndication;
	m_ucProfileCompatibility = ucProfileCompatibility;
	m_ucAVCLevelIndication = ucAVCLevelIndication;
	m_ucLengthSizeMinusOne = ucLengthSizeMinusOne | 0xFC;
	m_ucNumOfSequenceParameterSets = 0xE1;
	m_usSequenceParameterSetLength = strSPS.length();
	m_strSPS = strSPS;
	m_ucNumOfPictureParameterSets = 1;
	m_usPictureParameterSetLength = strPPS.length();
	m_strPPS = strPPS;

	uint64 ullLen = 11 + m_usSequenceParameterSetLength + m_usPictureParameterSetLength;

	setSize(ullLen);
	setType("avcC");

	printf("avcC : %d \n", getSize());
}

void AVCConfigurationBox::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);
	uint16	usTemp = 0;

	fwrite(&m_ucConfigurationVersion, 1, 1, fd);
	fwrite(&m_ucAVCProfileIndication, 1, 1, fd);
	fwrite(&m_ucProfileCompatibility, 1, 1, fd);
	fwrite(&m_ucAVCLevelIndication, 1, 1, fd);
	fwrite(&m_ucLengthSizeMinusOne, 1, 1, fd);

	fwrite(&m_ucNumOfSequenceParameterSets, 1, 1, fd);
	for (int i = 0; i < (m_ucNumOfSequenceParameterSets & 0x1F); i++)
	{
		usTemp = ntohs(m_usSequenceParameterSetLength);
		fwrite(&usTemp, 2, 1, fd);
		fwrite(m_strSPS.c_str(), m_strSPS.length(), 1, fd);
	}

	fwrite(&m_ucNumOfPictureParameterSets, 1, 1, fd);
	for (int i = 0; i < m_ucNumOfPictureParameterSets; i++)
	{
		usTemp = ntohs(m_usPictureParameterSetLength);
		fwrite(&usTemp, 2, 1, fd);
		fwrite(m_strPPS.c_str(), m_strPPS.length(), 1, fd);
	}

	printf("writeFile avcC : %d \n", getSize());
}

SLConfigDescriptor::SLConfigDescriptor()
{
	m_cTag = 6;
	m_cLength = 1;
	m_cPredefined = 2;
}

SLConfigDescriptor::~SLConfigDescriptor()
{

}

void SLConfigDescriptor::writeFile(FILE* fd)
{
	fwrite(&m_cTag, 1, 1, fd);
	fwrite(&m_cLength, 1, 1, fd);
	fwrite(&m_cPredefined, 1, 1, fd);
}

uint64 SLConfigDescriptor::getSize()
{
	return 3;
}

DecoderSpecificInfo::DecoderSpecificInfo()
{

}

DecoderSpecificInfo::~DecoderSpecificInfo()
{

}

void DecoderSpecificInfo::createDecoderSpecificInfo(unsigned char* ucData , int len)
{
	m_ctag = 5;
	m_clength = len;
	for (int i = 0; i < len; i ++)
	{
		m_iSpecificInfo[i] = ucData[i];
	}
}

void DecoderSpecificInfo::writeFile(FILE* fd)
{
	fwrite(&m_ctag, 1, 1, fd);
	fwrite(&m_clength, 1, 1, fd);
	for (int i = 0; i < m_clength; i++)
	{
		fwrite(&m_iSpecificInfo[i], 1, 1, fd);
	}
	
}

uint64 DecoderSpecificInfo::getSize()
{
	return m_clength + 2;
}

DecoderConfigDescriptor::DecoderConfigDescriptor()
{

}

DecoderConfigDescriptor::~DecoderConfigDescriptor()
{

}

void DecoderConfigDescriptor::createDecoderConfigDescriptor(int iMaxBitrate, int iAvgBitrate)
{
	m_ctag = 04;
	m_clength = m_stDecoderSpecificInfo.getSize() + 13;
	m_cObjectProfile = 0x40;
	m_cStreamType = 0x15;
	m_iBufferSizeDB = 0;
	m_iMaxBitrate = iMaxBitrate;
	m_iAvgBitrate = iAvgBitrate;
}

void DecoderConfigDescriptor::writeFile(FILE* fd)
{
	uint32 iTemp = 0;

	fwrite(&m_ctag, 1, 1, fd);
	fwrite(&m_clength, 1, 1, fd);
	fwrite(&m_cObjectProfile, 1, 1, fd);
	fwrite(&m_cStreamType, 1, 1, fd);
	fwrite(&m_iBufferSizeDB, 3, 1, fd);
	iTemp = htonl(m_iMaxBitrate);
	fwrite(&iTemp, 4, 1, fd);
	iTemp = htonl(m_iAvgBitrate);
	fwrite(&iTemp, 4, 1, fd);
	m_stDecoderSpecificInfo.writeFile(fd);
}

uint64 DecoderConfigDescriptor::getSize()
{
	return m_clength + 2;
}

ESDescriptor::ESDescriptor()
{

}

ESDescriptor::~ESDescriptor()
{

}

void ESDescriptor::writeFile(FILE* fd)
{
	MP4Box::writeFile(fd);

	fwrite(&m_ucVersion, 1, 1, fd);
	fwrite(m_ucFlag, 3, 1, fd);
	fwrite(&m_cTag, 1, 1, fd);
	fwrite(&m_cLength, 1, 1, fd);
	fwrite(&m_sESID, 2, 1, fd);
	fwrite(&m_cFlag, 1, 1, fd);
	m_stDecoderConfigDescriptor.writeFile(fd);
	m_stSLConfigDescriptor.writeFile(fd);
}

void ESDescriptor::createESDescriptor()
{
	m_ucVersion = 0;
	memset(m_ucFlag, 0, 3);
	m_cTag = 03;
	m_cLength = m_stDecoderConfigDescriptor.getSize() + m_stSLConfigDescriptor.getSize() + 3;
	m_sESID = 0;
	m_cFlag = 0;

	uint64 ullLen = m_cLength + 6;

	setSize(ullLen);
	setType("esds");
}
