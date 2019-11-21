#include "SysInfo.h"

#include <QtGlobal>

#ifdef Q_OS_WIN
#include "SysInfoWindowsImpl.h"
#elif defined(Q_OS_LINUX)
#include "SysInfoLinuxImpl.h"
#endif

SysInfo& SysInfo::instance()
{
#ifdef Q_OS_WIN
    static SysInfoWindowsImpl instance;
#elif defined(Q_OS_LINUX)
    static SysInfoLinuxImpl instance;
#endif

    return instance;
}

SysInfo::SysInfo()
{
}

SysInfo::~SysInfo()
{
}
