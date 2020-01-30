#ifndef REGISTER_QUICKMIXER_H
#define REGISTER_QUICKMIXER_H

#include <QtCore/QCoreApplication>
#include <QtQml/QQmlEngine>

// #include "src/quickdownload.h"

static void registerQuickMixer() {
    //qmlRegisterType<QuickMixer>("net.kirgroup.Mixer", 1, 0, "Mixer");
    //qmlRegisterType<QuickMixerStream>("net.kirgroup.Mixer", 1, 0, "MixerStream");
}

Q_COREAPP_STARTUP_FUNCTION(registerQuickMixer)

#endif // REGISTER_QUICKMIXER_H
