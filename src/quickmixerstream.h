#ifndef QUICKMIXERSTREAM_H
#define QUICKMIXERSTREAM_H

#include <QObject>
#include <QMixerStreamHandle>

class QuickMixer;

class QuickMixerStream : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool paused READ isPaused WRITE setPause NOTIFY pauseChanged)
    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(qreal volume READ getVolume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(int loop READ getLoop WRITE setLoop NOTIFY loopChanged)
    Q_PROPERTY(int position READ getPosition NOTIFY positionChanged)
    Q_PROPERTY(int state READ getState NOTIFY stateChanged)

public:
    explicit QuickMixerStream(QuickMixer *parent = nullptr);

    bool isPaused() const;
    void setPause(bool pause);
    QString getSource() const;
    void setSource(QString source);
    qreal getVolume() const;
    void setVolume(qreal volume);
    int getLoop() const;
    void setLoop(int loop);
    int getPosition() const;
    // void setPosition(int position);
    int getState() const;

public slots:
    void pause();
    void play();
    void stop();

private slots:
    void onHandleStateChange(QMixerStreamHandle handle, QtMixer::State state);


signals:
    void pauseChanged();
    void sourceChanged();
    void volumeChanged();
    void loopChanged();
    void positionChanged();
    void stateChanged();

private:
    QMixerStream *m_mixer;
    QMixerStreamHandle m_handle;
    bool m_created;
    int mutable m_loops;
    qreal mutable m_volume;
    bool m_paused;
    QString m_source;
    int mutable m_position;
};

#endif // QUICKMIXERSTREAM_H
