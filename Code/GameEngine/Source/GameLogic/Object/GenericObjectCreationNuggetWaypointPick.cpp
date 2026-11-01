// cl: /O1 /G7 /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// stlport
//
// ObjectCreationList.cpp bodies around GenericObjectCreationNugget::reallyCreate
// (retail 0x001F1634): the vector<Object*> base destructor at 0x001F1609 and the
// waypoint pick at 0x001F21E8 (WB 0xB082D0, ObjectCreationList.cpp line 1973).
//
// Target evidence:
//   0x001F1609  43 B, __thiscall, no frame; frees [this] through the bfmealloc
//               free path when the start pointer is set. Called through the
//               5-byte thunk 0x001F22A3 (which also tears down reallyCreate's
//               result) and from the unwind funclet 0x0076B1A1.
//   0x001F21E8  187 B, __thiscall, ret 4, own EH frame (handler 0x0076B1C0,
//               unwind map: 0 = allocator temporary -> 0x000B3FD0 empty ret,
//               1 and 2 = the matches vector through 0x001F22A3). Walks
//               TheTerrainLogic's waypoints (vftable +0x84 first, +0x1C next),
//               keeps those whose name (+0x08) starts with the nugget's
//               +0x10C string, picks one with GameLogicRandomValue (line 1973)
//               and copies its location (+0x0C) into the argument. Its only
//               caller is reallyCreate (0x001F1C01).
//
// Structural inference: state 0 is a get_allocator temporary whose destructor
// c1 does not treat as nothrow-trivial. This unit is /EHs (free may throw)
// with the allocator destructor spelled as disabled leak bookkeeping, the same
// model as the matched rows 0x0000B3C0 and 0x0000BE50; c2 empties it and it
// folds into the empty 0x000B3FD0 that retail's unwind map names. EA replaced
// the STLport allocator (reference/shims/bfmealloc/README), so the stock
// trivially-empty destructor is not the retail one. Known conflict: the matched
// copy ctor 0x001F206E (ObjectCreationListVectorCopy.cpp, /EHsc) gives its
// allocator temporary no state, so the model stays local to this unit.
#include <vector>
#include "ascii_string.h"
#include "Lib/Coord3D.h"

class Object;

namespace _STL {
enum { _STLP_LEAKS_CHECK = 0 };
template <> allocator<Object *>::~allocator() _STLP_NOTHROW { if (_STLP_LEAKS_CHECK) free(this); }
template <> _STLP_alloc_proxy<Object **, Object *, allocator<Object *> >::_STLP_alloc_proxy(const allocator<Object *> &a, Object **p);
template <> __forceinline _Vector_base<Object *, allocator<Object *> >::_Vector_base(const allocator<Object *> &a)
	: _M_start(0), _M_finish(0), _M_end_of_storage(a, (Object **)0) {}
template <> __forceinline vector<Object *>::vector(const allocator<Object *> &a) : _Vector_base<Object *, allocator<Object *> >(a) {}
template <> void vector<Object *>::push_back(Object *const &);
// Retail calls the vector destructor out of line (0x001F22A3) from the body and its unwind.
template <> inline __declspec(noinline) vector<Object *>::~vector() { _Destroy(this->_M_start, this->_M_finish); }
}

template _STL::_Vector_base<Object *, _STL::allocator<Object *> >::~_Vector_base();

class Waypoint
{
public:
	const StringBase<char> &getName() const { return m_name; }
	const Coord3D *getLocation() const { return &m_location; }
	Waypoint *getNext() const { return m_next; }
private:
	char m_pad00[8];
	StringBase<char> m_name;	// +0x08
	Coord3D m_location;	// +0x0C
	char m_pad18[4];
	Waypoint *m_next;	// +0x1C
};

#include "../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class GenericObjectCreationNugget
{
protected:
	void rva001F21E8(Coord3D *position) const;
private:
	char m_pad00[0x10C];
	StringBase<char> m_waypointNamePrefix;	// +0x10C
};

// Pick a random waypoint whose name starts with the nugget's prefix and move
// the position there; leave it alone when none does. WB's debug build gives the
// matches vector its own push_back (0xB09BD0, reallyCreate's is 0xB096D0), so
// the source element type is not Object*; retail folds both copies into
// 0x001F211B. Retail passes the loop variable itself to push_back, so the loop
// variable has the element type; both are spelled Object* here. The names are
// tested through StringBase<char>::startsWith(const StringBase &) (0x00035FB0),
// not the AsciiString shim's inline overload.
void GenericObjectCreationNugget::rva001F21E8(Coord3D *position) const
{
	_STL::vector<Object *> matches;
	for (Object *way = (Object *)TheTerrainLogic->getFirstWaypoint(); way; way = (Object *)((Waypoint *)way)->getNext()) {
		if (((Waypoint *)way)->getName().startsWith(m_waypointNamePrefix))
			matches.push_back(way);
	}
	int count = matches.size();
	if (count > 0) {
		int index = GetGameLogicRandomValue(0, count - 1,
			(char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 1973);
		*position = *((Waypoint *)matches[index])->getLocation();
	}
}
