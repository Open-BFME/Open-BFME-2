// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
// ?setLocal@Rva002BA8F1Logic@@QAEXPAVRva002E2903Player@@@Z @0x002B38F7 216B.
// setLocal logic player: skip when same; unregister old via rowed 0x002B359D;
// TheAudio slot 0x8C with 1,1,0; store new at +0x98; TheMouse slot 0x4C with 1;
// two rowed vslot helpers via g_009FE1C8+0x268; when new non-null build
// BfmeAudioEventPrefix136 from player+0x40+0x38 with 1, Weapon-cast setLeech
// true, TheAudio slot 0x64 addAudioEvent. Evidence: pin setLocal, rowed
// callees 0x002B359D 0x003EF2FF 0x003EF041 0x002D97D6 0x002D95FE 0x002D9A43,
// globals TheAudio TheMouse g_009FE1C8, callers 0x002BA9CD 0x002BC621.
#include "Common/BfmeAudioEventPrefix136.h"

class Rva002E2903Player
{
public:
	char m_pad00[0x40];
	Rva002E2903Player *m_40;
};

struct Rva002B359DOuter;
void __stdcall Rva002B359DSet(Rva002B359DOuter *outer, bool flag);

class AudioManager
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *evt);
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35(int a, int b, int c);
};
extern AudioManager *TheAudio;

class Mouse
{
public:
	virtual void m00();
	virtual void m01();
	virtual void m02();
	virtual void m03();
	virtual void m04();
	virtual void m05();
	virtual void m06();
	virtual void m07();
	virtual void m08();
	virtual void m09();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
	virtual void m14();
	virtual void m15();
	virtual void m16();
	virtual void m17();
	virtual void m18();
	virtual void m19(int flag);
};
extern Mouse *TheMouse;

class LivingWorldRegionEffectsManager
{
public:
	void rva003EF2FF();
};

class Rva003EF041
{
public:
	void rva003EF041();
};

class Rva0021294A
{
public:
	char m_pad[0x268];
	void *m_268;
};
extern Rva0021294A *g_009FE1C8;

class Weapon
{
public:
	void setLeechRangeActive(bool value);
};

class Rva002BA8F1Logic
{
public:
	void setLocal(Rva002E2903Player *player);
private:
	char m_pad00[0x98];
	Rva002E2903Player *m_98;
};

void Rva002BA8F1Logic::setLocal(Rva002E2903Player *player)
{
	Rva002E2903Player *old = m_98;
	if (old == player)
		return;
	if (old != 0)
		Rva002B359DSet((Rva002B359DOuter *)old, false);
	((AudioManager *)TheAudio)->s35(1, 1, 0);
	m_98 = player;
	((Mouse *)TheMouse)->m19(1);
	((LivingWorldRegionEffectsManager *)g_009FE1C8->m_268)->rva003EF2FF();
	((Rva003EF041 *)g_009FE1C8->m_268)->rva003EF041();
	Rva002E2903Player *cur = m_98;
	if (cur == 0)
		return;
	cur = cur->m_40;
	BfmeAudioEventPrefix136 evt(*(OpaqueRefElement4 *)((char *)cur + 0x38), 1);
	((Weapon *)&evt)->setLeechRangeActive(true);
	((AudioManager *)TheAudio)->addAudioEvent(&evt);
}
