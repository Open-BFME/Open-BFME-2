// cl: /DNDEBUG /MD
// ?rva0028BC58@Object@@QAEPAXH@Z @0x0028BC58 60B
// Object module-scan getter through the +0x244 array: asks each module's
// +0x0C sub-object for slot 28 (+0x70) and returns the first non-null result
// filtered by the int argument: when the argument is zero the first result
// wins, otherwise the result's own slot 30 (+0x78) must test true.
// Evidence: same +0x244 array via +0x0C lea as rowed getSpawnBehaviorInterface
// at 0x0028BCD4 and siblings rva0028BCF4 (slot 38) rva0028BD17 (slot 32)
// rva0028C4ED (slot 26); retail lea ecx [eax+0x0C] plus calls [eax+0x70] and
// [eax+0x78] prove the two slots; 40-plus callers; LINK BONUS names this exact
// mangling for 4 waiting files.
#include "../../../Include/GameLogic/Module/BehaviorModule.h"

class BfmeObjectModule
{
public:
	virtual void slot0();

private:
	unsigned int m_data[2];
};


class Rva0028BC58Res
{
public:
	virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
	virtual void r04(); virtual void r05(); virtual void r06(); virtual void r07();
	virtual void r08(); virtual void r09(); virtual void r10(); virtual void r11();
	virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15();
	virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19();
	virtual void r20(); virtual void r21(); virtual void r22(); virtual void r23();
	virtual void r24(); virtual void r25(); virtual void r26(); virtual void r27();
	virtual void r28(); virtual void r29();
	virtual bool slot30();
};

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	void *rva0028BC58(int a);
};

void *Object::rva0028BC58(int a)
{
	for (BehaviorModule **behaviorModule = m_modules244; *behaviorModule; ++behaviorModule)
	{
		void *res = (*behaviorModule)->slot28();
		if (!res)
			continue;
		if ((char)a == 0)
			return res;
		if (((Rva0028BC58Res *)res)->slot30())
			return res;
	}
	return 0;
}
