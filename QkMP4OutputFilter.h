#ifndef QKMP4OUTPUTFILTER_H
#define QKMP4OUTPUTFILTER_H

#include <QtCore/qglobalstatic.h>

#include "framework/QkFilter.h"
#include "utils/QkFrameHolderQueue.h"
#include "utils/QkFrameConfig.h"

#include "QkMP4RecorderSink.h"


class MP4;
class QkMP4OutputFilter : public QkFilter
{
	Q_OBJECT

public:
	QkMP4OutputFilter(quint32 uiIndex, QkVideoEncoderConfig& stVideoConfig, QkAudioEncoderConfig& stAudioConfig, QString strFilePath);
	virtual ~QkMP4OutputFilter();

	// 启动filter
	virtual int start();

	// 关闭filter
	virtual void stop();

	// 向filter中添加一个数据
	virtual int inputData(QkFrameHolder& stFrame);

	quint32 getIndex();

private:
	void getSPSAndPPS(unsigned char* pcData, int iLen);

private:
	quint32	m_uiIndex;
	//QkMP4RecorderSink	m_stMP4Sink;
	QString				m_strFilePath;

	QkVideoEncoderConfig m_stVideoConfig;
	QkAudioEncoderConfig m_stAudioConfig;

	MP4*	m_pstMP4;
	bool	m_bVideoFrame;
	bool	m_bAudioFrame;

	quint32 m_uLastTime;
};

#endif // QKMP4OUTPUTFILTER_H
