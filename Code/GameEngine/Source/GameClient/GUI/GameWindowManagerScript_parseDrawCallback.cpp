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

#include "../../../Include/Common/ScalarTypes.h"


#ifndef NULL
#include <stddef.h>
#endif

#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/NameKeyType.h"




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
	void *lookup34(int key, int index);
	void *lookup56(int key, int index);
	__forceinline void *bfme_lookup_4742d(int key, int index) { return ((FunctionLexicon *)(void *)this)->findFunction((NameKeyType)key, (FunctionLexicon::TableIndex)index); }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the lookup copy loses to the first-in-order copy. No flags touched.
	__forceinline void *bfme_lookup_c3028(int key, int index) { return ((FunctionLexicon *)(void *)this)->findFunction((NameKeyType)key, (FunctionLexicon::TableIndex)index); }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the lookup copy loses to the first-in-order copy. No flags touched.
	__forceinline void *bfme_lookup_7fde7(int key, int index) { return ((FunctionLexicon *)(void *)this)->findFunction((NameKeyType)key, (FunctionLexicon::TableIndex)index); }
};

// TheFunctionLexicon (GameEngine::init registers it under that name): matched
// references place it at VA 0xdff024 (zero-filled .bss). Read through the
// registry view.
FunctionLexicon *TheFunctionLexicon;
extern AsciiString g_drawCallbackName;
#include "WindowScriptCreateRecord.h"

class WinInstanceData;

#include <string.h>
namespace NativeScriptCrt {
extern "C" __declspec(dllimport) char *__cdecl strtok(char *, const char *);

}

// ?parseDrawCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
Bool parseDrawCallback(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;
	c = NativeScriptCrt::strtok(ptr, stringSeps);
	g_drawCallbackName.set(c);

	NameKeyType key = TheNameKeyGenerator->nameToKey(g_drawCallbackName);
	g_windowScriptCreateRecord.draw = ((Rva00DFF024Registry *)TheFunctionLexicon)->lookup34(key, -1);

	return true;
}

static const void *s_parseDrawCallbackAnchor = (const void *)parseDrawCallback;
