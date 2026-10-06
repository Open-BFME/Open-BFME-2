// ?rva00086B2C@Rva008B77D@@UAEXHHMMHH@Z
// partial score=0.986 date=2026-10-06
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?rva00086B2C@Rva008B77D@@UAEXHHMMHH@Z @0x003114A7 144B
// Slot 2 (offset 0x8) of vtable 0x007C7514 (class of ??1Rva008B77D@@UAE@XZ).
// Sister of Rva0089971::rva00086B2C (0x00086B2C, same ParabolicEase tail and
// m_04 clamp); here the fixed 257/255 array clears are absent (vector owner)
// and the trailing int flag gates a float zero at +0x38 with the stored int
// also latched as a bool at +0x46. Base prefix and ParabolicEase declaration
// come from the shared owner header; vector size (12B) puts derived floats
// at +0x38/+0x3C/+0x48/+0x4C/+0x50.
#include <vector>
#include "../../Include/GameClient/Rva0008990CArrayOwner.h"

struct BfmeStringHeadRecord184
{
	char m_data[184];
};

class Rva008B77D : public Rva000851F3
{
public:
	virtual void rva00047A69C(int);
	virtual void rva00086B2C(int value, int duration, Real first, Real second, int stored, int flag);
private:
	_STL::vector<BfmeStringHeadRecord184> m_records; // +0x2C (12B)
	float m_38; // +0x38
	volatile float m_3C; // +0x3C
	volatile int m_40; // +0x40
	char m_44; // +0x44 untouched pad/proven hole before +0x45
	volatile unsigned char m_45; // +0x45
	volatile bool m_46; // +0x46
	float m_48; // +0x48
	float m_4C; // +0x4C
	float m_50; // +0x50
};

void Rva008B77D::rva00086B2C(int value, int duration, Real first, Real second, int stored, int flag)
{
	(void)value;
	m_04 = duration > 1 ? duration : 1;
	m_08 = 0;
	m_18 = 0.0f;
	m_1C = 0.0f;
	m_20 = 0;
	m_28 = 1;
	m_10.rva0030E51F(first, second, (Real)duration);
	m_0C = stored;
	if ((unsigned char)flag)
		m_38 = 0.0f;
	m_40 = 0;
	m_45 = 0;
	m_3C = 0.0f;
	m_46 = stored != 0;
	m_48 = 0.0f;
	m_4C = 0.0f;
	m_50 = 0.0f;
	m_24 = true;
}
