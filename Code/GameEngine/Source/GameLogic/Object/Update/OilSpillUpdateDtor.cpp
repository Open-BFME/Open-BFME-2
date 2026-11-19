// cl: /O1 /GX /DNDEBUG /MD
// ??1OilSpillUpdate@@UAE@XZ @0x0048C2A3 79B
// Dtor restores three vptrs (+0 +0xC +0x10) then frees buffer at +0x2C via rowed _free and calls rowed base ??1FireWeaponUpdate at 0x0048BD11. Buffer is the vector<int> payload at +0x2C proven by ctor TU; modeled as void* since trivial-int destruction only frees. Model otherwise follows OilSpillUpdateCtor.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

class Thing;
class ModuleData;
class Object;

class FireWeaponBaseA
{
	virtual void unusedA();
	int m_a0;

protected:
	void *m_owner08;
};

class FireWeaponBaseB
{
	virtual void unusedB();
};

enum UpdateSleepTime;
// The +0x10 update interface: slot 0 of OilSpillUpdate's table is its rowed update.
class FireWeaponBaseC
{
public:
	virtual UpdateSleepTime update() = 0;
};

class FireWeaponUpdate : public FireWeaponBaseA, public FireWeaponBaseB, public FireWeaponBaseC
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponUpdate();

protected:
	void setWakeFrame(Object *obj, unsigned int frames);

private:
	unsigned char m_pad14[0x2C - 0x14];
};

class OilSpillUpdate : public FireWeaponUpdate
{
public:
	OilSpillUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~OilSpillUpdate();
	virtual UpdateSleepTime update();

private:
	void *m_buf2C;
	unsigned char m_pad30[0x38 - 0x30];
};

inline OilSpillUpdate::~OilSpillUpdate()
{
	if (m_buf2C)
		free(m_buf2C);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeOilSpillUpdateInlineAnchor@@YAXPAVOilSpillUpdate@@@Z absent-from-retail
void _bfmeOilSpillUpdateInlineAnchor(OilSpillUpdate *oilSpillUpdate)
{
    oilSpillUpdate->OilSpillUpdate::~OilSpillUpdate();
}
#pragma inline_depth()

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unusedB@FireWeaponBaseB@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?unusedA@FireWeaponBaseA@@EAEXXZ=??_GOilSpillUpdate@@UAEPAXI@Z")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
