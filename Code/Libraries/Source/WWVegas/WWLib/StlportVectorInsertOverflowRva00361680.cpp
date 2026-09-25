// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector::_M_insert_overflow at target boundary 0x00361680/191.
// The matched vector::push_back at 0x00361756 calls this helper. Retail uses a
// 0x94-byte element stride and calls the separately matched vector clear at
// 0x00361657; its copy/fill/allocation helpers are pinned from their own target
// call sites. The complete application element type/layout is not known.
//
// BfmeStringHeadRecord148 is only an emitter view: 148-byte size and a
// non-trivial copy trait. The target destructor/copy chain supports an
// AsciiString at offset zero, but this declaration's remaining int fields do
// not claim the retail record layout.
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
	__forceinline ~AsciiString() {}
	AsciiString &operator=(const AsciiString &);
};

struct BfmeStringHeadRecord148 { AsciiString s; int a[36]; };

namespace _STL {
template <> void _Construct<BfmeStringHeadRecord148, BfmeStringHeadRecord148>(
	BfmeStringHeadRecord148 *, const BfmeStringHeadRecord148 &);
}

template void _STL::vector<BfmeStringHeadRecord148>::_M_insert_overflow(
	BfmeStringHeadRecord148 *, const BfmeStringHeadRecord148 &,
	const _STL::__false_type &, unsigned int, bool);
