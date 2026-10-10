// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
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
#include <vector>
#include "ascii_string.h"

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class RenderObjClass
{
public:
	virtual void Delete_This();
#define V(n) virtual void slot##n();
	V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31)
	virtual RenderObjClass *Get_Sub_Object_By_Name(const char *name, Int *index) const;	// slot 32 (+0x80)
	V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)
	V(100)
	virtual void Set_Hidden(Int onoff);											// slot 101 (+0x194)
#undef V
	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}
	Int m_numRefs;																// +0x04
};

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

struct SplineEffectColor
{
	float r, g, b;
};

struct SplineEffectSubObject
{
	AsciiString m_name;										// +0x00
	RenderObjClass *m_renderObj;							// +0x04
	_STL::set<Int> m_visible;								// +0x08
	_STL::vector<SplineEffectColor> m_colors;				// +0x14
};

class SplineEffect
{
public:
	virtual ~SplineEffect();
	virtual void slot01();
	virtual void slot02();
	virtual void rva004E3383(const AsciiString &subObjName, Bool visible);
private:
	Int m_04;
	Int m_08;
	Int m_0C;
	Int m_10;
	_STL::vector<SplineEffectSubObject> m_subObjects;		// +0x14
	Bool m_allVisible;										// +0x20
};

void SplineEffect::rva004E3383(const AsciiString &subObjName, Bool visible)
{
	if (!visible)
		m_allVisible = false;
	for (UnsignedInt i = 0; i < m_subObjects.size(); ++i)
	{
		if (m_subObjects[i].m_renderObj == 0)
			continue;
		Int index;
		RenderObjClass *subObj = m_subObjects[i].m_renderObj->Get_Sub_Object_By_Name(
			Rva004E2ED9Construct(Rva005F17C6Build(m_subObjects[i].m_name + ".", (int)&subObjName)).str(), &index);
		if (subObj == 0)
			continue;
		subObj->Set_Hidden(!visible);
		subObj->Release_Ref();
		_STL::set<Int>::iterator it = m_subObjects[i].m_visible.find(index);
		if (visible)
		{
			if (it == m_subObjects[i].m_visible.end())
				m_subObjects[i].m_visible.insert(index);
		}
		else if (it != m_subObjects[i].m_visible.end())
		{
			m_subObjects[i].m_visible.erase(it);
		}
	}
}
