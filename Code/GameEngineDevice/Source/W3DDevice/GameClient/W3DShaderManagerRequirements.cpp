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

struct IDirect3DTexture8;
struct IDirect3DSurface8;
class Vector2;
struct GlowSampleVector;
struct BfmeGaussianParams;
class W3DShaderManager
{
private:
	friend class Rva00075655;
	friend void Rva00075695Notify(int index);
	friend bool __cdecl Rva000756BFSelect(int index, int a1, int a2);
	friend bool __cdecl Rva000756F1Dispatch(int index, int a1, int a2, int a3, int a4);
public:
	enum ShaderTypes { ST_INVALID };
protected:
	static int m_currentShader;
	static int m_currentFilter;
	static bool m_renderingToTexture;
	static unsigned long m_dwGlowPixelShader;
	static unsigned long m_dwGlowVertexShader;
public:
	static IDirect3DSurface8 *m_oldRenderSurface;
	static IDirect3DTexture8 *m_renderTexture;
	W3DShaderManager();
	static int getShaderPasses(ShaderTypes shader);
	static void startRenderToTexture();
	static IDirect3DTexture8 *endRenderToTexture();
	static IDirect3DTexture8 *getRenderTexture();
	static void drawViewport(int color, bool useExplicitDimensions, const Vector2 *dimensions);
	static bool testMinimumRequirements(ChipsetType *, CpuType *, int *, unsigned __int64 *, float *, float *, float *);
	static int setShroudTex(int);
	static void performGlow(float weightScale, const GlowSampleVector *samples, int textureSize, IDirect3DTexture8 *sourceTexture, IDirect3DSurface8 *tempSurface, IDirect3DTexture8 *tempTexture, IDirect3DSurface8 *destSurface);
	static void createGaussianVector(void *,BfmeGaussianParams *);
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
