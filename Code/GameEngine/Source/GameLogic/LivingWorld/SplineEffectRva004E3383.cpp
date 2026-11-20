// cl: /D_OPERATOR_NEW_DEFINED_ /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
//
// ?rva004E3383@SplineEffect@@UAEXABVAsciiString@@_N@Z retail 0x004E3383..0x004E34B1
// (302 bytes, EH, RET 8).
//
// Identity:
// - It is slot 3 of the three SplineEffect vtables 0x00862054 / 0x00862070 /
//   0x0086208C (??_7Rva004E3CD0 / Rva004E3D2A / Rva004E3D47), beside the
//   ParseGeometryName / ParseINIBlock strings.
// - Slot 4 is 0x004E34B1, the sub-object colour setter that
//   SplineEffectStringMaterialize_Rva004E2ED9.cpp names. It walks the same
//   32-byte entries and builds the same "<entry name>.<sub-object name>"
//   string.
// - The original method name is unknown, so it is address-named.
//
// What the body does:
// - Hiding anything clears the all-visible byte at +0x20.
// - For each entry (vector at +0x14) with a render object at +4, it:
//   - builds the full name through the rowed operator+ 0x000B49C5,
//     Rva005F17C6Build 0x005F17C6 and Rva004E2ED9Construct 0x004E2ED9;
//   - looks the sub-object up (render object slot 32, which also returns the
//     index);
//   - sets it hidden or shown (slot 101) and releases it;
//   - inserts the index into, or erases it from, the entry's set<int> at +8
//     (pinned _M_find 0x00388F63, rowed set<int>::insert 0x000BC15D, pinned
//     erase 0x005530A8).
// - Each set access re-evaluates m_subObjects[i], as retail does.
#include <set>
namespace _STL {
typedef _Rb_tree<int,int,_Identity<int>,less<int>,allocator<int> > NativeIntTree;
typedef _Rb_tree_iterator<int,_Nonconst_traits<int> > NativeIntIterator;
template <> __declspec(dllimport) __forceinline NativeIntIterator::_Rb_tree_iterator(const NativeIntIterator &p) { _M_node=p._M_node; }
template <> __declspec(dllimport) __forceinline int &NativeIntTree::_S_value(_Rb_tree_node<int> *p) { return p->_M_value_field; }
template <> __declspec(dllimport) __forceinline const int &NativeIntTree::_S_key(_Rb_tree_node<int> *p) { return _Identity<int>()(_S_value(p)); }
}

#include <vector>
#include "ascii_string.h"

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

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

#include "../../../Include/Common/ScalarTypes.h"



#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

struct Rva005F17C6S12
{
	int m0, m1, m2;
};
struct AsciiStringPlusText : Rva005F17C6S12
{
};
AsciiStringPlusText operator+(const AsciiString &lhs, const char *rhs);
struct Rva0020F58E
{
	int storage[4];
	operator AsciiString();
};
struct Rva005F17C6S16 : Rva0020F58E
{
};
Rva005F17C6S16 Rva005F17C6Build(const Rva005F17C6S12 &src, int v);
AsciiString Rva004E2ED9Construct(Rva0020F58E &value);

struct Rva004E34B1Color { float red,green,blue; };

struct SplineGeometry
{
    AsciiString name;
    RenderObjClass *render;
    _STL::set<int> subobjects;
    _STL::vector<Rva004E34B1Color> colors;
};

struct Rva00064390;

class Rva00064880Tree {public:
    bool atEnd(unsigned);
    bool rva005042F2(unsigned,Rva00064390 *);
    void *header;
    unsigned count,unknown08;
};

class SplineEffect
{
public:
    virtual ~SplineEffect();
    virtual void unused1();
    virtual void rvaSlot2(int);
    virtual void rva004E3383(const AsciiString &subObjName, Bool visible);
    void Execute();
    void SetSubObjectColor(const AsciiString &,const Rva004E34B1Color &);
private:
    Rva00064880Tree curve;
    unsigned frame;
    _STL::vector<SplineGeometry> geometry;
    Bool m_allVisible;
};

void SplineEffect::rva004E3383(const AsciiString &subObjName, Bool visible)
{
	if (!visible)
		m_allVisible = false;
	for (UnsignedInt i = 0; i < geometry.size(); ++i)
	{
		if (geometry[i].render == 0)
			continue;
		Int index;
		RenderObjClass *subObj = geometry[i].render->Get_Sub_Object_By_Name(
			Rva004E2ED9Construct(Rva005F17C6Build(geometry[i].name + ".", (int)&subObjName)).str(), &index);
		if (subObj == 0)
			continue;
		subObj->Set_Hidden(!visible);
		subObj->Release_Ref();
		_STL::set<Int>::iterator it = geometry[i].subobjects.find(index);
		if (visible)
		{
			if (it == geometry[i].subobjects.end())
				geometry[i].subobjects.insert(index);
		}
		else if (it != geometry[i].subobjects.end())
		{
			geometry[i].subobjects.erase(it);
		}
	}
}
