#include <QDebug>
#include <QByteArray>
#include <QAudioDecoder>
#include <QBuffer>

#include "QMixerDevice.h"
#include "QAudioDecoderStream.h"
#include "QMixerStreamHandle.h"
#include "QAbstractMixerStream.h"
#include "QMixerDevice_p.h"

QMixerDevice::QMixerDevice(const QAudioFormat &format)
	: d_ptr(new QMixerDevicePrivate(format))
{
	setOpenMode(QIODevice::ReadOnly);
}

QMixerStreamHandle QMixerDevice::openStream(const QString &fileName)
{
	QAudioDecoderStream *stream = new QAudioDecoderStream(fileName, d_ptr->m_format);
	QMixerStreamHandle handle(stream);

	d_ptr->m_streams << stream;

	connect(stream, &QAbstractMixerStream::stateChanged, this, &QMixerDevice::stateChanged);
	connect(stream, &QAbstractMixerStream::decodingFinished, this, &QMixerDevice::decodingFinished);

	return handle;
}

void QMixerDevice::closeStream(const QMixerStreamHandle &handle)
{
	QAbstractMixerStream *stream = handle.m_stream;

	if (stream)
	{
		stream->removeFrom(d_ptr->m_streams);
		stream->deleteLater();
	}
}

qint64 QMixerDevice::readData(char *data, qint64 maxlen)
{
	memset(data, 0, maxlen);

	const qint16 depth = sizeof(qint16);
	const qint16 samples = maxlen / depth;

	const QList<QAbstractMixerStream *> streams = d_ptr->m_streams;

	for (QAbstractMixerStream *stream : streams)
	{
		qint16 *cursor = (qint16 *)data;
		qint16 sample;

		for (int i = 0; i < samples; i++, cursor++)
		{
			if (stream->read((char *)&sample, depth))
			{
				*cursor = mix(*cursor, sample * stream->volume());
			}
		}

		if (stream->atEnd())
		{
			stream->stop();
		}
	}

	return maxlen;
}

qint64 QMixerDevice::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);

	return 0;
}

qint16 QMixerDevice::mix(qint32 sample1, qint32 sample2)
{
	const qint32 result = (sample1 + sample2); // / 2;

	if (Range::max() < result)
	{
		return Range::max();
	}

	if (result < Range::min())
	{
		return Range::min();
	}

	return result;
}
