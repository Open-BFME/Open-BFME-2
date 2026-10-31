// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport placement-copy helpers and distinct native copy owners, same-shape
// siblings of the rowed _Construct<AsciiString> at 0x0002C485 (45 bytes; see
// stlport_construct_asciistring.cpp). Each body is the null-guarded
// placement-new copy over a single element: the copy delegates out-of-line
// to T's own rowed copy ctor, and __EH_prolog resolves via its matched row.
// Unlike the opaque-struct batches, these T's come from the real STLport
// headers (<vector>, and _STL::pair over a minimal AsciiString declaration):
// declaration-only copy specializations below keep the calls out-of-line
// and resolve through the complete provider rows.

#include <memory>
#include <vector>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct NoCaseTreeValue4
{
	char m_body[4];
};

#include "../../../Include/Lib/Coord3D.h"

enum ScienceType
{
	SCIENCE_INVALID = -1
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> ConstructProbePair;
typedef _STL::vector<unsigned int> ConstructProbeVec;
typedef _STL::pair<const int, _STL::vector<unsigned int> > ConstructProbePairIV;
typedef _STL::vector<ScienceType> ConstructProbeSciVec;
typedef _STL::list<Coord3D> ConstructProbeCoordList;
typedef _STL::pair<const AsciiString, char> ConstructProbePairC;

// These helpers delegate to complete copy constructors already rowed in
// their provider units. Declaration-only specializations suppress incorrect
// local copies and their allocator/container machinery, preserving the
// actual out-of-line placement-copy calls.
namespace _STL {
template <> ConstructProbeVec::vector(const ConstructProbeVec &);
template <> ConstructProbePair::pair(const ConstructProbePair &);
template <> ConstructProbePairIV::pair(const ConstructProbePairIV &);
template <> ConstructProbeSciVec::vector(const ConstructProbeSciVec &);
template <> ConstructProbeCoordList::list(const ConstructProbeCoordList &);
template <> ConstructProbePairC::pair(const ConstructProbePairC &);
}


// Native 0x396170 is called through the eight-byte element view used by
// vector::push_back at 0x39A48E and both uninitialized workers. Its complete
// construction delegates to the existing pair copy at 0x466EA7. Preserve
// that witnessed storage operation without asserting an application identity.
struct Rva0039A48EElement { int a[2]; };
namespace _STL {
template <> void _Construct<Rva0039A48EElement, Rva0039A48EElement>(
    Rva0039A48EElement *__p, const Rva0039A48EElement &__val)
{
    ::new ((void *)__p) ConstructProbePair(
        *reinterpret_cast<const ConstructProbePair *>(&__val));
}
}

template void _STL::_Construct<ConstructProbeVec, ConstructProbeVec>(ConstructProbeVec *, const ConstructProbeVec &);
template void _STL::_Construct<ConstructProbePair, ConstructProbePair>(ConstructProbePair *, const ConstructProbePair &);
template void _STL::_Construct<ConstructProbePairIV, ConstructProbePairIV>(ConstructProbePairIV *, const ConstructProbePairIV &);
template void _STL::_Construct<ConstructProbeSciVec, ConstructProbeSciVec>(ConstructProbeSciVec *, const ConstructProbeSciVec &);
template void _STL::_Construct<ConstructProbeCoordList, ConstructProbeCoordList>(ConstructProbeCoordList *, const ConstructProbeCoordList &);
template void _STL::_Construct<ConstructProbePairC, ConstructProbePairC>(ConstructProbePairC *, const ConstructProbePairC &);

// ??0Rva0023FD06@@QAE@ABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z,
// retail 0x0023FC98..0x0023FCD3 (59 bytes, EH, RET 4): a counted holder of one
// such pair. The counted base (count at +0x04 cleared; EH state 0 once built)
// comes first, then the vtable 0x00BEDC94 and the pair copied into +0x08
// through its rowed out-of-line copy constructor 0x00466EA7.
// Vtable 0x00BEDC94 is Rva0023FD06Dtor.cpp's class: its slot 0 is the rowed
// scalar deleting dtor 0x0023FCEA (calling the rowed dtor 0x0023FD06) and its
// slot 1 the rowed 0x0023FCD3. Use that name so the dtor binds to its row.
#include "../../../../GameEngine/Include/Common/Rva0007DF07.h"

class Rva0023FD06 : public Rva0007DF07
{
public:
	Rva0023FD06(const ConstructProbePair &value);
	virtual ~Rva0023FD06();
	virtual int rva0023FCD3(float a, int b);
private:
	ConstructProbePair m_value;
};

Rva0023FD06::Rva0023FD06(const ConstructProbePair &value)
	: m_value(value)
{
}


// Distinct native copy helpers. Two-pointer ABI is proven; original signatures remain unknown.
void Rva0007975EConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePairIV(*static_cast<const ConstructProbePairIV *>(source));
}

void Rva001DD745Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva0020596AConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva0020D5E6Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva0020F321Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva00211F6DConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva0022112DConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva00222DBFConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva0023FC6BConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva002CF954Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva002FE87DConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva00317CA0Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva0031BDC1Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva0032ACFCConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva0035CA02Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva003EEFDBConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva004151EBConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva0041FA07Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva00467763Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva0049DD0BConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva004C3A9FConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva0052B6ACConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePair(*static_cast<const ConstructProbePair *>(source));
}

void Rva003F1A5FConstruct(void *dest, const void *source)
{
    ::new (dest) ConstructProbeVec(*static_cast<const ConstructProbeVec *>(source));
}

void Rva00460F18Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbeVec(*static_cast<const ConstructProbeVec *>(source));
}

void Rva001E7243Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePairIV(*static_cast<const ConstructProbePairIV *>(source));
}

void Rva00511CB9Construct(void *dest, const void *source)
{
    ::new (dest) ConstructProbePairC(*static_cast<const ConstructProbePairC *>(source));
}
