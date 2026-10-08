// ?rva00136E95@@YAXPAVRva00136E95Obj@@IIPAURva00136E95Range@@@Z
// partial score=0.6 date=2026-10-08
// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva00136E95@@YAXPAURva00136E95Obj@@IIPAURva00136E95Range@@@Z @0x00136E95 170B.
// Cdecl recursive walk over an object's children: skips the add step when the
// slot-3 predicate holds or the key found in the [begin,end) AsciiString range
// (STLport find instance 0x0007983D), otherwise runs slot-5 and calls the unrowed
// member 0x00136BE7 on the returned item, then recurses over the slot-30 children
// (count from slot-28), releasing each child through its refcount at +4.
// Evidence: target only; names are address-derived.
#include <vector>
#include <algorithm>

template <typename T> class StringBase
{
public:
	int compare(const char *s) const;

protected:
	char *m_data;
};
class AsciiString : public StringBase<char> {};

namespace _STL
{
template <class I, class T> I find(I, I, const T &);
}

class Rva00136E95Item
{
public:
	void rva00136BE7();
};

class Rva00136E95Obj
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual int slot0c();
	virtual void slot10();
	virtual Rva00136E95Item *slot14(unsigned, ...);
	virtual const char *slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6c();
	virtual int slot70();
	virtual Rva00136E95Obj *slot74();
	virtual Rva00136E95Obj *slot78(int);

	int m_refs;
};

struct Rva00136E95Range
{
	AsciiString *m_begin;
	AsciiString *m_end;
};

void rva00136E95(Rva00136E95Obj *obj, unsigned a1, unsigned a2, Rva00136E95Range *range)
{
	if (!obj)
		return;
	Rva00136E95Range *r = range;
	if (!obj->slot0c())
	{
		bool found = false;
		if (r->m_begin != r->m_end)
		{
			const char *key = obj->slot18();
			found = _STL::find(r->m_begin, r->m_end, key) != r->m_end;
		}
		if (!found)
			obj->slot14(a2)->rva00136BE7();
	}
	int count = obj->slot70();
	for (int i = 0; i < count; ++i)
	{
		Rva00136E95Obj *child = obj->slot78(i);
		rva00136E95(child, a1, a2, r);
		if (child && --child->m_refs == 0)
			child->slot00();
	}
}
