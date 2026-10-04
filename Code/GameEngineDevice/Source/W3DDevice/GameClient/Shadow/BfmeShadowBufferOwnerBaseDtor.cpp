// cl: /O1 /Ob0 /GX- /MD
// Native EFAD2/28 deleting destructor calls the108B4D/7 vtable reset.
// /Ob0 preserves that out-of-line call rather than inlining a29-byte copy.
// The explicit helper retains the generated destructor bodies; its own
// target entry is unpinned. Original class name and full table are unknown.
#include "BfmeShadowPrefix.h"
// ?destroyBaseExplicit present-unmatched
void destroyBaseExplicit(BfmeShadowBufferOwnerBase *p)
{
 p->BfmeShadowBufferOwnerBase::~BfmeShadowBufferOwnerBase();
}
