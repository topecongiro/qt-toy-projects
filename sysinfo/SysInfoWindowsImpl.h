#ifndef SYSINFOWINDOWSIMPL_H
#define SYSINFOWINDOWSIMPL_H

#include "SysInfo.h"

#include <tuple>
#include <QtGlobal>

typedef struct _FILETIME FILETIME;

class SysInfoWindowsImpl : public SysInfo
{
public:
    SysInfoWindowsImpl();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
    using CPUData = std::tuple<uint64_t, uint64_t, uint64_t>;

    CPUData cpuRawData();
    qulonglong convertFileTime(const FILETIME& filetime) const;

    CPUData mCpuLoadLastValues;
};

#endif // SYSINFOWINDOWSIMPL_H
