// ?rva004B0DAC@EmotionTrackerUpdate@@QAEXHMH@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /Oy- /arch:SSE /Op /DNDEBUG /MD
//
// ?rva004B0DAC@EmotionTrackerUpdate@@QAEXHMH@Z @0x004B0DAC 115B.
// When the float is positive, store the int at +0xB0, the frame count
// ceil(0.005f * float * 1000.0f) at +0xB4, and the id at +0x74 of the
// third argument (or 0) at +0xB8. Then run 0x004DD2C0 on the slot at
// +0x9C and clear it. Callers: Object::rva0028ECA8.
//
// /Op keeps the float fmul order (scale, then the argument, then 1000).
// The post-ceil cleanup is still fstp/pop/pop where retail is pop/fstp/pop.

extern "C" __declspec(dllimport) double __cdecl ceil(double);
extern float g_parseDurationMsecScale;
extern float g_00BBE358;

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class Rva004DD2C0
{
public:
	void rva004DD2C0();
};

class EmotionTrackerUpdate
{
public:
	void rva004B0DAC(int index, float value, int arg);

private:
	char m_pad[0x9C];
	Rva004DD2C0 *m_slot;
	char m_padA0[0xB0 - 0xA0];
	int m_B0;
	int m_B4;
	int m_B8;
};

void EmotionTrackerUpdate::rva004B0DAC(int index, float value, int arg)
{
	if (value <= 0.0f)
		return;
	m_B0 = index;
	value = (float)ceil((double)((g_parseDurationMsecScale * value) * g_00BBE358));
	m_B4 = fast_float2long_round(value);
	m_B8 = arg != 0 ? *(int *)((char *)arg + 0x74) : 0;
	Rva004DD2C0 *slot = m_slot;
	if (slot != 0)
	{
		slot->rva004DD2C0();
		m_slot = 0;
	}
}
