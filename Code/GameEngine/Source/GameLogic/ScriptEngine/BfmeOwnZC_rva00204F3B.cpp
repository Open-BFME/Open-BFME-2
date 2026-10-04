// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
#include "ascii_string.h"

// ?bfmeRunZC@BfmeOwnZC@@QAEPAXVBfmeRoomZC@@PAX@Z @0x00204F3B (128B): resolve the
// room name via the base resolveName, look up its ScriptList, fetch node+4
// through rowed 0x003B6911, and copy the resolved name into `extra` when both
// are present. Evidence: chain from landed 0x003B6911; rowed Rva00204E64Find
// 0x00204E64; pinned resolveName 0x002046C0; callers in BfmeRoomForwarder;
// BfmeRoomZC carries AsciiString at +0.
//
// The list lookup is the *thiscall twin* at 0x00204E64, not a free call: the
// retail rel32 at 0x00204F64 resolves there and 0x00204F5E does mov ecx,esi
// first, so reverse/symbols.csv pins
// ?rva00204E64@BfmeOwnZC@@QAEPAVScriptList@@ABVAsciiString@@@Z at that address.
class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &name);
};

class BfmeRoomZC
{
public:
	AsciiString m_name; // +0x00
};

class ScriptList;

class ScriptList
{
public:
	void *rva003B6911(const StringBase<char> &key);
};

class BfmeOwnZC : public Rva002046C0Owner
{
public:
	ScriptList *rva00204E64(const AsciiString &name);
	void *bfmeRunZC(BfmeRoomZC name, void *extra);
};

void *BfmeOwnZC::bfmeRunZC(BfmeRoomZC name, void *extra)
{
	AsciiString resolved = resolveName(name.m_name);
	ScriptList *list = rva00204E64(resolved);
	void *result;
	if (list != 0) {
		result = list->rva003B6911(*(const StringBase<char> *)&name.m_name);
		if (result != 0 && extra != 0)
			((StringBase<char> *)extra)->set(*(const StringBase<char> *)&resolved);
	} else
		result = 0;
	return result;
}

// Pin twin of the rowed free-function body at 0x00204E64; only the name moves.
#pragma comment(linker, "/alternatename:?rva00204E64@BfmeOwnZC@@QAEPAVScriptList@@ABVAsciiString@@@Z=?Rva00204E64Find@@YGPAVScriptList@@ABVAsciiString@@@Z")
