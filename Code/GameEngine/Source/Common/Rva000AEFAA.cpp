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

// ??0Rva000AF0E4@@QAE@PAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x000AF0E4 98B
// PostEffectsChunk binding, 2-arg (registry, parentLabel), no owner member.
// Evidence: same base pin 0x000ABB87 and caller 0x000AF238 as siblings; literal "PostEffectsChunk"; vtable g_00BC9600; ret 8.
class Rva000AF0E4 : public BfmeParserBindingBaseVE
{
public:
	Rva000AF0E4(BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
};

Rva000AF0E4::Rva000AF0E4(BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("PostEffectsChunk"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString))
{
}

// ??0Rva000AF082@@QAE@PAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x000AF082 98B
// GlobalLighting binding, 2-arg (registry, parentLabel), no owner member.
// Evidence: same base pin 0x000ABB87 and caller 0x000AF238 as siblings; literal "GlobalLighting"; vtable g_00BC95F8; ret 8.
class Rva000AF082 : public BfmeParserBindingBaseVE
{
public:
	Rva000AF082(BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
};

Rva000AF082::Rva000AF082(BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("GlobalLighting"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString))
{
}
