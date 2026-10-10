// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva002C6E4E@@QAE@XZ @0x002C6E4E 86B (the opaque pin spelling; scalar
// deleting dtor 0x004E938C). A non-polymorphic AIBuilder derivative with an
// owned pointee at +0x164 whose slot 0 (flag 0) result goes to operator
// delete and the map<AsciiString, TreeHintPayload001F8ACB> at +0x17C (tree
// dtor 0x001F8C23, spelled as a declaration-only specialisation so the call
// stays out of line); AIBuilder::~AIBuilder 0x004EC59A runs last. The class
// and pointee identities are unproven.
#include <map>
#include "ascii_string.h"

void __cdecl operator delete(void *block);

struct TreeHintPayload001F8ACB;
namespace _STL
{
template <> class _Rb_tree<AsciiString, pair<const AsciiString, TreeHintPayload001F8ACB>, _Select1st<pair<const AsciiString, TreeHintPayload001F8ACB> >, less<AsciiString>, allocator<pair<const AsciiString, TreeHintPayload001F8ACB> > >
{
public:
	~_Rb_tree();
private:
	char m_data[12];
};
}
typedef _STL::_Rb_tree<AsciiString, _STL::pair<const AsciiString, TreeHintPayload001F8ACB>, _STL::_Select1st<_STL::pair<const AsciiString, TreeHintPayload001F8ACB> >, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, TreeHintPayload001F8ACB> > > Rva002C6E4EMap;

class AIBuilder
{
public:
	~AIBuilder();
	char m_data[0x164];
};

class Rva002C6E4EPointee
{
public:
	virtual void *destroy(int flag);
};

class Rva002C6E4E : public AIBuilder
{
public:
	~Rva002C6E4E();
private:
	Rva002C6E4EPointee *m_164;
	char m_pad168[0x17C - 0x168];
	Rva002C6E4EMap m_17C;
};

Rva002C6E4E::~Rva002C6E4E()
{
	Rva002C6E4EPointee *p = m_164;
	if (p)
		operator delete(p->destroy(0));
}
