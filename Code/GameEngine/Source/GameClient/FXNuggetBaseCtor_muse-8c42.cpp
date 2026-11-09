// cl: /DNDEBUG /MD /EHsc
// ??0Rva001DFEAABase@@QAE@XZ @0x001DFEAA 117B
// FXNugget-family shared base ctor. Donor: BFME1 FXNugget ctor
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/FXNuggetConstructor.cpp)
// with BFME2 drift: four 76-byte members at +0x10/+0x5C/+0xA8/+0xF4 (Rva0042526Member 0x4C memset)
// two 4-byte filters at +0x08/+0x0C (Rva003623E5Member) trailing +0x140=2 +0x144=0
// vtable 0x00BDC940 callers 13 matched FXNugget ctors (EvaEvent 0x001DFFFA Sound 0x001E00A6 etc).
#include "../../Include/GameClient/Rva001DFEAABase.h"

Rva001DFEAABase::Rva001DFEAABase()
{
	m_nuggetType = 0;
	m_140 = 2;
	m_144 = false;
}
