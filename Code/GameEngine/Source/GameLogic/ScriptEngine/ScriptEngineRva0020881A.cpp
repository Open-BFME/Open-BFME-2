// cl: /Ireference/shims/bfme2_ascii /O1 /EHs
// stlport
// ?rva0020881A@ScriptEngine@@QAEPAXVAsciiString@@@Z @0x0020881A 134B
// Unlock sibling of 0x002086C5 via resolveName plus Rva0002C4FD plus find
// Target evidence: callers 0x0020945A and 0x003C0578 unblocks 0x003C0532
// neighbours ScriptEngine_dtor 0x002086BD and stlport growth 0x00209952
// member at this+0x190AC is second team map m_map190AC per ScriptEngine_dtor layout
#include "ascii_string.h"
#include <utility>

class AsciiString;
struct TeamMapNode;

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &name);
};

struct Rva0002C4FD : public _STL::pair<const AsciiString, AsciiString>
{
	Rva0002C4FD(const StringBase<char> &a, const StringBase<char> &b);
};

struct TeamMapNode
{
	char m_pad[0x18];
	char m_data[1];
};

class Rva0032C07COwner
{
public:
	TeamMapNode *find(Rva0002C4FD &key) throw();
};

class ScriptEngine : public Rva002046C0Owner
{
public:
	void *rva0020881A(AsciiString name);
private:
	char m_pad[0x190AC];
	Rva0032C07COwner m_owner;
};

void *ScriptEngine::rva0020881A(AsciiString name)
{
	AsciiString resolved = resolveName(name);
	Rva0002C4FD key(*(const StringBase<char> *)&resolved, *(const StringBase<char> *)&name);
	Rva0032C07COwner *owner = (Rva0032C07COwner *)((char *)this + 0x190AC);
	TeamMapNode *found = owner->find(key);
	if (found != *(TeamMapNode **)owner)
		return (void *)((char *)found + 0x18);
	return 0;
}

// Bind pin spelling to the rowed STL body at 0x0032C07C; only the name moves.
#pragma comment(linker, "/alternatename:?find@Rva0032C07COwner@@QAEPAUTeamMapNode@@AAURva0002C4FD@@@Z=??$_M_find@U?$pair@VAsciiString@@V1@@_STL@@@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@UTeamLess0019B850@@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@1@ABU?$pair@VAsciiString@@V1@@1@@Z")
