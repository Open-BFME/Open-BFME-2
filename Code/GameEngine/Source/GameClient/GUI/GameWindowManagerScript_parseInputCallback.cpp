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

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include <string.h>

#include "ascii_string.h"


#include "../../../Include/Common/NameKeyGenerator.h"

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
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the lookup copy loses to the first-in-order copy. No flags touched.
	__forceinline void *bfme_lookup_c3028(int key, int index) { return ((FunctionLexicon *)(void *)this)->findFunction((NameKeyType)key, (FunctionLexicon::TableIndex)index); }
};

class FunctionLexicon;
extern FunctionLexicon *TheFunctionLexicon;
extern AsciiString g_inputCallbackName;
#include "WindowScriptCreateRecord.h"

class WinInstanceData;


// ?parseInputCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
Bool parseInputCallback(char *token, WinInstanceData *instData, char *buffer, void *data)
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
	g_windowScriptCreateRecord.input = ((Rva00DFF024Registry *)TheFunctionLexicon)->bfme_lookup_c3028(key, 1);

	return true;
}

static const void *s_parseInputCallbackAnchor = (const void *)parseInputCallback;
