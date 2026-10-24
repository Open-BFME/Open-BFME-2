// cl: /EHsc
// stlport
// Open-BFME: GeometryInfo copy constructor, retail 0x000FFD10.
//
// BFME's GeometryInfo is larger than the older reference declaration: it has
// two STL vectors at +0x2C and +0x38, followed by the cached extent fields.
// The first vector's 0x24-byte element contains a StringBase<char> at +0x1C;
// the second vector's 0x10-byte element contains one at +0x0C.  These are the
// two member-copy calls visible in the retail constructor.  Their owning
// StringBase<char> members are non-trivial: normal GeometryInfo destruction
// destroys the record vector through 0x000FF7D0, then the shape vector through
// 0x000FF700.  The copy constructor's unwind map destroys an already-built
// shape vector if record copying throws; each vector copy constructor owns its
// partial-construction cleanup.  Both vector destructor loops call
// releaseBuffer at 0x00887940.

#include <vector>

// The rowed vector destructor supplies the shared out-of-line body.
struct GeometryShape;
namespace _STL { template <> vector<GeometryShape, allocator<GeometryShape> >::~vector(); }
// Suppress this TU's non-retail copy of ??0?$_Vector_base@UGeometryShape@@V?$allocator@UGeometryShape@@@_STL@@@_STL@@QAE@IABV?$all:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct GeometryShape;
namespace _STL { template <> _Vector_base<GeometryShape,allocator<GeometryShape> >::_Vector_base(unsigned int,allocator<GeometryShape> const &); }
// Suppress this TU's non-retail copy of ??$_Construct@UGeometryRecord@@U1@@_STL@@YAXPAUGeometryRecord@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct GeometryRecord;
namespace _STL { template <> void _Construct<GeometryRecord,GeometryRecord>(GeometryRecord *,GeometryRecord const &); }
// Suppress this TU's copy of ??$_Construct@UGeometryShape@@U1@@_STL@@YAXPAUGeometryShape@@ABU1@@Z:
// the rowed 18B body at 0x005EA9A9 (GeometryShapeConstruct005EA9A9.cpp) serves the link.
struct GeometryShape;
namespace _STL { template <> void _Construct<GeometryShape,GeometryShape>(GeometryShape *,GeometryShape const &) throw(); }
// The record vector copy is supplied by GeometryRecordVectorCopyConstructor.cpp.
namespace _STL { template <> vector<GeometryRecord>::vector(const vector<GeometryRecord> &); }
namespace _STL { template <> _Vector_base<GeometryRecord,allocator<GeometryRecord> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUGeometryShape@@U1@V?$allocator@UGeometryShape@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct GeometryShape;
namespace _STL { template <> GeometryShape * _STLP_alloc_proxy<GeometryShape *,GeometryShape,allocator<GeometryShape> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@UGeometryShape@@V?$allocator@UGeometryShape@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct GeometryShape;
namespace _STL { template <> _Vector_base<GeometryShape,allocator<GeometryShape> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UGeometryShape@@@_STL@@QBEXPAUGeometryShape@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct GeometryShape;
namespace _STL { template <> void allocator<GeometryShape>::deallocate(GeometryShape *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

typedef bool Bool;

template <typename T>
class StringBase
{
public:
	~StringBase()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	void *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();


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
	std::vector<GeometryShape> m_shapes;
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

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?copyFrom@BfmeElem440@@QAEXPBU1@@Z=??0GeometryInfo@@QAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:?copyFrom@BfmeElemFC@@QAEXPAU1@@Z=??0GeometryInfo@@QAE@ABV0@@Z")
