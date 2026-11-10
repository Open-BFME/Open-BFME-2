// cl: /MD
// ?shouldActivate@Rva005D9CD5@@UAE_NPAVObject@@@Z @0x005D9CE0 76B
// Evidence: gap between Rva005D9CD5 dtor 0x005D9CD5 and deleting dtor 0x005D9D2C plus vslot 6 of 0x00876424.
// Retail loads the float at RVA 0x00876420 (bits 0x3E99999A).
// Use its exact literal so MSVC supplies the constant instead of an unowned global.
class Object;
#include "../../Include/GameLogic/Module/AIUpdate.h"
#include "../../Include/Common/Rva005EE816.h"
class Rva005D9Float {
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual float getFloat();
};
class Object {
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface *const *)((const char *)this + 0x258); }
	Rva005D9Float *getBody() const { return *(Rva005D9Float *const *)((const char *)this + 0x254); }
};
class Rva005EE30C { public: virtual ~Rva005EE30C(); };
class Rva005D9CD5 : public Rva005EE30C {
public:
	virtual bool shouldActivate(Object *other);
};
bool Rva005D9CD5::shouldActivate(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (victim) {
		unsigned enemyCount = ((Rva005EE816 *)this)->rva005EE3B0(other, false);
		if (enemyCount > 20)
			return true;
		if (enemyCount != 0) {
			if (0.3f > other->getBody()->getFloat())
				return true;
		}
	}
	return false;
}
