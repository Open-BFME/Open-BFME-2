// cl: /DNDEBUG /MD
// ?rva0028BD3A@Object@@QBEPAXXZ, retail 0x0028BD3A, 35 bytes.
// Object behavior-scan getter through the +0x244 array: asks each module's
// +0x0C sub-object for slot 33 (+0x84) and returns the first non-null result.
// Evidence: same TU shape as the rowed ?getSpawnBehaviorInterface@Object@@
// at 0x0028BCD4 (slot 30) and siblings at 0x0028BCF4 (slot 38) 0x0028BD17
// (slot 32); slot 0x84 is the retail call immediate; callers test the result.
// Name stays address-derived with void* return; true interface name unproven.
#include "../../../Include/GameLogic/Module/BehaviorModule.h"

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	void *rva0028BD3A() const;
};

void *Object::rva0028BD3A() const
{
	for (BehaviorModule **behaviorModule = m_modules244; *behaviorModule; ++behaviorModule)
	{
		void *result = (*behaviorModule)->slot33();
		if (result)
			return result;
	}
	return 0;
}
