// ?Rva003BD72FEmit@@YGXUOpaqueRefElement4@@0@Z
// partial score=0.955 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /EHa /MD /DNDEBUG
//
// ?Rva003BD72FEmit@@YGXUOpaqueRefElement4@@0@Z @0x003BD72F 179B (dump range 18).
// Audio emit with a unit lookup, sibling of the banked 0x003BD5E0 emit:
// resolves the unit through rowed ScriptEngine 0x003588E7 getUnitNamed and
// bails when null, feeds TheAudio slot 0x12C with (value, ref-address),
// bails when the ref is null, builds a BfmeAudioEventPrefix136 through the
// rowed (ref, ObjectID) ctor 0x002DA461 with the unit's +0x74 id (the same
// m_id the landed ScriptGlueRva003BD19C TU establishes), stamps the
// controlling player's index through the rowed Rva0033F15DDwordSlot::set,
// plays it through TheAudio slot 0x19 addAudioEvent, destroys it through the
// header-aliased dtor 0x002D9A43, and releases the ref. The referent carries
// the Parameter the lookup unwraps (getUnitNamed reads Parameter+0x24/+0x10);
// that unwrap is inferred. Slot75 view shared with the 0x003BD5E0 stash.
#include "Common/BfmeAudioEventPrefix136.h"

class Rva0033F15DDwordSlot
{
public:
	void set(int value);
};

class Parameter;

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

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad[0x74];
	ObjectID m_id; // +0x74
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern ScriptEngine *TheScriptEngine;

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

struct Rva003BD72FScope
{
	Rva003BD72FScope() {}
	~Rva003BD72FScope() {}
};

void __stdcall Rva003BD72FEmit(OpaqueRefElement4 a, OpaqueRefElement4 b)
{
	Object *obj = TheScriptEngine->getUnitNamed((Parameter *)b.referent);
	if (obj == 0)
		return;
	TheAudio->slot75(&b, a);
	Rva003BD72FScope scope;
	if (b.referent == 0)
		return;
	{
		BfmeAudioEventPrefix136 event(b, obj->m_id);
		Player *player = obj->getControllingPlayer();
		if (player != 0)
			reinterpret_cast<Rva0033F15DDwordSlot *>(&event)->set(player->m_playerIndex);
		TheAudio->addAudioEvent(&event);
	}
	if (b.referent != 0)
		b.referent->Release_Ref();
}
