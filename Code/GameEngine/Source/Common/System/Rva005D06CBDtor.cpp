// cl: /Ireference/shims/bfme2_ascii /EHsc
class LivingWorldBattle;
// ??1Rva005CFACB@@UAE@XZ @ 0x005D06CB 103B: MI virtual dtor with three bases
// unregistering the second base via rowed erase 0x002B7250 on holder at
// g_009FEF10+0x2C then pinned third-base dtor 0x005EB753. Evidence:
// deleting-dtor caller 0x005D0A67; vtable stores 0x00C75554 0x00C75548
// 0x00C75540 then 0x00C62A14 0x00C75290; chain sibling of 0x005D078B.
class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class CreateAHeroData;
#include "../../../Include/Common/Rva002B7250.h"
#include "../../../Include/GameLogic/Rva002BA8F1Logic.h"

class Rva005D06CBB1
{
public:
	virtual ~Rva005D06CBB1() {}
	// Retail's table holds the shared empty body 0x000B3FD0 in slot 1.
	virtual void slot01() {}
private:
	int m_04;
};
// LivingWorldAutoResolveEventObserver: definition as Code/GameEngine/Include/Common/LivingWorldScoreKeeper.h holds it
class LivingWorldAutoResolveEventObserver {public: ~LivingWorldAutoResolveEventObserver(){} virtual void event2_0(int,int,int){} virtual void event2_1(int,int,int){} virtual void OnLivingWorldAutoResolveBattleCompleted(int,LivingWorldBattle*,void*){} };

class Rva005D06CBB2 : public LivingWorldAutoResolveEventObserver
{
public:
};
class Rva005EB753
{
public:
	virtual ~Rva005EB753();
	virtual void veterancySlot04();
};
class Rva005CFACB : public Rva005D06CBB1, public Rva005D06CBB2, public Rva005EB753
{
public:
	virtual ~Rva005CFACB();
	virtual void veterancySlot04();
};
Rva005CFACB::~Rva005CFACB()
{
	((Rva002B7250 *)((*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->field10 + 0x1C))->rva002B7250((CreateAHeroData *)(Rva005D06CBB2 *)this);
}
