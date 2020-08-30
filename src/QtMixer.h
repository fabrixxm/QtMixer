#ifndef QTMIXERGLOBAL_H
#define QTMIXERGLOBAL_H

#include <QtCore/QtGlobal>

#if defined QTMIXER_LIBRARY
#define QTMIXER_EXPORT Q_DECL_EXPORT
#else
#define QTMIXER_EXPORT Q_DECL_IMPORT
#endif

namespace QtMixer
{
	enum State
	{
		Playing,	// 0
		Paused,		// 1
		Stopped		// 2
	};
}

#endif // QTMIXERGLOBAL_H
