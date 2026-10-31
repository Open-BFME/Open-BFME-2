// cl: /O1 /G7 /arch:SSE /EHsc /MD
// Constructor 576DF1..576ED9 is 232 bytes, RET8, in the same 0x48-byte
// object allocated by the owned 576ED9 caller. Native table C6E430 and the
// derived C6E7F0 table both have translateGameMessage in slot0 and a deleting
// destructor in slot1. The carrier BDBA74 starts with purecall and a deleting
// destructor too; the old destructor-only slot0 declaration was incomplete.
// The primary input slots and both secondary interfaces follow the native
// tables; phase methods remain in StrategicInGameUIResolveBattlesBehavior.cpp.
// Member offsets and three-base lifetime are target facts. Owner+10 and
// values+14/+18 belong to the derived object; the +C listener occupies4B.
// The record at20 receives one saved owner->m_p receiver and the +4 base.
// Callee identities come from their existing matched providers; the owning
// phase and its lifetime rows share the native primary and secondary tables.
// Original member type identities remain unresolved.
// ??1Rva00576C4B@@UAE@XZ @0x00576C4B 186B: virtual dtor unregistering listener base at +0xC via rowed erase 0x002B7250 then conditional ptr-chase release then member teardown. Evidence: three vtable stores plus base restores 0x0086E7F0/0x0086E7E8/0x0086E7E4 to 0x007DBA74/0x0086E788; erase caller plus deleting-dtor caller at 0x00576DD5; callees all rowed.
enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
class GameMessage;
class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
class Rva002BA8F1Logic
{
public:
	char m_pad[0x5c];
	Rva002B7250 m_holder;
};

class Rva00328A83PtrChaseField
{
public:
	int get() const;
};
class Rva0042D6AEPtrChaseField
{
public:
	int get() const;
};
class VirtObj00576C4B
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
};
struct Inner00576C4B
{
	char m_pad[4];
	Rva00328A83PtrChaseField *m_p;
};
class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4();
	void clear();
	void *m_ptr;
};
class Rva005CD1A9;
class Rva00574A98 { public: void *rva00574A98(); };
class Rva005CD7BD { public: Rva005CD7BD(void *,int,int); private: int native[4]; };

class Rva005CD7DA
{
public:
	__forceinline Rva005CD7DA(void *source,Rva005CD1A9 *owner) : data(((Rva00574A98*)source)->rva00574A98(),((Rva00328A83PtrChaseField*)source)->get(),(int)owner) {}
	void rva005CD7DA();
	Rva005CD7BD data;
};
// Native +1C/+40 cleanups call the complete29B owning-pointer destructor.
// Use its existing real member lifetime instead of an unbound forwarding wrapper.
typedef Rva000AD6F4 WrapClear00576C4B;
// Native5CD7DA teardown observes the record's pointer+4 and active byte+C,
// then invokes slots6 and1 on the resolved subscriber. The concrete member
// identity remains unknown; this is the complete native cleanup, not a thunk.
struct ResolveRecordCleanupView
{
	void *m_vtable;
	Rva0042D6AEPtrChaseField *m_4;
	void *m_8;
	bool m_C;
};
struct Subscribable005CD7DA
{
	virtual void f0();
	virtual void f1(int);
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
};
struct Wrap2000576C4B
{
	__forceinline Wrap2000576C4B(void *source,Rva005CD1A9 *owner) : m_m(source,owner) {}
	__declspec(noinline) ~Wrap2000576C4B()
	{
		ResolveRecordCleanupView *record = (ResolveRecordCleanupView *)&m_m;
		if (record->m_C == 0)
			return;
		int v = record->m_4->get();
		Subscribable005CD7DA *obj = (Subscribable005CD7DA *)v;
		if (obj == 0)
			return;
		obj->f6();
		obj->f1(0);
	}
	Rva005CD7DA m_m;
};
class Rva005CD651
{
public:
	Rva005CD651(int);
	virtual ~Rva005CD651();
	char m_pad[12];
};
class Rva005CD1A9
{
public:
	Rva005CD1A9();
	virtual ~Rva005CD1A9();
	virtual int rva0057556D() = 0;
	void *m_ptr;
};
class Base0_00576C4B
{
public:
	Base0_00576C4B();
	virtual GameMessageDisposition translateGameMessage(const GameMessage *) = 0;
	virtual ~Base0_00576C4B() {}
};
// ??0Base0_00576C4B@@QAE@XZ @0x001DB0AC 9B: the default constructor, storing the
// class's own vtable (VA 0x00BDBA74) and returning this.
inline Base0_00576C4B::Base0_00576C4B()
{
}
struct IRegion2D;
struct Rva005CBC95Pixel;
class UserInputTranslator : public Base0_00576C4B
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *);
	// ?UserInputTranslator::slot02 present-unmatched
	virtual int slot02(const Rva005CBC95Pixel &, int) { return 0; }
	// ?UserInputTranslator::slot03 present-unmatched
	virtual int slot03(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::slot04 present-unmatched
	virtual int slot04(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::slot05 present-unmatched
	virtual int slot05(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::slot06 present-unmatched
	virtual int slot06(const Rva005CBC95Pixel &, const Rva005CBC95Pixel &, int) { return 0; }
	// ?UserInputTranslator::slot07 present-unmatched
	virtual int slot07(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::slot08 present-unmatched
	virtual int slot08(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::slot09 present-unmatched
	virtual int slot09(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::slot10 present-unmatched
	virtual int slot10(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::slot11 present-unmatched
	virtual int slot11(const Rva005CBC95Pixel &, const Rva005CBC95Pixel &, int) { return 0; }
	// ?UserInputTranslator::slot12 present-unmatched
	virtual int slot12(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::slot13 present-unmatched
	virtual int slot13(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::slot14 present-unmatched
	virtual int slot14(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::slot15 present-unmatched
	virtual int slot15(const Rva005CBC95Pixel &, const Rva005CBC95Pixel &, int) { return 0; }
	// ?UserInputTranslator::slot16 present-unmatched
	virtual int slot16(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::slot17 present-unmatched
	virtual int slot17(const Rva005CBC95Pixel &, int, int) { return 0; }
	// ?UserInputTranslator::OnMouseLeftClick present-unmatched
	virtual int OnMouseLeftClick(const IRegion2D &, int) { return 0; }
	// ?UserInputTranslator::slot19 present-unmatched
	virtual int slot19(const IRegion2D &, int) { return 0; }
	// ?UserInputTranslator::slot20 present-unmatched
	virtual int slot20(const IRegion2D &, int) { return 0; }
	// ?UserInputTranslator::slot21 present-unmatched
	virtual int slot21(const IRegion2D &, int) { return 0; }
	// ?UserInputTranslator::slot22 present-unmatched
	virtual int slot22(const IRegion2D &, int) { return 0; }
	// ?UserInputTranslator::slot23 present-unmatched
	virtual int slot23(const IRegion2D &, int) { return 0; }
	// ?UserInputTranslator::slot24 present-unmatched
	virtual int slot24(int, int) { return 0; }
	// ?UserInputTranslator::slot25 present-unmatched
	virtual int slot25(int, int) { return 0; }
};
class PhaseTranslator00576DF1 : public UserInputTranslator
{
};

class Listener00576C4B
{
public:
	Listener00576C4B();
	~Listener00576C4B() {}
	// ?Listener00576C4B::rva00576ACB present-unmatched
	virtual void rva00576ACB(void *, void *) {}

};
// ??0Listener00576C4B@@QAE@XZ @0x00576674 9B: the default constructor, storing the
// class's own vtable (VA 0x00C6E788) and returning this.
Listener00576C4B::Listener00576C4B()
{
}
class Rva00576B5E;
class Rva005A0B4CList { public: void append(struct Rva002BA8F1Listener *); };
struct ResolveWorldView { char prefix[0x98]; int player; };
void Rva00576753Func(int,int,int);
namespace StrategicInGameUI { class ResolveBattlesBehavior { public: class Impl; }; }

class StrategicInGameUI::ResolveBattlesBehavior::Impl : public PhaseTranslator00576DF1, public Rva005CD1A9, public Listener00576C4B
{
public:
	Impl(Rva00576B5E *,int);
	virtual GameMessageDisposition translateGameMessage(const GameMessage *);
	virtual ~Impl();
	virtual int rva0057556D();
	virtual void rva00576ACB(void *, void *);
	virtual int OnMouseLeftClick(const IRegion2D &, int);
	void CreateResolveRegionOwnershipChecklistItems();
	void rva00576AF3();
private:
	Inner00576C4B *m_s;
	int m_value14;
	int m_player18;
	WrapClear00576C4B m_1c;
	Wrap2000576C4B m_20;
	Rva005CD651 m_30;
	WrapClear00576C4B m_40;
	bool m_flag44;
};
StrategicInGameUI::ResolveBattlesBehavior::Impl::~Impl()
{
	(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_holder.rva002B7250((CreateAHeroData *)(Listener00576C4B *)this);
	if (m_flag44) {
		int v1 = m_s->m_p->get();
		int subscriber = ((Rva0042D6AEPtrChaseField *)v1)->get();
		if (subscriber)
			((VirtObj00576C4B *)subscriber)->f3();
	}
}

StrategicInGameUI::ResolveBattlesBehavior::Impl::Impl(Rva00576B5E *owner, int value)
	: m_s((Inner00576C4B *)owner), m_value14(value),
	  m_player18(((ResolveWorldView *)TheLivingWorldLogic)->player),
	  m_20(m_s->m_p, this), m_30(m_s->m_p->get()), m_flag44(false)
{
	Rva00576753Func(m_player18, (int)(Rva005CD1A9 *)this, m_value14);
	((StrategicInGameUI::ResolveBattlesBehavior::Impl *)this)->CreateResolveRegionOwnershipChecklistItems();
	((Rva005A0B4CList *)((char *)TheLivingWorldLogic + 0x5C))
		->append((Rva002BA8F1Listener *)(Listener00576C4B *)this);
	((StrategicInGameUI::ResolveBattlesBehavior::Impl *)this)->rva00576AF3();
}
