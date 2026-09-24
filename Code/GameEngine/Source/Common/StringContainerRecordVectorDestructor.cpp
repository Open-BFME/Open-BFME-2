// cl: /O1 /Ob2 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Owning vector teardown for BfmeContainerRecord00048139 at 0x004B193.
// The three sibling bodies live in StringContainerRecordVector.cpp
// (record dtor 0x00470A0, _Destroy range 0x004A9F3, owning range 0x004B205).
// This TU instantiates the STLport vector itself: EH frame over the
// _Destroy call through rowed 0x004A9F3 plus the conditional buffer free
// through rowed _free at 0x0030830. Retail carries the extra
// `or [ebp-4],-1` state store that /EHsc omits; /GX emits it (63 bytes).
// Split from the sibling TU per the per-function-flags law: the sibling
// stays /EHsc green, this shard takes /GX.
#include <vector>

template <typename T> class StringBase {
	StringBase(const StringBase &);
	~StringBase();
	void *m_data;
};

class AsciiString : private StringBase<char> {
public:
	~AsciiString();
};

struct BfmeContainerRecord00048139 {
	AsciiString text0;
	AsciiString text1;
	unsigned char m_pad[0x5C - 8];
	BfmeContainerRecord00048139();
	BfmeContainerRecord00048139(const BfmeContainerRecord00048139 &other);
	~BfmeContainerRecord00048139();
};

BfmeContainerRecord00048139::~BfmeContainerRecord00048139()
{
}

// ??1?$vector@UBfmeContainerRecord00048139@@V?$allocator@UBfmeContainerRecord00048139@@@_STL@@@_STL@@QAE@XZ @0x004B193
template class _STL::vector<BfmeContainerRecord00048139, _STL::allocator<BfmeContainerRecord00048139> >;
