// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva00328B9A@@QAE@PAVBfmeParserRegistryVE@@PBVAsciiString@@@Z, retail 0x00328B9A, 98 bytes.
// PolygonTriggers parser binding ctor same recipe as sibling Rva00328BFC
// WaterAreas: AsciiString literal plus empty-string fallback for null parent
// label base pin 0x000ABB87 vtable 0x0080D8CC caller 0x00328C76 constructs
// member via this function; landing makes 0x00328C5E ready.
// Evidence: string literal PolygonTriggers plus TheEmptyString plus rowed
// StringBase 0x00037BA0 plus pinned base 0x000ABB87 plus rowed releaseBuffer
// 0x00036410.
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

class Rva00328B9A : public BfmeParserBindingBaseVE
{
public:
	Rva00328B9A(BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
};

Rva00328B9A::Rva00328B9A(BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("PolygonTriggers"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString))
{
}
