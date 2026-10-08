// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?parseSystemCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x003163E8, 76 bytes.
// Dedicated TU.
//
// Battle for Middle-earth has no twin for this body (BFME2-new global
// callback registry); the shape clones the landed parseName TU (quote-scan,
// strtok, AsciiString set, nameToKey) with a registry lookup tail.
// BFME2 facts (all retail-measured):
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; the
//   single site emits the direct indirect call like retail).
// - stringSeps "\"" lives at 0xC0C2B4.
// - StringBase::set is the matched narrow row at 0x55F5 (public QAEXPBD;
//   AsciiString inline set forwards to it).
// - The callback name is the global AsciiString at 0xE01308 (extern object;
//   address patches from retail; shared with parseWinClass).
// - nameToKey(const AsciiString&) at 0x9FA65 is a matched row (declared,
//   never defined here); TheNameKeyGenerator is the extern pointer at
//   0xDF36A4 (DIR32 from retail).
// - The registry lookup at 0x2D225F is thiscall (key, index) over 12 slots
//   at manager+0x0C (null key returns null; index -1 scans all slots via
//   helper 0x2D2235; else slots[index]); pinned this batch as an opaque
//   Rva-holder method (Except-cluster precedent: the Rva name claims only
//   the address, the note describes the proven behavior).
// - The system slot is index 0; the resolved pointer stores to the global
//   at 0xE012F0 (extern; address patches from retail).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'SYSTEMCALLBACK'
//   with 0x7163E8 (entries are name@+0/fn@+4; the walker at 0x31701C
//   compares names and calls [eax+4]).

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

// Opaque registry holder (see header note). Decls match the same-batch pins.
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
extern AsciiString g_systemCallbackName;
extern void *g_systemCallback;
// g_systemCallback: matched references place it at VA 0xe012f0 (zero-filled .bss).
void * g_systemCallback;

class WinInstanceData;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseSystemCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseSystemCallback(char *token, WinInstanceData *instData, char *buffer, void *data)
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
	g_systemCallback = TheRva00DFF024Registry->lookup(key, 0);

	return true;
}

static const void *s_parseSystemCallbackAnchor = (const void *)parseSystemCallback;
