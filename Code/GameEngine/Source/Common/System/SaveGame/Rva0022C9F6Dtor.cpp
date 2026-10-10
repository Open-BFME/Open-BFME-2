// cl: /EHsc /MD
// stlport
//
// ??1Rva0022C9F6@@UAE@XZ @0x0022C9F6 59B: opaque virtual dtor.
// Vtable 0xBE74F0 store, then _List_base<int> dtor at +0x10 via rowed
// 0x004EC395, then SubsystemInterface dtor via rowed 0x001B4E74.
// Scalar at +0x0C untouched. The 28B ??_G at 0x0022C9DA calls this,
// proving the ??1 identity and virtualness. Owner identity unproven,
// honest Rva name with public-virtual UAE like opaque siblings
// (Rva00221027). Prev 0x0022C55B and next 0x0022CD65 share no TU,
// new file beside them. EH frame with states 0/-1 matches /EHsc.
#include <list>

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	char m_pad[8];
};

class Rva0022C9F6 : public SubsystemInterface
{
public:
	virtual ~Rva0022C9F6();

private:
	int m_unk0C;
	_STL::_List_base<int, _STL::allocator<int> > m_list10;
};

Rva0022C9F6::~Rva0022C9F6()
{
}
