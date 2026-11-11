// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
//
// ?rva00455076@CastleBehavior@@UAEXABUOpaqueRefElement4@@H@Z 104B @0x00455076:
// slot 13 of CastleBehavior vtable 0x0081A780 (and Rva00455050 0x00840608).
// Builds BfmeAudioEventPrefix136 from OpaqueRefElement4+0, applies int arg
// via rowed CondSetter, submits via TheAudio slot 0x64, stores result at
// +0x24, destroys tail record. Evidence: vtable slots, rowed E8 callees,
// TheAudio/TheEmptyString-style extern names in packet, prev/next WallHub
// neighbours. Owner class proven by vtable; method name stays honest.

#include "Common/BfmeAudioEventPrefix136.h"

#include "../../../../Include/GameLogic/Module/Rva002D9531.h"

#include "../../../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

class CastleBehavior
{
public:
	virtual void rva00455076(const OpaqueRefElement4 &o, int v);
private:
	char m_pad04[0x24 - 4];
	int m_24;
};

void CastleBehavior::rva00455076(const OpaqueRefElement4 &opaqueRefElement4, int v)
{
	BfmeAudioEventPrefix136 tmp(opaqueRefElement4, 0);
	((Rva002D9531 *)&tmp)->rva002D9531(v);
	int r = TheAudio->addAudioEvent(&tmp);
	m_24 = r;
}
