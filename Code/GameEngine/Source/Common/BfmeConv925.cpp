// A keyed lookup and a two-hop store.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeConv925.cpp); trimmed to the two T1
// bodies the sweep places.

// Open-BFME5 conversions.

struct BfmeNodeLC
{
	virtual void bfmeSlot92500();
	virtual void bfmeSlot92501();
	virtual void bfmeSlot92502();
	virtual void bfmeSlot92503();
	virtual void bfmeSlot92504();
	virtual void bfmeSlot92505();
	virtual void bfmeSlot92506();
	virtual void bfmeTail925B();
	char m_bfmePad0[4];
	void *m_bfmeP;
	char m_bfmePad1[0x10];
	unsigned short m_bfmeU;
	unsigned short m_bfmeV;
	char m_bfmePad2[0xc];
	void *m_bfmeQ;
	char m_bfmePad3[4];
	void *m_bfmeR;
};

#include "../../Include/GameClient/Bfme2GameWindow.h"

#include "../../Include/Common/BfmeKeyLC.h"

void *bfmeGo925A(BfmeKeyLC *k)
{
	BfmeNodeLC *comboBoxData = (BfmeNodeLC *)((GameWindow *)k)->winGetUserData();
	if (comboBoxData) {
		void *listBox = comboBoxData->m_bfmeQ;
		if (listBox)
			return listBox;
	}
	return 0;
}

class BfmeThing925D
{
public:
	void bfmeGo925D(void *v);
	BfmeKeyLC *m_bfmeKey;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void BfmeThing925D::bfmeGo925D(void *v)
{
	BfmeKeyLC *k = m_bfmeKey;
	if (k) {
		BfmeNodeLC *o = (BfmeNodeLC *)((GameWindow *)k)->winGetUserData();
		BfmeNodeLC *p = (BfmeNodeLC *)((GameWindow *)o->m_bfmeP)->winGetUserData();
		p->m_bfmeR = v;
	}
}

// ?bfmeAnchorBfmeGo925D absent-from-retail
void bfmeAnchorBfmeGo925D(BfmeThing925D *p)
{
	p->bfmeGo925D(0);
}

