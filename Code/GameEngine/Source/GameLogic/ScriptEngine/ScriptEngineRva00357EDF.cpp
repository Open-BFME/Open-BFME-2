// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00357EDF@ScriptEngine@@QAEXHABVAsciiString@@H@Z @0x00357EDF 50B
// ScriptEngine per-player timer push: m_playerLists1A308[index].push_back({crc,val}).
// Evidence: CRC 0x3ECA13 plus rowed list<BfmeSpecialPowerTimer8>::push_back 0x4DE74D,
// lea index*4+0x1A308 from neighbours 0x00357E7B/0x00357F43, ret 0xc void 3-arg.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

class AsciiString;
unsigned long __cdecl Rva003ECA13Get(const AsciiString &s);

#include "../../Common/BfmeSpecialPowerTimer8.h"

#include "../../../Include/GameLogic/ScriptEngine.h"

void ScriptEngine::rva00357EDF(int playerIndex, const AsciiString &asciiString, int val)
{
	BfmeSpecialPowerTimer8 timer;
	timer.m_templateID = Rva003ECA13Get(asciiString);
	timer.m_readyFrame = (unsigned int)val;
	m_finishedSpecialPowers[playerIndex].push_back(timer);
}
