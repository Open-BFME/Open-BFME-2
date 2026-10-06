// ?executeCrateBehavior@HealCrateCollide@@MAE_NPAVObject@@@Z
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
// 0x004BC8B9 134B slot 12 of vtable 0x0085A868 (class of ??0HealCrateCollide at 0x004BC80F).
// Protected virtual bool(Object*) like Salvage/Veterancy siblings (MAE_N).
// Donor ZH HealCrateCollide::executeCrateBehavior (getControllingPlayer, healAllObjects,
// TheAudio getMiscAudio m_crateHeal, setPosition, addAudioEvent, return TRUE).
// Retail calls rowed getControllingPlayer 0x28AFA9, healAllObjects 0x2AB06A,
// ctor 0x2D97D6, rva002D9508 0x2D9508, dtor 0x2D9A43, TheAudio 0x9FE6E8 slots 0x64/0x138.
#include "Common/BfmeAudioEventPrefix136.h"

class Object;
class Player;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
};

class Player
{
public:
	void healAllObjects();	// 0x002AB06A
};

class AudioManager;
extern AudioManager *TheAudio;

struct HealCrateMiscView
{
	char _pad[0x54];
	OpaqueRefElement4 crateHeal;	// +0x54 m_crateHeal
};

class HealCrateAudioView
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
	virtual const HealCrateMiscView *getMiscAudio();
};

class Rva002D9508
{
public:
	void rva002D9508(const void *src);	// 0x002D9508
};

class CrateCollide
{
public:
	virtual ~CrateCollide();
protected:
	virtual bool executeCrateBehavior(Object *other);
	virtual bool isValidToExecute(const Object *other) const;
};

class HealCrateCollide : public CrateCollide
{
protected:
	virtual bool executeCrateBehavior(Object *other);
};

bool HealCrateCollide::executeCrateBehavior(Object *other)
{
	Player *cratePlayer = other->getControllingPlayer();
	cratePlayer->healAllObjects();
	BfmeAudioEventPrefix136 soundToPlay(reinterpret_cast<HealCrateAudioView *>(TheAudio)->getMiscAudio()->crateHeal, 0);
	((Rva002D9508 *)&soundToPlay)->rva002D9508(other->getPosition());
	reinterpret_cast<HealCrateAudioView *>(TheAudio)->addAudioEvent(&soundToPlay);
	return true;
}
