// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// StrategicInGameUI::ArmyDetailsPanel::Impl::OnDestroyingArmySummary (WorldBuilder name, lines 761..762: clear the +0x1C map, reset +0x14, clear +0x2C and release +0x10).
// stlport
//
// was ?rva005E4995@Rva005E4995@@QAEXH@Z, retail 0x005E4995, 42 bytes.
// Clears map<int SBServer> at +0x1c via rowed 0x005E43A8, notifies holder at
// +0x14 via rowed 0x005F22D2, clears flag at +0x2c, erases this from list at
// [[+0x10]+0x78]+4 via rowed 0x002B7250. Evidence: callees rowed, ret 4 keeps
// the unused stack arg, this passed as CreateAHeroData* to the erase row.
#include <map>

struct SBServer
{
	void *m_handle;
};

class Rva005F22D2
{
public:
	void rva005F22D2();
};

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

struct Rva002B7250Inner
{
	int m_unk0;
	Rva002B7250 m_holder;
};

struct Rva002B7250Outer
{
	unsigned char m_pad[0x78];
	Rva002B7250Inner *m_ptr;
};

namespace StrategicInGameUI
{
class ArmyDetailsPanel
{
public:
	class Impl;
};
}
class StrategicInGameUI::ArmyDetailsPanel::Impl
{
public:
	void OnDestroyingArmySummary(int dummy);
private:
	unsigned char m_pad0[0x10];
	Rva002B7250Outer *m_outer;
	Rva005F22D2 *m_mid;
	unsigned char m_pad1[4];
	_STL::map<int, SBServer> m_map;
	unsigned char m_pad2[4];
	unsigned char m_flag;
};

void StrategicInGameUI::ArmyDetailsPanel::Impl::OnDestroyingArmySummary(int dummy)
{
	m_map.clear();
	m_mid->rva005F22D2();
	Rva002B7250Outer *outer = m_outer;
	m_flag = 0;
	outer->m_ptr->m_holder.rva002B7250((CreateAHeroData *)this);
}
