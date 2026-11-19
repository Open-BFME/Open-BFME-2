// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??0GeometryInfo@@QAE@W4GeometryType@@_NMMM@Z retail 0x00050B74 183 bytes.
// GeometryInfo five-argument constructor: installs the BC4E94 vtable, default
// constructs the shape and record vectors at +0x2C/+0x38, delegates extents to
// the rowed five-argument set at 0x6BFF50, then zeroes the +0x44/+0x48 cache,
// stores the height-scaled +0x4C through the height-scale global, zeroes the
// +0x50/+0x54/+0x58 tail in order, and erases the record vector through the
// rowed 0x50AF7. Direct reuse of the BFME1 GeometryInfoConstructor.cpp donor
// (retail 0x00100580 there); the ordered volatile tail keeps the scaled height
// live on the x87 stack across the two preceding zero stores.

#include <vector>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

extern "C" float INV;

#include "../../../Include/Common/ScalarTypes.h"


#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/Enums/GeometryType.h"






#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_majorRadius;
	char m_unmodelled00c[0x0C];
	Real m_offsetZ;
	AsciiString m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
public:
	GeometryRecord &operator=(const GeometryRecord &);
};

class Xfer;

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
// bfme link decl-only begin
namespace _STL { template <> vector<GeometryRecord, allocator<GeometryRecord> >::~vector(); }
namespace _STL { template <> vector<GeometryShape, allocator<GeometryShape> >::~vector(); }
// bfme link decl-only end


class GeometryInfo : public Snapshot
{
public:
	GeometryInfo();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
	GeometryInfo(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);
	void set(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);

private:
	Bool m_isSmall;
	Real m_scalar08;
	Real m_scalar0c;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	std::vector<GeometryShape> m_shapes;
	std::vector<GeometryRecord> m_records;
	Real m_cached44;
	Real m_cached48;
	Real m_cached4c;
	Real m_cached50;
	Real m_cached54;
	Real m_cached58;
public:
	virtual ~GeometryInfo();	// rowed elsewhere; declared so this unit binds to it
};

inline GeometryInfo::GeometryInfo(GeometryType type, Bool isSmall, Real height,
	Real majorRadius, Real minorRadius)
{
	m_scalar08 = 0;
	m_scalar0c = 0;
	std::vector<GeometryRecord> *records = &m_records;
	set(type, isSmall, height, majorRadius, minorRadius);
	Real scaledHeight = *(volatile Real *)&height * 0.5f;
	m_cached44 = 0;
	m_cached48 = 0;
	m_cached4c = scaledHeight;
	m_cached50 = 0;
	m_cached54 = 0;
	m_cached58 = 0;
	records->erase(records->begin(), records->end());
}

// Native table BC4E94 slot 1 holds the shared empty post-load hook at
// 4B3FD0; the slot takes no arguments and accesses no state.
void GeometryInfo::LoadPostProcess() {}

GeometryInfo::GeometryInfo()
{
	Real dim = *(volatile Real *)&INV;
	m_scalar08 = 0;
	m_scalar0c = 0;
	set(GEOMETRY_SPHERE, true, dim, dim, dim);
}
// _INV: the global at VA 0xbc2424 is ?g_Va00BC2424@@3MA.
#pragma comment(linker, "/alternatename:_INV=?g_Va00BC2424@@3MA")

// LINK-OWNER anchor: this unit owns the 5-arg ctor row; other units emit it
// inline, so the owner must also emit a select-any (inline) copy.
#pragma inline_depth(0)
// ?bfmeEmitGeometryInfoCtor@@YAXPAVGeometryInfo@@@Z present-unmatched
void bfmeEmitGeometryInfoCtor(GeometryInfo *geometryInfo)
{
	geometryInfo->GeometryInfo::GeometryInfo(GEOMETRY_SPHERE, true, 0, 0, 0);
}
#pragma inline_depth()
