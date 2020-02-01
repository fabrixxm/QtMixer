#include "quickmixer.h"

#if defined(QUICKMIXER_AUTO_REGISTER)
#include "register_quickmixer.h"
#endif

QuickMixer::QuickMixer(QObject *parent) : QObject(parent)
{
    const QAudioDeviceInfo &device = QAudioDeviceInfo::defaultOutputDevice();
    const QAudioFormat &audioFormat = device.preferredFormat();


    m_stream = new QMixerStream(audioFormat);
    m_output = new QAudioOutput(device, audioFormat);
    m_output->start(m_stream);
    m_output->suspend();
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
    return m_stream;
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
        case QAudio::ActiveState:
        case QAudio::SuspendedState:
            pauseChanged();
        break;
    }

    stateChanged();
}
