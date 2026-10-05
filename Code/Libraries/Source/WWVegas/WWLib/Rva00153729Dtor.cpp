// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00153729@@QAE@XZ, retail 0x00153729, 19 bytes.
// Holder size 0x4C with array[6] of vector<Rva005F8F96> at +4 torn down via ehvec dtor 0x629110.
// Evidence: push 0x1536EA vector dtor push 6 push 0xC add ecx 4 push ecx call ehvec ret; callers are Destroy loop 0x153BB6 stride 0x4C and deleting-dtor-like 0x15388C; ctor sibling 0x1538A8 zeroes +0 then ehvec ctor count 6 size 0xC.
#include <vector>
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
struct Rva005F8F96
{
	~Rva005F8F96();
	TargetRef00217D4C *m_00;
	int m_04;
};
namespace _STL { template<> vector<Rva005F8F96>::vector(const vector<Rva005F8F96>&); }
struct Rva00153729
{
	~Rva00153729();
	Rva00153729();
	int m_00;
	_STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> > m_04[6];
};
Rva00153729::~Rva00153729()
{
}
Rva00153729::Rva00153729() : m_00(0)
{
}

#include <new>
#pragma inline_depth(0)
// ?SolArrayCopyAnchor absent-from-retail
void* SolArrayCopyAnchor(void*p,const Rva00153729&s) {return new(p) Rva00153729(s);}
#pragma inline_depth()

// Implicit record copy constructor: native 0015375A..00153786, ret4,
// 44B. Copies key at+0 then EH array-copy helper for six 12B vectors.
// Both callback addresses are target ABS32 operands: vector destructor
// 001536EA and vector copy constructor0015350A. Use that kept provider
// rather than emitting the differing93B container copy from this TU.
// The anchor only emits the compiler-generated constructor; not retail.
#pragma comment(linker, "/alternatename:??0?$vector@URva005F8F96@@V?$allocator@URva005F8F96@@@_STL@@@_STL@@QAE@ABV01@@Z=??0?$vector@URva00153A27Element@@V?$allocator@URva00153A27Element@@@_STL@@@_STL@@QAE@ABV01@@Z")
