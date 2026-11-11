// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva00300419@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x00300419 104B
// MPPositionList parser binding ctor, same recipe as Rva003085FB (StandingWaterAreas 104B).
// Evidence: unlock lane, caller 0x003030E4 in 0x00302F2B, literal MPPositionList, base pin 0x000ABB87.
#include "ascii_string.h"

class BfmeParserRegistryVE
{
public:
	void *bfmeRegister(void *a, void *b, void *c, void *d);
};

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
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
private:
	BfmeParserRegistryVE *m_registry;
	void *m_token;
};

class Rva00300419 : public BfmeParserBindingBaseVE
{
public:
	Rva00300419(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	void *m_owner;
};

Rva00300419::Rva00300419(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("MPPositionList"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString)),
	m_owner(owner)
{
}
