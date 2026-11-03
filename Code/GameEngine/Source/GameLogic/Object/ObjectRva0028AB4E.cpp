// cl: /DNDEBUG /MD
// ?rva0028AB4E@Object@@QBEXXZ @0x0028AB4E 39B: Object module scan through +0x244 array via +0x0C sub-object slot 3 then result slot 2.
// Evidence: +0x244 Module** list (ObjectFindModule precedent); +0x0C second-base lea (ObjectRva0028B265 precedent); callers 1; neighbours Object rows.
class Rva0028AB4EResult
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
};
#include "../../../Include/GameLogic/Module/BehaviorModule.h"
#include "object.h"
void Object::rva0028AB4E() const
{
	for (BehaviorModule **behaviorModule = m_behaviors; *behaviorModule; ++behaviorModule)
	{
		Rva0028AB4EResult *r = reinterpret_cast<Rva0028AB4EResult *>((*behaviorModule)->getCreate());
		if (r != 0)
			r->slot02();
	}
}
