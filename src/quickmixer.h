#ifndef QUICKMIXER_H
#define QUICKMIXER_H
#include <qqml.h>

#include <QObject>
#include <QAudioOutput>
#include <QMixerStream>
#include <QMixerStreamHandle>

#include "quickmixerstream.h"

/**
  \todo FIX DOCS!

  QML Interface to QAudioOutput and QtMixerStream.

  To be used with QuickMixerStream

  Mixer {
    volume: 1.0

    paused: true
    // .pause() / .play()

    // state

    MixerStream {
        src: "file.mp3"
        volume: 1.0
        loop: -1
        paused: true

        // .play() / .pause()

    }
  }

*/
class QuickMixer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool paused READ isPaused WRITE setPause NOTIFY pauseChanged)
    Q_PROPERTY(qreal volume READ getVolume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(int state READ getState NOTIFY stateChanged)
    Q_PROPERTY(QQmlListProperty<QuickMixerStream> streams READ streams)

    Q_CLASSINFO("DefaultProperty", "streams")

public:
    explicit QuickMixer(QObject *parent = nullptr);

    QQmlListProperty<QuickMixerStream> streams();
    int streamsCount() const;
    QuickMixerStream *stream(int) const;

    bool isPaused() const;
    void setPause(bool pause);
    qreal getVolume() const;
    void setVolume(qreal volume);
    int getState() const;

    QMixerStream *getMixer();

public slots:
    void pause();
    void play();

private slots:
    void outputStateChanged(QAudio::State state);

signals:
    void pauseChanged();
    void volumeChanged();
    void stateChanged();

private:
    QMixerStream *m_stream;
    QAudioOutput *m_output;
    QList<QuickMixerStream *> m_streams;
};

#endif // QUICKMIXER_H
