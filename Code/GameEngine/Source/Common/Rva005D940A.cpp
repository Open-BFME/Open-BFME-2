// cl: /MD
// ?shouldActivate@Rva005D91AB@@UAE_NPAVObject@@@Z @0x005D940A 46B
// Evidence: vslot 6 of 0x00876278 class Rva005D91AB plus AI victim plus picker 0x005D91D2.
class Object;
#include "../../Include/GameLogic/Module/AIUpdate.h"
#include "../../Include/Common/Rva005EE816.h"
#include "../GameLogic/Object/object.h"
class Rva005EE30C { public: virtual ~Rva005EE30C(); };
class Rva005D91AB : public Rva005EE30C {
public:
	virtual bool shouldActivate(Object *other);
};
bool Rva005D91AB::shouldActivate(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (!victim) {
		unsigned v = ((Rva005EE816 *)this)->rva005D91D2(other);
		if (v != 0)
			return true;
	}
	return false;
}
