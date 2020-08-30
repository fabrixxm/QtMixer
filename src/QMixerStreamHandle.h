#ifndef QMIXERSTREAMHANDLE_H
#define QMIXERSTREAMHANDLE_H

#include "QtMixer.h"

class QAbstractMixerStream;
class QAudioDecoderStream;
class QMixerDevice;

/**
 * The QMixerStreamHandle class is the interface to control
 * mixer channels
 */
class QTMIXER_EXPORT QMixerStreamHandle
{
	friend class QMixerDevice;
	friend class QAudioDecoderStream;

	public:
		QMixerStreamHandle();

		void play();
		void pause();
		void stop();

		QtMixer::State state() const;

		int loops() const;
		void setLoops(int loops);

		int position() const;
		void setPosition(int position);

		int length() const;

		qreal volume() const;
		void setVolume(qreal volume);

		bool operator ==(const QMixerStreamHandle &other) const;

	private:
		QMixerStreamHandle(QAbstractMixerStream *stream);

		QAbstractMixerStream *m_stream;

};

#endif // QMIXERSTREAMHANDLE_H
