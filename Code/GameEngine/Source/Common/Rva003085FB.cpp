// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva003085FB@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x003085FB 104B
// StandingWaterAreas parser binding ctor, same recipe as Rva000AEFAA/Rva000AEF42 (BlendTileData/HeightMapData).
// Evidence: unlock lane, caller 0x000AF3C3 in 0x000AF238 (same caller as AEFAA/AEF42), literal StandingWaterAreas, base pin 0x000ABB87.
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

class Rva003085FB : public BfmeParserBindingBaseVE
{
public:
	Rva003085FB(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	void *m_owner;
};

Rva003085FB::Rva003085FB(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("StandingWaterAreas"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString)),
	m_owner(owner)
{
}
