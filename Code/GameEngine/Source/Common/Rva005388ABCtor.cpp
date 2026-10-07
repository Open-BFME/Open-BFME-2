// cl: /O1 /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE /G7
// stlport
// ??0Rva005388AB@@QAE@XZ @0x005388AB 23B
// Evidence: leaf lane, callees all rowed (Vector_base 0x00211E58 row PlayerAITypeSetCtor), callers 0x0030C5AB 0x0030C808 unclaimed, prev 0x00538839 reserve next 0x005388C2 QuadStrip copy, byte flag at +0x20 set 1 with vector base at +0.
#include <vector>

struct PlayerAITypeEntry
{
	char m_data[16];
};

class Rva005388AB
{
public:
	Rva005388AB();
private:
	_STL::vector<PlayerAITypeEntry> m_vec;
	char m_pad0C[0x20 - 0x0C];
	unsigned char m_20;
};

Rva005388AB::Rva005388AB() : m_vec()
{
	m_20 = 1;
}
