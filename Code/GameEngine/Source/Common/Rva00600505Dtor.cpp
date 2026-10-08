// cl: /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva00600505@@UAE@XZ @0x00600505 11B
// Virtual dtor: stores vtable 0x0087A64C then tail-jmps to pinned base dtor 0x005FEF65.
// Evidence: pin names the dtor; deleting dtor 0x00600510 calls it; vtable 0x00C7A64C slot0; base vtable 0x00C7A464.
#include "BattlePromptArmyPanelView.h"

class Rva00600505 : public Rva005FEF65
{
public:
	Rva00600505(int a, int b, const Rva005FEF11Input **inputs);
	virtual ~Rva00600505();
};

// ??0Rva00600505@@QAE@HHPAPBURva005FEF11Input@@@Z @0x006004C1 68B: the
// constructor, Rva005FF13A's twin (0x005FF0F6) with clip state 1 instead of
// 0: the rowed base constructor 0x005FEFCC (EH state 0 once built), vtable
// 0x00C7A64C, then the inherited +0x08 clip's rowed state setter 0x005FF4BD.
// The shared view keeps that clip private to the base and its one friend, so
// it is reached here by its offset.
Rva00600505::Rva00600505(int a, int b, const Rva005FEF11Input **inputs)
	: Rva005FEF65(a, b, inputs)
{
	reinterpret_cast<Rva005FED2A *>(reinterpret_cast<char *>(this) + 0x08)->rva005FF4BD(1);
}

Rva00600505::~Rva00600505()
{
}
