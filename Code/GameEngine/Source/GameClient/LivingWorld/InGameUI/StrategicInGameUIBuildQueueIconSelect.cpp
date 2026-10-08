// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon: Select (retail
// 0x005E70F8, 25 bytes), the ctor 0x005E7D77, its refresh 0x005E7C56 and
// the icon-slot listener slots of its vtable 0x00877F14.
// Name: WorldBuilder (StrategicInGameUIBuildQueueDetailsPanel.cpp line 552):
// unless already selected (+0x20), the icon's slot (GetIconSlot, inlined in
// retail as the +0x0C pointer) is put in state 2 through
// StrategicHUD::BuildQueueIconSlot::SetState (retail: virtual slot 9), then
// the icon is marked selected.
// Evidence: callers at 0x005E7A33 0x005E7CD4 0x005E87BA.

struct Rva005E76AEContext;
class Rva005E72B4Queue;

namespace StrategicHUD
{
class BuildQueueIconSlot
{
public:
	virtual bool v0();
	virtual void v1(void *listener);
	virtual void v2();
	virtual void v3(void *value);
	virtual void v4();
	virtual void v5(int value);
	virtual void v6();
	virtual void SetQuantity(int quantity);
	virtual void v8();
	virtual void SetState(int state);
};
}

// Impl::GetIconAtQueueIndex in WorldBuilder (rowed address-named, 0x005E73E4).
class Rva005E73E4
{
public:
	void *rva005E73E4(int queueIndex);
};

// The icon's help hide check (rowed address-named, 0x005E73B2).
class Rva005E73B2
{
public:
	void rva005E73B2();
};

namespace StrategicInGameUI
{
class BuildQueueDetailsPanel
{
public:
	class Impl;
};

class BuildQueueDetailsPanel::Impl
{
public:
	class Icon;

	void SelectQueueIndex(int queueIndex);
	void ShowUnitStats(int queueIndex); // 0x005E7B28 (WorldBuilder name, pinned)

private:
	Icon *GetIconAtQueueIndex(int queueIndex) { return (Icon *)((Rva005E73E4 *)this)->rva005E73E4(queueIndex); }

	char m_pad00[0x18];
 Rva005E76AEContext *m_context;
 Rva005E72B4Queue *m_queue;
 char m_pad20[0x30-0x20];
	int m_selectedQueueIndex; // +0x30, -1 when none
};

// The +0x1C member cleared by the ctor and destroyed on unwind.
struct Rva005E7D77Member
{
	Rva005E7D77Member() : m_value(0) {}
	~Rva005E7D77Member();

	int m_value;
};

// Target facts: vtable 0x00877F14 = { 0x005E7DF7, 0x005E712A, 0x005E73DC,
// 0x005E7977, 0x005E715F, 0x005E7166 }: the icon slot's listener. WorldBuilder
// names slots 0..3 OnBuildQueueIconSlotLeftClicked / RightClicked / RollOut /
// RollOver; slots 4 and 5 (clear / set +0x21) are unnamed there.
class BuildQueueDetailsPanel::Impl::Icon
{
public:
	Icon(Impl *owner, int queueIndex, StrategicHUD::BuildQueueIconSlot *iconSlot, void *value10, int value14, int quantity);
	void Select();
	void Deselect(); // 0x005E7111 (rowed)
	void rva005E7C56();
	void rva005E789A(); // 0x005E789A (pinned)

	virtual void OnBuildQueueIconSlotLeftClicked(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRightClicked(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRollOut(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRollOver(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void rva005E715F(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void rva005E7166(StrategicHUD::BuildQueueIconSlot *slot);

private:
	StrategicHUD::BuildQueueIconSlot *GetIconSlot() { return m_iconSlot; }

	Impl *m_owner;									// +0x04
	int m_queueIndex;								// +0x08
	StrategicHUD::BuildQueueIconSlot *m_iconSlot;	// +0x0C
	void *m_10;										// +0x10
	int m_14;										// +0x14
	int m_quantity;									// +0x18
	Rva005E7D77Member m_1c;							// +0x1C
	bool m_selected;								// +0x20
	bool m_21;										// +0x21
};
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::Select()
{
	if (m_selected)
		return;
	GetIconSlot()->SetState(2);
	m_selected = true;
}

// WorldBuilder Icon::Icon (StrategicInGameUIBuildQueueDetailsPanel.cpp:455).
StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::Icon(Impl *owner, int queueIndex, StrategicHUD::BuildQueueIconSlot *iconSlot, void *value10, int value14, int quantity)
	: m_owner(owner), m_queueIndex(queueIndex), m_iconSlot(iconSlot), m_10(value10), m_14(value14), m_quantity(quantity), m_selected(false), m_21(false)
{
	rva005E7C56();
}

// 0x005E7C56 (called by the ctor; unnamed in WorldBuilder): pushes the
// icon's values into its slot and registers itself as the slot's listener.
void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::rva005E7C56()
{
	StrategicHUD::BuildQueueIconSlot *slot = GetIconSlot();
	slot->v3(m_10);
	slot->v5(m_14);
	slot->SetQuantity(m_quantity);
	slot->SetState(m_selected ? 2 : 1);
	slot->v1(this);
	if (slot->v0())
		rva005E789A();
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::OnBuildQueueIconSlotLeftClicked(StrategicHUD::BuildQueueIconSlot *slot)
{
	m_owner->SelectQueueIndex(m_queueIndex);
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::OnBuildQueueIconSlotRollOut(StrategicHUD::BuildQueueIconSlot *slot)
{
	((Rva005E73B2 *)this)->rva005E73B2();
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::OnBuildQueueIconSlotRollOver(StrategicHUD::BuildQueueIconSlot *slot)
{
	rva005E789A();
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::rva005E715F(StrategicHUD::BuildQueueIconSlot *slot)
{
	m_21 = false;
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::rva005E7166(StrategicHUD::BuildQueueIconSlot *slot)
{
	m_21 = true;
}

// WorldBuilder Impl::SelectQueueIndex: selecting the selected index again
// deselects it; the unit stats follow the selection.
void StrategicInGameUI::BuildQueueDetailsPanel::Impl::SelectQueueIndex(int queueIndex)
{
	if (queueIndex != m_selectedQueueIndex)
	{
		if (m_selectedQueueIndex >= 0)
			GetIconAtQueueIndex(m_selectedQueueIndex)->Deselect();
		GetIconAtQueueIndex(queueIndex)->Select();
		m_selectedQueueIndex = queueIndex;
	}
	else
	{
		GetIconAtQueueIndex(queueIndex)->Deselect();
		m_selectedQueueIndex = -1;
	}
	ShowUnitStats(m_selectedQueueIndex);
}

// Native build-queue file pass. WB StrategicInGameUIBuildQueueDetailsPanel.cpp
// independently supplies the operation and call relationships; retail supplies
// every layout and ABI used here. The generic queue interface's original class
// and the summary's entry types remain unknown, so their views are address-named.
// Rva004E3184 is the existing 88B SpawnArmy temporary view, ctor pin4E30D5 and
// matched dtor4E3184. Its name+2C and integer+48 are native accesses. Summary
// entries at+40/+44 have stride8; queue slots4/12/13 fill a temporary, return
// elapsed time and the production vector. Ordinary file-static C++ helpers
// preserve ECX, ESI/EDI, EDI and EAX private conventions when the true caller
// and callees compile together. All branches, calls, EH and return construction
// are C++; no dummy register parameter or forcing caller is present.
// The existing 59B lookup is rehomed with its actual queue argument, formerly
// implicit in the old standalone wrapper. Each new helper is rowed separately.
#include "ascii_string.h"
#include "unicode_string.h"
class Rva004E3184 { public:
 Rva004E3184(void *);
 virtual ~Rva004E3184();
 char pad04[0x2c-4]; AsciiString name; char pad30[0x48-0x30]; int m_48; char pad4C[0x58-0x4c];
};
class Rva003B8E89 { public: void *rva003B8E89(void *); };
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;
struct Rva005E72B4Production { int *begin,*end,*capacity; };
class Rva005E72B4Queue { public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual bool slot4(int,Rva004E3184 *);
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual int slot12();
 virtual const Rva005E72B4Production *slot13();
};
struct Rva005E72B4Entry { char bytes[8]; };
struct Rva005E72B4Summary { char pad0[0x40]; Rva005E72B4Entry *begin,*end; };
__declspec(noinline) static void *rva005E72B4Get(Rva005E72B4Queue *queue,int id)
{
 Rva004E3184 army(0);
 queue->slot4(id,&army);
 Rva005E72B4Summary *summary=(Rva005E72B4Summary *)((Rva003B8E89 *)TheCampaignManager)->rva003B8E89(&army.name);
 if(!summary) return 0;
 if((summary->end-summary->begin)<1) return 0;
 return summary;
}

class Rva00319CED { public: UnicodeString rva004E25AF(int); };
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *); };
extern Rva002D06CA *TheThingFactory;
struct Rva005E7322MidRet { char pad[4]; AsciiString text; };
class Rva005E7322R { public: Rva005E7322MidRet *mid(int); };
struct Rva005E76AEContext { char pad[0x18]; int m_id; };
__declspec(noinline) static void *rva005E7322Get(Rva005E72B4Queue *queue,int id)
{
 void *r=rva005E72B4Get(queue,id);
 if(!r) return 0;
 AsciiString *name=&((Rva005E7322R *)r)->mid(0)->text;
 if(name->isEmpty()) return 0;
 return TheThingFactory->rva002D06CA(name);
}
__declspec(noinline) static int rva005E7582Get(Rva005E72B4Queue *queue,int index)
{
 int id=queue->slot13()->begin[index];
 Rva004E3184 army(0);
 queue->slot4(id,&army);
 int time=army.m_48;
 if(index==0) time-=queue->slot12();
 return time;
}
__declspec(noinline) static UnicodeString rva005E76AEGet(Rva005E76AEContext *context,Rva005E72B4Queue *queue,int id)
{
 Rva004E3184 army(0);
 if(queue->slot4(id,&army)) return ((Rva00319CED *)&army)->rva004E25AF(context->m_id);
 return UnicodeString::TheEmptyString;
}
__declspec(noinline) static UnicodeString rva005E7721Get(Rva005E76AEContext *context,Rva005E72B4Queue *queue,int index)
{
 return rva005E76AEGet(context,queue,queue->slot13()->begin[index]);
}
class Rva005F772E { public: void rva005F772E(const UnicodeString &); void rva005F7470(); };
class Rva005F7478 { public: void rva005F7478(int); };
class Rva005F7480 { public: void rva005F7480(); };
class Rva005F7488 { public: void rva005F7488(int); };
class Rva005F7490 { public: void rva005F7490(); };
struct Rva005EThing { char pad[0x618]; int m_commandPoints; };
void StrategicInGameUI::BuildQueueDetailsPanel::Impl::ShowUnitStats(int index)
{
 if(index>=0) {
  ((Rva005F772E *)this)->rva005F772E(rva005E7721Get(m_context,m_queue,index));
  ((Rva005F7478 *)this)->rva005F7478(rva005E7582Get(m_queue,index));
  Rva005E72B4Queue *nugget=m_queue;
  Rva005EThing *thing=(Rva005EThing *)rva005E7322Get(nugget,nugget->slot13()->begin[index]);
  ((Rva005F7488 *)this)->rva005F7488(thing ? thing->m_commandPoints : 0);
 } else {
  ((Rva005F772E *)this)->rva005F7470();
  ((Rva005F7480 *)this)->rva005F7480();
  ((Rva005F7490 *)this)->rva005F7490();
 }
}
