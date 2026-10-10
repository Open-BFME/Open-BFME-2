// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// Apt callbacks of a list of up to eight row movies (destructor 0x005105D7,
// so the class keeps the name its rowed deleting destructor gives it). Its
// constructor 0x005103A3 binds "_level<n>._OnRowShown" and "_OnRowHidden",
// and the indexed query over "NumOfPlayers" and "InSkirmish", as member
// pointers; that binding is their only reference.
#include "ascii_string.h"

extern "C" char *__cdecl strcpy(char *destination, const char *source);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *format, ...);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

// BfmePathLeafAfterMarker.cpp's path helpers, and the unrowed 0x004128F0
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

class Rva00575674
{
public:
	void rva00575674(Object *row);
};

class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4();
	void clear();

	void *m_ptr;
};

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

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}

	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount(0) {}
	virtual void anchor();
	int m_refCount; // +0x04
};

class Rva0057BC63FunctorWrapper : public FunctorWrapperHead
{
public:
	Rva0057BC63FunctorWrapper(const FunctorBinding &binding) : m_binding(binding) {}
	void invoke();
	FunctorBinding m_binding;
};

void *__cdecl operator new(unsigned int size);

// The holder constructor (row 0x0057BC63, Rva0057BC63FunctorHolder.cpp) is
// visible here as an inline, never-inlined definition. Retail's compiler knew
// it only reads the binding, so the query binding built inside the loop below
// (WorldBuilder's shape) is hoisted out of it and the loop counter shares the
// dead name home [ebp+0xC]; declared out of line, cl picks other registers.
class Rva0057BC63FunctorHolder
{
public:
	__declspec(noinline) Rva0057BC63FunctorHolder(const FunctorBinding &binding)
	{
		m_ptr = new Rva0057BC63FunctorWrapper(binding);
		if (m_ptr != 0)
			m_ptr->m_refCount++;
	}
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

__forceinline FunctorBinding MakeExternBinding(FunctorTarget*target,FunctorMethod method){FunctorBinding binding(method,target);return binding;}
class AptCommandMap;
class AptExternHandler;

class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
	unsigned char m_names[12]; // an STLport vector<AsciiString>
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	unsigned char m_names[12]; // an STLport vector<AsciiString>
};

// The 0x58-byte callback registry (as in BfmeAptGameWindowDestructor.cpp),
// constructed by the pinned 0x002D2C34.
class Rva002D2C34
{
public:
	void rva002D2C34();
};

class __declspec(novtable) Rva005248D0
{
public:
	__forceinline Rva005248D0() { ((Rva002D2C34 *)this)->rva002D2C34(); }
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10

private:
	unsigned char m_pad01C[0x58 - 0x1C];
};

// RegistryAsciiPath.cpp's narrow concatenation nodes: "level + name" is a
// two-string node built in place; appending a char or a text goes out of
// line, and operator AsciiString() materializes the result.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
 Rva000B3F84Pair*init(const char*);
 const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringRefWithChar : AsciiStringRef
{
	char m_char;
};

struct AsciiStringCharPlusText : AsciiStringRefWithChar
{
	Rva000B3F84Pair m_right;
};

struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

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
Rva0050F23E operator+(const AsciiStringPlusStringChar &left, const char *right){Rva000B3F84Pair text;text.init(right);Rva0050F23E result;static_cast<AsciiStringPlusStringChar&>(result)=left;result.m_text=text;return result;}
AsciiStringCharPlusText operator+(const AsciiStringRefWithChar &left, const char *right);

// Retail folds "two strings + text" into the byte-identical "string and
// char + text" body at 0x00109CFD (both copy an 8-byte node and append a
// text reference), so this TU calls it under that body's name.
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString&left,const char*right){Rva000B3F84Pair text;text.init(right);AsciiStringPlusStringText result;static_cast<AsciiStringPlusString&>(result)=left;result.m_text=text;return result;}
typedef AsciiStringPlusStringText (*PlusStringText)(const AsciiStringPlusString &left, const char *right);
typedef AsciiStringCharPlusText (*CharPlusText)(const AsciiStringRefWithChar &left, const char *right);

// TheGameInfo's slots and ThePlayerList's players.
class GameSlot
{
public:
	bool isOccupied() const;

	unsigned char m_pad000[0x34];
	AsciiString m_playerName; // +0x34
};

class GameInfo
{
public:
	const GameSlot *getConstSlot(int index) const;
};

extern GameInfo *TheGameInfo;

class Player;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};

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

static const char*const s_queries[2]={"NumOfPlayers","InSkirmish"};
#pragma pointers_to_members(full_generality, multiple_inheritance)
Rva005105D7::Rva005105D7(int level, const AsciiString &name)
	: Rva0050EA74(level, name),
	  m_count(0)
{
	AsciiString levelName;
	levelName.format("_level%u.", m_level);
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva005105D7::OnRowShown);
		m_commandMaps.AddCommandMap((levelName + m_name)+ "_OnRowShown", AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva005105D7::OnRowHidden);
		m_commandMaps.AddCommandMap((levelName + m_name)+ "_OnRowHidden", AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		int i = 0;
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva005105D7::rva0050E823);
		AsciiStringPlusString prefix = levelName + m_name;
		for (; i < 2; ++i)
		{
			m_externHandlers.AddExternHandler(prefix + '_' + s_queries[i], i, AptRef<AptExternHandler>(MakeExternBinding(reinterpret_cast<FunctorTarget *>(this),method)));
		}
	}
	rva0050EEDC();
}

