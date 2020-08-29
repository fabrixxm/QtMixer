#ifndef QABSTRACTMIXERSTREAM_H
#define QABSTRACTMIXERSTREAM_H

#include <QIODevice>

#include "QtMixer.h"
#include "QMixerStreamHandle.h"

/**
 * The QAbstractMixerStream class is the abstract type that
 * defines sources of data for mixer channels
 */
class QAbstractMixerStream : public QIODevice
{
	Q_OBJECT

	friend class QMixerDevice;

	public:
		virtual void play() = 0;
		virtual void pause() = 0;
		virtual void stop() = 0;

		virtual QtMixer::State state() const = 0;

		virtual int loops() const = 0;
		virtual void setLoops(int loops) = 0;

		virtual int position() const= 0;
		virtual void setPosition(int position) = 0;

		virtual int length() = 0;

        virtual qreal volume() const = 0;
        virtual void setVolume(qreal volume) = 0;

	private:
		void removeFrom(QList<QAbstractMixerStream *> &streams)
		{
			streams.removeAll(this);
		}

	signals:
		void stateChanged(QMixerStreamHandle handle, QtMixer::State state);
		void decodingFinished(QMixerStreamHandle handle);
};

#endif // QABSTRACTMIXERSTREAM_H
