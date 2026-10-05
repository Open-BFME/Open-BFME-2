// ?Rva003BE8DCProbe@@YGXUOpaqueRefElement4@@0@Z
// partial score=0.95 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /EHa /MD /DNDEBUG
//
// PROBE for ?Rva003BE8DC @0x003BE8DC 255B (dump range 18). Team-gated audio
// emit: builds a stack AsciiString copy from [ebp+0xc] (rowed StringBase copy
// ctor 0x00365F0), resolves the team through rowed getTeamNamed 0x003584E9,
// bails when null, takes the rowed Team first member 0x0039E8EB, bails when
// null, gates on a flag at [member+4]+0x115 bit 0x20, optionally walks a
// two-virtual chain ([esi+0x250] slot 0x7c, then slot 0x110) replacing the
// object, then runs the standard audio-emit tail (slot75, (ref,ObjectID)
// ctor 0x002DA461 with +0x74 id, ThePlayerList index set, addAudioEvent,
// dtor, release). Uses real AsciiString first to observe the head codegen
// (push filler, esp save, arg dtor) before deciding the final spelling.
#include "Common/BfmeAudioEventPrefix136.h"
#include "ascii_string.h"

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

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;

class Rva003BE8DCLinkB;

class Rva003BE8DCLinkA
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad0a(); virtual void pad0b();
	virtual void pad0c(); virtual void pad0d(); virtual void pad0e(); virtual void pad0f();
	virtual void pad10(); virtual void pad11(); virtual void pad12(); virtual void pad13();
	virtual void pad14(); virtual void pad15(); virtual void pad16(); virtual void pad17();
	virtual void pad18(); virtual void pad19(); virtual void pad1a(); virtual void pad1b();
	virtual void pad1c(); virtual void pad1d(); virtual void pad1e();
	virtual Rva003BE8DCLinkB *rva007C();
};

class Rva003BE8DCLinkB
{
public:
	virtual void q00(); virtual void q01(); virtual void q02(); virtual void q03();
	virtual void q04(); virtual void q05(); virtual void q06(); virtual void q07();
	virtual void q08(); virtual void q09(); virtual void q0a(); virtual void q0b();
	virtual void q0c(); virtual void q0d(); virtual void q0e(); virtual void q0f();
	virtual void q10(); virtual void q11(); virtual void q12(); virtual void q13();
	virtual void q14(); virtual void q15(); virtual void q16(); virtual void q17();
	virtual void q18(); virtual void q19(); virtual void q1a(); virtual void q1b();
	virtual void q1c(); virtual void q1d(); virtual void q1e(); virtual void q1f();
	virtual void q20(); virtual void q21(); virtual void q22(); virtual void q23();
	virtual void q24(); virtual void q25(); virtual void q26(); virtual void q27();
	virtual void q28(); virtual void q29(); virtual void q2a(); virtual void q2b();
	virtual void q2c(); virtual void q2d(); virtual void q2e(); virtual void q2f();
	virtual void q30(); virtual void q31(); virtual void q32(); virtual void q33();
	virtual void q34(); virtual void q35(); virtual void q36(); virtual void q37();
	virtual void q38(); virtual void q39(); virtual void q3a(); virtual void q3b();
	virtual void q3c(); virtual void q3d(); virtual void q3e(); virtual void q3f();
	virtual void q40(); virtual void q41(); virtual void q42(); virtual void q43();
	virtual Object *rva0110();
};

struct Rva003BE8DCFlag
{
	char m_pad[0x115];
	unsigned char m_f115;
};

class Object
{
public:
	char m_pad00[4];
	Rva003BE8DCFlag *m_p04; // +0x04
	char m_pad08[0x74 - 0x08];
	ObjectID m_id; // +0x74
	char m_pad78[0x250 - 0x78];
	Rva003BE8DCLinkA *m_p250; // +0x250
};

class Team
{
public:
	Object *rva0039E8EB();
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool createIfMissing);
};
extern ScriptEngine *TheScriptEngine;

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

void __stdcall Rva003BE8DCProbe(OpaqueRefElement4 a, OpaqueRefElement4 b)
{
	Team *team = TheScriptEngine->getTeamNamed(*(const AsciiString *)b.referent, false);
	if (team == 0)
		return;
	Object *obj = team->rva0039E8EB();
	if (obj == 0)
		return;
	if ((obj->m_p04->m_f115 & 0x20) != 0) {
		Rva003BE8DCLinkA *link = obj->m_p250;
		if (link != 0) {
			Rva003BE8DCLinkB *link2 = link->rva007C();
			if (link2 != 0) {
				Object *obj2 = link2->rva0110();
				if (obj2 != 0)
					obj = obj2;
			}
		}
	}
	TheAudio->slot75(&b, a);
	if (b.referent == 0)
		return;
	{
		BfmeAudioEventPrefix136 event(b, obj->m_id);
		reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(ThePlayerList->m_localPlayer->m_playerIndex);
		TheAudio->addAudioEvent(&event);
	}
	if (b.referent != 0)
		b.referent->Release_Ref();
}
