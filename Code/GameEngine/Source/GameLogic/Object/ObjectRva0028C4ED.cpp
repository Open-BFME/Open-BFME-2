// cl: /DNDEBUG /MD /EHsc
//
// ?rva0028C4ED@Object@@QBE_NXZ @0x0028C4ED 38B
// Object module-scan bool predicate through the +0x244 array: asks each
// module's +0x0C sub-object for slot 26 (+0x68) and returns true on the first
// true. Evidence: same +0x244 array as rowed getSpawnBehaviorInterface at
// 0x0028BCD4 and siblings rva0028BD3A (slot 33) rva0028BCF4 (slot 38)
// rva0028BD17 (slot 32); retail lea ecx [eax+0x0C] plus call [eax+0x68]
// proves the +0x0C interface and slot; callers at 0x0029340C 0x003792C8 test
// al; plain ret proves 0 args; name stays address-derived (Object owner proven
// by +0x244 and callers, identity unproven).

#include "../../../Include/GameLogic/Module/BehaviorModule.h"

class BfmeObjectModule
{
public:
	virtual void slot0();

private:
	unsigned int m_data[2];
};


class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	bool rva0028C4ED() const;
};

bool Object::rva0028C4ED() const
{
	for (BehaviorModule **behaviorModule = m_modules244; *behaviorModule; ++behaviorModule)
	{
		if ((*behaviorModule)->slot26())
			return true;
	}
	return false;
}
