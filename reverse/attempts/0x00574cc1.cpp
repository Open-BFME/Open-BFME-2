// ??1Impl@CommonBehavior@StrategicInGameUI@@UAE@XZ
// partial score=0.979 date=2026-10-11
// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::CommonBehavior::Impl (WorldBuilder
// StrategicInGameUICommonBehavior.cpp names its translateGameMessage, align).
// Target facts for 0x00574910: offers the message to its +0x5C member (0x005CC26E), its +0x54 sub-translator (when set, vslot 2) and its +0x28 member (0x005C9BE3), consuming it
// (1) when one does, else defers to the base
// UserInputTranslator::translateGameMessage 0x005CBC95 (WorldBuilder name,
// pinned). Member types are the callees' views (inference).
//
// Destructor 0x00574CC1 (vtable 0x00C6E528 slot 1 via ??_G 0x00574E86):
// six bases at +0..+0x14, whose own tables 0x00BDBA74, 0x00C6E350,
// 0x00C6E330 (twice), 0x00C6E344 and 0x00C1C780 it reinstalls in reverse;
// it leaves the observer lists at +4 of the +0x24, +0x28, +0x74 and +0x6C
// owners, releases the +0x20 holder's two parts, then unwinds the members
// whose destructors the retail calls name (0x005C9B9C, 0x005CB8D4,
// 0x000AD6F4, 0x005CC287 and two counted handles). Base and owner types are
// address-named views; which observer each base is remains unproven.

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

class GameMessage;

class UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	virtual ~UserInputTranslator() {}
};

// The translators behind the behavior (ManualPhaseEnder.cpp's units).
namespace StrategicInGameUI
{
class ManualPhaseEnder
{
public:
	GameMessageDisposition Translate(const GameMessage *msg); // 0x005CD8F7

private:
	char m_data[0x10];
};
}

// A nullable sub-translator viewed by slot: vslot 2 translates.
class Rva00574910SubTranslator
{
public:
	virtual void vslot0();
	virtual void vslot1();
	virtual GameMessageDisposition Translate(const GameMessage *msg);
};

// The +0x5C and +0x28 members' translate methods (0x005CC26E rowed and
// 0x005C9BE3 pinned, both address-named).
class Rva005CC26E
{
public:
	int rva005CC26E(void *msg);
};
class Rva005C9BE3
{
public:
	GameMessageDisposition Translate(const GameMessage *msg);
};

// Member destructors named by the retail calls.
class Rva005C9B76 { public: virtual ~Rva005C9B76(); char m_data[0x1C]; };
class Rva005CB8D4 { public: virtual ~Rva005CB8D4(); char m_data[0x8]; };
class Rva000AD6F4 { public: ~Rva000AD6F4(); Rva00574910SubTranslator *m_ptr; };
class Rva005CC287 { public: virtual ~Rva005CC287(); char m_data[0xC]; };
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva00574CC1Handle
{
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva00574CC1Handle() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class CreateAHeroData;
class Rva002B7250 { public: void rva002B7250(CreateAHeroData *); };
struct Rva002BED91;
class Rva005748B7 { public: void rva005748B7(Rva002BED91 *); };
class Rva0042D6FDPtrChaseField { public: int get() const; };
class Rva0042D69DPtrChaseField { public: int get() const; };
class Rva00574CC1Part1 { public: virtual void vslot0(); virtual void vslot1(int); };
class Rva00574CC1Part2 { public: virtual void vslot0(); virtual void vslot1(); virtual void vslot2(); virtual void vslot3(); };
// An owner whose observer list sits at +4.
struct Rva00574CC1OwnerBase { virtual void vslot0(); };
struct Rva00574CC1Owner : public Rva00574CC1OwnerBase, public Rva002B7250 {};

class Rva00574CC1Base04 { public: virtual ~Rva00574CC1Base04() {} };
class Rva00574CC1Base08 { public: virtual ~Rva00574CC1Base08() {} };
class Rva00574CC1Base0C { public: virtual ~Rva00574CC1Base0C() {} };
class Rva00574CC1Base10 { public: virtual ~Rva00574CC1Base10() {} };
class Rva00574CC1Base14 { public: virtual ~Rva00574CC1Base14() {} };

namespace StrategicInGameUI
{
class CommonBehavior
{
public:
	class Impl;
};
}

class StrategicInGameUI::CommonBehavior::Impl : public UserInputTranslator,
	public Rva00574CC1Base04, public Rva00574CC1Base08, public Rva00574CC1Base0C,
	public Rva00574CC1Base10, public Rva00574CC1Base14
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	virtual ~Impl();

private:
	char m_pad18[0x20 - 0x18];
	Rva0042D6FDPtrChaseField *m_parts; // +0x20
	Rva00574CC1Owner *m_owner24; // +0x24
	Rva005C9B76 m_translator28; // +0x28
	Rva005CB8D4 m_48; // +0x48
	Rva000AD6F4 m_sub; // +0x54
	char m_pad58[0x5C - 0x58];
	Rva005CC287 m_translator5C; // +0x5C
	Rva00574CC1Owner *m_owner6C; // +0x6C
	Rva00574CC1Handle m_handle70; // +0x70
	Rva00574CC1Owner *m_owner74; // +0x74
	Rva00574CC1Handle m_handle78; // +0x78
};

GameMessageDisposition StrategicInGameUI::CommonBehavior::Impl::translateGameMessage(const GameMessage *msg)
{
	Rva00574910SubTranslator *sub;
	if (reinterpret_cast<Rva005CC26E *>(&m_translator5C)->rva005CC26E((void *)msg) == 1)
		return DESTROY_MESSAGE;
	if ((sub = m_sub.m_ptr) != 0 && sub->Translate(msg) == DESTROY_MESSAGE)
		return DESTROY_MESSAGE;
	if (reinterpret_cast<Rva005C9BE3 *>(&m_translator28)->Translate(msg) == DESTROY_MESSAGE)
		return DESTROY_MESSAGE;
	return UserInputTranslator::translateGameMessage(msg);
}

StrategicInGameUI::CommonBehavior::Impl::~Impl()
{
	CreateAHeroData *observer10 = (CreateAHeroData *)(Rva00574CC1Base10 *)this;
	if (m_owner24)
		m_owner24->rva002B7250(observer10);
	reinterpret_cast<Rva00574CC1Owner *>(&m_translator28)->rva002B7250((CreateAHeroData *)(Rva00574CC1Base04 *)this);
	if (m_owner74) {
		reinterpret_cast<Rva005748B7 *>(this)->rva005748B7((Rva002BED91 *)&m_handle78);
		m_owner74->rva002B7250((CreateAHeroData *)(Rva00574CC1Base0C *)this);
	}
	if (m_owner6C) {
		reinterpret_cast<Rva005748B7 *>(this)->rva005748B7((Rva002BED91 *)&m_handle70);
		m_owner6C->rva002B7250((CreateAHeroData *)(Rva00574CC1Base08 *)this);
	}
	if (Rva00574CC1Part1 *part = (Rva00574CC1Part1 *)m_parts->get())
		part->vslot1(0);
	if (Rva00574CC1Part2 *part = (Rva00574CC1Part2 *)reinterpret_cast<Rva0042D69DPtrChaseField *>(m_parts)->get())
		part->vslot3();
}
