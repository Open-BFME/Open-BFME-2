// cl: /O1 /DNDEBUG /MD /arch:SSE /Oy-
// ?ForceEmotion@EmotionTrackerUpdate@@QAEXHMH@Z @0x004B0DAC 115B. Linkbody via
// caller 0x0028ECD3 (Object::rva0028ECA8 forwards index value arg). Stores
// index at +0xB0 when value>0; ceil scaled duration at +0xB4 via IAT ceil;
// source id at +0xB8 from arg+0x74 or 0; clears +0x9C slot via rowed
// rva004DD2C0. Evidence: pin name LINK BONUS, rowed/pinned callees,
// g_parseDurationMsecScale g_00BBE358, neighbours.
extern float g_parseDurationMsecScale;
extern float g_00BBE358;
extern "C" __declspec(dllimport) double __cdecl ceil(double);

// BaseType.h verbatim: C cast emits out-of-line _ftol plus qword shape;
// retail holds inline fld/fistp so the helper is load-bearing.
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

struct Rva004B0DACArg
{
	char m_pad[0x74];
	int m_74;
};

class EmotionTrackerUpdate
{
public:
	void ForceEmotion(int index, float value, int arg);
private:
	char m_pad00[0x9C];
	Rva004DD2C0 *m_9C;
	char m_padA0[0xB0 - 0xA0];
	int m_B0;
	int m_B4;
	int m_B8;
};

void EmotionTrackerUpdate::ForceEmotion(int index, float value, int arg)
{
	if (value <= 0.0f)
		return;
	m_B0 = index;
	float prod = g_parseDurationMsecScale * value;
	prod *= g_00BBE358;
	float tmp = (float)ceil(prod);
	m_B4 = fast_float2long_round(tmp);
	int v = (arg != 0) ? ((Rva004B0DACArg *)arg)->m_74 : 0;
	m_B8 = v;
	Rva004DD2C0 **slotp = &m_9C;
	Rva004DD2C0 *slot = *slotp;
	if (slot != 0) {
		slot->rva004DD2C0();
		*slotp = 0;
	}
}
