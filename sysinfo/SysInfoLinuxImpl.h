#ifndef SYSINFOLINUXIMPL_H
#define SYSINFOLINUXIMPL_H

#include <tuple>
#include <QtGlobal>

#include "SysInfo.h"

class SysInfoLinuxImpl : public SysInfo
{
public:
    SysInfoLinuxImpl();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
    using CPUData = std::tuple<uint64_t, uint64_t, uint64_t, uint64_t>;

    CPUData cpuRawData();

    CPUData mCpuLoadLastValue;
};

#endif // SYSINFOLINUXIMPL_H
