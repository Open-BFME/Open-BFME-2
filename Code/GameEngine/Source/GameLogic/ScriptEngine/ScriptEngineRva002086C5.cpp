// cl: /Ireference/shims/bfme2_ascii /O1 /EHs
// stlport
// ?rva002086C5@ScriptEngine@@QAEPAXVAsciiString@@@Z @0x002086C5 134B
// Unlock of 5 free functions (2 ready): findTeam-like lookup via resolveName plus Rva0002C4FD plus find.
// Target evidence: caller 0x003E7CE8 sets ecx to ScriptEngine* (g_Va009FE16C), ret 4 with pointer return,
// neighbours ScriptEngine_dtor 0x002086BD and stlport growth 0x00209952. Recipe: EH with AsciiString temps.
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
	void *rva002086C5(AsciiString name);
private:
	char m_pad[0x190A0];
	Rva0032C07COwner m_owner;
};

void *ScriptEngine::rva002086C5(AsciiString name)
{
	AsciiString resolved = resolveName(name);
	Rva0002C4FD key(*(const StringBase<char> *)&resolved, *(const StringBase<char> *)&name);
	Rva0032C07COwner *owner = (Rva0032C07COwner *)((char *)this + 0x190A0);
	TeamMapNode *found = owner->find(key);
	if (found != *(TeamMapNode **)owner)
		return (void *)((char *)found + 0x18);
	return 0;
}

// Bind pin spelling to the rowed STL body at 0x0032C07C; only the name moves.
#pragma comment(linker, "/alternatename:?find@Rva0032C07COwner@@QAEPAUTeamMapNode@@AAURva0002C4FD@@@Z=??$_M_find@U?$pair@VAsciiString@@V1@@_STL@@@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@UTeamLess0019B850@@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@1@ABU?$pair@VAsciiString@@V1@@1@@Z")
