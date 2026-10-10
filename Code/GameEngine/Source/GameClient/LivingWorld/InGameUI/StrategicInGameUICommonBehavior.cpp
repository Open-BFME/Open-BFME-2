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
class Rva005C9B76 { public: Rva005C9B76(void *arg); virtual ~Rva005C9B76(); char m_data[0x1C]; };
class Rva005CB8D4 { public: Rva005CB8D4(void *parts); virtual ~Rva005CB8D4(); char m_data[0x8]; };
class Rva000AD6F4 { public: Rva000AD6F4() : m_ptr(0) {} ~Rva000AD6F4(); Rva00574910SubTranslator *m_ptr; };
// The +0x5C member: constructor 0x005CC254, destructor 0x005CC287 (rowed
// under its own address name; only the unwind funclets reach it here).
class Rva005CC254 { public: Rva005CC254(void *parts); virtual ~Rva005CC254(); char m_data[0xC]; };
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva00574CC1Handle
{
	Rva00574CC1Handle() : m_ptr(0) {}
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva00574CC1Handle() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class CreateAHeroData;
class Rva00574A8A;
struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *p); };
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
	Impl(Rva00574A8A *owner, unsigned int arg, unsigned int parts);
	virtual ~Impl();

private:
	Rva00574A8A *m_owner18; // +0x18
	unsigned int m_1C;
	Rva0042D6FDPtrChaseField *m_parts; // +0x20
	Rva00574CC1Owner *m_owner24; // +0x24
	Rva005C9B76 m_translator28; // +0x28
	Rva005CB8D4 m_48; // +0x48
	Rva000AD6F4 m_sub; // +0x54
	char m_pad58[0x5C - 0x58];
	Rva005CC254 m_translator5C; // +0x5C
	Rva00574CC1Owner *m_owner6C; // +0x6C
	Rva00574CC1Handle m_handle70; // +0x70
	Rva00574CC1Owner *m_owner74; // +0x74
	Rva00574CC1Handle m_handle78; // +0x78
	bool m_7C;
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

// ??0Impl@CommonBehavior@StrategicInGameUI@@QAE@PAVRva00574A8A@@II@Z retail
// 0x0057525F (215 bytes, ret 12; pinned for its caller 0x00575336 as
// ??0Rva0057525FCall): six base tables, the owner/arg/parts words at
// +0x18/+0x1C/+0x20, the +0x28 translator (0x005C9B76) from the arg, the
// +0x48 (0x0057431D, unrowed, pinned) and +0x5C (0x005CC254) members from
// the parts, cleared holders, then the +4 base joins the +0x28 member's
// observer list (rowed append 0x005A0B4C). Its destructor 0x00574CC1 is
// banked (reverse/attempts) one register tie short.
StrategicInGameUI::CommonBehavior::Impl::Impl(Rva00574A8A *owner, unsigned int arg, unsigned int parts)
	: m_owner18(owner), m_1C(arg), m_parts((Rva0042D6FDPtrChaseField *)parts), m_owner24(0),
	  m_translator28((void *)arg), m_48((void *)m_parts), m_translator5C((void *)m_parts),
	  m_owner6C(0), m_owner74(0), m_7C(false)
{
	((Rva005A0B4CList *)((char *)&m_translator28 + 4))->append((Rva002BA8F1Listener *)(Rva00574CC1Base04 *)this);
}
