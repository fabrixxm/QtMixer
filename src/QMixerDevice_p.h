#ifndef QMIXERSTREAM_P_H
#define QMIXERSTREAM_P_H

#include <QList>
#include <QAudioFormat>

class QMixerDevice;
class QAbstractMixerStream;

class QMixerDevicePrivate
{
	friend class QMixerDevice;

	public:
		QMixerDevicePrivate(const QAudioFormat &format);

	private:
		QList<QAbstractMixerStream *> m_streams;
		QAudioFormat m_format;
};

#endif // QMIXERSTREAM_P_H
