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
    $$PWD/src/QMixerStreamHandle.cpp \
    $$PWD/src/QMixerDevice.cpp \
    $$PWD/src/QMixerDevice_p.cpp

HEADERS += \
    $$PWD/qpm.h \
    $$PWD/src/quickmixer.h \
    $$PWD/src/quickmixerstream.h \
    $$PWD/register_quickmixer.h \
    $$PWD/src/QMixerStreamHandle.h \
    $$PWD/src/QtMixer.h \
    $$PWD/src/QAudioDecoderStream.h \
    $$PWD/src/QAbstractMixerStream.h \
    $$PWD/src/QMixerDevice.h \
    $$PWD/src/QMixerDevice_p.h

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

