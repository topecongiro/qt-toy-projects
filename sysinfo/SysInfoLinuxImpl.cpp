#include "SysInfoLinuxImpl.h"

#include <sys/types.h>
#include <sys/sysinfo.h>
#include <QFile>

SysInfoLinuxImpl::SysInfoLinuxImpl() :
    SysInfo(),
    mCpuLoadLastValue()
{
}

void SysInfoLinuxImpl::init()
{
    mCpuLoadLastValue = cpuRawData();
}

double SysInfoLinuxImpl::cpuLoadAverage()
{
    CPUData firstSample = mCpuLoadLastValue;
    CPUData secondSample = cpuRawData();
    mCpuLoadLastValue = secondSample;

    double overall = (std::get<0>(secondSample) - std::get<0>(firstSample))
            + (std::get<1>(secondSample) - std::get<1>(firstSample))
            + (std::get<2>(secondSample) - std::get<2>(firstSample));

    double total = overall + (std::get<3>(secondSample) - std::get<3>(firstSample));
    double percent = (overall / total) * 100.0;

    return qBound(0.0, percent, 100.0);
}

SysInfoLinuxImpl::CPUData SysInfoLinuxImpl::cpuRawData()
{
    QFile file("/proc/stat");
    file.open(QIODevice::ReadOnly);

    QByteArray line = file.readLine();
    file.close();

    uint64_t totalUser = 0;
    uint64_t totalUserNice = 0;
    uint64_t totalSystem = 0;
    uint64_t totalIdle = 0;

    std::sscanf(line.data(), "cpu %lu %lu %lu %lu",
                &totalUser, &totalUserNice, &totalSystem, &totalIdle);

    return {
        totalUser,
        totalUserNice,
        totalSystem,
        totalIdle
    };
}

double SysInfoLinuxImpl::memoryUsed()
{
    struct sysinfo memInfo;
    sysinfo(&memInfo);

    uint64_t totalMemory = memInfo.totalram;
    totalMemory += memInfo.totalswap;
    totalMemory *= memInfo.mem_unit;

    uint64_t totalMemoryUsed = memInfo.totalram - memInfo.freeram;
    totalMemoryUsed += memInfo.totalswap - memInfo.freeswap;
    totalMemoryUsed *= memInfo.mem_unit;

    double percent = static_cast<double>(totalMemoryUsed) / static_cast<double>(totalMemory) * 100.0;
    return qBound(0.0, percent, 100.0);
}
