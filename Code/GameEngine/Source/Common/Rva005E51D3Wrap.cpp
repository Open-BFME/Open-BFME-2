// cl: /DNDEBUG /MD
// ?rva005E51D3@Rva005E51D3@@QAEXXZ @0x005E51D3 31B lea-call-push-call.
// Same shape as twins 0x005E3E41/0x005E4389 but first is empty 0x00B3FD0.
// Address-derived.
class VirtualBaseTable
{
public:
	int m_pad0;
	int m_virtualBaseOffset;
};

#include "../../Include/Common/Rva000B3FD0Empty.h"

// API-only declaration: the +4 owner pointer is passed unchanged to the
// now-owned ArmyDetailsPanel callback. No owner layout is asserted here.
namespace StrategicInGameUI {
class ArmyDetailsPanel { public: class Impl { public: void OnIconLeftClicked(int); }; };
}

class Rva005E51D3
{
public:
	void rva005E51D3();
};

void Rva005E51D3::rva005E51D3()
{
	unsigned char *th = (unsigned char *)this;
	VirtualBaseTable **ppOuter = (VirtualBaseTable **)(th - 0x14);
	VirtualBaseTable *pOuter = *ppOuter;
	int inner4 = pOuter->m_virtualBaseOffset;
	Rva000B3FD0Empty *pFirst = (Rva000B3FD0Empty *)(inner4 + (int)th - 0x14);
	pFirst->rva000B3FD0Empty();
	int arg = *(int *)(th - 0x0C);
	StrategicInGameUI::ArmyDetailsPanel::Impl *pSecond = *(StrategicInGameUI::ArmyDetailsPanel::Impl **)(th - 0x10);
	pSecond->OnIconLeftClicked(arg);
}
