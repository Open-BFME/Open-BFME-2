// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?canUnitRotate@HordeMeleeFormation@@UAE_NH@Z retail 0x00584F6B 84B.
// VSlot 9 (offset 0x24) of vtable 0x0086FD90 (class of ??0HordeMeleeFormation@@QAE@PAX0@Z).
// Gap between ?Rva00584F37 (slot8) and ?Rva00584FBF (slot10) in Rva00586D8EVSlots.cpp.
// Bounds-checked vec84 (stride 0x54) field +0x20 vs frame at [TheGameLogic+0x40]
// OR held array at [ecx+4]+0x188 stride 0x1C field +0x18 >= 0. No callers.
#include <vector>

struct BfmeV84 { int m_00; char m_pad04[0x20 - 4]; unsigned int m_20; char m_pad24[84 - 0x20 - 4]; };
struct HeldEntry { char m_pad00[0x18]; int m_18; };
struct HeldBlock { char m_pad00[0x188]; HeldEntry* m_entries; };

struct GameLogicFrame { char m_pad00[0x40]; unsigned int m_frame; };
extern class GameLogic *TheGameLogic;

class Rva005D6FCC
{
public:
	Rva005D6FCC(void* held);
	virtual ~Rva005D6FCC();
	void* m_held;
};

class HordeMeleeFormation : public Rva005D6FCC
{
public:
	virtual ~HordeMeleeFormation();
	virtual bool canUnitRotate(int idx);
private:
	_STL::vector<BfmeV84> m_vec;
	bool m_flag;
	void* m_other;
};

bool HordeMeleeFormation::canUnitRotate(int idx)
{
	if (idx < 0 || (unsigned)idx >= m_vec.size())
		return false;
	HeldBlock* h = (HeldBlock*)m_held;
	return m_vec[idx].m_20 > (*(GameLogicFrame **)&TheGameLogic)->m_frame || h->m_entries[idx].m_18 >= 0;
}
