// cl: /DNDEBUG /MD
// StrategicInGameUI::RegionDetailsArmiesPage::Impl::Update (WorldBuilder name, line 496: PopulateIconSlots when dirty, release +0x28, then refresh).
// was ?rva005E1B9A@Rva005E1B9A@@QAEXXZ @0x005E1B9A 42B.
// If +0x20 byte nonzero calls pinned 0x005E1B4E (this-only void).
// Then if +0x28 dword nonzero calls pinned 0x005E19CA (this+int void) with it
// and clears +0x28. Tail-jmps to pinned 0x005EF3F6 with this+0x0C.
// Ret void via tail, this only. Address-derived.
class Rva005E1B4E
{
public:
	void rva005E1B4E();
};

class Rva005E19CA
{
public:
	void rva005E19CA(int a);
};

class Rva005EF3F6
{
public:
	void rva005EF3F6();
};

namespace StrategicInGameUI
{
class RegionDetailsArmiesPage
{
public:
	class Impl;
};
}
class StrategicInGameUI::RegionDetailsArmiesPage::Impl
{
public:
	void Update();
protected:
	unsigned char m_pad[0x20];
	unsigned char m_20;
	unsigned char m_pad2[7];
	int m_28;
};

void StrategicInGameUI::RegionDetailsArmiesPage::Impl::Update()
{
	if (m_20 != 0)
		((Rva005E1B4E *)this)->rva005E1B4E();
	int v = m_28;
	if (v == 0)
		goto tail;
	((Rva005E19CA *)this)->rva005E19CA(v);
	m_28 = 0;
tail:
	((Rva005EF3F6 *)((unsigned char *)this + 0x0C))->rva005EF3F6();
}
