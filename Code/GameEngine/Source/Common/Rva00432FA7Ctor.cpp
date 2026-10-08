// cl: /MD
// ??0Rva00432FA7@@QAE@XZ, retail 0x00432FA7, 72 bytes.
// Ctor: baseConstruct 0x001B4E63 then vtable g_00C3CA30 then five ints at
// +0xC/+0x10/+0x14/+0x18/+0x1C zeroed then three FLT_MAX floats at
// +0x20/+0x24/+0x28 from pool 0x007BB8E0 then singleton g_00E032D0 set if zero.
// Base size 0xC from BFME2NativeNetworkBaseConstruct (vptr+flag+value).
// Precedent Rva0026201C 0x00262002 (/O1 /MD, baseConstruct then zeros then
// vtable). Floats via FLT_MAX link (never extern per linking rule).
#include <float.h>

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

extern const void *const g_00C3CA30[];
class Rva00432FA7;
// ?g_00E032D0@@3PAVRva00432FA7@@A: the global at this VA is ?g_004C9DC9Container@@3PAVRva00432F23@@A; this name is an alias for it.
extern class Rva00432F23 *g_004C9DC9Container;
#pragma comment(linker, "/alternatename:?g_00E032D0@@3PAVRva00432FA7@@A=?g_004C9DC9Container@@3PAVRva00432F23@@A")

class Rva00432FA7
{
	int m_pad00[3];
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	float m_20;
	float m_24;
	float m_28;
public:
	Rva00432FA7();
};

Rva00432FA7::Rva00432FA7()
{
	((BFME2NativeNetwork *)this)->baseConstruct();
	*(const void **)this = g_00C3CA30;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = FLT_MAX;
	m_24 = FLT_MAX;
	m_28 = FLT_MAX;
	if ((*(Rva00432FA7 **)&g_004C9DC9Container) == 0)
		(*(Rva00432FA7 **)&g_004C9DC9Container) = this;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00C3CA30@@3QBQBXB=??_7Rva00432FA7@@6B@")
