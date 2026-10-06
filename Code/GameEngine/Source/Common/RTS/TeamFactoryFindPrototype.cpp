// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?findPrototype@Rva0039FE6COwner@@QAEPAVTeamPrototype@@ABVAsciiString@@0@Z @0x0039FE6C 79B
// TeamFactory prototype map find by two name keys. Converts both AsciiStrings
// via TheNameKeyGenerator then lower_bounds the +0xB0 map through rowed
// 0x0039EA4E; null when the node is the header, else the TeamPrototype at +0x18.
// Evidence: LINK packet pin, callers 0x00206389 0x00357100 0x00358643, sibling
// Rva003570D1 declares this signature, map/key/node match Rva0039EA4EFinish.
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

class Rva0039FE6COwner
{
public:
	TeamPrototype *findPrototype(const AsciiString &a, const AsciiString &b);
private:
	unsigned char m_pad00[0xB0];
	Rva0039EA4E m_mapB0;
};

TeamPrototype *Rva0039FE6COwner::findPrototype(const AsciiString &a, const AsciiString &b)
{
	int keyB = TheNameKeyGenerator->nameToKey(b);
	int keyA = TheNameKeyGenerator->nameToKey(a);
	Rva0039D8FBKey key;
	key.m_first = keyA;
	key.m_second = keyB;
	Rva0039EA4ENode *node = m_mapB0.rva0039EA4E(key);
	if (node != m_mapB0.m_header00)
		return node->m_value18;
	return 0;
}
