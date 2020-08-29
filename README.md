QtMixer
=======

Summary
-----------

A lightweight software audio mixing library depending only on Qt.
For use with QAudioOutput, using QAudioDecoder for decoding of input files.
With QML types!

Installation
-----------

Linux:

```
qmake
make
sudo make install
```

Windows (MSVC):

QtMixer can be compiled with MinGW too, but you won't get any sound.  
This is because QAudioDecoder relies on WMF on Windows (http://qt-project.org/wiki/Qt_Multimedia_Backends), which requires compiling with MSVC.

```
qmake
nmake
nmake install
```

Simple usage
-----------

```
# your.pro
include(./QtMixer/net_kirgroup_mixer.pri)
```

```C++
#include <QMixerStream>
#include <QMixerStreamHandle>
```

```C++
const QAudioDeviceInfo &device = QAudioDeviceInfo::defaultOutputDevice();
const QAudioFormat &audioFormat = device.preferredFormat();

QMixerDevice mixer(audioFormat);
QAudioOutput output(device, audioFormat);
output.setVolume(0.5);
output.start(&mixer);

QMixerStreamHandle handle1 = mixer.openStream("music.ogg");
handle1.play();

QMixerStreamHandle handle2 = mixer.openStream("sfx.wav");
handle2.setLoops(5);
handle2.play();
```

QML Types
---------

import net.kirgroup.mixer 1.0

Mixer {
    id: mixer

    MixerStream {
	    id: ch1
		source: "music.ogg"
		volume = 0.5
		loop = -1
	}
	MixerStream {
	    id: ch2
		source: "sfx.wav"
		volume = 1
		loop = 0
	}
}


Notes
-----

QMixerDevice
        |
   QMixerDevice::openStream(filename)
        v
QMixerStreamHandle
        |
		v
QMixerDecoderStream (QAbstractMixerStream)


QMixerDevice::openStream(filename) creates a QAudioDecoderStream and  returns it's QMixerStreamHandle.
When read, loops over all streams, read a chunk of data and return a mix.
When a stream is at end, QMixerDevice stops it.

QAudioDecoderStream when read, reads a chunk of data from a  buffer of decoded audio data.
When there is no more data in buffer to read, check "loops" value and rewind if needed.

QuickMixer (QML 'net.kirgroup.mixer.Mixer') initalize a QMixerDevice and keep a list of
QuickMixerStream as children

QuickMixerStream (QML 'net.kirgroup.mixer.MixerStream') opens a mixer stream when
it's 'source' property is set, and keeps and wraps the resulting QMixerStreamHandle

