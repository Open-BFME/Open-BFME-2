// cl: /MD /DNDEBUG
// stlport

// ?Rva004C7542Destroy@@YAXPAU?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@0@Z RVA 0x004C7542 size 25
// Evidence: callee pair dtor rowed at 0x000796BC; callers at 0x004C7781 and 0x004C77AE; stride 0x10 proves 16-byte pair; explicit loop exact mod reloc.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport, and <stddef.h> with it so
// their _errno declarations agree.
#define _CRTIMP
#include <stddef.h>
#include <stdlib.h>
#undef _CRTIMP

#include <vector>
#include <map>

#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/Enums/LocomotorSetType.h"













class LocomotorTemplate;

typedef _STL::vector<const LocomotorTemplate *> LocomotorVec;
// Keep this existing specialization's 16-byte layout, but declare the
// established complete destructor instead of generating an incidental
// default allocator cleanup or scalar-deleting destructor in this TU.
namespace _STL {
template <> struct pair<const LocomotorSetType, LocomotorVec> {
    const LocomotorSetType first;
    LocomotorVec second;
    ~pair();
};
}
typedef _STL::pair<const LocomotorSetType, LocomotorVec> LocoPair;
typedef char LocoPairSizeMustBe16[sizeof(LocoPair) == 16 ? 1 : -1];

void Rva004C7542Destroy(LocoPair *first, LocoPair *last)
{
	for (; first != last; ++first)
		first->~LocoPair();
}

// ?rva004C77A6@Rva004C77A6@@QAEXXZ RVA 0x004C77A6 size 30
// Evidence: calls Rva004C7542Destroy rowed at 0x004C7542 plus _free rowed at 0x00030830; caller at 0x004C785A; chain lane unblocks 0x004C77C4; exact mod reloc.

class Rva004C77A6
{
public:
	void rva004C77A6();

private:
	LocoPair *m_start;
	LocoPair *m_finish;
};

void Rva004C77A6::rva004C77A6()
{
	Rva004C7542Destroy(m_start, m_finish);
	LocoPair *locoPair = m_start;
	if (locoPair)
		free(locoPair);
}

// Native4C74D4..4C74DD is a separate nine-byte cdecl body between the
// complete91B sort ending in RET at4C74D3 and the next sort at4C74DD.
// It passes its sole pointer argument as this to the existing whole15B
// destructor796BC. This neutral wrapper recovers that observed operation.
// LocoPair is the existing callee owner's compatible call view; neither
// its type nor the matching donor _Destroy<int/vector> specialization is
// asserted as this unreferenced wrapper's original template identity.
void Rva004C74D4Destroy(LocoPair *value)
{
    value->~LocoPair();
}
