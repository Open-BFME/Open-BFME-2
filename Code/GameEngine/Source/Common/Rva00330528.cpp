// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva00330528@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x00330528 104B
// CameraAnimationList parser binding ctor, same recipe as Rva003085FB/Rva000AEFAA (StandingWaterAreas/BlendTileData).
// Evidence: unlock lane, caller 0x000AF540 in 0x000AF238 (same caller as siblings), literal CameraAnimationList, vtable g_00C0DB58, base pin 0x000ABB87.
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

class Rva00330528 : public BfmeParserBindingBaseVE
{
public:
	Rva00330528(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	void *m_owner;
};

Rva00330528::Rva00330528(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("CameraAnimationList"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString)),
	m_owner(owner)
{
}
