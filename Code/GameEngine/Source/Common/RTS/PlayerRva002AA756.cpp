// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// ?rva002AA756@Player@@QAEXH@Z @0x002AA756 144B
// Player counter at +0x318 plus template audio at +0x34/+0x1a4 with playerIndex at +0x54.
// Evidence: caller 0x003BC7EF passes Player* from getEachPlayerFromMask; callee rows
// Rva004210A0 BfmeAudioEventPrefix136 set Rva0033F15D dtor tail144; TheAudio virtual 0x64;
// shape follows Player_Radar.cpp removeRadar/addRadar audio-event precedent.
#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;

class Rva0033F15DDwordSlot
{
public:
	void set(int);
	char lead[0x6C];
	int value;
};

class Rva004210A0
{
public:
	void rva004210A0(int delta);
private:
	int m_unk0;
	int m_val;
};

struct PlayerTemplateView
{
	char pad[0x1A4];
	OpaqueRefElement4 ref;
};

class Rva002AA756AudioView
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
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *);
};

class Player
{
private:
	char m_pad00[0x34];
	PlayerTemplateView *m_template;
	char m_pad38[0x54 - 0x38];
	int m_playerIndex;
	char m_pad58[0x318 - 0x58];
	Rva004210A0 m_counter318;
public:
	void rva002AA756(int delta);
};

void Player::rva002AA756(int delta)
{
	m_counter318.rva004210A0(delta);
	if (m_template == 0)
		return;
	if (delta <= 0)
		return;
	OpaqueRefElement4 *ref = &m_template->ref;
	if (ref->referent == 0)
		return;
	if (TheAudio == 0)
		return;
	BfmeAudioEventPrefix136 event(*ref, 0);
	reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(m_playerIndex);
	reinterpret_cast<Rva002AA756AudioView *>(TheAudio)->addAudioEvent(&event);
}
