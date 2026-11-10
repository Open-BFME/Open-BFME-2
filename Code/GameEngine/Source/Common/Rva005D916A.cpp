// cl: /MD
// ?shouldActivate@Rva005D8EE8@@UAE_NPAVObject@@@Z @0x005D916A 47B
// Evidence: vslot 6 of 0x00876254 class Rva005D8EE8 plus AI victim plus picker 0x005D8F0F.
class Object;
#include "../../Include/GameLogic/Module/AIUpdate.h"
#include "../../Include/Common/Rva005EE816.h"
#include "../GameLogic/Object/object.h"
class Rva005EE30C { public: virtual ~Rva005EE30C(); };
class Rva005D8EE8 : public Rva005EE30C {
public:
	virtual bool shouldActivate(Object *other);
};
bool Rva005D8EE8::shouldActivate(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (victim) {
		unsigned v = ((Rva005EE816 *)this)->rva005D8F0F(other);
		if (v >= 2)
			return true;
	}
	return false;
}
