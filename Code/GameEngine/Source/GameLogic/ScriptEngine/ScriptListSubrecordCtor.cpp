// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Constructor of ScriptList's 0x20-byte subrecords at 0x003B761E (41B).
// The subrecord holds two 12-byte vectors (built through the rowed
// vector_base at 0x00211E58 with a one-byte stack allocator temp, hence
// the EBP frame) plus two ints initialized to -1 (plain -1 stores take
// the or-form under /O1). The same body serves both the +0x0C and +0x2C
// members (called twice from the ScriptList constructor at 0x003B7720),
// so it carries one address-derived row. The vectors are BfmeE12
// stand-ins: the image fixes only the 12-byte stride, and the swap at
// 0x003B56A5 resolves its calls through the rowed vector<UBfmeE12>::swap.

#include <vector>

struct BfmeE12 { float x, y, z; };

class Rva003B761E
{
public:
	Rva003B761E();

private:
	_STL::vector<BfmeE12> m_a;			// +0x00
	_STL::vector<BfmeE12> m_b;			// +0x0C
	int m_first;						// +0x18
	int m_second;						// +0x1C
};

// ??0Rva003B761E@@QAE@XZ
Rva003B761E::Rva003B761E() : m_first(-1), m_second(-1)
{
}
