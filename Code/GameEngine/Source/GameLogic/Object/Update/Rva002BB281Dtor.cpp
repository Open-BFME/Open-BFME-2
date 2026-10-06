// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva002BB281@@QAE@XZ @ 0x002BB281 54B
// Evidence: EH dtor calls rowed vector dtor 0x002B703F at +0x2C then pinned Rva002BB281Member08 dtor at dup 0x002BAD1C (same 57B clear-plus-free as Rva000427195) at +8; same shape as sibling BfmeAssignRecord52 dtor 0x002B707E; unblocks 0x002BC971; chain from 0x002B703F.
#include <vector>

struct Rva0040DC56Element
{
	~Rva0040DC56Element();
	int m_pad[4];
};

struct Rva002BB281Member08
{
	~Rva002BB281Member08();
	char m_pad[20];
};

class Rva002BB281
{
public:
	~Rva002BB281();
private:
	char m_pad00[8];
	Rva002BB281Member08 m_08;
	char m_pad1C[16];
	_STL::vector<Rva0040DC56Element> m_2C;
};

Rva002BB281::~Rva002BB281()
{
}
