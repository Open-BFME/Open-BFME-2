// Target boundary 0x00057B9D/191 is STLport vector::_M_insert_overflow
// false_type. Matched push_back at 0x00058A33 calls it at 0x00058A63 with the
// vector in ECX and five overflow arguments; retail advances 0x90-byte records.
// Target copy path 0x53DFE -> 0x51B40 calls 0x2D99E3 for the record prefix and
// copies the tail words at +0x88/+0x8C. Target destruction reaches matched
// BfmeStringTailRecord144::~ at 0x2D9A43 through 0x5401D and thunk 0x50FC4.
// Together these caller/copy/destruction facts establish this element identity.
// The field declaration below follows the separately verified target layout
// documented in stlport_stringtailrecord144_dtor.cpp; it is not a size guess.
// The out-of-line copy constructor is target-pinned at 0x51B40.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

template<class T> class StringBase {
	void *m_data;
	void releaseBuffer();
public:
	StringBase();
	StringBase(const StringBase &);
	StringBase &operator=(const StringBase &);
protected:
	__forceinline ~StringBase() { releaseBuffer(); }
};

class AsciiString : private StringBase<char> {
public:
	__forceinline AsciiString() {}
	__forceinline AsciiString(const AsciiString &o) : StringBase<char>(o) {}
	~AsciiString();
	AsciiString &operator=(const AsciiString &);
};

class PoolMember { public: void Rva0050ED3(); };
struct BfmePoolHolder88 { unsigned char pad[0x88]; PoolMember m_ref; };
class BfmePoolRef08 {
	PoolMember *m_target;
public:
	__forceinline ~BfmePoolRef08() { if (m_target != 0) m_target->Rva0050ED3(); }
};
class BfmePoolRef10 {
	BfmePoolHolder88 *m_target;
public:
	__forceinline ~BfmePoolRef10() { if (m_target != 0) m_target->m_ref.Rva0050ED3(); }
};

struct BfmeStringTailRecord144 {
	virtual ~BfmeStringTailRecord144();
	AsciiString m_string04;
	BfmePoolRef08 m_pool08;
	int m_int0C;
	BfmePoolRef10 m_pool10;
	int m_int14;
	int m_int18;
	AsciiString m_string1C;
	AsciiString m_string20;
	int m_data[24];
	AsciiString m_string84;
	int m_tail[2];
	BfmeStringTailRecord144(const BfmeStringTailRecord144 &);
	BfmeStringTailRecord144 &operator=(const BfmeStringTailRecord144 &);
};

typedef char VerifyRecordSize[(sizeof(BfmeStringTailRecord144) == 0x90) ? 1 : -1];

template void _STL::_Construct<BfmeStringTailRecord144, BfmeStringTailRecord144>(
	BfmeStringTailRecord144 *, const BfmeStringTailRecord144 &);
template void _STL::vector<BfmeStringTailRecord144>::_M_clear();
template void _STL::vector<BfmeStringTailRecord144>::_M_insert_overflow(
	BfmeStringTailRecord144 *, const BfmeStringTailRecord144 &,
	const _STL::__false_type &, unsigned int, bool);
