// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FA10F (89B): guarded one-time init. If +0x78 != -1 return; else
// inc +0x7C, call 0x4F922C(0), 0x4F6187, 0x4F9F39, then loop 0x4F971E plus
// 0x4F99CC(&ready) until ready, then 0x4F9D6A, 0x4F9E59, 0x4F61B1.
// addUnitsForCurrentRound and 0x4F971E (chooseTargets) are now in their
// WB-named class; the remaining callees retain their existing opaque views.

#include "../../Include/GameLogic/LivingWorldAutoResolveBattle.h"

class Rva004F9E59
{
public:
	void rva004F9E59();
};

class Rva004FA10FOwner
{
public:
	void rva004FA10F();

private:
	char m_pad[0x78];	// +0x00..0x77
	int m_78;		// +0x78 guard (-1 = needs init)
	int m_7C;		// +0x7C counter
};

void Rva004FA10FOwner::rva004FA10F()
{
	if (m_78 != -1)
		return;
	m_7C++;
	((LivingWorldAutoResolveBattle *)this)->addUnitsForCurrentRound(0);
	((LivingWorldAutoResolveBattle *)this)->rva004F6187();
	((LivingWorldAutoResolveBattle *)this)->rva004F9F39();
	bool ready = false;
	do
	{
		((LivingWorldAutoResolveBattle *)this)->rva004F971E();
		((LivingWorldAutoResolveBattle *)this)->rva004F99CC(&ready);
	} while (!ready);
	((LivingWorldAutoResolveBattle *)this)->completeRound();
	((Rva004F9E59 *)this)->rva004F9E59();
	((LivingWorldAutoResolveBattle *)this)->rva004F61B1();
}
