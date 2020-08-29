#ifndef QAUDIODECODERSTREAM_H
#define QAUDIODECODERSTREAM_H

#include <QBuffer>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <QFile>

#include "QAbstractMixerStream.h"

/**
 * @brief The QAudioDecoderStream class read and decode audio data from file.
 *
 * It's the source of data for a mixer channel
 * It knows about loops and volume.
 *
 * loops can be set to 0 (no loops), -1 (infinite loops) , n > 0 (fixed number of loops)
 *
 * volume is used by mixer when mixing audio data (see QMixerStream::mix() )
 *
 */

class QAudioDecoderStream : public QAbstractMixerStream
{
	public:
		QAudioDecoderStream(const QString &fileName, const QAudioFormat &format);

		bool atEnd() const override;

		void play() override;
		void pause() override;
		void stop() override;

		QtMixer::State state() const override;

		int loops() const override;
		void setLoops(int loops) override;

		int position() const override;
		void setPosition(int position) override;

		int length() override;

		qreal volume() const override;
		void setVolume(qreal volume) override;

	protected:
		qint64 readData(char *data, qint64 maxlen) override;
		qint64 writeData(const char *data, qint64 len) override;

	private:
		void rewind();
		void bufferReady();
		void finished();

		QFile m_file;
		QBuffer m_input;
		QBuffer m_output;
		QByteArray m_data;
		QAudioDecoder m_decoder;
		QAudioFormat m_format;

		QtMixer::State m_state;

		int m_loops;
		int m_remainingLoops;
        qreal m_volume;
};

#endif // QAUDIODECODERSTREAM_H
