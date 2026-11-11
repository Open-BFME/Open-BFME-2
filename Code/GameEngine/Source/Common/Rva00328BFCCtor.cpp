// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva00328BFC@@QAE@PAVBfmeParserRegistryVE@@PBVAsciiString@@@Z, retail 0x00328BFC, 98 bytes.
// WaterAreas parser binding ctor same recipe as siblings Rva0030C97E
// StandingWaveAreas plus Rva000AEFAA BlendTileData: AsciiString literal plus
// empty-string fallback for null parent label base pin 0x000ABB87
// vtable 0x0080D8CC caller 0x00328C5E constructs member at +0x0c.
// Evidence: string literal WaterAreas plus TheEmptyString plus rowed StringBase
// 0x00037BA0 plus pinned base 0x000ABB87 plus rowed releaseBuffer 0x00036410.
#include "ascii_string.h"

class BfmeParserRegistryVE
{
public:
	void *bfmeRegister(void *a, void *b, void *c, void *d);
};

class DataChunkInput;
#include "../../Include/Common/DataChunkParser.h"

class __declspec(novtable) BfmeParserBindingBaseVE
{
public:
	// The base is the rowed DataChunkParser ctor (0x000ABB87), called by that name.
	__declspec(dllimport) __forceinline BfmeParserBindingBaseVE(BfmeParserRegistryVE *registry, void *label, void *parentLabel)
	{ reinterpret_cast<DataChunkParser *>(this)->DataChunkParser::DataChunkParser((DataChunkInput *)registry, (const AsciiString *)label, (const AsciiString *)parentLabel); }
	virtual ~BfmeParserBindingBaseVE();
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
private:
	BfmeParserRegistryVE *m_registry;
	void *m_token;
};

class Rva00328BFC : public BfmeParserBindingBaseVE
{
public:
	Rva00328BFC(BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
};

Rva00328BFC::Rva00328BFC(BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("WaterAreas"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString))
{
}
