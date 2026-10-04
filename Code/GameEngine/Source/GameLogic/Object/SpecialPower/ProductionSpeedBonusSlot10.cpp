// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE
//
// ?rva004C2F6A@ProductionSpeedBonus@@UAEXH@Z, retail 0x004C2F6A, 124 bytes:
// slot 10 of the special-power interface vtable 0x00C5C9E0 that
// ProductionSpeedBonus's ctor 0x004C2EF5 installs at +0x10, the untargeted
// use. For each entry of the module data's 4-byte list (+0x84..+0x88) it
// hands the owner's controlling player (pinned member 0x002AE8CF) the entry,
// the bonus (m - 1) / -m in double precision for the +0x80 factor m, and the
// +0x7C duration; then, unless the owner is disabled (rowed BitFlags<11>::any
// on +0x1C8), runs slot 12 at the owner's position with the same options.
// Compiled with the +0x10 subobject this. Names by address.
template <int N>
class BitFlags
{
public:
	bool any() const;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

#include "ascii_string.h"

class Player
{
public:
	void rva002AE8CF(const AsciiString *name, float bonus, int frames);
};

class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_pad000[0x38];
	Coord3D m_pos; // +0x38
	unsigned char m_pad044[0x1C8 - 0x44];
	BitFlags<11> m_disabled; // +0x1C8
};

struct ProductionSpeedBonusModuleData
{
	unsigned char m_pad00[0x7C];
	int m_7C; // +0x7C
	float m_80; // +0x80
	const AsciiString *m_begin; // +0x84
	const AsciiString *m_end; // +0x88
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ProductionSpeedBonusModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
private:
	unsigned char m_pad0C[0x10 - 0x0C];
};

class SpecialPowerModuleInterface
{
public:
	virtual void s0() = 0; virtual void s1() = 0; virtual void s2() = 0; virtual void s3() = 0;
	virtual void s4() = 0; virtual void s5() = 0; virtual void s6() = 0; virtual void s7() = 0;
	virtual void s8() = 0; virtual void s9() = 0;
	virtual void rva004C2F6A(int options) = 0;
	virtual void s11() = 0;
	virtual void rva004C2F6ASlot12(const Coord3D *pos, int options) = 0;
};

class ProductionSpeedBonus : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	virtual void rva004C2F6A(int options);
};

void ProductionSpeedBonus::rva004C2F6A(int options)
{
	Object *obj = m_object;
	const ProductionSpeedBonusModuleData *d = m_moduleData;
	Player *player = obj->getControllingPlayer();
	for (const AsciiString *it = d->m_begin; it != d->m_end; ++it)
		player->rva002AE8CF(it, (float)((d->m_80 - 1.0) / (d->m_80 * -1.0)), d->m_7C);
	if (!obj->m_disabled.any())
		rva004C2F6ASlot12(&obj->m_pos, options);
}
