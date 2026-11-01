// cl: /O1 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??1GeometryInfo@@UAE@XZ retail 0x00050B2A 63 bytes.
// GeometryInfo destructor: destroys the record vector at 38 through the
// rowed 0x50AB8 and the shape vector at 2C through the rowed 0x50A79, then
// restores the Snapshot vtable. The members carry declared-only wrapper
// dtors so the rowed bodies resolve; the inline Snapshot base dtor performs
// the vtable restore after the members fall. novtable suppresses the entry
// vtable store retail lacks; the restore to BBB554 stays explicit. The next
// 11 bytes are a separate push-push-call-ret tail, not claimed here.


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

class Xfer;

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"


#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct GeometryRecord
{
	~GeometryRecord();

	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
};

namespace _STL
{

template <>
inline void _Destroy<GeometryRecord *>(GeometryRecord *__first, GeometryRecord *__last)
{
	for ( ; __first != __last; ++__first)
		_Destroy(&*__first);
}

}

extern "C" void _free(void *);

struct GeometryShapeVector
{
	~GeometryShapeVector();

	void *m_head[3];
};

class __declspec(novtable) GeometryInfo : public Snapshot
{
public:
	virtual ~GeometryInfo();

private:
	char m_pad04[0x28];
	GeometryShapeVector m_shapes;
	std::vector<GeometryRecord> m_records;
};
// ??1GeometryInfo@@UAE@XZ @0x00050B2A
inline GeometryInfo::~GeometryInfo()
{
}

// ??1GeometryRecord@@QAE@XZ @0x0004F82B
inline GeometryRecord::~GeometryRecord()
{
}

// ??1Rva002189C5@@QAE@XZ @0x00218803
// A second GeometryRecord vector destructor: the same 63 bytes as 0x50AB8
// (rowed _Destroy 0x217B1E, then free) under its own EH handler. The scalar
// deleting destructor 0x002189C5 and FontLibrary's map-value cleanup call it
// directly; the owning class is not established, so it keeps its address
// name and spells out the vector destructor over the vector's base.
class Rva002189C5 : public _STL::_Vector_base<GeometryRecord, _STL::allocator<GeometryRecord> >
{
public:
	~Rva002189C5();
};
Rva002189C5::~Rva002189C5()
{
	_STL::_Destroy(_M_start, _M_finish);
}

// The three bodies above are header inlines elsewhere: other units emit
// select-any copies, so strong definitions here were duplicates in the linked
// build. This anchor only makes this unit emit its copies for the ledger rows;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitGeometryInfoDtor@@YAXPAVGeometryInfo@@PAUGeometryRecord@@11@Z present-unmatched
void bfmeEmitGeometryInfoDtor(GeometryInfo *pi, GeometryRecord *pr, GeometryRecord *first, GeometryRecord *last)
{
	pi->GeometryInfo::~GeometryInfo();
	pr->GeometryRecord::~GeometryRecord();
	_STL::_Destroy(first, last);
}
#pragma inline_depth()
