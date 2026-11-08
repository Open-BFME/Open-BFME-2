// cl: /MD
// ??0Rva0030F47A@@QAE@PAX@Z at 0x0030F47A (53B).
// Vtable ctor with PlayerList chain for +0x14 and arg for +0x10 plus zeroed
// tail. Evidence: vtable 0x809840, ThePlayerList 0xDFEEE8 +0x10 +0x54,
// 5 callers, unblocks 3.

#include "../../Include/Common/Player.h"
#include "../../Include/Common/PlayerList.h"

extern "C" const void *const __identifier("??_7GameMessage@@6B@")[];

class Rva0030F47A
{
public:
	Rva0030F47A(void *arg);
private:
	void *m_vft;
	int m_04;
	int m_08;
	int m_0C;
	void *m_10;
	int m_14;
	bool m_18;
	int m_1C;
	int m_20;
};

Rva0030F47A::Rva0030F47A(void *arg)
{
	*(const void **)this = __identifier("??_7GameMessage@@6B@");
	m_14 = ThePlayerList->m_local->m_playerIndex;
	m_10 = arg;
	m_1C = 0;
	m_20 = 0;
	m_18 = false;
	m_0C = 0;
	m_04 = 0;
	m_08 = 0;
}
