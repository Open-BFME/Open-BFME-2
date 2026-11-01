// cl: /DNDEBUG /MD
// ?rva0028BD5D@Object@@QBEPAXH@Z @0x0028BD5D 53B
// Object behavior-scan predicate through the +0x244 array: asks each
// module's +0x0C sub-object for slot 25 (+0x64); when non-null asks its
// slot 4 (+0x10) bool and returns the first pointer whose predicate is true,
// else null. Takes one unused int (retail ret 4 with no stack reads).
// Evidence: same +0x244 array and +0x0C lea as rowed getSpawnBehaviorInterface
// at 0x0028BCD4 and siblings rva0028BD3A (slot 33) rva0028BCF4 (slot 38);
// retail lea ecx [eax+0x0C] plus call [eax+0x64] plus call [eax+0x10] plus
// test al jne prove slots and bool; callers at 0x0036E20F 0x0041BB51;
// name stays address-derived (Object owner proven by +0x244).

class Rva0028BD5DResult
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual bool slot04();
};

#include "../../../Include/GameLogic/Module/BehaviorModule.h"



class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	void *rva0028BD5D(int unused) const;
};

void *Object::rva0028BD5D(int unused) const
{
	(void)unused;
	for (BehaviorModule **behaviorModule = m_modules244; *behaviorModule; ++behaviorModule)
	{
		Rva0028BD5DResult *r = static_cast<Rva0028BD5DResult *>((*behaviorModule)->slot25());
		if (r != 0 && r->slot04())
			return r;
	}
	return 0;
}
