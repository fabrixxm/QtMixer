#ifndef QMIXERSTREAM_H
#define QMIXERSTREAM_H

#include <QIODevice>
#include <QAudioFormat>

#include "QtMixer.h"
#include "QMixerStreamHandle.h"

typedef std::numeric_limits<qint16> Range;

class QMixerDevicePrivate;

/**
 * @brief The QMixerDevice class is the mixer.
 *
 * It's a QIODevice that mix data from channels to be sent to audio output
 *
 * It can open/close streams, adding/removing mixer channels
 *
 */
class QTMIXER_EXPORT QMixerDevice : public QIODevice
{
	Q_OBJECT

	public:
		QMixerDevice(const QAudioFormat &format);

		QMixerStreamHandle openStream(const QString &fileName);

		void closeStream(const QMixerStreamHandle &handle);

	protected:
		qint64 readData(char *data, qint64 maxlen) override;
		qint64 writeData(const char *data, qint64 len) override;

	private:
		qint16 mix(qint32 sample1, qint32 sample2);

		QMixerDevicePrivate *d_ptr;

	signals:
		void stateChanged(QMixerStreamHandle handle, QtMixer::State state);
		void decodingFinished(QMixerStreamHandle handle);
};

#endif // QMIXERSTREAM_H
