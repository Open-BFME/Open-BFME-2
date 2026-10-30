// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon: Select (retail
// 0x005E70F8, 25 bytes), the ctor 0x005E7D77, its refresh 0x005E7C56 and
// the icon-slot listener slots of its vtable 0x00877F14.
// Name: WorldBuilder (StrategicInGameUIBuildQueueDetailsPanel.cpp line 552):
// unless already selected (+0x20), the icon's slot (GetIconSlot, inlined in
// retail as the +0x0C pointer) is put in state 2 through
// StrategicHUD::BuildQueueIconSlot::SetState (retail: virtual slot 9), then
// the icon is marked selected.
// Evidence: callers at 0x005E7A33 0x005E7CD4 0x005E87BA.

class Rva005E7ED7;
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

// The icon's +0x1C counted handle uses the rowed destructor at 0x005F8F96.
class Rva005F8F96
{
public:
	Rva005F8F96() : m_value(0) {}
	~Rva005F8F96();

	void *m_value;
};

// Match the existing vector growth provider: no STL exception wrapper and
// local min/max overloads, avoiding incompatible external COMDAT copies.
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned &max(const unsigned &a,const unsigned &b){return a<b?b:a;}
static inline const int &min(const int &a,const int &b){return b<a?b:a;}
}
#include <vector>
#undef free
struct Rva005E71C6Ref;
class Rva005E87E0;
struct Rva005CE172Context;
class Rva005E7D72 { public: virtual ~Rva005E7D72(); };
class Rva005E7FE2 {
public:
 Rva005E7D72 *m_ptr;
 Rva005E7FE2() : m_ptr(0) {}
 ~Rva005E7FE2() {
  Rva005E7D72 *p=m_ptr;
  m_ptr=0;
  if(p) {
   p->Rva005E7D72::~Rva005E7D72();
   ::operator delete(p);
  }
 }
 void reset(Rva005E7D72 *);
};
class Rva005F830A
{
public:
	Rva005F830A(void *,void *,void *,void *);
	virtual ~Rva005F830A();
private:
	void *m_heap; // +0x04
};
#include "../../../../Include/Common/Rva0057605DSecond.h"
#define BFME_BASE0C_80FD_INLINE_CTOR
#include "../../../../Include/Common/Base0C_80FD.h"
#undef BFME_BASE0C_80FD_INLINE_CTOR
__forceinline Rva0057605DSecond::Rva0057605DSecond() {}
__declspec(dllimport) __forceinline Base0C_80FD::Base0C_80FD() {}

namespace StrategicInGameUI
{
class BuildQueueDetailsPanel
{
public:
	class Impl;
};

class BuildQueueDetailsPanel::Impl : public Rva005F830A, public Rva0057605DSecond, public Base0C_80FD
{
public:
	class Icon;
	class InProgressIcon;
 Impl(Rva005E87E0 *,void *,void *,Rva005CE172Context *);
 virtual ~Impl();
 virtual void rva005E716D();
 virtual void onLivingWorldBuildingNuggetSpawnArmyUnitDequeued(Rva005E72B4Queue &,int);
 virtual void onLivingWorldBuildingNuggetSpawnArmyUnitQueued(Rva005E72B4Queue &,int);
	friend class Icon;
 friend class InProgressIcon;
	friend class ::Rva005E7ED7;

	void SelectQueueIndex(int queueIndex);
	void ShowUnitStats(int queueIndex); // 0x005E7B28 (WorldBuilder name, pinned)
	void rva005E7AC6();

private:
	Icon *GetIconAtQueueIndex(int queueIndex) { return (Icon *)((Rva005E73E4 *)this)->rva005E73E4(queueIndex); }

 Rva005E87E0 *m_owner;
 void *m_help; // native hover-help caller follows +14
 Rva005E76AEContext *m_context;
 Rva005E72B4Queue *m_queue;
 Rva005E7FE2 m_first; // +0x20
 _STL::vector<Rva005E71C6Ref> m_icons; // +0x24
	int m_selectedQueueIndex; // +0x30, -1 when none
};

// Target facts: vtable 0x00877F14 = { 0x005E7DF7, 0x005E712A, 0x005E73DC,
// 0x005E7977, 0x005E715F, 0x005E7166 }: the icon slot's listener. WorldBuilder
// names slots 0..3 OnBuildQueueIconSlotLeftClicked / RightClicked / RollOut /
// RollOver; slots 4 and 5 (clear / set +0x21) are unnamed there.
class BuildQueueDetailsPanel::Impl::Icon
{
public:
	Icon(Impl *owner, int queueIndex, StrategicHUD::BuildQueueIconSlot *iconSlot, void *value10, int value14, int quantity);
	~Icon(); // native constructor EH calls existing 61B body5E7C19
	void Select();
	void Deselect(); // 0x005E7111 (rowed)
	void rva005E7C56();
	void rva005E789A(); // 0x005E789A (pinned)
 void Update();

	virtual void OnBuildQueueIconSlotLeftClicked(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRightClicked(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRollOut(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRollOver(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void rva005E715F(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void rva005E7166(StrategicHUD::BuildQueueIconSlot *slot);

friend class ::Rva005E7ED7;
 friend class InProgressIcon;
private:
	StrategicHUD::BuildQueueIconSlot *GetIconSlot() { return m_iconSlot; }

	Impl *m_owner;									// +0x04
	int m_queueIndex;								// +0x08
	StrategicHUD::BuildQueueIconSlot *m_iconSlot;	// +0x0C
	void *m_10;										// +0x10
	int m_14;										// +0x14
	int m_quantity;									// +0x18
	Rva005F8F96 m_1c;							// +0x1C
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
// SpawnArmy is the existing 88B SpawnArmy temporary view, ctor pin4E30D5 and
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
class Image;
class SpawnArmy { public:
	UnicodeString rva004E25AF(int);
	UnicodeString GetButtonHelp(int);
 SpawnArmy(int index);
 const Image *GetPortraitImage(int index);	// 0x004E24DC
 virtual ~SpawnArmy();
 char pad04[0x2c-4]; AsciiString name; char pad30[0x48-0x30]; int m_48; char pad4C[0x58-0x4c];
};
class Rva003B8E89 { public: void *rva003B8E89(void *); };
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;
struct Rva005E72B4Production { int *begin,*end,*capacity; };
class Rva005E72B4Queue { public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual bool slot4(int,SpawnArmy *);
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
 SpawnArmy army(0);
 queue->slot4(id,&army);
 Rva005E72B4Summary *summary=(Rva005E72B4Summary *)((Rva003B8E89 *)TheCampaignManager)->rva003B8E89(&army.name);
 if(!summary) return 0;
 if((summary->end-summary->begin)<1) return 0;
 return summary;
}

class Image;
class ThingTemplate;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &name); };
extern ThingFactory *TheThingFactory;
struct Rva005E7322MidRet { char pad[4]; AsciiString text; };
// 0x0040CB2C, the rowed indexed getter Rva0040CB2CIndexedField::get (second dword).
class Rva0040CB2CIndexedField { public: int get(int) const; };
struct Rva005E76AEContext { char pad[0x18]; int m_id; };
// WorldBuilder StrategicInGameUI::GetThingTemplate, WB VA 0x016025A0 (callgraph lead, score 1.0).
namespace StrategicInGameUI {
__declspec(noinline) static void *GetThingTemplate(Rva005E72B4Queue *queue,int id)
{
 void *r=rva005E72B4Get(queue,id);
 if(!r) return 0;
 AsciiString *name=&((Rva005E7322MidRet *)((const Rva0040CB2CIndexedField *)r)->get(0))->text;
 if(name->isEmpty()) return 0;
 return (void *)TheThingFactory->findTemplate(*name);
}
}
// WorldBuilder StrategicInGameUI::GetBuildTimeAtIndex, WB VA 0x01603E70 (callgraph lead, score 3.0).
namespace StrategicInGameUI {
__declspec(noinline) static int GetBuildTimeAtIndex(Rva005E72B4Queue *queue,int index)
{
 int id=queue->slot13()->begin[index];
 SpawnArmy army(0);
 queue->slot4(id,&army);
 int time=army.m_48;
 if(index==0) time-=queue->slot12();
 return time;
}
}
// WorldBuilder StrategicInGameUI::GetDisplayName, WB VA 0x01603430 (callgraph lead, score 2.0).
namespace StrategicInGameUI {
__declspec(noinline) static UnicodeString GetDisplayName(Rva005E76AEContext *context,Rva005E72B4Queue *queue,int id)
{
 SpawnArmy army(0);
 if(queue->slot4(id,&army)) return ((SpawnArmy *)&army)->rva004E25AF(context->m_id);
 return UnicodeString::TheEmptyString;
}
}
// WorldBuilder StrategicInGameUI::GetDisplayNameAtIndex, WB VA 0x01603350 (callgraph lead, score 1.0).
namespace StrategicInGameUI {
__declspec(noinline) static UnicodeString GetDisplayNameAtIndex(Rva005E76AEContext *context,Rva005E72B4Queue *queue,int index)
{
 return StrategicInGameUI::GetDisplayName(context,queue,queue->slot13()->begin[index]);
}
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
  ((Rva005F772E *)this)->rva005F772E(StrategicInGameUI::GetDisplayNameAtIndex(m_context,m_queue,index));
  ((Rva005F7478 *)this)->rva005F7478(StrategicInGameUI::GetBuildTimeAtIndex(m_queue,index));
  Rva005E72B4Queue *nugget=m_queue;
  Rva005EThing *thing=(Rva005EThing *)StrategicInGameUI::GetThingTemplate(nugget,nugget->slot13()->begin[index]);
  ((Rva005F7488 *)this)->rva005F7488(thing ? thing->m_commandPoints : 0);
 } else {
  ((Rva005F772E *)this)->rva005F7470();
  ((Rva005F7480 *)this)->rva005F7480();
  ((Rva005F7490 *)this)->rva005F7490();
 }
}

// Native hover-help siblings: the same 88B temporary provides the description
// through the retail by-value return call. Icon owns a counted 12B help object
// at+1C; the matched help constructor and holder setter establish its layout.
// Preserve both temporary UnicodeString lifetimes across constructor and set.
// WorldBuilder StrategicInGameUI::GetDisplayDescription, WB VA 0x01603640 (callgraph lead, score 2.0).
namespace StrategicInGameUI {
__declspec(noinline) static UnicodeString GetDisplayDescription(Rva005E76AEContext *context,Rva005E72B4Queue *queue,int id)
{
 SpawnArmy army(0);
 if(queue->slot4(id,&army)) return ((SpawnArmy *)&army)->GetButtonHelp(context->m_id);
 return UnicodeString::TheEmptyString;
}
}
// WorldBuilder StrategicInGameUI::GetDisplayDescriptionAtIndex, WB VA 0x01603560 (callgraph lead, score 1.0).
namespace StrategicInGameUI {
__declspec(noinline) static UnicodeString GetDisplayDescriptionAtIndex(Rva005E76AEContext *context,Rva005E72B4Queue *queue,int index)
{
 return StrategicInGameUI::GetDisplayDescription(context,queue,queue->slot13()->begin[index]);
}
}
class __declspec(novtable) Rva005398CDRefCounted {
public:
 Rva005398CDRefCounted() : m_refCount(0) {}
 virtual ~Rva005398CDRefCounted(); int m_refCount;
};
class InGameSimpleHelp : public Rva005398CDRefCounted {
public:
 class Impl;
 InGameSimpleHelp(const UnicodeString &,const UnicodeString &);
 virtual ~InGameSimpleHelp();
private: Impl *m_impl;
};
struct TargetRef00217D4C;
class Rva002BED91 { public: TargetRef00217D4C *m_ptr; void set(TargetRef00217D4C *); };
struct TreeHintRef00217D4C;
class Rva001FF3A9 { public: void rva001FF3A9(const TreeHintRef00217D4C &); };
void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::rva005E789A()
{
 if(!m_1c.m_value)
  ((Rva002BED91 *)&m_1c)->set((TargetRef00217D4C *)new InGameSimpleHelp(StrategicInGameUI::GetDisplayNameAtIndex(m_owner->m_context,m_owner->m_queue,m_queueIndex),StrategicInGameUI::GetDisplayDescriptionAtIndex(m_owner->m_context,m_owner->m_queue,m_queueIndex)));
 ((Rva001FF3A9 *)m_owner->m_help)->rva001FF3A9(*(const TreeHintRef00217D4C *)&m_1c);
}

// Native queued-icon pass. The real constructor supplies the three ESI queue
// helper calls; their providers use the already verified army/template lookups.
// MI layout: Icon24 + the existing Rva0007DF07 counted base8 + slot pointer2C.
// Keep the address-derived owner whose destructor already lives at5E7ED7.
// Native EH calls Icon61 at5E7C19 and the counted base7 at4E84A4. Declaring
// the real Icon destructor prevents an incorrect implicit member-only cleanup.
// The base vtable points to rowed deleting destructor7E5EE; this view emits
// that same29B body. The derived deleting destructor28 and adjustor8 reproduce
// native5E7EBB/5E7EB3, with the compiler's weak vector-to-scalar fallback.
// WorldBuilder StrategicInGameUI::GetPortraitImage, WB VA 0x01604120 (callgraph lead, score 3.0).
namespace StrategicInGameUI {
__declspec(noinline) static const Image *GetPortraitImage(Rva005E76AEContext *context,Rva005E72B4Queue *queue,int id)
{
 SpawnArmy army(0);
 if(queue->slot4(id,&army)) return army.GetPortraitImage(context->m_id);
 return 0;
}
}
struct Rva005E735DTemplate { char pad[0x5c4]; int imageID; char pad5c8[0x618-0x5c8]; int field618; };
namespace StrategicInGameUI {
__declspec(noinline) static int GetCommandPointsAtIndex(Rva005E72B4Queue *queue,int index)
{
 Rva005E735DTemplate *thing=(Rva005E735DTemplate *)StrategicInGameUI::GetThingTemplate(queue,queue->slot13()->begin[index]);
 if(thing) return thing->field618;
 return 0;
}
}
// WorldBuilder StrategicInGameUI::GetPortraitImageAtIndex, WB VA 0x01604060 (align lead, score 2.0).
namespace StrategicInGameUI {
__declspec(noinline) static const Image *GetPortraitImageAtIndex(Rva005E76AEContext *context,Rva005E72B4Queue *queue,int index)
{
 return StrategicInGameUI::GetPortraitImage(context,queue,queue->slot13()->begin[index]);
}
}
const Image *Rva005F01C7Get(int);
struct Rva005E7625Template { char pad[0x5c4]; int imageID; };
__declspec(noinline) static const Image *rva005E7625Get(Rva005E72B4Queue *queue,int index)
{
 Rva005E7625Template *thing=(Rva005E7625Template *)StrategicInGameUI::GetThingTemplate(queue,queue->slot13()->begin[index]);
 if(!thing) return 0;
 return Rva005F01C7Get(thing->imageID);
}
class Rva0037E07C { public: int rva0037E07C(); };
__declspec(noinline) static int rva005E77F0Get(Rva005E72B4Queue *queue,int index)
{
 void *summary=rva005E72B4Get(queue,queue->slot13()->begin[index]);
 if(summary) return ((Rva0037E07C *)((const Rva0040CB2CIndexedField *)summary)->get(0))->rva0037E07C();
 return 0;
}
// Native 5E735D..5E73B2: three by-id helpers emitted after GetThingTemplate
// in the same static convention (queue in ECX, id on the stack). No call,
// jump or absolute reference to any of them survives in the image; their WB
// twins 0x016055B0 (the +0x618 field) and 0x016042F0 (the +0x5C4 image) call
// GetThingTemplate(queue,id). Identities unproven; RVA-qualified names.
__declspec(noinline) static int rva005E735DGet(Rva005E72B4Queue *queue,int id)
{
 Rva005E735DTemplate *thing=(Rva005E735DTemplate *)StrategicInGameUI::GetThingTemplate(queue,id);
 if(thing) return thing->field618;
 return 0;
}
__declspec(noinline) static const Image *rva005E7375Get(Rva005E72B4Queue *queue,int id)
{
 Rva005E735DTemplate *thing=(Rva005E735DTemplate *)StrategicInGameUI::GetThingTemplate(queue,id);
 if(!thing) return 0;
 return Rva005F01C7Get(thing->imageID);
}
__declspec(noinline) static int rva005E7391Get(Rva005E72B4Queue *queue,int id)
{
 void *summary=rva005E72B4Get(queue,id);
 if(summary) return ((Rva0037E07C *)((const Rva0040CB2CIndexedField *)summary)->get(0))->rva0037E07C();
 return 0;
}
// Retail keeps the three helpers above without any surviving caller; this
// anchor only forces cl to emit them in the TU's static convention.
// ?Rva005E735DAnchor absent-from-retail
int Rva005E735DAnchor(Rva005E72B4Queue *queue,int id)
{
 return rva005E735DGet(queue,id)+(int)rva005E7375Get(queue,id)+rva005E7391Get(queue,id)+StrategicInGameUI::GetCommandPointsAtIndex(queue,id);
}
class Rva005F6B12 { public: int rva005F6B12(int) const; };
// Native reference-count writes occur at base+4 (queued object+28).
// Its own direct member initializer preserves the ctor EH-state/store order.
#include "../../../../Include/Common/Rva0007DF07.h"
class Rva005E7ED7 : public StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon, public Rva0007DF07 {
public:
 typedef StrategicInGameUI::BuildQueueDetailsPanel::Impl Owner;
 Rva005E7ED7(Owner *,int);
 void MoveTo(int);
 virtual ~Rva005E7ED7();
private: StrategicHUD::BuildQueueIconSlot *slot;
};
class Rva005E7E05QueuedSlot {
public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void v5();virtual void v6();virtual void v7();
 virtual void v8();virtual void v9();virtual void v10();virtual void SetNumTurns(int);
};
Rva005E7ED7::Rva005E7ED7(Owner *owner,int index)
 : Icon(owner,index,(StrategicHUD::BuildQueueIconSlot *)((Rva005F6B12 *)owner)->rva005F6B12(index-1),
        (void *)StrategicInGameUI::GetPortraitImageAtIndex(owner->m_context,owner->m_queue,index),
        (int)rva005E7625Get(owner->m_queue,index),rva005E77F0Get(owner->m_queue,index)),
 slot((StrategicHUD::BuildQueueIconSlot *)((Rva005F6B12 *)owner)->rva005F6B12(index-1))
{
 int time=StrategicInGameUI::GetBuildTimeAtIndex(owner->m_queue,index);
 ((Rva005E7E05QueuedSlot *)slot)->SetNumTurns(time);
}

// WorldBuilder names the native91B constructor's only non-base callee
// InProgressIcon::Init(bool). Retail+8 owner/+C bool and RET8 agree;
// both slot reads use the already rowed integer getter at5F6B0B.
// Icon24 + the in-progress slot pointer24 gives the native28B allocation.
class Rva005F6B0BPtrChaseField { public: int get() const; };
class StrategicInGameUI::BuildQueueDetailsPanel::Impl::InProgressIcon : public StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon {
public:
 InProgressIcon(Impl *,bool);
 void Init(bool);
private: StrategicHUD::BuildQueueIconSlot *m_progressSlot;
};
StrategicInGameUI::BuildQueueDetailsPanel::Impl::InProgressIcon::InProgressIcon(Impl *owner,bool selected)
 : Icon(owner,0,(StrategicHUD::BuildQueueIconSlot *)((Rva005F6B0BPtrChaseField *)owner)->get(),0,0,0),
 m_progressSlot((StrategicHUD::BuildQueueIconSlot *)((Rva005F6B0BPtrChaseField *)owner)->get())
{ Init(selected); }

// Native outer146B constructor shares Rva0007DF07 virtually: primary0,
// vbptr4, owned 52B child8, counted virtual baseC and counter10.
// Existing exact57B base5CC5E5 makes only field/vtable writes, no calls;
// its nonthrowing declaration preserves retail's EH state across the call.
// Native child457B (including its catch) returns this/RET16 and stores its owner at+10;
// original outer and child names remain unknown, so retain address views.
class Rva005CC5E5 : public virtual Rva0007DF07 {
public:
 Rva005CC5E5() throw();
 virtual void slot0();
 virtual ~Rva005CC5E5();
};
struct Rva005CE172Context;
class Rva005E87E0;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva005E71C6Ref {
 Rva005E7ED7 *m_object;
 Rva005E71C6Ref(Rva005E7ED7 *p) : m_object(p) { if(p) ++static_cast<Rva0007DF07 *>(p)->m_04; }
 Rva005E71C6Ref(const Rva005E71C6Ref &r) : m_object(r.m_object) { if(m_object) ++static_cast<Rva0007DF07 *>(m_object)->m_04; }
 ~Rva005E71C6Ref() { if(m_object) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)(Rva0007DF07 *)m_object); }
};
// Reuse the existing native range loop; the caller's local tag is part of
// the STLport false-type dispatch ABI verified at 005E7FB0.
struct Rva005E74AA;
void Rva005E7BE2Destroy(Rva005E74AA *,Rva005E74AA *,void *);
namespace _STL {
template<> __declspec(noinline) inline void _Destroy<Rva005E71C6Ref *>(Rva005E71C6Ref *f,Rva005E71C6Ref *l) {
 char tag;
 Rva005E7BE2Destroy((Rva005E74AA *)f,(Rva005E74AA *)l,&tag);
}
}
// Keep the game allocator's already expanded cleanup inline, avoiding
// external copies that compete with units using the CRT declaration.
namespace _STL {
template<> __declspec(dllimport) __forceinline void allocator<Rva005E71C6Ref>::deallocate(Rva005E71C6Ref *p,size_t n)const {if(p) _STL::free(p);}
template<> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<Rva005E71C6Ref *,Rva005E71C6Ref,allocator<Rva005E71C6Ref> >::deallocate(Rva005E71C6Ref *p,size_t n){static_cast<allocator<Rva005E71C6Ref> &>(*this).deallocate(p,n);}
}
class Rva002DF9E9 { public: UnicodeString rva002DF9E9(); };
class Rva004E0625 { public: int rva004E0625() const; };
struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *); };
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *data);
};
class Rva005E8095 { public: void rva005E8095(unsigned); };
struct Rva005E8350Building { char unknown0[0x28]; Rva002DF9E9 *label; };
// Field offsets are native evidence; this accessor name is reconstructed.
// Keeping the pointer access inline gives the native hidden-return scheduling.
struct Rva005CE172Context {
 void *help;
 Rva005E8350Building *building;
 void *link;
 inline Rva002DF9E9 *getLabelObject() const { return building->label; }
};
extern unsigned g_Va00E06724[4];
static const int MaximumQueuedIcons=7;
inline void *rvaUnicodeAddress(const UnicodeString &unicodeString) { return (void *)&unicodeString; }
class Rva005E87E0 : public Rva005CC5E5 {
public:
 Rva005E87E0(void *,void *,Rva005CE172Context *);
 virtual ~Rva005E87E0();
private: StrategicInGameUI::BuildQueueDetailsPanel::Impl *payload;
};
Rva005E87E0::Rva005E87E0(void *a,void *b,Rva005CE172Context *c)
 : payload(new StrategicInGameUI::BuildQueueDetailsPanel::Impl(this,a,b,c)) {}

class Rva005E7DD6 { public: void setRva005E7DD6(int); };
void Rva005E7ED7::MoveTo(int index)
{
 if(index!=m_queueIndex) {
  m_queueIndex=index;
  ((Rva005E7E05QueuedSlot *)slot)->SetNumTurns(0);
  slot=(StrategicHUD::BuildQueueIconSlot *)((Rva005F6B12 *)m_owner)->rva005F6B12(index-1);
  ((Rva005E7DD6 *)this)->setRva005E7DD6((int)slot);
  int time=StrategicInGameUI::GetBuildTimeAtIndex(m_owner->m_queue,index);
  ((Rva005E7E05QueuedSlot *)slot)->SetNumTurns(time);
 }
}

// WB tooltip provider, index wrapper and Icon::Update share the native queue
// ABI: ECX queue + ESI hidden return; EAX queue + stack return/index respectively.
// The null-template branch copies the existing empty UnicodeString global,
// not a character literal. Mouse consumes the final string by value and owns
// its parameter cleanup. Native54B update requires no caller EH frame.
namespace StrategicInGameUI { UnicodeString __cdecl GetTooltipText(int); }
__declspec(noinline) static UnicodeString rva005E764FGet(Rva005E72B4Queue *queue,int id)
{
 Rva005E7625Template *thing=(Rva005E7625Template *)StrategicInGameUI::GetThingTemplate(queue,id);
 if(!thing) return UnicodeString::TheEmptyString;
 return StrategicInGameUI::GetTooltipText(thing->imageID);
}
// WorldBuilder StrategicInGameUI::GetTooltipTextAtIndex, WB VA 0x01602450 (callgraph lead, score 1.0).
namespace StrategicInGameUI {
__declspec(noinline) static UnicodeString GetTooltipTextAtIndex(Rva005E72B4Queue *queue,int index)
{ return rva005E764FGet(queue,queue->slot13()->begin[index]); }
}
struct RGBColor;
class Mouse { public: void rva001EEA6D(UnicodeString,int,const RGBColor *,float); };
extern Mouse *TheMouse;
// ?StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::Update present-unmatched
void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::Update()
{ if(m_21) TheMouse->rva001EEA6D(StrategicInGameUI::GetTooltipTextAtIndex(m_owner->m_queue,m_queueIndex),-1,0,1.0f); }

// Init at 0x005E797F is 327B through RET4 at 0x005E7AC3. WorldBuilder
// names InProgressIcon::Init(bool); retail independently fixes the owner+4,
// queue+1C, context+18 and progress-slot+24 accesses. The portrait army ends
// before selection; the second 88B army remains alive through progress/hover.
// Retain the returned ID array, then reload the queue for virtual slot4;
// retail performs that reload after slot13. Progress uses virtual slot12.
inline static const Image *rva005E704EInline(Rva005E76AEContext *context,Rva005E72B4Queue *queue,int id)
{
 SpawnArmy army(0);
 if(queue->slot4(id,&army)) return army.GetPortraitImage(context->m_id);
 return 0;
}
inline static const Image *rva005E7607Inline(Rva005E76AEContext *context,Rva005E72B4Queue *queue,int index)
{
 return rva005E704EInline(context,queue,queue->slot13()->begin[index]);
}
class Rva005E70AD { public: void rva005E70AD(int); };
class Rva005E70C6 { public: void rva005E70C6(int); };
class Rva005E70DF { public: void rva005E70DF(int); };

class Rva005E797FProgressSlot {
public:
 virtual bool v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void v5();virtual void v6();virtual void v7();
 virtual void v8();virtual void v9();virtual void v10();virtual void v11();
 virtual void SetProgress(int,int);
};

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::InProgressIcon::Init(bool selected)
{
 ((Rva005E73B2 *)this)->rva005E73B2();
 ((Rva005E70AD *)this)->rva005E70AD((int)rva005E7607Inline(m_owner->m_context,m_owner->m_queue,0));
 ((Rva005E70C6 *)this)->rva005E70C6((int)rva005E7625Get(m_owner->m_queue,0));
 ((Rva005E70DF *)this)->rva005E70DF(rva005E77F0Get(m_owner->m_queue,0));
 if(selected) Select(); else Deselect();
 SpawnArmy army(0);
 int *ids=m_owner->m_queue->slot13()->begin;
 SpawnArmy *armyPtr=&army;
 m_owner->m_queue->slot4(ids[0],armyPtr);
 int total=army.m_48;
 int remaining=total-m_owner->m_queue->slot12();
 Rva005E797FProgressSlot *progress=(Rva005E797FProgressSlot *)m_progressSlot;
 if(remaining<=0) remaining=0;
 progress->SetProgress(total,remaining);
 if(m_progressSlot->v0()) rva005E789A();
}

// Native 005E7AC6..005E7B28 RET0, directly before ShowUnitStats: runs the
// panel's 0x005F7498 step, re-posts the 0x00E06724 label as the mouse
// tooltip while the 0x005F6B35 flag is set, then updates the in-progress
// icon (+0x20) and every queued icon (+0x24..+0x28) through Icon::Update.
// Method name unrecovered; the receiver is proven by the Icon::Update calls
// on the panel's own icon members.
class Rva005F7498 { public: void rva005F7498(); };
class Rva005F6B35ByteChaseField { public: unsigned char get() const; };
class Rva005E755E { public: UnicodeString rva005e755e(); };
extern unsigned g_Va00E06724[4];

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::rva005E7AC6()
{
	((Rva005F7498 *)this)->rva005F7498();
	if (((Rva005F6B35ByteChaseField *)this)->get())
		TheMouse->rva001EEA6D(((Rva005E755E *)&g_Va00E06724)->rva005e755e(), -1, 0, 1.0f);
	if (m_first.m_ptr)
		((Icon *)m_first.m_ptr)->Update();
	Rva005E71C6Ref *end = m_icons.end();
	for (Rva005E71C6Ref *it = m_icons.begin(); it != end; ++it)
		it->m_object->Update();
}

// Native 005E8350..005E8519: initialize the title and both observers, create
// at most seven queued icons, and unregister the building listener on failure.
// The actual STLport push_back/growth bodies must remain visible to preserve
// the eight-byte local frame and reuse the dead context argument for the title.
// Whole body, catch and eleven-state EH graph are byte exact; see
// reverse/attempt_evidence/0x005e8350_visibility.txt.
StrategicInGameUI::BuildQueueDetailsPanel::Impl::Impl(Rva005E87E0 *o,void *a,void *b,Rva005CE172Context *c)
 : Rva005F830A(a,b,rvaUnicodeAddress(c->getLabelObject()->rva002DF9E9()),(void *)g_Va00E06724[2]),
 m_owner(o),m_help(c->help),m_context((Rva005E76AEContext *)c->building),m_queue((Rva005E72B4Queue *)((Rva004E0625 *)c->building)->rva004E0625()),m_selectedQueueIndex(-1)
{
 ((Rva005A0B4CList *)((char *)m_context+8))->append((Rva002BA8F1Listener *)(Rva0057605DSecond *)this);
 try {
 const Rva005E72B4Production *production=m_queue->slot13();
 int count=production->end-production->begin;
 if(count>0) {
  m_first.reset((Rva005E7D72 *)new StrategicInGameUI::BuildQueueDetailsPanel::Impl::InProgressIcon((StrategicInGameUI::BuildQueueDetailsPanel::Impl *)this,false));
  if(count>1) {
   int available=count-1;
   int n=_STL::min(available,MaximumQueuedIcons);
   ((Rva005E8095 *)&m_icons)->rva005E8095(n);
   for(int i=0;i<n;++i) m_icons.push_back(Rva005E71C6Ref(new Rva005E7ED7((StrategicInGameUI::BuildQueueDetailsPanel::Impl *)this,i+1)));
  }
 }
 ((Rva005A0B4CList *)((char *)m_queue+4))->append((Rva002BA8F1Listener *)(Base0C_80FD *)this);
 } catch(...) {
 ((Rva002B7250 *)((char *)m_context+8))->rva002B7250((CreateAHeroData *)(Rva0057605DSecond *)this);
 throw;
 }
}
