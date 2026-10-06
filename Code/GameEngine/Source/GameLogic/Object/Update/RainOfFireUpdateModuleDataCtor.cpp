// cl: /DNDEBUG /MD
//
// ??0RainOfFireUpdateModuleData@@QAE@XZ, retail 0x004AC03D, 89 bytes.
// Frameless SSE ctor: two global floats into +0x10/+0x14, vtable literal,
// ints 150/120 at +8/+0xC, zeros plus two 1.0f stores across +0x18/+0x2C.
// Explicit m_vtable plus /arch:SSE per the DemoTrap precedent.

// Retail default floats arrive via absolute loads (DIR32-masked externs,
// free per the DieMuxData precedent): emitter height at 0x00BC292C, darkness
// level at 0x00BBB8D4. The 1.0f defaults stay literals: the compiler folds
// them onto the shared literal at 0x00BBB8D8 per the Prone precedent.

extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

class RainOfFireUpdateModuleData
{
public:
	RainOfFireUpdateModuleData();

private:
	void *m_vtable;
	int m_unused04;
	int m_startRainTime;
	int m_darknessFadeTime;
	float m_rainEmitterHeight;
	float m_darknessLevel;
	float m_jitterRadius;
	float m_dpsMin;
	float m_dpsMax;
	float m_dpsRampupTime;
	float m_rainOffset;
	float m_pad2C;
};

// ??0RainOfFireUpdateModuleData@@QAE@XZ
RainOfFireUpdateModuleData::RainOfFireUpdateModuleData()
{
	m_rainEmitterHeight = 100.0f;
	m_darknessLevel = 0.25f;
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00C4ED70));
	m_startRainTime = 150;
	m_darknessFadeTime = 120;
	m_jitterRadius = 0.0f;
	m_dpsMin = 1.0f;
	m_dpsMax = 1.0f;
	m_dpsRampupTime = 0.0f;
	m_rainOffset = 0.0f;
	m_pad2C = 0.0f;
}
