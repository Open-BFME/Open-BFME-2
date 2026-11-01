// cl: /DNDEBUG /MD
// ?rva0028BD17@Object@@QBEPAXXZ, retail 0x0028BD17, 35 bytes.
// Object behavior-scan getter through the +0x244 array: asks each module's
// +0x0C sub-object for slot 32 (+0x80) and returns the first non-null result.
// Evidence: same TU shape as the rowed ?getSpawnBehaviorInterface@Object@@
// at 0x0028BCD4 (slot 30) and the just-landed ?rva0028BCF4 (slot 38); slot
// 0x80 is the retail call immediate; 40-plus callers test the result. Name
// stays address-derived with void* return; true interface name unproven.
#include "../../../Include/GameLogic/Module/BehaviorModule.h"

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	void *rva0028BD17() const;
};

void *Object::rva0028BD17() const
{
	for (BehaviorModule **behaviorModule = m_modules244; *behaviorModule; ++behaviorModule)
	{
		void *result = (*behaviorModule)->slot32();
		if (result)
			return result;
	}
	return 0;
}
