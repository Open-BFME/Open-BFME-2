// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva001E1890@Rva001E1890@@QAE... @0x001E1890 318B: chain parse that news Rva001E125D (0x1A0) and fills bone/trigger fields.
// Evidence: calls rowed ctor 0x001E1221, INI getNextAsciiString/set/toLower, strncpy to +0x160, FollowBone/scanBool to +0x14C, FXTrigger/scanIndexList to +0x150, list<int> push_back of nugget plus flag at instance+8.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <list>
#include <new>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

#include <string.h>

#include "ascii_string.h"

#include "../../Include/Common/INI/INI.h"

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
	virtual ~Rva001DFEAABase();
	int m04;
private:
	char m_pad[0x148 - 8];
};

class Rva001E125D : public Rva001DFEAABase
{
public:
	Rva001E125D();
	AsciiString m_str148;
	unsigned char m_14C;
	char m_pad14D[3];
	int m_150;
	char m_pad154[0x160 - 0x154];
	char m_buf160[64];
};

// Retail's FXTrigger index list at RVA 0x009B8DB4 (.data): three names and the null terminator (the next
// list, {NONE, FRONT/RIGHT/BACK/LEFT_DESTROYED}, follows at 0x009B8DC4).
const char *g_00DB8DB4[] = { "NONE", "CATAPULT_ROCK", "TREBUCHET_ROCK", 0 };

class Rva001E1890Nugget;
void __cdecl Rva001E1890Parse(INI *ini, void *instance, void *store, const void *user)
{
	Rva001E125D *nugget = new Rva001E125D;
	((StringBase<char> &)(nugget->m_str148)).set((const StringBase<char> &)(ini->getNextAsciiString()));
	((StringBase<char> &)(nugget->m_str148)).toLower();
	const char *tok = ini->getNextTokenOrNull(*(const char **)((char *)ini + 0x420));
	strncpy(nugget->m_buf160, tok, 0x3F);
	const char *tok2 = ini->getNextTokenOrNull(*(const char **)((char *)ini + 0x420));
	if (tok2 && strcmp(tok2, "FollowBone") == 0) {
		const char *btok = ini->getNextToken(*(const char **)((char *)ini + 0x420));
		nugget->m_14C = ini->scanBool(btok);
	} else {
		nugget->m_14C = 0;
	}
	const char *tok3 = ini->getNextTokenOrNull(*(const char **)((char *)ini + 0x420));
	if (tok3 && strcmp(tok3, "FXTrigger") == 0) {
		const char *itok = ini->getNextToken(*(const char **)((char *)ini + 0x420));
		nugget->m_150 = ini->scanIndexList(itok, g_00DB8DB4);
	} else {
		nugget->m_150 = 0;
	}
	((_STL::list<int> *)((char *)instance + 4))->push_back((int)nugget);
	*(unsigned char *)((char *)instance + 8) = 1;
}
