// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?parseDrawCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z,
// retail 0x003164CC, 76 bytes. Dedicated TU.
//
// Clones the landed parseSystemCallback TU.
// - name global AsciiString at 0xE01314, store global at 0xE012F8.
// - registry lookup34 wrapper at 0x2D2341 is pinned (tries slot 3 then
//   slot 4 for index -1); sole caller is this verb.
// - dispatch table at 0x9BE198 pairs 'DRAWCALLBACK' with 0x7164CC.

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "ascii_string.h"


class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// The registry is TheFunctionLexicon; its lookup is FunctionLexicon::findFunction
// 0x002D225F (rowed in Common/System/FunctionLexicon.cpp), reached through
// this unit's forwarding view.
class Rva00DFF024Registry;
class FunctionLexicon
{
public:
	enum TableIndex { TABLE_ANY = -1 };
protected:
	void *findFunction(NameKeyType key, TableIndex index);	// 0x002D225F
	friend class Rva00DFF024Registry;
};

class Rva00DFF024Registry
{
public:
	__forceinline void *lookup(int key, int index) { return ((FunctionLexicon *)(void *)this)->findFunction((NameKeyType)key, (FunctionLexicon::TableIndex)index); }
	void *lookup34(int key, int index);
	void *lookup56(int key, int index);
};

extern Rva00DFF024Registry *TheRva00DFF024Registry;
// TheRva00DFF024Registry: matched references place it at VA 0xdff024 (zero-filled .bss).
Rva00DFF024Registry * TheRva00DFF024Registry;
extern AsciiString g_drawCallbackName;
extern void *g_drawCallback;
// g_drawCallback: matched references place it at VA 0xe012f8 (zero-filled .bss).
void * g_drawCallback;

class WinInstanceData;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseDrawCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseDrawCallback(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;
	c = strtok(ptr, stringSeps);
	g_drawCallbackName.set(c);

	NameKeyType key = TheNameKeyGenerator->nameToKey(g_drawCallbackName);
	g_drawCallback = TheRva00DFF024Registry->lookup34(key, -1);

	return true;
}

static const void *s_parseDrawCallbackAnchor = (const void *)parseDrawCallback;
