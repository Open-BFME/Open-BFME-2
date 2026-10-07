// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
//
// ?executeCrateBehavior@MoneyCrateCollide@@MAE_NPAVObject@@@Z, retail
// 0x004BC9E9, 244 bytes: MoneyCrateCollide's executeCrateBehavior, placed
// directly after its matched ctor 0x004BC93F and pool key 0x004BC988, the
// slot SalvageCrateCollide and UnitCrateCollide fill with their own. As ZH's
// MoneyCrateCollide does, the module data's money (unsigned, +0x5C) goes to
// the picker's controlling player and the misc-audio crate-money sound plays
// on the picker. BFME 2 deltas, shared with the rowed
// SalvageCrateCollide::doMoney 0x004BD342: in multiplayer (the rowed
// GameLogic gate 0x0023C6FD) the amount is scaled by the local player's
// TheWritableGlobalData money multiplier, and the deposit is the player's
// ScaleMoney amount through the rowed Money member 0x003B0D7C with the
// player's +0x3BC score keeper. The sound is misc-audio +0x60, copied with
// the rowed event ctor 0x002D97D6 (flag 0) and given the picker's ID by the
// rowed setObjectID 0x002D9531, then TheAudio slot 25 (addAudioEvent).
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

// The multiplayer gate 0x0023C6FD is rowed under this name (BfmeConv939Call939D.cpp);
// it is called on TheGameLogic.
class BfmeGlob939D
{
public:
	char bfmeCall939D();	// 0x0023C6FD
};

class PlayerList
{
public:
	int rva002A7C0B(bool flag);	// 0x002A7C0B
};
extern PlayerList *ThePlayerList;

class MultiPlayMults
{
public:
	float getMoneyMult(int slot) const;	// 0x00235971
};

class GlobalData
{
public:
	char m_pad000[0xEC4];
	MultiPlayMults m_multiPlayMults;	// +0xEC4
};
extern class GlobalData *TheWritableGlobalData;

class Rva0039B7AD
{
	char m_pad[4];
};

class Rva003B0D7C
{
public:
	void rva003B0D7C(int amount, Rva0039B7AD *score, bool flag);	// 0x003B0D7C
	char m_pad[4];
};

class Player
{
public:
	int ScaleMoney(int amount);	// 0x002A9E36
	char m_pad000[0x90];
	Rva003B0D7C m_money;		// +0x90
	char m_pad094[0x3BC - 0x94];
	Rva0039B7AD m_3BC;		// +0x3BC
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	int getID() const { return m_id; }
	char m_pad000[0x74];
	int m_id;			// +0x74
};

class AudioManager;
extern AudioManager *TheAudio;

struct MoneyCrateMiscView
{
	char _pad[0x60];
	OpaqueRefElement4 crateMoney;	// +0x60
};

template <int N> class MoneyCrateAudioSlots : public MoneyCrateAudioSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class MoneyCrateAudioSlots<0>
{
};

class MoneyCrateAudioView : public MoneyCrateAudioSlots<25>
{
public:
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *evt);	// slot 25
	virtual void gap26(); virtual void gap27(); virtual void gap28(); virtual void gap29();
	virtual void gap30(); virtual void gap31(); virtual void gap32(); virtual void gap33();
	virtual void gap34(); virtual void gap35(); virtual void gap36(); virtual void gap37();
	virtual void gap38(); virtual void gap39(); virtual void gap40(); virtual void gap41();
	virtual void gap42(); virtual void gap43(); virtual void gap44(); virtual void gap45();
	virtual void gap46(); virtual void gap47(); virtual void gap48(); virtual void gap49();
	virtual void gap50(); virtual void gap51(); virtual void gap52(); virtual void gap53();
	virtual void gap54(); virtual void gap55(); virtual void gap56(); virtual void gap57();
	virtual void gap58(); virtual void gap59(); virtual void gap60(); virtual void gap61();
	virtual void gap62(); virtual void gap63(); virtual void gap64(); virtual void gap65();
	virtual void gap66(); virtual void gap67(); virtual void gap68(); virtual void gap69();
	virtual void gap70(); virtual void gap71(); virtual void gap72(); virtual void gap73();
	virtual void gap74(); virtual void gap75(); virtual void gap76(); virtual void gap77();
	virtual const MoneyCrateMiscView *getMiscAudio();	// slot 78
};

class Rva002D9531
{
public:
	void rva002D9531(int v);	// 0x002D9531 (AudioEventRTS::setObjectID)
};

struct MoneyCrateCollideModuleData
{
	char m_pad00[0x5C];
	unsigned int m_moneyProvided;	// +0x5C
};

class CrateCollide
{
public:
	virtual ~CrateCollide();
protected:
	virtual bool executeCrateBehavior(Object *other);
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class MoneyCrateCollide : public CrateCollide
{
protected:
	virtual bool executeCrateBehavior(Object *other);
private:
	const MoneyCrateCollideModuleData *getMoneyCrateCollideModuleData() const
	{
		return (const MoneyCrateCollideModuleData *)m_moduleData;
	}
};

// ?executeCrateBehavior@MoneyCrateCollide@@MAE_NPAVObject@@@Z @0x004BC9E9
bool MoneyCrateCollide::executeCrateBehavior(Object *other)
{
	unsigned int money = getMoneyCrateCollideModuleData()->m_moneyProvided;
	if (reinterpret_cast<BfmeGlob939D *>(TheGameLogic)->bfmeCall939D())
	{
		float mult = TheWritableGlobalData->m_multiPlayMults.getMoneyMult(ThePlayerList->rva002A7C0B(false));
		money = (unsigned int)(money * mult);
	}

	Player *player = other->getControllingPlayer();
	if (player)
	{
		int amount = player->ScaleMoney(money);
		player->m_money.rva003B0D7C(amount, &player->m_3BC, true);
	}

	MoneyCrateAudioView *audio = reinterpret_cast<MoneyCrateAudioView *>(TheAudio);
	BfmeAudioEventPrefix136 soundToPlay(audio->getMiscAudio()->crateMoney, 0);
	((Rva002D9531 *)&soundToPlay)->rva002D9531(other->getID());
	reinterpret_cast<MoneyCrateAudioView *>(TheAudio)->addAudioEvent(&soundToPlay);
	return true;
}
