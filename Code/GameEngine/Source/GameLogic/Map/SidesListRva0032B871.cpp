// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// ?rva0032B871@SidesList@@QAEX_N@Z, retail 0x0032B871..0x0032B88C (27 bytes,
// RET 4): store the flag at +0xF7C, then post the slot +0x24 member callback
// (the compiler vcall thunk 0x000D20D6) with this owner through the +0x10
// notifier (rowed SidesListNotifier::post 0x0032B522, SidesListCtor.cpp).
// Target evidence: the rowed neighbour SidesList::exchangeFlag 0x0032B833
// swaps the same +0xF7C byte and posts through the same +0x10 notifier.
// Only this prefix of SidesList is represented; the method name and the
// listener's slot identity are unknown (address-derived).
class Rva00281A15Listener
{
public:
	virtual void notify(void *);
	virtual void slot04(void *);
	virtual void slot08(void *);
	virtual void slot0C(void *);
	virtual void slot10(void *);
	virtual void slot14(void *);
	virtual void slot18(void *);
	virtual void slot1C(void *);
	virtual void slot20(void *);
	virtual void slot24(void *);
};

#include "../../../Include/Common/Rva00330757Member.h"

class Rva00281A15Listener;
#include "../../../Include/Common/SidesListNotifier.h"

#include "../../../Include/Common/SidesList.h"

void SidesList::rva0032B871(bool value)
{
	m_fieldF7C = value;
	post(&Rva00281A15Listener::slot24, this);
}
