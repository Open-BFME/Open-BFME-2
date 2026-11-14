// cl: /DNDEBUG /MD
#include "../../Include/GameClient/AptSaveLoad.h"
// ?rva002B8860@Rva002B8860@@QAEXXZ @0x002B8860 140B. guard +0x168, globals, vector erase, clear, singleton fwd, forEach, tail endgame.
// Evidence: caller 0x002B9DC7, callees rowed/pinned, vtable slot 0x28, push 0x9CB260.
void Rva00433D27Enable();
void Rva00437E9C(int);

#include "../../Include/Common/Rva00222A8BTarget.h"
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
namespace _STL
{
template <class _Tp> class allocator
{
};
template <class _Tp, class _Alloc> class vector
{
public:
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end;
	_Tp *erase(_Tp *first, _Tp *last);
};
}

#include "../../Include/Common/Rva002BED91.h"

#include "../../Include/Common/Rva002B6151Listener.h"
class Rva002B6151List
{
public:
	void forEach(void (Rva002B6151Listener::*notify)(void *), void *arg);
private:
	Rva002B6151Listener **m_begin;
	Rva002B6151Listener **m_end;
	Rva002B6151Listener **m_capacity;
	unsigned int m_index;
};

#include "../../Include/Common/Rva005CB260.h"

#include "../../Include/GameLogic/LivingWorldLogic.h"

class Rva002B8860
{
	friend class LivingWorldLogic;

public:
	void rva002B8860();
private:
	char m_pad0[0x4C];
	Rva002B6151List m_4c;
	char m_pad5C[0x100 - 0x5C];
	void *m_100;
	char m_pad104[0x154 - 0x104];
	_STL::vector<TreeHintRef00217D4C, _STL::allocator<TreeHintRef00217D4C> > m_154;
	Rva002BED91 m_160;
	void *m_164;
	unsigned char m_168;
	char m_pad169[0x175 - 0x169];
	unsigned char m_175;
};

void Rva002B8860::rva002B8860()
{
	if (m_168)
		return;
	if (AptSaveLoad::s_instance)
	{
		Rva00433D27Enable();
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->v10();
	}
	if (TheGameLogic)
		TheGameLogic->rva00376D49();
	m_168 = 1;
	m_164 = (char *)m_100 + 0x3C;
	_STL::vector<TreeHintRef00217D4C, _STL::allocator<TreeHintRef00217D4C> > *p154 = &m_154;
	p154->erase(p154->_M_start, p154->_M_finish);
	m_160.clear();
	m_175 = 1;
	Rva00437E9C(1);
	m_4c.forEach(reinterpret_cast<void (Rva002B6151Listener::*)(void *)>(static_cast<void (Rva005CB260::*)()>(&Rva005CB260::rva005CB260)), this);
	((LivingWorldLogic *)this)->ShowEndGameSplashScreen();
}

// ?rva002B88EC@LivingWorldLogic@@QAEXXZ @0x002B88EC 97B, retail's next body
// after 0x002B8860 on the same object (0x002B8860 itself ends by calling
// LivingWorldLogic::ShowEndGameSplashScreen on its this): the +0x154 vector
// erase, +0x160 clear, +0x175 latch and Rva00437E9C(1) of 0x002B8860, then
// +0x164 = -1, the HideEndGame firer 0x002B29BD (retail loads ECX = this
// before the call although the 27B callee ignores it), the +0x4C listener
// walk unless +0x168 is set, and GameLogic's exit tail 0x0023D0E3(false).
void LivingWorldLogic::rva002B88EC()
{
	Rva002B8860 *self = reinterpret_cast<Rva002B8860 *>(this);
	_STL::vector<TreeHintRef00217D4C, _STL::allocator<TreeHintRef00217D4C> > *p154 = &self->m_154;
	p154->erase(p154->_M_start, p154->_M_finish);
	self->m_160.clear();
	self->m_175 = 1;
	Rva00437E9C(1);
	self->m_164 = (void *)-1;
	rva002B29BD();
	if (!self->m_168)
		self->m_4c.forEach(reinterpret_cast<void (Rva002B6151Listener::*)(void *)>(static_cast<void (Rva005CB260::*)()>(&Rva005CB260::rva005CB260)), this);
	TheGameLogic->DoExitMap(false);
}
