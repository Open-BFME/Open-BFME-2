// cl: /DNDEBUG /MD /EHsc
// ?rva00589135@WeaponModeSpecialPowerUpdateBase@@QAEXH@Z, retail 0x00589135 54B. Vslot 10 of 0x00870108 via rowed BitFlags 0x0023C58B any plus slot0 virtual on this-4 with 5 args. Donor WeaponModeSpecialPowerUpdateBaseCtor plus open-bfme-1 WeaponModeSpecialPowerUpdateCtorThunk.
template<int N>
class BitFlags
{
public:
	bool any() const;
};

struct VirtBase
{
	virtual void vf(void *a, int b, int c, int d, int e);
};

#include "../../../../Include/Common/Overridable.h"

class SpecialPowerTemplate;
class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva002AC6B1PlayerTimers
{
public:
	unsigned int getOrStart(const SpecialPowerTemplate *tmpl);
};

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

struct VirtPrimary
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual const Overridable *f6() const;
};

class WeaponModeSpecialPowerUpdateBase
{
public:
	void rva00589135(int commandOptions);
	void rva0058916B(int arg1, int commandOptions);
	void rva005891A3(int arg1, int commandOptions);
	void rva005891DB(int loc, int angle, int commandOptions);
	int rva005893AD();
	bool rva005778AD();
private:
	unsigned char m_pad00[4];
	int m_04;
	int m_08;
	int m_0C;
};

// ?rva005778AD@WeaponModeSpecialPowerUpdateBase@@QAE_NXZ, retail 0x005778AD 9B.
// Vslot 3 of 0x00870108 (and of DeflectSpecialPower's 0x00C4E900 and
// SiegeDeploySpecialPower's 0x00C5DC68, the same +0x24 interface): whether
// the +8 count the slots above test is positive.
bool WeaponModeSpecialPowerUpdateBase::rva005778AD()
{
	return m_08 > 0;
}
