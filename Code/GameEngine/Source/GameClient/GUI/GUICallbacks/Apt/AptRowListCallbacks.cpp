// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Apt callbacks of a list of up to eight row movies (destructor 0x005105D7,
// so the class keeps the name its rowed deleting destructor gives it). Its
// constructor 0x005103A3 binds "_level<n>._OnRowShown" and "_OnRowHidden",
// and the indexed query over "NumOfPlayers" and "InSkirmish", as member
// pointers; that binding is their only reference.
// Retail calls _mbscpy through the import thunk at 0x00629176.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include "ascii_string.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// AptUtils.cpp's path helpers, and the unrowed 0x004128F0
// (239 bytes) next to them that reads one "key=value" parameter, pinned by
// address.
namespace AptUtils { const char *__cdecl SkipLevelN(const char *path); }
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *path); }
bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);

// TheGameLogic's mode at +0x110 (2 in a skirmish).
class GameLogic;
extern GameLogic *TheGameLogic;

struct AptRowListGameLogic
{
	unsigned char m_pad000[0x110];
	int m_mode; // +0x110
};

// The row movie built by the unrowed constructor 0x0050F909 (pinned by
// address) from the movie's level and path and the row's two values; the
// row's holder sets it through its rowed 0x00575674 and clears it through
// Rva000AD6F4's.
class Rva0050F909
{
public:
	Rva0050F909(int level, const AsciiString &path, int value0, int value4);

	unsigned char m_pad[0x5C];
};

class Object;

#include "../../../../../Include/Common/Rva00575674.h"

#include "../../../../../Include/Common/Rva000AD6F4.h"

// A row: the slot index and player it shows, and its movie once built.
struct AptRowListRow
{
	AptRowListRow() : m_value0(-1), m_value4(0) {}

	int m_value0;
	int m_value4;
	Rva000AD6F4 m_movie; // +0x08
};

// The page base (Rva0050EA74Ctor.cpp): a reference-counted page with its
// level and name; vslots 1 and 2 show and hide it.
class Rva0050EA74
{
public:
	Rva0050EA74(int level, const AsciiString &name);
	virtual ~Rva0050EA74();
	virtual void show();
	virtual void hide();
	virtual int v03(int message, int key, int state);
	virtual int v04(int message, int key, int state);
	virtual void v05();

	int m_references; // +0x04
	int m_level; // +0x08
	AsciiString m_name; // +0x0C
	bool m_shown; // +0x10
};

// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// AptInGameChat.cpp).
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

#include "../../../../../Include/GameClient/FunctorBinding.h"

#include "../../../../../Include/Common/FunctorWrapperHead.h"

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}

	FunctorWrapperHead *m_ptr;
};

__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;
class AptExternHandler;

#include "../../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"

// The 0x58-byte callback registry (as in BfmeAptGameWindowDestructor.cpp),
// constructed by the pinned 0x002D2C34.
class Rva002D2C34
{
public:
	void rva002D2C34();
};

#include "../../../../../Include/GameClient/Rva005248D0.h"

// RegistryAsciiPath.cpp's narrow concatenation nodes: "level + name" is a
// two-string node built in place; appending a char or a text goes out of
// line, and operator AsciiString() materializes the result.
#include "../../../../../Include/Common/Rva000B3F84Pair.h"

#include "../../../../../Include/Common/AsciiStringRef.h"

#include "../../../../../Include/Common/AsciiStringRefWithChar.h"

struct AsciiStringCharPlusText : AsciiStringRefWithChar
{
	Rva000B3F84Pair m_right;
};

#include "../../../../../Include/Common/AsciiStringPlusString.h"

struct AsciiStringPlusStringChar : AsciiStringPlusString
{
	char m_char;
};

struct AsciiStringPlusStringText : AsciiStringPlusString
{
	operator AsciiString();

	Rva000B3F84Pair m_text;
};

struct Rva0050F23E : AsciiStringPlusStringChar
{
	operator AsciiString();

	Rva000B3F84Pair m_text;
};

inline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString node;
	node.m_string = &left;
	node.m_second.m_string = &right;
	return node;
}

AsciiStringPlusStringChar operator+(const AsciiStringPlusString &left, char c);
Rva0050F23E operator+(const AsciiStringPlusStringChar &left, const char *right);
AsciiStringCharPlusText operator+(const AsciiStringRefWithChar &left, const char *right);

// Retail folds "two strings + text" into the byte-identical "string and
// char + text" body at 0x00109CFD (both copy an 8-byte node and append a
// text reference), so this TU calls it under that body's name.
typedef AsciiStringPlusStringText (*PlusStringText)(const AsciiStringPlusString &left, const char *right);
typedef AsciiStringCharPlusText (*CharPlusText)(const AsciiStringRefWithChar &left, const char *right);

// TheGameInfo's slots and ThePlayerList's players.
#include "../../../../../Include/GameNetwork/GameInfo.h"


extern GameInfo *TheGameInfo;

class Player;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

// The "StatusPage" page (AptTributePageCallbacks.cpp's factory builds it):
// one row per occupied slot with a player.
class Rva005105D7 : public Rva0050EA74, public Rva005248D0
{
public:
	Rva005105D7(int level, const AsciiString &name);

	void OnRowShown(const char *params);
	void OnRowHidden(const char *params);
	// Bound for "NumOfPlayers" (0) and "InSkirmish" (1). Name unknown.
	void rva0050E823(int which, char *result, bool skip);
	// Fills the rows. Name unknown.
	void rva0050EEDC();

private:
	int m_count; // +0x6C
	AptRowListRow m_rows[8]; // +0x70
};

// Retail 0x0050E823, 102 bytes. Name unknown. Answers the player count or
// whether this is a skirmish.
void Rva005105D7::rva0050E823(int which, char *result, bool skip)
{
	result[0] = '0';
	result[1] = 0;
	switch (which)
	{
	case 0:
		if (!skip)
			_snprintf(result, 0xFF, "%d", m_count);
		break;
	case 1:
		if (!skip)
		{
			AptRowListGameLogic *logic = (AptRowListGameLogic *)TheGameLogic;
			_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>(logic && logic->m_mode == 2 ? "1" : "0"));
		}
		break;
	}
}

// Retail inlines AsciiString::isEmpty here (the shared header calls it out
// of line); it reads the string data header {int refCount; unsigned short
// length; unsigned short capacity;}.
static inline bool isEmptyText(const AsciiString &text)
{
	const char *data = *(const char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

// Retail 0x0050EEDC, 166 bytes: one row for each occupied slot whose
// player name names a player.
void Rva005105D7::rva0050EEDC()
{
	for (int i = 0; i < 8; ++i)
	{
		const GameSlot *slot = TheGameInfo->getConstSlot(i);
		if (slot == 0 || !slot->isOccupied())
			continue;
		AsciiString name = slot->m_field34;
		if (isEmptyText(name))
			continue;
		Player *player = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name));
		if (player == 0)
			continue;
		AptRowListRow &row = m_rows[m_count++];
		row.m_value0 = i;
		row.m_value4 = (int)player;
	}
}

// Retail 0x0050EF82, 122 bytes: "_OnRowHidden" drops the indexed row's
// movie.
void Rva005105D7::OnRowHidden(const char *params)
{
	AsciiString indexText;
	if (!Rva004128F0GetParam(params, "index", indexText))
		return;
	int index = atoi(indexText.str());
	if (index < 0 || index > m_count)
		return;
	AptRowListRow &row = m_rows[index];
	Rva000AD6F4 &movie = row.m_movie;
	movie.clear();
}

// Retail 0x0050FAF7, 349 bytes: "_OnRowShown" builds the indexed row's
// movie once, when the shown movie is on this list's level.
void Rva005105D7::OnRowShown(const char *params)
{
	AsciiString indexText;
	if (!Rva004128F0GetParam(params, "index", indexText))
		return;
	int index = atoi(indexText.str());
	if (index < 0 || index > m_count)
		return;
	AptRowListRow *row = &m_rows[index];
	Rva000AD6F4 *movie = &row->m_movie;
	if (movie->m_ptr)
		return;
	AsciiString name;
	if (!Rva004128F0GetParam(params, "name", name))
		return;
	int level = AptUtils::LevelIndexFromTarget(name.str());
	if (level != m_level)
		return;
	((Rva00575674 *)movie)->rva00575674((Object *)new Rva0050F909(level, AsciiString(AptUtils::SkipLevelN(name.str())), row->m_value0, row->m_value4));
}

// The constructor's matched home is AptRowListConstructor.cpp; these anchors keep the rowed
// implicit destructor and the row constructor emitted in this unit.
#pragma inline_depth(0)
// ?bfmeAnchorRva005105D7Dtor absent-from-retail
void bfmeAnchorRva005105D7Dtor(Rva005105D7 *statusPage) { statusPage->Rva005105D7::~Rva005105D7(); }
// ?bfmeAnchorAptRowListRow absent-from-retail
void bfmeAnchorAptRowListRow(AptRowListRow *aptRowListRow) { aptRowListRow->AptRowListRow::AptRowListRow(); }
#pragma inline_depth()
