// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// ??0Rva0030BF80@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x0030BF80 104B.
// RiverAreas parser binding ctor, same recipe as sibling Rva0030C97E
// (StandingWaveAreas): AsciiString literal plus empty-string fallback for
// null parent label, base pin 0x000ABB87, owner at +0x0C,
// caller 0x000AF3F3 in 0x000AF238.
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

class Rva0030BF80 : public BfmeParserBindingBaseVE
{
public:
	Rva0030BF80(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	void *m_owner;
};

Rva0030BF80::Rva0030BF80(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("RiverAreas"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString)),
	m_owner(owner)
{
}
