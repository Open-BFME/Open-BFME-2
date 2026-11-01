// cl: /O1 /MD
// ??1BfmeStringTailRecord156@@QAE@XZ @0x0010F149 12B. Non-virtual dtor:
// if (m_ptr) m_ptr->Release_Ref() tail-jmp to rowed
// ?Release_Ref@OpaqueRefCounted@@QAEXXZ. Pins name the dtor; callers include
// FamilyDeletingDtors2 ??_G plus STL destroy helpers.
#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
class BfmeStringTailRecord156 {
public:
	~BfmeStringTailRecord156();
private:
	OpaqueRefCounted *m_ptr;
};
inline BfmeStringTailRecord156::~BfmeStringTailRecord156()
{
	if (m_ptr)
		m_ptr->Release_Ref();
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeBfmeStringTailRecord156InlineAnchor@@YAXPAVBfmeStringTailRecord156@@@Z absent-from-retail
void _bfmeBfmeStringTailRecord156InlineAnchor(BfmeStringTailRecord156 *p)
{
    p->BfmeStringTailRecord156::~BfmeStringTailRecord156();
}
#pragma inline_depth()
