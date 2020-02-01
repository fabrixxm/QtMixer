CONFIG += c++11
QT += qml multimedia

!contains(QUICKMIXER_CONFIG,"noautoregister") {
    DEFINES += QUICKMIXER_AUTO_REGISTER
}

INCLUDEPATH += \
    $$PWD \
    $$PWD/src

SOURCES += \
    $$PWD/src/quickmixer.cpp \
    $$PWD/src/quickmixerstream.cpp \
    $$PWD/src/QAudioDecoderStream.cpp \
    $$PWD/src/QMixerStream.cpp \
    $$PWD/src/QMixerStreamHandle.cpp \
    $$PWD/src/QMixerStream_p.cpp

HEADERS += \
    $$PWD/qpm.h \
    $$PWD/src/quickmixer.h \
    $$PWD/src/quickmixerstream.h \
    $$PWD/register_quickmixer.h \
    $$PWD/src/QMixerStream.h \
    $$PWD/src/QMixerStreamHandle.h \
    $$PWD/src/QtMixer.h \
    $$PWD/src/QMixerStream \
    $$PWD/src/QMixerStreamHandle \
    $$PWD/src/QAudioDecoderStream.h \
    $$PWD/src/QMixerStream_p.h \
    $$PWD/src/QAbstractMixerStream.h

DISTFILES += \
    $$PWD/README.md \
    $$PWD/LICENSE

RESOURCES += \
    $$PWD/net_kirgroup_mixer.qrc

exists(.git) {
    unix {
        GIT_BRANCH_NAME = $$system(git rev-parse --abbrev-ref HEAD)
        message("Mixer branch $$GIT_BRANCH_NAME")
    }
}

