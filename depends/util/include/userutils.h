#pragma once

#include <QString>

#include "libutil_config.h"

namespace Util
{
// Get the Directory representing the User's Desktop
LIBUTIL_EXPORT QString getDesktopDir();

// Create a shortcut at *location*, pointing to *dest* called with the arguments *args*
// call it *name* and assign it the icon *icon*
// return true if operation succeeded
LIBUTIL_EXPORT bool createShortCut(QString location, QString dest, QStringList args,
								   QString name, QString iconLocation);
}
