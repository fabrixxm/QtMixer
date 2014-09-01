#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QAudioDecoder>
#include <QBuffer>

#include "QMixerStream.h"
#include "QAudioDecoderStream.h"
#include "QMixerWrapperStream.h"
#include "QMixerStreamHandle.h"
#include "QAbstractMixerStream.h"

QMixerStream::QMixerStream(const QAudioFormat &format)
	: m_format(format)
{
	setOpenMode(QIODevice::ReadOnly);
}

QMixerStreamHandle QMixerStream::openEncodedStream(QIODevice *device)
{
	QAudioDecoderStream *stream = new QAudioDecoderStream(device, m_format);
	QMixerStreamHandle handle(stream);

	m_streams << stream;

	connect(stream, &QAbstractMixerStream::stateChanged, this, &QMixerStream::stateChanged);

	return handle;
}

QMixerStreamHandle QMixerStream::openRawStream(QIODevice *device)
{
	QMixerWrapperStream *stream = new QMixerWrapperStream(device);
	QMixerStreamHandle handle(stream);

	m_streams << stream;

	connect(stream, &QAbstractMixerStream::stateChanged, this, &QMixerStream::stateChanged);

	return handle;
}

void QMixerStream::closeStream(const QMixerStreamHandle &handle)
{
	QAbstractMixerStream *stream = handle.m_stream;

	if (stream)
	{
		stream->removeFrom(m_streams);
		stream->deleteLater();
	}
}

qint64 QMixerStream::readData(char *data, qint64 maxlen)
{
	memset(data, 0, maxlen);

	const qint16 depth = sizeof(qint16);
	const qint16 samples = maxlen / depth;

	const QList<QAbstractMixerStream *> streams = m_streams;

	for (QAbstractMixerStream *stream : streams)
	{
		qint16 *cursor = (qint16 *)data;
		qint16 sample;

		for (int i = 0; i < samples; i++, cursor++)
		{
			if (stream->read((char *)&sample, depth))
			{
				*cursor = mix(*cursor, sample);
			}
		}

		if (stream->atEnd())
		{
			stream->stop();
		}
	}

	return maxlen;
}

qint64 QMixerStream::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);

	return 0;
}

qint16 QMixerStream::mix(qint32 sample1, qint32 sample2)
{
	const qint32 result = sample1 + sample2;

	if (Range::max() < result)
	{
		return Range::max();
	}

	if (Range::min() > result)
	{
		return Range::min();
	}

	return result;
}
