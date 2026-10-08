// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?parseInputCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z,
// retail 0x00316434, 76 bytes. Dedicated TU.
//
// Clones the landed parseSystemCallback TU.
// - name global AsciiString at 0xE0130C, store global at 0xE012F4.
// - registry lookup (pinned 0x2D225F) with index 1.
// - dispatch table at 0x9BE198 pairs 'INPUTCALLBACK' with 0x716434.

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
};

extern Rva00DFF024Registry *TheRva00DFF024Registry;
extern AsciiString g_inputCallbackName;
extern void *g_inputCallback;
// g_inputCallback: matched references place it at VA 0xe012f4 (zero-filled .bss).
void * g_inputCallback;

class WinInstanceData;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseInputCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseInputCallback(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;
	c = strtok(ptr, stringSeps);
	g_inputCallbackName.set(c);

	NameKeyType key = TheNameKeyGenerator->nameToKey(g_inputCallbackName);
	g_inputCallback = TheRva00DFF024Registry->lookup(key, 1);

	return true;
}

static const void *s_parseInputCallbackAnchor = (const void *)parseInputCallback;
