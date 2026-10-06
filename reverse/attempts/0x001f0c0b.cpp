// ?rva001F0C0B@@YAXPAVINI@@@Z
// partial score=0.75 date=2026-10-06
// ?rva001F0C0B@@YAXPAVINI@@@Z
// partial score=0.7 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva001F0C0B@@YAXPAVINI@@@Z @0x001F0C0B 249B.
// INI token replace-and-register worker (ObjectCreationList neighbourhood:
// the 0x00BE07F0 table opens with CreateObject; neighbours are
// addObjectCreationNugget/create@AttackNugget). Target facts from game.dat:
// - cdecl free function of INI*: token = INI::getNextToken(ini, 0) (rowed),
//   key = TheNameKeyGenerator->nameToKey(token) (NameKeyCacheGet spelling,
//   global 0x00DF36A4), looked up in the map at TheObjectCreationListStore
//   +0x0C (global 0x00DFDCCC, ObjectCreationListStore view).
// - When found and INI+8 == 5 (the RankInfoParse INI view places m_loadType
//   there; value 5 unproven): tree-erase the node (rowed int/void* erase via
//   a stack-built iterator), push its [node+0x14] value onto the vector at
//   store+0x18 (ObjectCreationNugget* ICF-shared push_back pin; holder
//   pushed under that spelling, cast documented) and flag value+0x0C.
// - Fresh 20B holder via scalar operator new (rowed ??2; explicit null
//   check, so plain new shape), token string built by placement new into a
//   raw slot (StringBase char ctor rowed 0x00037BA0) with a bool/live flag
//   guarding the explicit AsciiString teardown (rowed 0x00036410 worker),
//   holder init through the unrowed thiscall 0x001F073A (pinned from the
//   emitted spelling; it returns its own this), stored via the rowed
//   map<int,int> operator[] through an int pun of the void* map, then
//   INI::initFromINI(holder, CreateObject table at hardcoded 0x00BE07F0,
//   RankInfoParse reinterpret_cast precedent).
// The strict holder/element types, the +0x0C flag meaning and the load-type
// value are unproven; puns and the placement construction are explicit.
#include <map>
#include <vector>
#include <string>
#include <new>

#include "ascii_string.h"

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *table);
	int getLoadType() const { return m_loadType; }
private:
	unsigned char m_pad[8];
	int m_loadType;
};

class ObjectCreationNugget;

struct Rva001F073AHolder
{
	void *rva001F073A(AsciiString *s);
};

struct Holder20
{
	char m_bytes[20];
};

class ObjectCreationListStore
{
public:
	char m_pad00[0x0C];
	_STL::map<int, int> m_map0C;
	_STL::vector<ObjectCreationNugget *> m_vec18;
};

extern ObjectCreationListStore *TheObjectCreationListStore;

void __cdecl rva001F0C0B(INI *ini)
{
	bool strBuilt = false;
	char tokenStor[sizeof(AsciiString)];
	const char *token = ini->getNextToken(0);
	NameKeyType key = TheNameKeyGenerator->nameToKey(token);
	int keySlot = key;
	_STL::map<int, int> *map = &TheObjectCreationListStore->m_map0C;
	_STL::map<int, int>::iterator found = map->find(keySlot);
	if (found != map->end() && ini->getLoadType() == 5)
	{
		_STL::map<int, void *>::iterator eit = (_STL::map<int, void *>::iterator &)found;
		((_STL::map<int, void *> *)map)->erase(eit);
		ObjectCreationNugget *old = (ObjectCreationNugget *)found->second; // NOLINT
		if (old)
		{
			TheObjectCreationListStore->m_vec18.push_back(old);
			*(char *)((char *)old + 0x0C) = 1;
		}
	}
	Rva001F073AHolder *result = 0;
	Holder20 *hold = new Holder20;
	if (hold != 0)
	{
		new ((void *)tokenStor) AsciiString(token);
		strBuilt = true;
		result = (Rva001F073AHolder *)((Rva001F073AHolder *)hold)->rva001F073A((AsciiString *)tokenStor); // NOLINT(readability/casting)
	}
	if (strBuilt)
		((AsciiString *)tokenStor)->~AsciiString();
	(*map).operator[](keySlot) = (int)result;
	ini->initFromINI(result, reinterpret_cast<const FieldParse *>(0x00BE07F0));
}
