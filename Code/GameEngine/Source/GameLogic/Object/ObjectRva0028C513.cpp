// cl: /DNDEBUG /MD /EHsc
//
// ?rva0028C513@Object@@QBE?AW4ObjectID@@XZ @0x0028C513 39B
// Object module-scan ObjectID getter through the +0x244 array: asks each
// module's +0x0C sub-object for slot 26 (+0x68); on the first non-null result
// tail-forwards to its slot 0 which returns the ID, else INVALID_ID.
// Evidence: same +0x244 array and +0x0C lea as sibling rva0028C4ED (slot 26
// bool) and void* siblings rva0028BD3A/BD17/BCF4; retail call [eax+0x68] plus
// jmp [edx] immediates prove slot and tail; caller at 0x00293422 pushes eax
// to rowed findObjectByID which takes W4ObjectID proving ObjectID return;
// plain ret proves 0 args; name stays address-derived (Object owner proven by
// +0x244 and callers, identity unproven).

enum ObjectID
{
	INVALID_ID = 0
};

class Rva0028C513Result
{
public:
	virtual ObjectID slot0();
};

#include "../../../Include/GameLogic/Module/BehaviorModule.h"



class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	ObjectID rva0028C513() const;
};

ObjectID Object::rva0028C513() const
{
	for (BehaviorModule **behaviorModule = m_modules244; *behaviorModule; ++behaviorModule)
	{
		Rva0028C513Result *r = static_cast<Rva0028C513Result *>((*behaviorModule)->slot26());
		if (r != 0)
			return r->slot0();
	}
	return INVALID_ID;
}
