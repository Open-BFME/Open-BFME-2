// cl: /O1 /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE /G7
// stlport
// ??0Rva002BB7AA@@QAE@HH@Z @0x002BB7AA 44B.
// Two-int ctor with hash_map and vector members.
// Evidence: unlock plus caller 0x002BCA7D; hash_map row 0x002BB686 plus Vector_base row 0x00211E58; prev next STL same alloc flags.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <hash_map>
#include <vector>

struct Rva002BB686Element
{
	char m_data[1];
};

struct PlayerAITypeEntry
{
	char m_data[16];
};

class Rva002BB7AA
{
public:
	Rva002BB7AA(int a, int b);

private:
	int m_0;
	int m_4;
	_STL::hash_map<int, Rva002BB686Element> m_8;
	char m_pad1C[0x10];
	_STL::vector<PlayerAITypeEntry> m_2c;
};

// ??0Rva002BB7AA@@QAE@HH@Z
Rva002BB7AA::Rva002BB7AA(int a, int b) : m_0(a), m_4(b), m_8(), m_2c()
{
}
