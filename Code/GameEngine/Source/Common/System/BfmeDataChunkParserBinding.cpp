// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common/System
// A small parser binding built as a virtual base plus three derived fields.
// The derived constructor calls the base constructor out of line, and retail
// lands that call on the rowed DataChunkParser constructor at 0x000ABB87, so
// the base constructor is declared here, not given an inline body: an inline
// body made this unit emit the only tree copy of the name, which every other
// caller then bound to instead of that row.
// Parameter types (identity_evidence/parser_binding_ctor_001920c0.md): the
// retail caller 0x0019B030 passes a by-value 8-byte SidesList member callback,
// and binding vtable 0x0109BFD4 is the one the SidesList loaders 0x0019EC80
// and 0x0074ACB0 install inline. The class name stays address-free but unproven.

typedef void (__cdecl *BfmeChunkParserVE)(void);

extern void __cdecl bfmeChunkParserVE(void);

class AsciiString;
class DataChunkInput;
struct DataChunkInfo;
class SidesList;

#include "../../../Include/Common/BfmeParserRegistryVE.h"

class DataChunkInput;
#include "../../../Include/Common/DataChunkParser.h"

class __declspec(novtable) BfmeParserBindingBaseVE
{
public:
	// The base is the rowed DataChunkParser ctor (0x000ABB87), called by that name.
	__declspec(dllimport) __forceinline BfmeParserBindingBaseVE(BfmeParserRegistryVE *registry, void *label, void *parentLabel)
	{ reinterpret_cast<DataChunkParser *>(this)->DataChunkParser::DataChunkParser((DataChunkInput *)registry, (const AsciiString *)label, (const AsciiString *)parentLabel); }

	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);

private:
	BfmeParserRegistryVE *m_registry;
	void *m_token;
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
typedef bool (SidesList::*BfmeSidesListChunkCallback)(DataChunkInput &, DataChunkInfo *);

class BfmeParserBindingVE : public BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingVE(SidesList *owner, BfmeSidesListChunkCallback callback,
		DataChunkInput *input, const AsciiString &label, const AsciiString &parentLabel);

	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);

private:
	SidesList *m_owner;
	BfmeSidesListChunkCallback m_callback;
};

// ??0BfmeParserBindingVE@@QAE@PAVSidesList@@P81@AE_NAAVDataChunkInput@@PAUDataChunkInfo@@@ZPAV2@ABVAsciiString@@5@Z
BfmeParserBindingVE::BfmeParserBindingVE(SidesList *owner, BfmeSidesListChunkCallback callback,
	DataChunkInput *input, const AsciiString &label, const AsciiString &parentLabel)
	: BfmeParserBindingBaseVE((BfmeParserRegistryVE *)input, (void *)&label, (void *)&parentLabel),
	  m_owner(owner),
	  m_callback(callback)
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?bfmeSlot0@BfmeParserBindingVE@@UAEXXZ=??_GRva003B241AOwner@@QAEPAXI@Z")
#pragma comment(linker, "/alternatename:?bfmeSlot1@BfmeParserBindingVE@@UAEXXZ=?invoke@Rva000AD770Binding@@QAEEPAX0@Z")
