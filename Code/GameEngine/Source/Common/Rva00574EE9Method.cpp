// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva00574EE9@Rva00574EA2@@QAEXXZ retail 0x00574EE9..0x00575038 (335 bytes).
// Third step of the per-frame method 0x00575038 (which calls the rowed
// 0x00574EA2 and then this on the same object): lazily caches the panel
// returned by the rowed getter 0x0042D6FD on the manager at +0x20 into +0x24,
// registers the observer base at +0x10 with the panel's observable at +4 (rowed
// append 0x005A0B4C) and shows it (slots 1 and 7) unless the living-world
// state gates it; then keeps the panel shown following the rowed living-world
// check 0x002B254F and the campaign state flag at +0x20 behind 0x002B256E,
// flashes command button 0 once (+0x7C, 5.0f) and when slot 0 is empty fills
// it with a reference made by the rowed factory 0x00574BA5 (released through
// the rowed 0x0007DEEF). WorldBuilder twin 0x014CA340 is unnamed; its callees
// name the observable as Observable<StrategicHUD::SelectionDetailsUIObserver>
// and the command UI calls as StrategicHUD::CommandUI FlashButton
// IsButtonInSlot and CreateButtonInSlot (virtual slots 4 0 and 1 here).
#include "BattlePromptCallbackPayloadView.h"

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva002B256EState
{
	unsigned char m_pad00[0x20];
	bool m_flag20; // +0x20
};

#include "../../Include/Common/Rva002B254F.h"
#include "../../Include/Common/Rva002B256E.h"

#include "../../Include/Common/Rva0042D6FDPtrChaseField.h"

#include "../../Include/Common/Rva0042D69DPtrChaseField.h"

#include "../../Include/Common/Rva0042D6B4PtrChaseField.h"

struct Rva002BA8F1Listener
{
	char opaque[4];
};

#include "../../Include/Common/Rva005A0B4CList.h"

class Rva00574ABB
{
public:
	struct Payload
	{
		Payload(int first, int second) { v[0] = first; v[1] = second; }
		int v[2];
	};
	Rva00574ABB(const Payload *src) throw();
	// Inline empty, as Rva005CE259Ctor.cpp's view: its deleting-dtor copy is
	// first in link order and inlines this body.
	virtual ~Rva00574ABB() {}
	virtual RvaCloneResult<Rva00574ABB> clone() const;
	int m_ref;
	Payload m_data;
};

// Visible-callee lever (U1 r6): cl 13.10 only shares the byte temp of show(flag) with the 8-byte payload
// (frame 0xc instead of 0x10) when the factory it calls is call-free apart from operator new, so the rowed
// constructor 0x00574ABB (vptr install, zero count, copy of the payload words) is defined here as well.
inline Rva00574ABB::Rva00574ABB(const Payload *src) throw() : m_ref(0), m_data(*src) {}

inline __declspec(noinline) RvaCloneResult<Rva00574ABB> Rva00574BA5Create(const Rva00574ABB::Payload *src)
{
	return RvaCloneResult<Rva00574ABB>(new Rva00574ABB(src));
}

class Rva00574EE9Panel
{
public:
	virtual bool isShown();
	virtual void show(bool shown);
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void refresh();
};

class Rva00574EE9CommandUI
{
public:
	virtual bool isButtonInSlot(int slot);
	virtual void createButtonInSlot(int slot, const RvaCloneResult<Rva00574ABB> &button);
	virtual void slot02();
	virtual void slot03();
	virtual void flashButton(int slot, float seconds);
};

class Rva00574EA2
{
public:
	void rva00574EE9();

private:
	Rva00574EE9Panel *getPanel() const { return (Rva00574EE9Panel *)m_cache24; }

	char m_pad00[0x10];
	Rva002BA8F1Listener m_lis10; // +0x10
	char m_pad14[0x0C];
	void *m_mgr20; // +0x20
	int m_cache24; // +0x24
	char m_pad28[0x7C - 0x28];
	bool m_flashed7C; // +0x7C
};

void Rva00574EA2::rva00574EE9()
{
	if (m_cache24 == 0)
	{
		int panel = ((Rva0042D6FDPtrChaseField *)m_mgr20)->get();
		m_cache24 = panel;
		if (panel != 0)
		{
			((Rva005A0B4CList *)(panel + 4))->append(&m_lis10);
			if (!(unsigned char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F()
				|| ((Rva002B256EState *)((Rva002B256E *)TheLivingWorldLogic)->rva002B256E())->m_flag20)
			{
				getPanel()->show(true);
				getPanel()->refresh();
			}
		}
	}
	if (m_cache24 == 0)
		return;

	if (TheLivingWorldLogic && (unsigned char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F())
	{
		bool flag = ((Rva002B256EState *)((Rva002B256E *)TheLivingWorldLogic)->rva002B256E())->m_flag20;
		getPanel()->show(flag);
		if (flag && !m_flashed7C)
		{
			Rva00574EE9CommandUI *ui = (Rva00574EE9CommandUI *)((Rva0042D69DPtrChaseField *)m_mgr20)->get();
			if (ui)
			{
				ui->flashButton(0, 5.0f);
				m_flashed7C = true;
			}
		}
	}
	else if (!getPanel()->isShown())
	{
		getPanel()->show(true);
	}

	Rva00574EE9CommandUI *ui = (Rva00574EE9CommandUI *)((Rva0042D69DPtrChaseField *)m_mgr20)->get();
	if (ui && !ui->isButtonInSlot(0))
	{
		int button = ((Rva0042D6B4PtrChaseField *)m_mgr20)->get();
		if (button)
		{
			Rva00574ABB::Payload payload(button, m_cache24);
			RvaCloneResult<Rva00574ABB> result = Rva00574BA5Create(&payload);
			ui->createButtonInSlot(0, result);
		}
	}
}
