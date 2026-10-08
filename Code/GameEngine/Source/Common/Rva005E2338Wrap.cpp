// cl: /O1 /DNDEBUG /MD
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

// The icon's counted help handle (assignment 0x002174A4, release 0x0007DEEF)
// and its two builders: the pinned 0x0056BB8C from the element's +0x20
// object, and 0x0056BC3D (WorldBuilder StrategicInGameUI::CreateHelpFor)
// from the element itself; both return the handle by value.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};
struct RvaF6Ret
{
	~RvaF6Ret()
	{
		if (m_ptr != 0)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	operator const TreeHintRef00217D4C &() const { return *(const TreeHintRef00217D4C *)this; }
	TargetRef00217D4C *m_ptr;
};
struct RvaF6Ret __cdecl Helper0056BB8C(int value);

class Rva005E2338Mid
{
public:
	unsigned char m_pad[0x170];
	Rva005E2338Elem **m_170;
};

namespace StrategicInGameUI
{
RvaF6Ret __cdecl CreateHelpFor(const Rva005E2338Elem *element);
}

// The help box (WorldBuilder InGameHelpBox::Show at 0x001FF3A9, pinned).
class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &help);
};

class Rva005E2338Inner
{
public:
	unsigned char m_pad[8];
	Rva005E2338Virt *m_8;
	Rva005E2338Mid *m_C;
	Rva001FF3A9 *m_helpBox; // +0x10
	unsigned char m_pad14[0x24 - 0x14];
	int m_24; // the clicked icon's index
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
	virtual void OnRegionDetailsStructuresIconSlotLeftClicked(int ignored);
	virtual void OnRegionDetailsStructuresIconSlotRightClicked(int ignored);
	virtual void OnRegionDetailsStructuresIconSlotRollOver(int ignored);
	virtual void OnRegionDetailsStructuresIconSlotTypeRollOut(int ignored);
protected:
	unsigned char m_pad04[8 - 4];
	Rva005E2338Inner *m_8;
	int m_C;
	TreeHintRef00217D4C m_help; // +0x10
	bool m_14;
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

// Retail 0x005E215E (12 B), vtable 0x00877B04 slot 3 (WorldBuilder
// OnRegionDetailsStructuresIconSlotLeftClicked): the page records this
// icon's index (+0x0C) at +0x24.
void StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon::OnRegionDetailsStructuresIconSlotLeftClicked(int ignored)
{
	m_8->m_24 = m_C;
}

// Retail 0x005E216A (7 B), slot 7 (WorldBuilder
// OnRegionDetailsStructuresIconSlotTypeRollOut): clears +0x14.
void StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon::OnRegionDetailsStructuresIconSlotTypeRollOut(int ignored)
{
	m_14 = false;
}

// Retail 0x005E23A6 (147 B), slot 6 (WorldBuilder
// OnRegionDetailsStructuresIconSlotRollOver): builds the icon's help from
// its element's +0x20 object when set, else from the element, and shows it
// in the page's help box.
void StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon::OnRegionDetailsStructuresIconSlotRollOver(int ignored)
{
	Rva005E2338Elem *element = m_8->m_C->m_170[m_C];
	if (element->m_20)
		m_help = Helper0056BB8C((int)element->m_20);
	else
		m_help = CreateHelpFor(element);
	m_8->m_helpBox->rva001FF3A9(m_help);
}
