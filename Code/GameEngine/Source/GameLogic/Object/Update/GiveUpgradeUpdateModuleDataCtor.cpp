// cl: /O1 /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
//
// ??0GiveUpgradeUpdateModuleData@@QAE@XZ, retail 0x0049C4D2 (72 bytes).
// Frameless derived ctor over the pinned Rva0044EB54 intermediate base
// (0x0044EB54, size 0xC8): the base holds the vptr (a placeholder virtual;
// the +0xC8 member offset proves it, identity unknown) so the derived
// shares it without shifting, the compiler installs vtable 0x00C51280
// before the +0xC8 vector member constructs through the ICF-folded
// Vector_base at 0x00211E58 (allocator temp on esp), then the body clears
// two int slots and a flag byte and loads the +0xDC float slot from an
// extern 0.025 global (DIR32-masked like the retail global; a literal would
// emit an integer mov-imm instead of the retail literal load). No EH: every
// subobject is trivially destructible, so the throwing vector-base call
// needs no unwind. Element type int is a stand-in (trivial plus resolving
// through the ICF-folded int row; AsciiString is refuted by the missing EH
// frame; the true element is unproven). Identity is the ModuleFactory
// registration under "GiveUpgradeUpdate" (sole-caller data factory per the
// superseded ctor pin).

#include <vector>

class Rva0044EB54
{
public:
	Rva0044EB54();
	virtual void Rva0044EB54_virt00();

private:
	unsigned char m_opaque[0xC8 - 4];
};

extern float g_bfmeGiveUpgrade0025;	// 0.025 at retail 0xC5127C (DIR32-masked)

class GiveUpgradeUpdateModuleData : public Rva0044EB54
{
public:
	GiveUpgradeUpdateModuleData();

private:
	_STL::vector<int> m_vecC8;	// +0xC8, element stand-in
	int m_intD4;	// +0xD4
	int m_intD8;	// +0xD8
	float m_floatDC;	// +0xDC
	bool m_flagE0;	// +0xE0
};

GiveUpgradeUpdateModuleData::GiveUpgradeUpdateModuleData()
	: Rva0044EB54()
{
	m_floatDC = g_bfmeGiveUpgrade0025;
	m_intD4 = 0;
	m_intD8 = 0;
	m_flagE0 = false;
}
