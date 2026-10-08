// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?Rva003B3371Call@@YAXH@Z @0x003B3371 81B. Free cdecl void(int): if global
// ScriptEngine at 0x009FE16C is set, builds AsciiString temp from table
// 0x009C1050[index] via pinned AsciiString(PBD) at 0x00037BA0, calls rowed
// ScriptEngine::rva00357DD2, destroys temp via releaseBuffer. Evidence:
// rowed StringBase ctor plus rowed rva00357DD2 plus releaseBuffer; 6 callers.
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class ScriptEngine
{
public:
	void rva00357DD2(const AsciiString &s);
};
extern ScriptEngine *TheScriptEngine;
// Scripts.cpp owns the native29-entry shell table at VA DC1050.
// The adjacent six pointers are ShakeIntensities and are not shell hooks.
extern char *TheShellHookNames[];

void __cdecl Rva003B3371Call(int index)
{
	if (TheScriptEngine == 0)
		return;
	AsciiString tmp(TheShellHookNames[index]);
	TheScriptEngine->rva00357DD2(tmp);
}
