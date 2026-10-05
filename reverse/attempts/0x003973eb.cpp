// ?rva003973EB@Rva003973EB@@QAE_NPAVPlayer@@H@Z
// partial score=0.85 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva003973EB@Rva003973EB@@QAE_NPAVPlayer@@H@Z @0x003973EB 62B: true when the
// player name keys into the +0x68 map. Evidence: empty map (node count)
// false path, TheNameKeyGenerator nameToKey on Player+0x58 through rowed
// 0x0009FA65, rowed map<int,int> _M_find 0x00388F63 compared against the map
// header end; second arg dead (slot reused). Flags and map idiom follow
// Rva0028951FFind.cpp.
#include <map>
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Player
{
public:
	char m_pad00[0x58];
	AsciiString m_name58;
};

struct Rva003973EBInner
{
	char m_pad00[0x68];
	_STL::map<int, int> m_map68;
};

class Rva003973EB
{
public:
	bool rva003973EB(Player *p, int /*unused*/);

private:
	char m_pad00[4];
	Rva003973EBInner *m_inner04;
};

bool Rva003973EB::rva003973EB(Player *p, int /*unused*/)
{
	Rva003973EBInner *inner = m_inner04;
	if (inner->m_map68.size() <= 0)
		return false;
	return inner->m_map68.find(TheNameKeyGenerator->nameToKey(p->m_name58)) != inner->m_map68.end();
}
