// cl: /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva00600505@@UAE@XZ @0x00600505 11B
// Virtual dtor: stores vtable 0x0087A64C then tail-jmps to pinned base dtor 0x005FEF65.
// Evidence: pin names the dtor; deleting dtor 0x00600510 calls it; vtable 0x00C7A64C slot0; base vtable 0x00C7A464.
#include "BattlePromptArmyPanelView.h"

class Rva00600505 : public Rva005FEF65
{
public:
	virtual ~Rva00600505();
};

Rva00600505::~Rva00600505()
{
}
