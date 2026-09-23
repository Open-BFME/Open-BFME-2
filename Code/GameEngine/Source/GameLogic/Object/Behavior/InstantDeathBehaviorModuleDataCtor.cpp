// cl: /O1 /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0InstantDeathBehaviorModuleData@@QAE@XZ, retail 0x0045D176 (71 bytes).
// Frameless derived ctor over the pinned Rva00253510 intermediate base
// (0x00253510, size 0x38): the base holds the vptr (a placeholder virtual;
// the +0x38 member offset proves it, identity unknown) so the derived
// shares it without shifting, the compiler installs vtable 0x00C41F28
// before the four vector members construct through the ICF-folded
// Vector_base at 0x00211E58 (one-byte allocator temporaries on ebp). No EH:
// every subobject is trivially destructible, so the throwing base calls
// need no unwind. Element type int is a stand-in (trivial plus resolving
// through the ICF-folded int row; the ZH donor carries pointer vectors but
// the 29B body is T-independent per the folded rows; the true elements are
// unproven). Identity is the ModuleFactory registration under
// "InstantDeathBehavior" (sole-caller data factory per the superseded ctor
// pin).

#include <vector>

class Rva00253510
{
public:
	Rva00253510();
	virtual void Rva00253510_virt00();

private:
	unsigned char m_opaque[0x38 - 4];
};

class InstantDeathBehaviorModuleData : public Rva00253510
{
public:
	InstantDeathBehaviorModuleData();

private:
	_STL::vector<int> m_vec38;	// +0x38, element stand-in
	_STL::vector<int> m_vec44;	// +0x44, element stand-in
	_STL::vector<int> m_vec50;	// +0x50, element stand-in
	_STL::vector<int> m_vec5C;	// +0x5C, element stand-in
};

InstantDeathBehaviorModuleData::InstantDeathBehaviorModuleData()
	: Rva00253510()
{
}
