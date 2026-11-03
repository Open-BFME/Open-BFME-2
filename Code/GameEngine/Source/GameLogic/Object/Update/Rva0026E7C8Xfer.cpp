// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00332975@Rva0026E7C8Ctor@@QAEXPAVXfer@@@Z, retail 0x00332975, 378 bytes.
//
// Target evidence: slot 3 (offset 0xC) of the table at VA 0x00BFA3A4 that
// ??0Rva0026E7C8Ctor stores at +0. Xfer Version1 (0x53EE), then the +4
// vector's element count (size / 12) through the int slot and reserve
// (rowed 0x33259F); per element two AsciiStrings (the second homed in the
// dead xfer argument slot). Storing: keyToName of the two element keys,
// xfer both strings, xferSTLObjectIDList (0x331F2D) on the element's +8
// list. Loading: xfer both strings, nameToKey both, push_back (0x3328B6) a
// temporary built by the rowed Rva00331EAD(int,int) ctor (0x331EAD) whose
// implicit destructor runs the pinned list destructor (0x268902), then
// reset (0x26549E) and xferSTLObjectIDList on back()'s list. Neither mode:
// only the string destructors run.
// Structural inference: Rva00331EAD is modelled as a ctor-only derivation of
// the 12-byte element and the list view derives from the
// xferSTLObjectIDList parameter type, so the rowed names stay distinct
// without pointer casts. Original class and member names are unproven.

#include "ascii_string.h"
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?push_back@?$vector@URva003328B6Element@@V?$allocator@URva003328B6Element@@@_STL@@@_STL@@Q:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003328B6Element;
namespace _STL { template <> void vector<Rva003328B6Element,allocator<Rva003328B6Element> >::push_back(Rva003328B6Element const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAURva003328B6Element@@IU1@@_STL@@YAPAURva003328B6Element@@PAU1@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003328B6Element;
namespace _STL { template <> Rva003328B6Element * __uninitialized_fill_n<Rva003328B6Element *,unsigned int,Rva003328B6Element>(Rva003328B6Element *,unsigned int,Rva003328B6Element const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAURva003328B6Element@@PAU1@@_STL@@YAPAURva003328B6Element@@PAU1@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003328B6Element;
namespace _STL { template <> Rva003328B6Element * __uninitialized_copy<Rva003328B6Element *,Rva003328B6Element *>(Rva003328B6Element *,Rva003328B6Element *,Rva003328B6Element *,__false_type const &); }
// Suppress this TU's non-retail copy of ?reserve@?$vector@URva003328B6Element@@V?$allocator@URva003328B6Element@@@_STL@@@_STL@@QAE:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<Rva003328B6Element,allocator<Rva003328B6Element> >::reserve(unsigned int); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@URva003328B6Element@@V?$allocator@URva003328B6Element@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003328B6Element;
namespace _STL { template <> void vector<Rva003328B6Element,allocator<Rva003328B6Element> >::_M_insert_overflow(Rva003328B6Element *,Rva003328B6Element const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAURva003328B6Element@@U1@V?$allocator@URva003328B6Element@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003328B6Element;
namespace _STL { template <> Rva003328B6Element * _STLP_alloc_proxy<Rva003328B6Element *,Rva003328B6Element,allocator<Rva003328B6Element> >::allocate(unsigned int); }
// Inline the allocator release so vector cleanup uses the native game free.
struct Rva003328B6Element;
namespace _STL { template <> __declspec(dllimport) __forceinline void allocator<Rva003328B6Element>::deallocate(Rva003328B6Element *p,unsigned int) const { if (p) free(p); } }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
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
class DamageInfo;

#include "../../../../Include/Common/BfmeXfer.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

struct BridgeBehaviorObjectIDNode
{
	BridgeBehaviorObjectIDNode *m_next;
	BridgeBehaviorObjectIDNode *m_prev;
	int m_value;
};

class BridgeBehaviorObjectIDList
{
public:
	BridgeBehaviorObjectIDNode *m_node;
};

Xfer *xferSTLObjectIDList(Xfer *xfer, BridgeBehaviorObjectIDList *list);

class Rva0029FB3BMember : public BridgeBehaviorObjectIDList
{
public:
	~Rva0029FB3BMember() throw();
	void reset();
};

struct Rva003328B6Element
{
	__forceinline ~Rva003328B6Element() {}
	NameKeyType m_key1;
	NameKeyType m_key2;
	Rva0029FB3BMember m_list;
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Construct<Rva003328B6Element,Rva003328B6Element>(Rva003328B6Element *p,Rva003328B6Element const &v) { new (p) Rva003328B6Element(v); } }

namespace _STL {
template <> void _Destroy<Rva003328B6Element *>(Rva003328B6Element *, Rva003328B6Element *);
}

class Rva00331EAD : public Rva003328B6Element
{
public:
	Rva00331EAD(int a, int b);
};

class Rva0026E7C8Ctor
{
public:
	Rva0026E7C8Ctor();
	void rva00332975(Xfer *xfer);

private:
	void *m_unk0;
	_STL::vector<Rva003328B6Element> m_vec;
};

void Rva0026E7C8Ctor::rva00332975(Xfer *xfer)
{
	xfer->Version1();
	int count = (int)m_vec.size();
	*xfer == count;
	m_vec.reserve(count);
	for (int i = 0; i < count; ++i)
	{
		AsciiString name1;
		AsciiString name2;
		if (xfer->IsStoring())
		{
			Rva003328B6Element &e = m_vec[i];
			name1 = TheNameKeyGenerator->keyToName(e.m_key1);
			name2 = TheNameKeyGenerator->keyToName(e.m_key2);
			*xfer == name1;
			*xfer == name2;
			xferSTLObjectIDList(xfer, &e.m_list);
		}
		else if (xfer->IsLoading())
		{
			*xfer == name1;
			*xfer == name2;
			NameKeyType key1 = TheNameKeyGenerator->nameToKey(name1);
			NameKeyType key2 = TheNameKeyGenerator->nameToKey(name2);
			m_vec.push_back(Rva00331EAD(key1, key2));
			Rva0029FB3BMember *list = &m_vec.back().m_list;
			list->reset();
			xferSTLObjectIDList(xfer, list);
		}
	}
}
