// ??1PhysicsBehavior@@UAE@XZ (was ??1Rva003908C2@@UAE@XZ)
// partial score=0.96 date=2026-09-30
// cl: /DNDEBUG /MD /EHs
//
// ??1PhysicsBehavior@@UAE@XZ, retail 0x003908C2, 79 bytes.
// Identity: vtable 0x00C19F74 is installed by the rowed PhysicsBehavior ctor
// 0x003907A6 and its slot 0 is this dtor's deleting dtor 0x003909DE; the
// +0x20 free is the ctor's BfmeE16 vector.
// Evidence: vtable 0x00819F74 plus s_secondary0C at +0x0C plus g_00C19F68
// at +0x10 plus _free of +0x20 via rowed 0x00030830 plus base dtor
// ??1Rva0024A797 rowed 0x0024A797; EH prolog 0x00629188; caller 0x003909DE.
// MI fix: three vptrs are implicit via two empty polymorphic bases, moving and-ebp-4-0 late after load.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../Include/GameLogic/Module/UpdateModule.h"

class PhysicsBehavior : public UpdateModule
{
public:
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override
	virtual ~PhysicsBehavior();
private:
	void *m_p20;
};

PhysicsBehavior::~PhysicsBehavior()
{
	if (m_p20)
		free(m_p20);
}
