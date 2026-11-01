// cl: /DNDEBUG /MD
// ?rva0028BCF4@Object@@QBEPAXXZ, retail 0x0028BCF4, 35 bytes.
// Object behavior-scan getter through the +0x244 array: asks each module's
// +0x0C sub-object for slot 38 (+0x98) and returns the first non-null result.
// Evidence: same TU shape as the rowed ?getSpawnBehaviorInterface@Object@@
// at 0x0028BCD4 which scans +0x244 via +0x0C for slot 30; slot 0x98 is the
// retail call immediate; callers at 0x00397299 0x00397211 test the result then
// call its slot 0x0C. Name stays address-derived with void* return like the
// ?rva0028C197 precedent; true interface name unproven.
#include "../../../Include/GameLogic/Module/BehaviorModule.h"

class BfmeObjectModule
{
public:
	virtual void slot0();

private:
	unsigned int m_data[2];
};


class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	void *rva0028BCF4() const;
};

void *Object::rva0028BCF4() const
{
	for (BehaviorModule **behaviorModule = m_modules244; *behaviorModule; ++behaviorModule)
	{
		void *result = (*behaviorModule)->slot38();
		if (result)
			return result;
	}
	return 0;
}
