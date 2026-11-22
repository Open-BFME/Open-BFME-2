// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva002C6E4E@@QAE@XZ @0x002C6E4E 86B (the opaque pin spelling; scalar
// deleting dtor 0x004E938C). A non-polymorphic AIBuilder derivative with an
// owned pointee at +0x164 whose slot 0 (flag 0) result goes to operator
// delete and the map<AsciiString, TreeHintPayload001F8ACB> at +0x17C (tree
// dtor 0x001F8C23, declared as a member specialisation so the call stays
// out of line); AIBuilder::~AIBuilder 0x004EC59A runs last. The class
// and pointee identities are unproven.
#include <map>
#include "ascii_string.h"

#include <new>

struct TreeHintPayload001F8ACB;

// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Rb_tree<AsciiString,pair<AsciiString const ,TreeHintPayload001F8ACB>,_Select1st<pair<AsciiString const ,TreeHintPayload001F8ACB> >,less<AsciiString>,allocator<pair<AsciiString const ,TreeHintPayload001F8ACB> > >::~_Rb_tree(); }

typedef _STL::pair<const AsciiString, TreeHintPayload001F8ACB> TreeHintPair001F8ACB;

typedef _STL::map<AsciiString, TreeHintPayload001F8ACB, _STL::less<AsciiString>, _STL::allocator<TreeHintPair001F8ACB> > Map001F8ACB;

class AIBuilder
{
public:
	~AIBuilder();
private:
	unsigned char m_prefix[0x15C];
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
	char m_pad15C[0x164 - 0x15C];
	Rva002C6E4EPointee *m_164;
	char m_pad168[0x17C - 0x168];
	Map001F8ACB m_17C;
};

Rva002C6E4E::~Rva002C6E4E()
{
	Rva002C6E4EPointee *p = m_164;
	if (p)
		operator delete(p->destroy(0));
}
