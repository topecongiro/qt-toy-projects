#include "SysInfo.h"

#include <QtGlobal>

#ifdef Q_OS_WIN
#include "SysInfoWindowsImpl.h"
#endif

SysInfo& SysInfo::instance()
{
#ifdef Q_OS_WIN
    static SysInfoWindowsImpl instance;
#endif

    return instance;
}

SysInfo::SysInfo()
{
}

SysInfo::~SysInfo()
{
}
