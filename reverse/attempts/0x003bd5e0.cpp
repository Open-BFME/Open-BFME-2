// ?Rva003BD5E0Emit@@YGXUOpaqueRefElement4@@@Z
// partial score=0.92 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /EHa /MD /DNDEBUG
//
// ?Rva003BD5E0Emit@@YGXUOpaqueRefElement4@@@Z @0x003BD5E0 153B (dump range 18).
// Counted-ref audio emit with an EH frame: looks the ref up through TheAudio
// slot 0x12C, bails when null, builds a BfmeAudioEventPrefix136 on the stack
// through rowed ctor 0x002D97D6, stamps the local player's index through the
// rowed Rva0033F15DDwordSlot::set (the Player_Radar reinterpret_cast idiom),
// plays it through TheAudio slot 0x19 addAudioEvent, destroys it through the
// aliased rowed dtor 0x002D9A43, and releases the ref. Slot 0x12C takes the
// ref by value plus its address; its purpose is unproven.
#include "Common/BfmeAudioEventPrefix136.h"

class Rva0033F15DDwordSlot
{
public:
	void set(int value);
};

class Player
{
public:
	unsigned char m_pad[0x54];
	int m_playerIndex; // +0x54
};
class PlayerList
{
public:
	char m_pad00[0x10];
	Player *m_localPlayer; // +0x10
};
extern PlayerList *ThePlayerList;

class Rva003BD5E0AudioView
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24)
#undef V
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *event);
#define V(n) virtual void pad##n();
	V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74)
#undef V
	virtual void slot75(OpaqueRefElement4 *b, OpaqueRefElement4 a);
};
extern Rva003BD5E0AudioView *TheAudio;

void __stdcall Rva003BD5E0Emit(OpaqueRefElement4 ref)
{
	TheAudio->slot75(&ref, ref);
	if (ref.referent == 0)
		return;
	BfmeAudioEventPrefix136 event(ref, 0);
	reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(ThePlayerList->m_localPlayer->m_playerIndex);
	TheAudio->addAudioEvent(&event);
	if (ref.referent != 0)
		ref.referent->Release_Ref();
}
