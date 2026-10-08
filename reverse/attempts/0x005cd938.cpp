// ?Update@ManualPhaseEnder@StrategicInGameUI@@QAEXXZ
// partial score=0.95 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::ManualPhaseEnder (WorldBuilder
// StrategicInGameUIManualPhaseEnder.cpp). Target facts for Translate
// 0x005CD8F7 (thiscall, ret 4): on message type 0x16, unless TheInGameUI's
// vslot 95 holds, when the message's first argument byte is 0x39 it ends
// the phase (0x005CD8A5, WorldBuilder OnEndPhase) and consumes the message.
// Called by the strategic phase behaviors' translateGameMessage.

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

union GameMessageArgumentType
{
	int integer;
	unsigned char byteValue;
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(int argIndex) const;

	int getType() const { return m_type; }

private:
	char m_pad00[0x10];
	int m_type; // +0x10
};

// TheInGameUI viewed by slot: vslot 95 (+0x17C) returns a bool.
class InGameUI
{
public:
	virtual void vslot00();
	virtual void vslot01();
	virtual void vslot02();
	virtual void vslot03();
	virtual void vslot04();
	virtual void vslot05();
	virtual void vslot06();
	virtual void vslot07();
	virtual void vslot08();
	virtual void vslot09();
	virtual void vslot10();
	virtual void vslot11();
	virtual void vslot12();
	virtual void vslot13();
	virtual void vslot14();
	virtual void vslot15();
	virtual void vslot16();
	virtual void vslot17();
	virtual void vslot18();
	virtual void vslot19();
	virtual void vslot20();
	virtual void vslot21();
	virtual void vslot22();
	virtual void vslot23();
	virtual void vslot24();
	virtual void vslot25();
	virtual void vslot26();
	virtual void vslot27();
	virtual void vslot28();
	virtual void vslot29();
	virtual void vslot30();
	virtual void vslot31();
	virtual void vslot32();
	virtual void vslot33();
	virtual void vslot34();
	virtual void vslot35();
	virtual void vslot36();
	virtual void vslot37();
	virtual void vslot38();
	virtual void vslot39();
	virtual void vslot40();
	virtual void vslot41();
	virtual void vslot42();
	virtual void vslot43();
	virtual void vslot44();
	virtual void vslot45();
	virtual void vslot46();
	virtual void vslot47();
	virtual void vslot48();
	virtual void vslot49();
	virtual void vslot50();
	virtual void vslot51();
	virtual void vslot52();
	virtual void vslot53();
	virtual void vslot54();
	virtual void vslot55();
	virtual void vslot56();
	virtual void vslot57();
	virtual void vslot58();
	virtual void vslot59();
	virtual void vslot60();
	virtual void vslot61();
	virtual void vslot62();
	virtual void vslot63();
	virtual void vslot64();
	virtual void vslot65();
	virtual void vslot66();
	virtual void vslot67();
	virtual void vslot68();
	virtual void vslot69();
	virtual void vslot70();
	virtual void vslot71();
	virtual void vslot72();
	virtual void vslot73();
	virtual void vslot74();
	virtual void vslot75();
	virtual void vslot76();
	virtual void vslot77();
	virtual void vslot78();
	virtual void vslot79();
	virtual void vslot80();
	virtual void vslot81();
	virtual void vslot82();
	virtual void vslot83();
	virtual void vslot84();
	virtual void vslot85();
	virtual void vslot86();
	virtual void vslot87();
	virtual void vslot88();
	virtual void vslot89();
	virtual void vslot90();
	virtual void vslot91();
	virtual void vslot92();
	virtual void vslot93();
	virtual void vslot94();
	virtual bool vslot95();
};
extern InGameUI *TheInGameUI;

namespace StrategicInGameUI
{
class ManualPhaseEnder
{
public:
	GameMessageDisposition Translate(const GameMessage *msg);
	void Update();
    void OnEndPhase(); // 0x005CD8A5 (WorldBuilder name, pinned)
};
}

GameMessageDisposition StrategicInGameUI::ManualPhaseEnder::Translate(const GameMessage *msg)
{
	if (msg->getType() == 0x16 && !TheInGameUI->vslot95() && msg->getArgument(0)->byteValue == 0x39)
	{
		OnEndPhase();
		return DESTROY_MESSAGE;
	}
	return KEEP_MESSAGE;
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct DelegateDesc {
 void *m_object;
 void *m_method;
};
class Rva00579E47 {
public:
 Rva00579E47(const DelegateDesc &);
 ~Rva00579E47() { if(m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
 void *m_ptr;
};
class Rva0042D6AEPtrChaseField { public: int get() const; };
struct PhaseEndButton {
 virtual void f0();
 virtual void f1(int);
 virtual void f2();
 virtual void f3();
 virtual void f4();
 virtual void f5(Rva00579E47 *);
};
struct ManualPhaseEnderNativeView {
 void *unknown00;
 Rva0042D6AEPtrChaseField *button;
 void *unknown08;
 bool installed;
};
// ?Update@ManualPhaseEnder@StrategicInGameUI@@QAEXXZ present-unmatched
void StrategicInGameUI::ManualPhaseEnder::Update()
{
 ManualPhaseEnderNativeView *state=(ManualPhaseEnderNativeView *)this;
 if(state->installed) return;
 PhaseEndButton *button=(PhaseEndButton *)state->button->get();
 if(!button) return;
 DelegateDesc desc;
 void (StrategicInGameUI::ManualPhaseEnder::*method)()=&StrategicInGameUI::ManualPhaseEnder::OnEndPhase;
 desc.m_method=*reinterpret_cast<void **>(&method);
 desc.m_object=this;
 {
  Rva00579E47 wrapper(desc);
  button->f5(&wrapper);
 }
 button->f1(1);
 state->installed=true;
}
