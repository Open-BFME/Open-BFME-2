// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00546A78@SynchronizeGroupOrder@@UAEXH@Z @0x00546A78 72B evidence: vslot slot 4 offset 0x10 of vtable 0x0086A314 class of ??1SynchronizeGroupOrder; bool at +0x24 early-out; set<int> at +0x18 built from base int range at +0x4..+0x8 via rowed set<int>::insert 0x000BC15D then key erase via rowed Rva002EE9B7::rva0046EDEF 0x0046EDEF.
#include <set>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
typedef _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> > Lk11RbIntSet;
template <> pair<Lk11RbIntSet::iterator, bool> Lk11RbIntSet::insert_unique(const int &);
}
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef _STL::set<int> SetInt;

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

class GroupOrder
{
public:
	virtual ~GroupOrder();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	int *m_04; // +4 range begin
	int *m_08; // +8 range end
	void *m_0C; // +0xC storage end
	void *m_10; // +0x10
	void *m_14; // +0x14
};

class Rva002EE9B7
{
public:
	unsigned int rva0046EDEF(const int &x);
	~Rva002EE9B7();
private:
	void *m_header; // +0x00
	int m_flag; // +0x04
};

class SynchronizeGroupOrder : public GroupOrder
{
public:
	virtual ~SynchronizeGroupOrder();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	virtual void rva00546A78(int val);
	virtual bool rva005468AB(int unused);
	virtual unsigned int rva00546AC0(int val);
private:
	SetInt m_18; // +0x18
	bool m_24; // +0x24
};

void SynchronizeGroupOrder::rva00546A78(int val)
{
	if (m_24)
		return;
	if (m_18.empty())
	{
		for (int *p = m_04; p != m_08; ++p)
			m_18.insert(*p);
	}
	reinterpret_cast<Rva002EE9B7 *>(&m_18)->rva0046EDEF(val);
}

// ?rva005468AB@SynchronizeGroupOrder@@UAE_NH@Z @0x005468AB 16B: slot 5 of
// 0x00C6A314. Once the +0x18 set has emptied the +0x24 flag latches; returns
// the flag. The int argument is unused (ret 4).
bool SynchronizeGroupOrder::rva005468AB(int unused)
{
	if (m_18.empty())
		m_24 = true;
	return m_24;
}

// ?rva00546AC0@SynchronizeGroupOrder@@UAEIH@Z @0x00546AC0 16B: slot 6 of
// 0x00C6A314. Erases the key from the +0x18 set through the same rowed
// erase(const key &) 0x0046EDEF slot 4 uses, returning its count.
unsigned int SynchronizeGroupOrder::rva00546AC0(int val)
{
	return reinterpret_cast<Rva002EE9B7 *>(&m_18)->rva0046EDEF(val);
}
