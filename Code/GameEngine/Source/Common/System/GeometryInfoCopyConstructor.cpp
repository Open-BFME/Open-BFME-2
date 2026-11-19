// cl: /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /MD /D_CRTIMP= /Ireference/shims/bfmealloc /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc-
// stlport
// GeometryInfo copy constructor, native929E8/173B.
// EHsc- matches the native lifecycle provider: C free() is not assumed
// nonthrowing, preserving the observed vector-base unwind-state reset.
// This unit uses the actual owning record view for member2C; the old
// mutable5EA9BB GeometryShape helper stays an independent legacy family.
//
// Retail owns two vectors at2C and38 and cached scalar fields from44.
// The first uses the proved36-byte owning record; the second's16-byte
// element has a string atC. Native copy929E8 calls their separate providers.
// Its cleanup graph destroys an already-built first vector if the second
// copy fails; the first vector's destructor is the verified50A79 family.

#include <vector>

// The rowed vector destructor supplies the shared out-of-line body.
struct GeometryShape;
namespace _STL { template <> vector<GeometryShape, allocator<GeometryShape> >::~vector(); }
// Suppress this TU's non-retail copy of ??0?$_Vector_base@UGeometryShape@@V?$allocator@UGeometryShape@@@_STL@@@_STL@@QAE@IABV?$all:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _Vector_base<GeometryShape,allocator<GeometryShape> >::_Vector_base(unsigned int,allocator<GeometryShape> const &); }
// Suppress this TU's non-retail copy of ??$_Construct@UGeometryRecord@@U1@@_STL@@YAXPAUGeometryRecord@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct GeometryRecord;
namespace _STL { template <> void _Construct<GeometryRecord,GeometryRecord>(GeometryRecord *,GeometryRecord const &); }
// Independent legacy5EA9xx placement-copy contract; keep its existing
// throw() declaration for the separately retained mutable38-byte helper.
namespace _STL { template <> void _Construct<GeometryShape,GeometryShape>(GeometryShape *,GeometryShape const &) throw(); }
// The record vector copy is supplied by GeometryRecordVectorCopyConstructor.cpp.
namespace _STL { template <> vector<GeometryRecord>::vector(const vector<GeometryRecord> &); }
// Existing legacy private declaration; actual member2C uses the coherent
// BfmeStringRecord vector declaration below, whose native copy is9292B.
namespace _STL { template <> vector<GeometryShape>::vector(const vector<GeometryShape> &); }
namespace _STL { template <> _Vector_base<GeometryRecord,allocator<GeometryRecord> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUGeometryShape@@U1@V?$allocator@UGeometryShape@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> GeometryShape * _STLP_alloc_proxy<GeometryShape *,GeometryShape,allocator<GeometryShape> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@UGeometryShape@@V?$allocator@UGeometryShape@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _Vector_base<GeometryShape,allocator<GeometryShape> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UGeometryShape@@@_STL@@QBEXPAUGeometryShape@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void allocator<GeometryShape>::deallocate(GeometryShape *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

#include "../../../Include/Common/ScalarTypes.h"

#include "ascii_string.h"


struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	char m_unmodelled00c[0x0C];
	float m_offsetZ;
	StringBase<char> m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];
};

struct BfmeStringRecord00063BE4 {
    unsigned int word0, word1, word2, word3, word4, word5, word6;
    AsciiString text;
    unsigned char tail0, tail1;
    BfmeStringRecord00063BE4();
    BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &);
    ~BfmeStringRecord00063BE4();
    BfmeStringRecord00063BE4 &operator=(const BfmeStringRecord00063BE4 &);
};
namespace _STL { template <> vector<BfmeStringRecord00063BE4>::vector(const vector<BfmeStringRecord00063BE4> &); }

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	StringBase<char> m_name;
};

// The malloc-backed retail allocator release is rowed in GeometryInfoDtor.cpp.
// Keep this unit from supplying the node-allocator implementation at that name.
namespace _STL { template <> void allocator<GeometryRecord>::deallocate(GeometryRecord *, size_t) const; }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Xfer;

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
class GeometryInfo : public Snapshot
{
public:
	GeometryInfo(const GeometryInfo &other);
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
private:
	Bool m_isSmall;
	int m_scalar08;
	int m_scalar0c;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	std::vector<BfmeStringRecord00063BE4> m_shapes;
	std::vector<GeometryRecord> m_records;
	int m_cached44;
	int m_cached48;
	int m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;
public:
	virtual ~GeometryInfo();	// rowed elsewhere; declared so this unit binds to it
};

GeometryInfo::GeometryInfo(const GeometryInfo &other)
	: Snapshot(other),
	  m_isSmall(other.m_isSmall),
	  m_scalar08(other.m_scalar08),
	  m_scalar0c(other.m_scalar0c),
	  m_scalar10(other.m_scalar10),
	  m_scalar14(other.m_scalar14),
	  m_scalar18(other.m_scalar18),
	  m_scalar1c(other.m_scalar1c),
	  m_scalar20(other.m_scalar20),
	  m_scalar24(other.m_scalar24),
	  m_scalar28(other.m_scalar28),
	  m_shapes(other.m_shapes),
	  m_records(other.m_records),
	  m_cached44(other.m_cached44),
	  m_cached48(other.m_cached48),
	  m_cached4c(other.m_cached4c),
	  m_cached50(other.m_cached50),
	  m_cached54(other.m_cached54),
	  m_cached58(other.m_cached58)
{
}

// The mutable-source shape range copy (retail 0x005EA9BB, the callee of
// _M_insert_overflow 0x005EB379) is rowed here; the vector copy, supplied
// elsewhere, calls the const-source instantiation at 0x00064289 instead.
template GeometryShape *_STL::__uninitialized_copy<GeometryShape *, GeometryShape *>(
	GeometryShape *, GeometryShape *, GeometryShape *, const _STL::__false_type &);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?copyFrom@BfmeElem440@@QAEXPBU1@@Z=??0GeometryInfo@@QAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:?copyFrom@BfmeElemFC@@QAEXPAU1@@Z=??0GeometryInfo@@QAE@ABV0@@Z")
