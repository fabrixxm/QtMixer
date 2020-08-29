#include "quickmixerstream.h"
#include "quickmixer.h"
#include <QDebug>

QuickMixerStream::QuickMixerStream(QObject *parent)
	: QObject(parent)
	, m_created(false)
	, m_loops(0)
	, m_volume(1)
	, m_paused(false)
	, m_source("")
	, m_position(0)
{
}

bool QuickMixerStream::isPaused() const
{
	return m_paused;
}

void QuickMixerStream::setPause(bool pause)
{
	m_paused = pause;
	if (m_created == false) return;
	if (pause) {
		m_handle.pause();
	} else {
		m_handle.play();
	}
}

QString QuickMixerStream::getSource() const
{
	return m_source;
}

void QuickMixerStream::setSource(QString source)
{
	QuickMixer *m_quickmixer = (QuickMixer *) parent();
	Q_ASSERT(m_quickmixer);
	QMixerDevice *m_mixer = m_quickmixer->getMixer();

	if (m_mixer != NULL) {
		if (m_created == false) {
			m_handle = m_mixer->openStream(source);
		} else {
			m_mixer->closeStream(m_handle);
			m_handle = m_mixer->openStream(source);
		}
		m_created = true;
		m_handle.setLoops(m_loops);
		m_handle.setVolume(m_volume);
		setPause(m_paused);

		m_source = source;
		sourceChanged();
	}
}

qreal QuickMixerStream::getVolume() const
{
	if (m_created == true)
		m_volume = m_handle.volume();
	return m_volume;
}

void QuickMixerStream::setVolume(qreal volume)
{
	if (volume > 1.0) volume=1.0;
	if (volume < 0) volume=0;
	m_volume = volume;
	if (m_created == true)
		m_handle.setVolume(m_volume);
	volumeChanged();
}

int QuickMixerStream::getLoop() const
{
	if (m_created == true)
		m_loops = m_handle.loops();
	return m_loops;
}

void QuickMixerStream::setLoop(int loop)
{
	m_loops = loop;
	if (m_created == true)
		m_handle.setLoops(m_loops);
	loopChanged();
}

int QuickMixerStream::getPosition() const
{
	if (m_created == true)
		m_position = m_handle.position();
	return m_position;
}

/*
void QuickMixerStream::setPosition(int position)
{
	m_position = position;
	if (m_created == true)
		m_handle.setPosition(m_position);
	positionChanged();
}
*/

int QuickMixerStream::getState() const
{
	if (m_created == false) return -1;
	return m_handle.state();
}

void QuickMixerStream::close()
{
	if (m_created) {
		QuickMixer *m_quickmixer = (QuickMixer *) parent();
		Q_ASSERT(m_quickmixer);
		QMixerDevice *m_mixerstream = m_quickmixer->getMixer();
		m_mixerstream->closeStream(m_handle);
		m_created = false;
	}
}

void QuickMixerStream::pause()
{
	setPause(true);
}

void QuickMixerStream::play()
{
	setPause(false);
}

void QuickMixerStream::stop()
{
	if (m_created == false) return;
	m_handle.stop();
}


void QuickMixerStream::onHandleStateChange(QMixerStreamHandle handle, QtMixer::State state)
{
	Q_UNUSED(handle);
	switch(state) {
	case QtMixer::Paused:
		pauseChanged();
		break;
	case QtMixer::Playing:
		pauseChanged();
		break;
	case QtMixer::Stopped:
		// do nothing
		break;
	}
	stateChanged();
}
