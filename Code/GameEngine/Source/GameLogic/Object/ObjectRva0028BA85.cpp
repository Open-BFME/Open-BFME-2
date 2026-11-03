// cl: /DNDEBUG /MD
// ?rva0028BA85@Object@@QBEXXZ @0x0028BA85 41B
// Object module broadcast through the +0x244 array: calls each module's
// +0x0C sub-object slot 46 (+0xB8) with the int at +0x45C. Evidence: same
// +0x244 array and +0x0C lea as rowed getSpawnBehaviorInterface at 0x0028BCD4
// and siblings rva0028C4ED (slot 26) rva0028C513 rva0028BD3A/BD17/BCF4;
// retail lea ecx [eax+0x0C] plus call [eax+0xB8] plus push [edi+0x45C] prove
// the interface slot and int arg; null-terminated scan with plain ret proves
// 0 args void; setter sibling at 0x0028BAAE stores +0x45C then calls this;
// name stays address-derived (Object owner proven by +0x244 and callers).

#include "../../../Include/GameLogic/Module/BehaviorModule.h"

#include "object.h"

void Object::rva0028BA85() const
{
	for (BehaviorModule **behaviorModule = m_behaviors; *behaviorModule; ++behaviorModule)
		(*behaviorModule)->slot46(m_45c);
}

void Object::rva0028BAAE(int v)
{
	m_45c = v;
	rva0028BA85();
}
