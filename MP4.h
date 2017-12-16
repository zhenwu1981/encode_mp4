#pragma once

#include <stdio.h>

#include "MP4Ftyp.h"
#include "MP4Moov.h"
#include "MP4Mdat.h"

class MP4
{
public:
	MP4();
	~MP4();

	bool open(const char* pcPath);
	void close();

	bool setVideoConfig(int iWidth, int iHeight,const char* pucSPS, int iSPSLength, const char* pucPPS, int iPPSLength);
	bool setAudioConifg(int iChannels, int iSample, int iBitRate, int iBitsPerSample);

	bool isVideoConfig();
	bool isAudioConfig();

	bool setVideoFrame(const char* pacBuffer, int iLength, uint64 uiPTS, uint64 uiDTS , int iVideoFlag);	//1 ±íÊ¾IÖ¡
	bool setAudioFrame(const char* pacBuffer, int iLength, uint64 uiPTS);

	bool setVideoFrameImpl(const char* pacBuffer, int iLength, uint64 uiPTS, uint64 uiDTS, int iVideoFlag);
	bool setAudioFrameImple(const char* pacBuffer, int iLength, uint64 uiPTS);

	int getAudioType(int sample);

private:
	MP4Ftyp		m_stFtyp;
	MP4Mdat		m_stMdat;
	MP4Moov		m_stMoov;
	FILE*		m_pstFD;

	int			m_iVideoIndex;
	int			m_iAudioIndex;
	
	//
	int			m_iWidth;
	int			m_iHeight;
	int			m_iChannels;
	int			m_iSample;
	int			m_iBitRate;
	int			m_iBitPerSample;

	//
	int			m_iFileSeek;
	uint64		m_ullTimescale;
	uint64		m_ulltotalLen;

	uint64		m_ullOffset;

	//video
	uint64	m_uiVideoStartTime;
	uint64	m_uiVideoEndTime;
	unsigned char*	m_pucVideoBuffer;
	int				m_iVideoLength;
	uint64			m_iVideoLastTime;
	int				m_iVideoDuration;
	int				m_iVideoFrameIndex;
	int				m_iVideoChunkIndex;
	int				m_iVideoSampleSize;
	int 			m_iVideoTimestamp;
	int 			m_iVideoCostTimestamp;

	//audio
	uint64	m_uiAudioStartTime;
	uint64	m_uiAudioEndTime;
	unsigned char*	m_pucAudioBuffer;
	int				m_iAudioLength;
	uint64			m_iAudioLastTime;
	int				m_iAudioDuration;
	int				m_iAudioFrameIndex;
	int				m_iAudioChunkIndex;
	int				m_iAudioSampleSize;
	int 			m_iAudioTimetamp;
};

