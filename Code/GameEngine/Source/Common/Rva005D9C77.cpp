// cl: /MD
// ?shouldActivate@Rva005D9C6C@@UAE_NPAVObject@@@Z @0x005D9C77 48B
// Evidence: gap between Rva005D9C6C dtor 0x005D9C6C and deleting dtor 0x005D9CA7 plus vslot 6 of 0x008763FC.
class Object;
#include "../../Include/GameLogic/Module/AIUpdate.h"
#include "../../Include/Common/Rva005EE816.h"
#include "../GameLogic/Object/object.h"
class Rva005EE30C { public: virtual ~Rva005EE30C(); };
class Rva005D9C6C : public Rva005EE30C {
public:
	virtual bool shouldActivate(Object *other);
};
bool Rva005D9C6C::shouldActivate(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (!victim) {
		unsigned v = ((Rva005EE816 *)this)->rva005EE3B0(other, true);
		if (v != 0)
			return true;
	}
	return false;
}
