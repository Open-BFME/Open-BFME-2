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

extern "C" const void *const vtbl_00BBB554[];  // folded, 23 classes; via ??_7BfmeBaseVUQ@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@")

#include <vector>

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BBB554));
}

template <class T> class StringBase
{
	friend struct AsciiString;
	void releaseBuffer();
public:
	char *m_data;
};
struct AsciiString : public StringBase<char>
{
public:
	~AsciiString() { releaseBuffer(); }
};

struct GeometryRecord
{
	~GeometryRecord();

	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
};

struct GeometryShape
{
	~GeometryShape();

	char m_pad[0x24];
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

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1ClearanceTestingSlowDeathBehaviorModuleDataMember@@QAE@XZ=??1GeometryInfo@@UAE@XZ")
