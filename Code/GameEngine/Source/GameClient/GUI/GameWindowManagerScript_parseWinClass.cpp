// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?parseWinClass@@YA_NPADPAVWinInstanceData@@0PAX@Z,
// retail 0x0031639C, 76 bytes. Dedicated TU.
//
// Clones the landed parseSystemCallback TU (quote-scan, strtok,
// AsciiString set, nameToKey, registry lookup tail).
// BFME2 facts (all retail-measured):
// - strtok rides the msvcr71 import at 0xBBA5EC.
// - stringSeps "\"" lives at 0xC0C2B4.
// - StringBase::set is the matched narrow row at 0x55F5.
// - The callback name shares the system global AsciiString at 0xE01308.
// - nameToKey(const AsciiString&) at 0x9FA65 is matched; TheNameKeyGenerator
//   at 0xDF36A4.
// - The registry lookup56 wrapper at 0x2D2371 is pinned (tries slot 5 then
//   slot 6 for index -1); sole caller is this verb.
// - The winclass slot stores to the global at 0xE012EC.
// - Identity: the .data dispatch table at 0x9BE198 pairs 'WINCLASS'
//   with 0x71639C.

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

class Rva00DFF024Registry
{
public:
	void *lookup(int key, int index);
	void *lookup34(int key, int index);
	void *lookup56(int key, int index);
};

class FunctionLexicon;
extern FunctionLexicon *TheFunctionLexicon;
extern AsciiString g_systemCallbackName;
#include "WindowScriptCreateRecord.h"

class WinInstanceData;


// ?parseWinClass@@YA_NPADPAVWinInstanceData@@0PAX@Z
Bool parseWinClass(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	// scan to the first " mark
	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;  // skip the first "
	c = strtok(ptr, stringSeps);  // name value
	g_systemCallbackName.set(c);

	NameKeyType key = TheNameKeyGenerator->nameToKey(g_systemCallbackName);
	g_windowScriptCreateRecord.winClass = ((Rva00DFF024Registry *)TheFunctionLexicon)->lookup56(key, -1);

	return true;
}

static const void *s_parseWinClassAnchor = (const void *)parseWinClass;
