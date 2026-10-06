// cl: /DNDEBUG /MD
// stlport
//
// ?removeFromContainList@OpenContain@@UAEXPAVObject@@@Z, retail 0x00462F75 62 bytes.
// OpenContain slot 13 (offset 0x34) of vtable 0x008435E8 and 13 sibling
// Contain vtables; called by SiegeEngineContain and HordeSiegeEngineContain
// slot 13 overrides. Iterates list<int> at +0x54 comparing node data at +8
// to rider pointer value, erases match via rowed list<int>::erase 0x00438539
// and decrements count at +0x58. Same list/count pattern as
// SiegeEngineContainRiders.cpp (+0x11C/+0x120) using list<int> storing rider
// as int.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


struct Rva00462F34StateAt04
{
	unsigned char m_pad00[0x10C];
	unsigned char m_flags10C;
};

class Object
{
public:
	unsigned char m_pad00[4];
	Rva00462F34StateAt04 *m_04;
};

struct Rva00462F34Pair
{
	void *m00;
	const _STL::list<Object *> *m04;
};

template <int N> class Rva00462F34Slots : public Rva00462F34Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class Rva00462F34Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva00462F34ContainModuleInterface : public Rva00462F34Slots<70>
{
public:
	virtual void rva0046D27ASlot70(Rva00462F34Pair &pair) = 0;
};

class OpenContain
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void removeFromContainList(Object *rider);
    void rva00462F34();
private:
	unsigned char m_pad04[0x54 - 4];
	_STL::list<int> m_list54;
	int m_count58;
	unsigned char m_pad5C[0x68 - 0x5C];
	int m_count68;
};

// The Ghidra 65B body resets +0x68, gets a two-pointer range through slot 70
// on the interface at this+0x20, and walks the returned list. For each list
// value it tests bit 1 at value+4+0x10C and increments +0x68 when set. The
// slot signature and pair layout follow the rowed ContainModuleInterface
// callers; OpenContain's +0x20 interface and +0x68 field are measured by its
// matched constructor. The count's purpose and bit meaning remain unresolved.
// ?rva00462F34@OpenContain@@QAEXXZ
void OpenContain::rva00462F34()
{
	m_count68 = 0;
	Rva00462F34Pair pair;
	((Rva00462F34ContainModuleInterface *)((char *)this + 0x20))->rva0046D27ASlot70(pair);
	const _STL::list<Object *> *items = pair.m04;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *item = *it;
		if ((item->m_04->m_flags10C & 2) != 0)
			++m_count68;
	}
}

void OpenContain::removeFromContainList(Object *rider)
{
	_STL::list<int>::iterator end = m_list54.end();
	for (_STL::list<int>::iterator it = m_list54.begin(); it != end;)
	{
		if (*it == (int)rider)
		{
			it = m_list54.erase(it);
			--m_count58;
		}
		else
		{
			++it;
		}
	}
}
