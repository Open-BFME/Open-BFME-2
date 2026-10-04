// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// ??0Rva0030C97E@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x0030C97E 104B.
// StandingWaveAreas parser binding ctor, same recipe as siblings Rva000AEFAA
// (BlendTileData) and Rva000AEF42 (HeightMapData): AsciiString literal plus
// empty-string fallback for null parent label, base pin 0x000ABB87,
// vtable 0x0080894C, owner at +0x0C, caller 0x000AF423 in 0x000AF238.
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

class Rva0030C97E : public BfmeParserBindingBaseVE
{
public:
	Rva0030C97E(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	void *m_owner;
};

Rva0030C97E::Rva0030C97E(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("StandingWaveAreas"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString)),
	m_owner(owner)
{
}
