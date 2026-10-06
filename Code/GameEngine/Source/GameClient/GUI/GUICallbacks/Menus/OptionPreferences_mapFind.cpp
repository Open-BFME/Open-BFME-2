// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Fold-duplicate of OptionPreferences_getCampaignDifficulty.cpp (same class,
// same body, same flags): the getCampaignDifficulty definition folds
// byte-identical with its landed row, while this TU additionally claims the
// map<AsciiString,AsciiString> _Rb_tree _M_find worker (78B @0x1F8437) that
// every getter TU emits via odr-use of find but none rows. The worker's two
// less<> calls resolve through the primitive operator< pin at 0x5598C (23B
// compare+setl); the pair-lexicographic helper at 0x206BCF is a different
// function (it calls operator< thrice) and is pinned under its own name.

// The preference TUs (SkirmishPreferences.cpp, GameSpyLoginPreferences.cpp,
// OnlineMiscPref*.cpp, GameModePreferencesUserName.cpp) reach this worker
// through a private throw() view, SkirmishFindMap::find, whose symbols.csv pin
// is this same address (0x1F8437). Bind that spelling to the definition here
// rather than emit a second body for one retail function.
#pragma comment(linker, "/alternatename:?find@SkirmishFindMap@@QBEPAUSkirmishFindNode@@ABVAsciiString@@@Z=??$_M_find@VAsciiString@@@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@V1@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@V1@@_STL@@@1@ABVAsciiString@@@Z")

#include <map>
#include <stdlib.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

enum GameDifficulty
{
	DIFFICULTY_EASY,
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD,

	DIFFICULTY_COUNT
};

class ScriptEngine
{
	char m_pad[0x1A4C4];
	GameDifficulty m_gameDifficulty;

public:
	GameDifficulty getGlobalDifficulty() const { return m_gameDifficulty; }
};

extern ScriptEngine *TheScriptEngine;

typedef _STL::map<AsciiString, AsciiString> AsciiPreferenceMap;

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	Int getCampaignDifficulty();
};

// ?getCampaignDifficulty@OptionPreferences@@QAEHXZ
Int OptionPreferences::getCampaignDifficulty(void)
{
	OptionPreferences::const_iterator it = find("CampaignDifficulty");
	if (it == end())
		return TheScriptEngine->getGlobalDifficulty();

	Int factor = atoi(it->second.str());
	if (factor < DIFFICULTY_EASY)
		factor = DIFFICULTY_EASY;
	if (factor > DIFFICULTY_HARD)
		factor = DIFFICULTY_HARD;

	return factor;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?find@CustomPreferenceMapShim@@QAEPAUCustomMapNodeShim@@PAUCustomAsciiStringShim@@@Z=??$_M_find@VAsciiString@@@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@V1@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@V1@@_STL@@@1@ABVAsciiString@@@Z")
