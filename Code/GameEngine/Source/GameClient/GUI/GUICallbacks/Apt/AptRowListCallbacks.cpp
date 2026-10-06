// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
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
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);
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
	void clear();

	void *m_ptr;
};

struct AptRowListRow
{
	int m_value0;
	int m_value4;
	Rva000AD6F4 m_movie; // +0x08
};

class Rva005105D7
{
public:
	void OnRowShown(const char *params);
	void OnRowHidden(const char *params);
	// Bound for "NumOfPlayers" (0) and "InSkirmish" (1). Name unknown.
	void rva0050E823(int which, char *result, bool skip);

private:
	unsigned char m_pad00[0x08];
	int m_level; // +0x08
	unsigned char m_pad0c[0x6C - 0x0C];
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
			strcpy(result, logic && logic->m_mode == 2 ? "1" : "0");
		}
		break;
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
	int level = Rva004128BBGetLevel(name.str());
	if (level != m_level)
		return;
	((Rva00575674 *)movie)->rva00575674((Object *)new Rva0050F909(level, AsciiString(Rva00412845AfterLevel(name.str())), row->m_value0, row->m_value4));
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
