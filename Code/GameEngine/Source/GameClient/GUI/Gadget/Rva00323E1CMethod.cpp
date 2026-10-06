// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
// ?rva00323E1C@Rva00323E1C@@QAEXXZ @0x00323E1C 121B
// GUI disabled-click style sound: null-check this then winGetUserData 0x005C4ACD then byte +0xe then TheAudio getMiscAudio slot78 +0x138 with int 2 plus field +0xc0 into BfmeAudioEventPrefix136 ctor 0x002D97D6 then addAudioEvent slot25 +0x64 then dtor 0x002D9A43.
// Evidence: callees rowed 0x005C4ACD 0x002D97D6 0x002D9A43 plus TheAudio ?TheAudio@@3PAVAudioManager@@A; callers 0x003250DC 0x00325770; precedent GameWindowCursorSearch.cpp.
#include "Common/BfmeAudioEventPrefix136.h"

class GameWindow
{
public:
	void *winGetUserData();
};

class AudioManager;
extern AudioManager *TheAudio;

struct Rva00323E1CMiscView
{
	char _pad[0xC0];
	OpaqueRefElement4 fieldC0;
};

class Rva00323E1CAudioView
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
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *evt);
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
	virtual void slot41();
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
	virtual const Rva00323E1CMiscView *getMiscAudio();
};

struct Rva00323E1CUserData
{
	char _pad[0x0E];
	unsigned char flag0E;
};

class Rva00323E1C
{
public:
	void rva00323E1C();
};

void Rva00323E1C::rva00323E1C()
{
	if (this == 0)
		return;
	void *userData = ((GameWindow *)this)->winGetUserData();
	if (userData == 0)
		return;
	if (!((Rva00323E1CUserData *)userData)->flag0E)
		return;
	BfmeAudioEventPrefix136 evt(((Rva00323E1CAudioView *)TheAudio)->getMiscAudio()->fieldC0, 2);
	if (TheAudio != 0)
		((Rva00323E1CAudioView *)TheAudio)->addAudioEvent(&evt);
}
