// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PAVRva003A6360Record@@PAV1@@_STL@@YAPAVRva003A6360Record@@PAV1@00ABU__false_type@0@@Z 0x0052C2CA 41B evidence: stride 0x10 via rowed copy ctor 0x0052BB9A; callers 0x0052C8AB 0x00565FC1; sibling Rva003A6F70UninitCopy same template
#include <vector>
class Rva003A6360Record
{
public:
	Rva003A6360Record(const Rva003A6360Record &other) throw();

	int m_vtable;
	int m_word04;
	unsigned char m_byte08;
	int m_word0C;
};
// _Construct<Rva003A6360Record> is emitted by StlportConstructCopySiblings.cpp (0x0052BD28); here it only inlines.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Construct<Rva003A6360Record, Rva003A6360Record>(Rva003A6360Record *p, const Rva003A6360Record &v) throw()
{ new (p) Rva003A6360Record(v); } }
template Rva003A6360Record *_STL::__uninitialized_copy(Rva003A6360Record *, Rva003A6360Record *, Rva003A6360Record *, const _STL::__false_type &);
