// cl: /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Fix over the banked 0.93 attempt, from the retail unwind map: five states,
// the first two destroying real vector members at +0x04 and +0x10 (folded
// _Vector_base dtor 0x0047FAB3), then the strings at +0x54/+0x58/+0x5C. The
// attempt had folded the two vectors into a forceinline base destructor, which
// dropped their states. The element type of the two vectors is not known from
// this body (only their storage is freed); void * stands in.
// ??1Rva0040AFF3@@QAE@XZ retail 0x0040AFF3 117B
// Evidence: EH dtor releases StringBase<D> at +0x60 +0x5C +0x58 +0x54 via 0x00036410 then frees +0x10 +0x4 via 0x00030830; deleting dtor caller 0x0040B2E1; precedent Rva002E5791Dtor
template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


#include <vector>

struct Rva0040AFF3
{
	int m_00;
	_STL::vector<void *> m_vec04;
	_STL::vector<void *> m_vec10;
	char m_pad1C[0x54 - 0x1C];
	StringBase<char> m_str54;
	StringBase<char> m_str58;
	StringBase<char> m_str5C;
	StringBase<char> m_str60;
// ??1Rva0040AFF3@@QAE@XZ @0x0040AFF3
	~Rva0040AFF3();
};

Rva0040AFF3::~Rva0040AFF3()
{
}
