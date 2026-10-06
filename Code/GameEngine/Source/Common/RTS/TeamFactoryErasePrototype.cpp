// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva0039FE11@Rva0039FE6COwner@@QAEXABURva003A0CD1@@@Z @0x0039FE11 91B
// TeamFactory prototype map erase by two name keys. Converts both AsciiStrings
// via TheNameKeyGenerator then lower_bounds the +0xB0 map through rowed
// 0x0039EA4E; erases the node via rowed STL map<int void*> erase 0x005530A8
// when it is not the header. Same owner/map/key/node as sibling findPrototype
// 0x0039FE6C; single stack arg at +0x10/+0x14 proves the two-string struct.
// Evidence: callees all rowed; caller 0x003A0CD1 pushes its this; LINK BONUS none.
#include <map>
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct Rva0039D8FBKey
{
	int m_first;
	int m_second;
};

class TeamPrototype;

struct Rva0039EA4ENode
{
	int m_color00;
	Rva0039EA4ENode *m_parent04;
	Rva0039EA4ENode *m_left08;
	Rva0039EA4ENode *m_right0C;
	Rva0039D8FBKey m_key10;
	TeamPrototype *m_value18;
};

class Rva0039EA4E
{
public:
	Rva0039EA4ENode *rva0039EA4E(const Rva0039D8FBKey &key);
	Rva0039EA4ENode *m_header00;
};

struct Rva003A0CD1
{
	char m_pad00[0x10];
	AsciiString m_a10;
	AsciiString m_b14;
};

class Rva0039FE6COwner
{
public:
	void rva0039FE11(const Rva003A0CD1 &x);
private:
	unsigned char m_pad00[0xB0];
	Rva0039EA4E m_mapB0;
};

void Rva0039FE6COwner::rva0039FE11(const Rva003A0CD1 &x)
{
	int keyB = TheNameKeyGenerator->nameToKey(x.m_b14);
	int keyA = TheNameKeyGenerator->nameToKey(x.m_a10);
	Rva0039D8FBKey key;
	key.m_first = keyA;
	key.m_second = keyB;
	Rva0039EA4ENode *node = m_mapB0.rva0039EA4E(key);
	if (node != m_mapB0.m_header00) {
		typedef _STL::pair<const int, void *> V;
		typedef _STL::_Rb_tree<int, V, _STL::_Select1st<V>, _STL::less<int>, _STL::allocator<V> > Tree;
		((Tree *)&m_mapB0)->erase(Tree::iterator((Tree::_Link_type)node));
	}
}
