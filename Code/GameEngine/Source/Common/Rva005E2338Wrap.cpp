// cl: /DNDEBUG /MD
// ?rva005E2338@Rva005E2338@@QAEXH@Z @0x005E2338 57B indexed plus virtual.
// m_8->m_C[index] -> element; if element->m_20 null or its rowed getter
// 0x004E0625 (const int) 0 return; else virtual slot +0x10 on m_8->m_8
// with element->m_20 as arg. Ret 4 ignores int. Address-derived.
class Rva004E0625
{
public:
	int rva004E0625() const;
};

class Rva005E2338Elem
{
public:
	unsigned char m_pad[0x20];
	Rva004E0625 *m_20;
};

class Rva005E2338Virt;

class Rva005E2338Mid
{
public:
	unsigned char m_pad[0x170];
	Rva005E2338Elem **m_170;
};

class Rva005E2338Inner
{
public:
	unsigned char m_pad[8];
	Rva005E2338Virt *m_8;
	Rva005E2338Mid *m_C;
};

class Rva005E2338Virt
{
public:
	virtual void _s0();
	virtual void _s1();
	virtual void _s2();
	virtual void _s3();
	virtual void rva005E2338Slot(Rva004E0625 *a);
};

namespace StrategicInGameUI
{
class RegionDetailsStructuresPage
{
public:
	class Impl;
};
class RegionDetailsStructuresPage::Impl
{
public:
	class Icon;
};
}
// StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon::OnRegionDetailsStructuresIconSlotRightClicked: WorldBuilder name (StrategicInGameUIRegionDetailsStructuresPage.cpp
// line 308); a virtual, its address sits in the icon vtable at VA 0x00C77B14..18.
class StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon
{
public:
	virtual void OnRegionDetailsStructuresIconSlotRightClicked(int ignored);
protected:
	unsigned char m_pad04[8 - 4];
	Rva005E2338Inner *m_8;
	int m_C;
};

void StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon::OnRegionDetailsStructuresIconSlotRightClicked(int ignored)
{
	(void)ignored;
	Rva005E2338Elem *elem = m_8->m_C->m_170[m_C];
	Rva004E0625 *o = elem->m_20;
	if (o == 0)
		return;
	int r = o->rva004E0625();
	if (r == 0)
		return;
	Rva005E2338Inner *inner = m_8;
	Rva005E2338Virt *v = (Rva005E2338Virt *)inner->m_8;
	v->rva005E2338Slot(o);
}
