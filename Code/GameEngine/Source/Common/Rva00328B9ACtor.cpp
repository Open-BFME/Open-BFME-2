// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva00328B9A@@QAE@PAVBfmeParserRegistryVE@@PBVAsciiString@@@Z, retail 0x00328B9A, 98 bytes.
// PolygonTriggers parser binding ctor same recipe as sibling Rva00328BFC
// WaterAreas: AsciiString literal plus empty-string fallback for null parent
// label base pin 0x000ABB87 vtable 0x0080D8CC caller 0x00328C76 constructs
// member via this function; landing makes 0x00328C5E ready.
// Evidence: string literal PolygonTriggers plus TheEmptyString plus rowed
// StringBase 0x00037BA0 plus pinned base 0x000ABB87 plus rowed releaseBuffer
// 0x00036410.
#include "ascii_string.h"

#include "../../Include/Common/BfmeParserRegistryVE.h"

class DataChunkInput;
#include "../../Include/Common/DataChunkParser.h"

namespace ParserBindingTable { extern "C" const void *const __identifier("??_7BfmeParserBindingBaseVE@@6B@")[]; }

#include "../../Include/GameLogic/Q1Forwardee0000871A.h"

class __declspec(novtable) BfmeParserBindingBaseVE
{
public:
	// The base is the rowed DataChunkParser ctor (0x000ABB87), called by that name.
	__declspec(dllimport) __forceinline BfmeParserBindingBaseVE(BfmeParserRegistryVE *registry, void *label, void *parentLabel)
	{ reinterpret_cast<DataChunkParser *>(this)->DataChunkParser::DataChunkParser((DataChunkInput *)registry, (const AsciiString *)label, (const AsciiString *)parentLabel); }
	// The parser binding destructor supplies this shared table and cleanup.
	virtual ~BfmeParserBindingBaseVE()
	{
		int token = (int)m_token;
		*(const void **)this = ParserBindingTable::__identifier("??_7BfmeParserBindingBaseVE@@6B@");
		((Q1Forwardee0000871A *)m_registry)->handle(token);
	}
	virtual void bfmeSlot0() = 0;
	virtual void bfmeSlot1() = 0;
private:
	BfmeParserRegistryVE *m_registry;
	void *m_token;
};

class Rva00328B9A : public BfmeParserBindingBaseVE
{
public:
	Rva00328B9A(BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
	// Table 0x0080D8CC slot 1 (0x005CC208): hands the call on to the pure slot 2.
	virtual void bfmeSlot0() { bfmeSlot1(); }
};

Rva00328B9A::Rva00328B9A(BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("PolygonTriggers"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString))
{
}
