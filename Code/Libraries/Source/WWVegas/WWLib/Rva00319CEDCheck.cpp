// stlport
// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva00319CED@SpawnArmy@@QAE_NXZ, retail 0x00319CED, 20 bytes.
// Evidence: push of AsciiString::TheEmptyString VA 0x009E0878 then add ecx,0x2c
// then rowed StringBase<char>::compare 0x000069D6 then neg/sbb/neg bool normalize.
// Callers test al,al (e.g. 0x004E23C1). Owner unknown so honest Rva address name.
#include "ascii_string.h"

#include "../../../../GameEngine/Include/Common/SpawnArmy.h"

bool SpawnArmy::rva00319CED()
{
	return m_2c.compare(AsciiString::TheEmptyString) != 0;
}
