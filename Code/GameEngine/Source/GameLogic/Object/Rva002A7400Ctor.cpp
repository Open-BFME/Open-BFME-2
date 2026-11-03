// cl: /DNDEBUG /MD /EHsc
// ??0Rva002A7400@@QAE@XZ @0x002A7400 97B.
// EH ctor zeroing +0/+4 constructing +8 member and initFromStorages with
// two default FixedStorage copies. Evidence: unlock lane, neighbours
// Rva002A73B8Dtor share /O1 layout, callees member ctor/init pin-only and
// FixedStorage copy rowed, __EH_prolog frame, returns this.
#include "../../../Include/Common/BfmeFixedStorage0004543D.h"
#include "../../../Include/GameLogic/Module/Rva003623E5Member.h"
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
class Rva002A7400
{
public:
	Rva002A7400();
private:
	int m_pad0;
	int m_pad4;
	Rva003623E5Member m_member8;
};
Rva002A7400::Rva002A7400() : m_pad0(0), m_pad4(0), m_member8()
{
	m_member8.initFromStorages(*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE),
		*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE));
}

