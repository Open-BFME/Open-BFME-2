// cl: /O1 /arch:SSE /G7 /EHsc /MD
// ?rva00526F0B@Rva005258B2@@QAEXXZ @0x00526F0B 7B: forwards to the rowed hero-select
// interface update (0x005264F5) on the implementation object this one holds at +0
// (tail call). Callers: the AptPalantir update (0x002D65F6).
#include "../../Include/GameClient/InGameHeroSelectInterface.h"

class Rva005258B2
{
public:
	void rva00526F0B();
private:
	InGameHeroSelectInterface::Impl *m_impl;
};

void Rva005258B2::rva00526F0B()
{
	m_impl->Update();
}
