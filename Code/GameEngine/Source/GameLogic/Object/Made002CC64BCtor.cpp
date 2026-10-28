// cl: /I. /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE /Oi- /GX- /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// ??0Made002CC64B@@QAE@XZ @0x00508BE5 (97B).
// AttributeModifierNugget ctor over rowed base Rva00507823 0x0050775B,
// vtable 0x00C64370. Derived members: AsciiString name at +0x128 (4B,
// single-pointer shim, inline default ctor zeroes the word), int 0x1D at
// +0x12C, float 0.0 at +0x130, angle pi at +0x134 (0x00BC7468), 4-byte
// mask at +0x138 built by the rowed BitFlags<11> default ctor 0x003B31AD
// plus a duplicate 4-byte memset, FX pointer null at +0x13C. Size 0x140
// from the parseAttributeModifierNugget news. Caller
// parseAttributeModifierNugget 0x002CC64B (WeaponNuggetParse.cpp).
// Layout corroborated by rva00508987 (AttributeModifierNuggetEffect.cpp:
// name128/angle134/mask138/FX13C) and the destructor 0x00508CF7 rowed as
// ??1Rva00508CF7@@UAE@XZ (AsciiString at +0x128, then base). Same
// ctor-plus-duplicate-memset idiom as Made002CC5E1Ctor.cpp. /Oi- keeps
// the mask memset a real out-of-line call.
#include <string.h>

#include "ascii_string.h"

struct Coord3D;
struct Rva00508987Weapon;
class Object;

class Rva00507823
{
public:
	Rva00507823();
	virtual ~Rva00507823();
	virtual bool accepts(Rva00508987Weapon *weapon, Object *target) = 0;
	virtual void s08() = 0; virtual void s0C() = 0; virtual void s10() = 0;
	virtual void rva00508B9E(Rva00508987Weapon *weapon, Object *target) = 0;
	virtual void rva00508C46(Rva00508987Weapon *weapon, const Coord3D *position) = 0;
private:
	char m_pad[0x128 - 4];
};

typedef unsigned int UnsignedInt;

template <int NUM_BITS>
class BitFlags
{
public:
	BitFlags() throw();
private:
	UnsignedInt m_words[1];
};

class FXList;

// AttributeModifierNugget (vtable 0x00C64370, 0x140 bytes from the parser's
// new): the constructor 0x00508BE5 and the effect body 0x00508987 witness
// name +0x128, 0x1D at +0x12C, radius +0x130, angle +0x134, mask +0x138
// and FX +0x13C.
class Made002CC64B : public Rva00507823
{
public:
	Made002CC64B();
	void rva00508987(Rva00508987Weapon *weapon, Object *target);
	virtual void rva00508B9E(Rva00508987Weapon *weapon, Object *target);
	virtual void rva00508C46(Rva00508987Weapon *weapon, const Coord3D *position);
private:
	AsciiString m_name128;
	int m_12C;
	float m_130;	// +0x130, the effect radius
	float m_angle134;
	BitFlags<11> m_mask138;
	FXList *m_fx13C;
};

Made002CC64B::Made002CC64B()
{
	m_130 = 0.0f;
	m_12C = 0x1D;
	m_angle134 = 3.1415927f;
	memset(&m_mask138, 0, sizeof(m_mask138));
	m_fx13C = 0;
}
