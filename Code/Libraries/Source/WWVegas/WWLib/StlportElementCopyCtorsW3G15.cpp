// cl: /MD
// ??0Rva004C734DElement@@QAE@ABU0@@Z @0x004C7330 29B via 0x001F206E
// ??0Rva004F868AElement@@QAE@ABU0@@Z @0x004F802C 29B via 0x004F69D6
// ??0?$pair@$$CBHURva00501776@@@_STL@@QAE@ABU01@@Z @0x00501DD4 29B via 0x005017B4
// ??0Rva00502667Element@@QAE@ABU0@@Z @0x005020AF 29B via 0x00501B33
// ??0?$pair@$$CBHURva00501656@@@_STL@@QAE@ABU01@@Z @0x00502909 29B via 0x005026EE
// ??0Rva00557C90Element@@QAE@ABU0@@Z @0x005564EB 29B via 0x0038630B
// Six 29-byte element copy constructors called by the rowed _Construct
// siblings in StlportConstructFamilyW3G15.cpp (found by family_scan --wide
// as an operand-shape family). Each copies the leading int, then tail-copies
// the +4 subobject through its pinned copy constructor. The element names
// reuse the pinned placeholder spellings the _Construct rows already
// reference, so those rows resolve unchanged; the subobject types stay
// address-named placeholders and no layout beyond int-plus-subobject is
// claimed. The sibling TU's minimal element views are intentionally not
// touched: its _Construct bodies only pass pointers through.
// Two of the elements are STLport pair<const int, S> of the LivingWorld AI
// records GatherWorldInformation (0x0050366B) builds: S = Rva00501656
// (0x58 region record, copy 0x005026EE) and S = Rva00501776 (0x2C player
// record, copy 0x005017B4). Each is the value type of the int-keyed tree
// whose _M_create_node reaches it through _Construct (0x00502EA4 -> 0x00502C53,
// 0x00502645 -> 0x00502082), so they are declared here as that pair.
namespace _STL
{
template <class T1, class T2> struct pair;
}
struct Rva004C7330Sub
{
	Rva004C7330Sub(const Rva004C7330Sub &o);
};

struct Rva004C734DElement
{
	int m_00;
	Rva004C7330Sub m_04;
	Rva004C734DElement(const Rva004C734DElement &o);
};

Rva004C734DElement::Rva004C734DElement(const Rva004C734DElement &o)
	: m_00(o.m_00)
	, m_04(o.m_04)
{
}

struct Rva004F802CSub
{
	Rva004F802CSub(const Rva004F802CSub &o);
};

struct Rva004F868AElement
{
	int m_00;
	Rva004F802CSub m_04;
	Rva004F868AElement(const Rva004F868AElement &o);
};

Rva004F868AElement::Rva004F868AElement(const Rva004F868AElement &o)
	: m_00(o.m_00)
	, m_04(o.m_04)
{
}

struct Rva00501776
{
	Rva00501776(const Rva00501776 &o);
};

namespace _STL
{
template <> struct pair<const int, Rva00501776>
{
	const int first;
	Rva00501776 second;
	pair(const pair &o);
};
}

_STL::pair<const int, Rva00501776>::pair(const _STL::pair<const int, Rva00501776> &o)
	: first(o.first)
	, second(o.second)
{
}

struct Rva005020AFSub
{
	Rva005020AFSub(const Rva005020AFSub &o);
};

struct Rva00502667Element
{
	int m_00;
	Rva005020AFSub m_04;
	Rva00502667Element(const Rva00502667Element &o);
};

Rva00502667Element::Rva00502667Element(const Rva00502667Element &o)
	: m_00(o.m_00)
	, m_04(o.m_04)
{
}

struct Rva00501656
{
	Rva00501656(const Rva00501656 &o);
};

namespace _STL
{
template <> struct pair<const int, Rva00501656>
{
	const int first;
	Rva00501656 second;
	pair(const pair &o);
};
}

_STL::pair<const int, Rva00501656>::pair(const _STL::pair<const int, Rva00501656> &o)
	: first(o.first)
	, second(o.second)
{
}

struct Rva005564EBSub
{
	Rva005564EBSub(const Rva005564EBSub &o);
};

struct Rva00557C90Element
{
	int m_00;
	Rva005564EBSub m_04;
	Rva00557C90Element(const Rva00557C90Element &o);
};

Rva00557C90Element::Rva00557C90Element(const Rva00557C90Element &o)
	: m_00(o.m_00)
	, m_04(o.m_04)
{
}

struct Rva0050245DElement
{
	int m_00;
	Rva005020AFSub m_04;
	Rva0050245DElement(const int &a, const Rva005020AFSub &b);
};

Rva0050245DElement::Rva0050245DElement(const int &a, const Rva005020AFSub &b)
	: m_00(a)
	, m_04(b)
{
}
