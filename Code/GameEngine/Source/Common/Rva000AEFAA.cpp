// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva000AEFAA@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x000AEFAA 104B
// Evidence: unlock lane, BlendTileData literal, vtable g_00BC95D8, base pin 0x000ABB87, caller 0x000AF238.
#include "ascii_string.h"

class BfmeParserRegistryVE
{
public:
	void *bfmeRegister(void *a, void *b, void *c, void *d);
};

class BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingBaseVE(BfmeParserRegistryVE *registry, void *label, void *parentLabel);
	virtual ~BfmeParserBindingBaseVE();
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
private:
	BfmeParserRegistryVE *m_registry;
	void *m_token;
};

class Rva000AEFAA : public BfmeParserBindingBaseVE
{
public:
	Rva000AEFAA(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	void *m_owner;
};

Rva000AEFAA::Rva000AEFAA(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("BlendTileData"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString)),
	m_owner(owner)
{
}

// ??0Rva000AEF42@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x000AEF42 104B
// Evidence: unlock lane, HeightMapData literal, vtable g_00BC95D0, base pin 0x000ABB87, caller 0x000AF238.
class Rva000AEF42 : public BfmeParserBindingBaseVE
{
public:
	Rva000AEF42(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	void *m_owner;
};

Rva000AEF42::Rva000AEF42(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("HeightMapData"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString)),
	m_owner(owner)
{
}
