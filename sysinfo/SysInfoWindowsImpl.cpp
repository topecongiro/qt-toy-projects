#include "SysInfoWindowsImpl.h"

#include "Windows.h"

SysInfoWindowsImpl::SysInfoWindowsImpl() :
    SysInfo(),
    mCpuLoadLastValues()
{

}

void SysInfoWindowsImpl::init()
{
    mCpuLoadLastValues = cpuRawData();
}

double SysInfoWindowsImpl::cpuLoadAverage()
{
    CPUData firstSample = mCpuLoadLastValues;
    CPUData secondSample = cpuRawData();
    mCpuLoadLastValues = secondSample;

    std::uint64_t currentIdle = std::get<0>(secondSample) - std::get<0>(firstSample);
    std::uint64_t currentKernel = std::get<1>(secondSample) - std::get<1>(firstSample);
    std::uint64_t currentUser = std::get<2>(secondSample) - std::get<2>(firstSample);
    std::uint64_t currentSystem = currentKernel + currentUser;

    double percent = (currentSystem - currentIdle) * 100.0 / currentSystem;
    return qBound(0.0, percent, 100.0);
}

double SysInfoWindowsImpl::memoryUsed()
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memoryStatus);
    auto memoryPhysicalUsed = memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys;
    return static_cast<double>(memoryPhysicalUsed) / static_cast<double>(memoryStatus.ullTotalPhys) * 100.0;
}

SysInfoWindowsImpl::CPUData SysInfoWindowsImpl::cpuRawData()
{
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    return {convertFileTime(idleTime), convertFileTime(kernelTime), convertFileTime(userTime)};
}

qulonglong SysInfoWindowsImpl::convertFileTime(const FILETIME &filetime) const
{
    ULARGE_INTEGER largeInteger;
    largeInteger.LowPart = filetime.dwLowDateTime;
    largeInteger.HighPart = filetime.dwHighDateTime;
    return largeInteger.QuadPart;
}
