// cl: /Ireference/shims/bfmelist /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
//
// ?rva00525ABF@Rva00525ABF@@QAEXPAVXfer@@@Z, retail 0x00525ABF, 518 bytes.
// Unlock lane: missing callee of 1 free function; landing makes 0x00525E00 ready.
// Storing (IsStoring via Xfer slot 0x08) counts two lists and xfers counts plus
// ObjectID/int/int per node plus int at +0x18; loading Version(1,3) via slot
// 0x28 rebuilds both lists in temp list<BfmePod12>s with push_back
// (element zeroed once before each loop) then swaps into +0x10/+0x14, version-gated second list (>=2) and +0x18 (>=3),
// then forEach listener 0x005CC208. Layout: Rva005258E2List base 0x10 plus two
// 4-byte STL lists plus int, same as Rva00526275 ctor precedent.
#include <list>

// Retail compares these typed list nodes inline; avoid an incidental copy of
// the shared base-iterator comparator (as in NetPacket.cpp).
namespace _STL {
template <class T, class L, class R>
static __forceinline bool operator!=(const _List_iterator<T, L> &a, const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);


class Rva005258E2Listener
{
public:
	virtual void notify();
};

struct Rva005253A0Call
{
	void (Rva005258E2Listener::*notify)();
};

class Rva005258E2List
{
public:
	void forEach(void (Rva005258E2Listener::*notify)());
	void apply(const Rva005253A0Call &call);

private:
	Rva005258E2Listener **m_begin;
	Rva005258E2Listener **m_end;
	Rva005258E2Listener **m_capacity;
	unsigned int m_index;
};

// Retail hands forEach the slot-2 vcall thunk 0x005CC208 (jmp [eax+8]).
class Rva005CC208 : public Rva005258E2Listener
{
public:
	virtual void slot04();
	virtual void rva005CC208();
};

struct BfmePod12 { int a[3]; };

// Node allocation stays out of line in insert, as rowed at 0x00420B35.
template <> inline __declspec(noinline) _STL::_List_node<BfmePod12> *_STL::list<BfmePod12>::_M_create_node(const BfmePod12 &x)
{
	_Node *p = this->_M_node.allocate(1);
	_Construct(&p->_M_data, x);
	return p;
}

class Rva00525ABF : public Rva005258E2List
{
public:
	void rva00525ABF(Xfer *xfer);
private:
	_STL::list<BfmePod12> m_list10;
	_STL::list<BfmePod12> m_list14;
	int m_18;
};

void Rva00525ABF::rva00525ABF(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	if (xfer->IsStoring()) {
		int count = (int)m_list10.size();
		*xfer == count;
		for (_STL::list<BfmePod12>::iterator it = m_list10.begin(); it != m_list10.end(); ++it) {
			BfmePod12 &element = *it;
			XferObjectID(xfer, (ObjectID *)&element.a[0]);
			*xfer == element.a[1];
			*xfer == element.a[2];
		}
		int n14 = (int)m_list14.size();
		*xfer == n14;
		for (_STL::list<BfmePod12>::iterator it = m_list14.begin(); it != m_list14.end(); ++it) {
			BfmePod12 &element = *it;
			XferObjectID(xfer, (ObjectID *)&element.a[0]);
		}
		*xfer == m_18;
		return;
	}
	int count;
	*xfer == count;
	_STL::list<BfmePod12> tmp10;
	BfmePod12 v10;
	v10.a[0] = 0;
	v10.a[1] = 0;
	v10.a[2] = 0;
	for (; count > 0; --count) {
		XferObjectID(xfer, (ObjectID *)&v10.a[0]);
		*xfer == v10.a[1];
		*xfer == v10.a[2];
		tmp10.push_back(v10);
	}
	m_list10.swap(tmp10);
	_STL::list<BfmePod12> tmp14;
	if (version.m_minimum >= 2) {
		int n14;
		*xfer == n14;
		BfmePod12 v14;
		v14.a[0] = 0;
		((char *)&v14.a[1])[0] = 0;
		*(float *)&v14.a[2] = -1.0f;
		for (; n14 > 0; --n14) {
			XferObjectID(xfer, (ObjectID *)&v14.a[0]);
			tmp14.push_back(v14);
		}
	}
	m_list14.swap(tmp14);
	if (version.m_minimum >= 3) {
		*xfer == m_18;
	} else {
		m_18 = 0;
	}
	forEach(reinterpret_cast<void (Rva005258E2Listener::*)()>(&Rva005CC208::rva005CC208));
}
