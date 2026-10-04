// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /EHsc
// ?rva0043A28A@Rva0043A278@@UAEXH@Z @0x0043A28A 148B
// Evidence: vslot 2 offset 0x8 of vtable 0x0083D478; rowed ctor 0x002D97D6 (BfmeAudioEventPrefix136 ref+2 hoisted push 2) plus rowed Weapon::setLeechRangeActive 0x002D95FE plus rowed dtor 0x002D9A43 plus TheAudio 0x009FE6E8 slots 0x64/0xa4/0x138 plus BfmeStrVM0::rva0025D9CB 0x0025D9CB via TheDisplay; precedent Rva00323E1CMethod/Gadget slot78 getMisc plus GlobalWeatherSystemAudio slot25 addAudioEvent plus Rva003FAB93 Weapon-cast setLeech.
#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;
extern class Display *TheDisplay;

struct Rva0043A28AMiscView
{
	char _pad[0x98];
	OpaqueRefElement4 field98;
};

class Rva0043A28AAudioView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *evt);
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual bool slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual const Rva0043A28AMiscView *getMiscAudio();
};

class Weapon
{
public:
	void setLeechRangeActive(bool);
};

class BfmeStrVM0
{
public:
	void rva0025D9CB(bool flag);
};

class Rva00490470
{
public:
	Rva00490470();
	virtual ~Rva00490470();
	virtual void baseSlot1();
};

class Rva0043A278 : public Rva00490470
{
public:
	Rva0043A278();
	virtual void rva0043A28A(int dummy);
};

void Rva0043A278::rva0043A28A(int dummy)
{
	(void)dummy;
	if (!reinterpret_cast<Rva0043A28AAudioView *>(TheAudio)->slot41()) {
		BfmeAudioEventPrefix136 evt(reinterpret_cast<Rva0043A28AAudioView *>(TheAudio)->getMiscAudio()->field98, 2);
		reinterpret_cast<Weapon *>(&evt)->setLeechRangeActive(false);
		evt.m_b52 = 1;
		reinterpret_cast<Rva0043A28AAudioView *>(TheAudio)->addAudioEvent(&evt);
	}
	reinterpret_cast<BfmeStrVM0 *>(TheDisplay)->rva0025D9CB(true);
}
