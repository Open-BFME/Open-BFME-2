// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva005242D7@@QAE@XZ @0x005242D7 47B
// Evidence: chain via rowed 0x00524021 and vector<AsciiString> dtor 0x0002CC70;
// dtor body does UI-erase loop then vector member dtor; 40+ callers
#include <vector>

#include "ascii_string.h"


class Rva00524021
{
public:
	void rva00524021();
};

#include "../../../../GameEngine/Source/Common/BattlePromptArmyPanelClipImplView.h"

Rva005242D7::~Rva005242D7()
{
	((Rva00524021 *)this)->rva00524021();
}
