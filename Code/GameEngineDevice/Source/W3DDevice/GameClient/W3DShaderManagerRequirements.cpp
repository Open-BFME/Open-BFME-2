// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /Ireference/shims/bfmecpudetect /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// ZH W3DShaderManager.cpp: testMinimumRequirements, donor ba7ddda7e8.
// Native 76629..766E1 RET0 preserves the three CPU thresholds and benchmark
// ordering. Target RAM output is 64-bit, established independently by the
// existing CPUDetectClass header and native paired stores. The chipset probe
// remains address-named: its full 2023-byte boundary starts at 75E42.
#include "cpudetect.h"

enum ChipsetType { DC_UNKNOWN = 0 };
enum CpuType { XX, P3, P4, K7 };
extern int g_Va001FDE58;
void rva00075E42();
extern "C" int RunBenchmark(int, char **, float *, float *, float *);

class W3DShaderManager {
public:
    static bool testMinimumRequirements(ChipsetType *, CpuType *, int *,
        unsigned __int64 *, float *, float *, float *);
};

bool W3DShaderManager::testMinimumRequirements(ChipsetType *videoChipType,
    CpuType *cpuType, int *cpuFreq, unsigned __int64 *numRAM,
    float *intBenchIndex, float *floatBenchIndex, float *memBenchIndex)
{
    if (videoChipType) {
        rva00075E42();
        *videoChipType = static_cast<ChipsetType>(g_Va001FDE58);
    }
    if (cpuType) {
        *cpuType = XX;
        if (CPUDetectClass::Get_Processor_Manufacturer() == CPUDetectClass::MANUFACTURER_AMD &&
            CPUDetectClass::Get_AMD_Processor() >= CPUDetectClass::AMD_PROCESSOR_ATHLON_025)
            *cpuType = K7;
        if (CPUDetectClass::Get_Processor_Manufacturer() == CPUDetectClass::MANUFACTURER_INTEL &&
            CPUDetectClass::Get_Intel_Processor() >= CPUDetectClass::INTEL_PROCESSOR_PENTIUM_III_MODEL_7)
            *cpuType = P3;
        if (CPUDetectClass::Get_Processor_Manufacturer() == CPUDetectClass::MANUFACTURER_INTEL &&
            CPUDetectClass::Get_Intel_Processor() >= CPUDetectClass::INTEL_PROCESSOR_PENTIUM4)
            *cpuType = P4;
    }
    if (cpuFreq)
        *cpuFreq = CPUDetectClass::Get_Processor_Speed();
    if (numRAM)
        *numRAM = CPUDetectClass::Get_Total_Physical_Memory();
    if (intBenchIndex && floatBenchIndex && memBenchIndex)
        RunBenchmark(0, 0, floatBenchIndex, intBenchIndex, memBenchIndex);
    return true;
}

bool Rva000768F5(ChipsetType *videoChipType, CpuType *cpuType, int *cpuFreq,
    unsigned __int64 *numRAM, float *intBenchIndex, float *floatBenchIndex,
    float *memBenchIndex)
{
    return W3DShaderManager::testMinimumRequirements(videoChipType, cpuType, cpuFreq,
        numRAM, intBenchIndex, floatBenchIndex, memBenchIndex);
}
