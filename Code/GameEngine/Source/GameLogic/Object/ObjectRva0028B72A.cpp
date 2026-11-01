// cl: /DNDEBUG /MD
// ?rva0028B72A@Object@@QBEXXZ @0x0028B72A 31B: Object module broadcast
// through +0x244 array; calls each +0x0C sub-object slot44 (+0xB0) with no
// args. Evidence: same +0x244/+0x0C shape as sibling rva0028BA85 slot46 at
// 0x0028BA85; retail lea ecx [eax+0x0C] plus call [eax+0xB0] prove slot;
// null-terminated scan with plain ret proves 0 args void.
#include "../../../Include/GameLogic/Module/BehaviorModule.h"

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	void rva0028B72A() const;
};

void Object::rva0028B72A() const
{
	for (BehaviorModule **behaviorModule = m_modules244; *behaviorModule; ++behaviorModule)
		(*behaviorModule)->slot44();
}
