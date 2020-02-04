#include "quickmixer.h"
#include <QDebug>

#if defined(QUICKMIXER_AUTO_REGISTER)
#include "register_quickmixer.h"
#endif

QuickMixer::QuickMixer(QObject *parent)
    : QObject(parent)
    , m_mixerstream(NULL)
{
    const QAudioDeviceInfo &device = QAudioDeviceInfo::defaultOutputDevice();
    const QAudioFormat &audioFormat = device.preferredFormat();


    m_mixerstream = new QMixerStream(audioFormat);
    m_output = new QAudioOutput(device, audioFormat);
    m_output->start(m_mixerstream);
    m_output->suspend();

    connect(m_output, &QAudioOutput::stateChanged, this, &QuickMixer::outputStateChanged);
    connect(m_mixerstream, &QMixerStream::stateChanged, this, &QuickMixer::onMixerStreamStateChanged);
}


QQmlListProperty<QuickMixerStream> QuickMixer::streams()
{
    return {this, m_streams};
}

int QuickMixer::streamsCount() const
{
    return m_streams.count();
}

QuickMixerStream *QuickMixer::stream(int index) const
{
    return m_streams.at(index);
}

bool QuickMixer::isPaused() const
{
    return m_output->state() == QAudio::SuspendedState;
}

void QuickMixer::setPause(bool pause)
{
    qDebug() << "setPause " << pause;
    if (pause) {
        m_output->suspend();
    } else {
        m_output->resume();
    }
}

qreal QuickMixer::getVolume() const
{
    return m_output->volume();
}

void QuickMixer::setVolume(qreal volume)
{
    m_output->setVolume(volume);
    volumeChanged();
}

int QuickMixer::getState() const
{
    return m_output->state();
}

QMixerStream *QuickMixer::getMixer()
{
    return m_mixerstream;
}

void QuickMixer::pause()
{
    setPause(true);
}

void QuickMixer::play()
{
    setPause(false);
}

void QuickMixer::outputStateChanged(QAudio::State state)
{
    switch(state) {
    case QAudio::StoppedState:
    case QAudio::IdleState:
    case QAudio::InterruptedState:
        break;
    case QAudio::ActiveState:
    case QAudio::SuspendedState:
        pauseChanged();
    break;
    }

    stateChanged();
}

void QuickMixer::onMixerStreamStateChanged(QMixerStreamHandle handle, QtMixer::State state)
{
    Q_UNUSED(handle);
    qDebug() << "onMixerStreamStateChanged() " << state;
}
