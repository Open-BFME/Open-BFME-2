// cl: /O2 /G7 /MD
// Native6E63D0..6E6429,32B nonvirtual AptIntervalTimer array delete.
// The owned constructor6E3CF0 and destructor6E4F60 corroborate type/stride;
// parent6E6060 creates this array, and6E6430 destroys it.
void Rva006CD460Free(void *);
#include "../../../GameEngine/Include/Common/Rva006DB270.h"
extern Rva006DB270 *g_pChainBlockAllocator;
class AptIntervalTimer {
 char data[32];
public:
 ~AptIntervalTimer();
 static void operator delete(void *p,unsigned size){g_pChainBlockAllocator->freeBlock(p,size);}
 static void operator delete[](void *p){Rva006CD460Free(p);}
};
// ?EmitIntervalTimerArrayDelete absent-from-retail
void EmitIntervalTimerArrayDelete(AptIntervalTimer *aptIntervalTimer){delete[] aptIntervalTimer;}
