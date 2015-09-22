#include "utils/QkGlobal.h"
#include "framework/EventManager.h"

#include "mp4/MP4.h"

#include "QkMP4OutputFilter.h"



QkMP4OutputFilter::QkMP4OutputFilter(quint32 uiIndex, QkVideoEncoderConfig& stVideoConfig, QkAudioEncoderConfig& stAudioConfig, QString strFilePath)
:QkFilter(MP4_SINK_1)
, m_uiIndex(uiIndex)
, m_strFilePath(strFilePath)
, m_stVideoConfig(stVideoConfig)
, m_stAudioConfig(stAudioConfig)
{
	m_bVideoFrame = false;
	m_bAudioFrame = false;

	m_uLastTime = 0;
}

QkMP4OutputFilter::~QkMP4OutputFilter()
{

}

int QkMP4OutputFilter::start()
{
	//m_stMP4Sink.Open(m_stVideoConfig, m_stAudioConfig, m_strFilePath);

	m_pstMP4 = new MP4;
	m_pstMP4->open(m_strFilePath.toLocal8Bit().data(), m_stVideoConfig.iWidth, m_stVideoConfig.iHeight, m_stAudioConfig.iChannels, m_stAudioConfig.iSampleRate, m_stAudioConfig.iBitRate, 16);
	m_bVideoFrame = false;
	m_bAudioFrame = false;

	m_uLastTime = 0;

	OutputEvents::MP4EncodeInfo stEvent;
	stEvent.m_iWidth = m_stVideoConfig.iWidth;
	stEvent.m_iHeight = m_stVideoConfig.iHeight;
	stEvent.m_strPath = m_strFilePath;
	EventManager::instance().fireInputMP4EncodeInfo(stEvent);

	return QkFilter::start();
}

void QkMP4OutputFilter::stop()
{
	//m_stMP4Sink.Finalize();
	//m_stMP4Sink.Close();

	m_pstMP4->close();
	delete m_pstMP4;
	m_pstMP4 = NULL;

	QkFilter::stop();
}

int QkMP4OutputFilter::inputData(QkFrameHolder& stFrame)
{
	if (kRawVideoFrame == stFrame->m_eFrameType)
	{
		if (!m_bVideoFrame)
		{
			if (stFrame->m_bKeyFrame)
			{
				m_bVideoFrame = true;
				m_bAudioFrame = true;
				getSPSAndPPS(stFrame->m_ucData, stFrame->m_iLength);
				m_pstMP4->setAudioConifg();
			}
			else
			{
				return QK_OK;
			}
		}

		if (0 == m_uLastTime)
		{
			m_pstMP4->setVideoFrame((const char *)stFrame->m_ucData, stFrame->m_iLength, 0, 0, stFrame->m_bKeyFrame);
		}
		else
		{
			m_pstMP4->setVideoFrame((const char *)stFrame->m_ucData, stFrame->m_iLength, stFrame->m_uiTimesTamp - m_uLastTime, stFrame->m_uiTimesTamp - m_uLastTime, stFrame->m_bKeyFrame);
		}

		//m_pstMP4->setVideoFrame((const char *)stFrame->m_ucData, stFrame->m_iLength, stFrame->m_uiTimesTamp, stFrame->m_uiTimesTamp, stFrame->m_bKeyFrame);

		//m_stMP4Sink.WriteVideoFrame(stFrame->m_ucData, stFrame->m_iLength, stFrame->m_bKeyFrame, stFrame->m_uiTimesTamp);
	} 
	else
	{
		if (!m_bAudioFrame)
		{
			//m_bAudioFrame = true;
			//m_pstMP4->setAudioConifg();
			return QK_OK;
		}

		if (0 == m_uLastTime)
		{
			m_uLastTime = stFrame->m_uiTimesTamp;
		}

		m_pstMP4->setAudioFrame((const char *)stFrame->m_ucData, stFrame->m_iLength, stFrame->m_uiTimesTamp - m_uLastTime);

		//m_stMP4Sink.WriteAudioFrame(stFrame->m_ucData, stFrame->m_iLength, stFrame->m_uiTimesTamp);
	}

	return QK_OK;
}

quint32 QkMP4OutputFilter::getIndex()
{
	return m_uiIndex;
}

void QkMP4OutputFilter::getSPSAndPPS(unsigned char* pcH264Buf, int iH264Len)
{
	std::string strSps = "";
	std::string strPps = "";

	int iStart = 4;
	int iEnd = 0;
	int iType = (int)(pcH264Buf[4] & 0x1f);

	// sps,pps,其他特殊段,i帧
	for (int i = iStart; i < iH264Len; i++)
	{
		if (pcH264Buf[i + 0] == 0 && pcH264Buf[i + 1] == 0 && pcH264Buf[i + 2] == 1)
		{
			//还需要往前判断

			if (pcH264Buf[i - 1] == 0)
			{
				iEnd = i - 2;
			}
			else
			{
				iEnd = i - 1;
			}

			if (iType == 7) //SPS
			{
				int iCount = iEnd - iStart + 1;
				strSps.assign((const char *)&pcH264Buf[iStart], iCount);
			}
			else if (iType == 8) //PPS
			{
				int iCount = iEnd - iStart + 1;
				strPps.assign((const char *)&pcH264Buf[iStart], iCount);

				iStart = i + 3;
				iType = (int)(pcH264Buf[i + 3] & 0x1f);

				break;
			}

			// 跳转到下一个数据块
			iStart = i + 3;
			iType = (int)(pcH264Buf[i + 3] & 0x1f);
		}
	}

	// 发送sps和pps
	if (!strSps.empty() && !strPps.empty())
	{
		m_pstMP4->setVideoConfig(strSps.c_str(), strSps.length(), strPps.c_str(), strPps.length());
	}
}
