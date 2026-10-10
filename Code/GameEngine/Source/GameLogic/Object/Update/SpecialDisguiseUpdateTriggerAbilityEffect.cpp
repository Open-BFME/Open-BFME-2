// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?triggerAbilityEffect@SpecialDisguiseUpdate@@UAEXXZ, retail 0x004B0653 (431 bytes).
// Slot 17 of SpecialDisguiseUpdate's vftable 0x00856398 (the address sits at
// 0x008563DC). Like the other SpecialAbilityUpdate slot-17 overrides it first
// runs the base slot (pinned triggerAbilityEffect 0x0045108D). Then, for an
// idle owner (AIUpdateInterface slot 110 at Object+0x258) in ability state 1
// (+0x24): if model condition 300 is already set (pinned Object test
// 0x0006F039) it is cleared and the pinned 0x004B04B2 gets true; otherwise
// the owner's contain module (Object+0x250) is told to act on its contents
// (slot 42) when it reports any (slot 69), the drawable gets the pinned
// 0x00275DCE(2, 0.2, 0.7, 2.0), condition 300 is set, 0x004B04B2 gets
// whether the owner is the local player's, and for the local player the
// drawable's "DisguiseStarted" sound (rowed keyed lookup 0x00274CD8) is
// played for the owner through TheAudio (slot 25), as in
// TurretAIStartRotOrPitchSound.cpp. Method identity beyond the slot is not
// established.

#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

class AIUpdateInterface
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	SLOT08(s18,s19,s1A,s1B,s1C,s1D,s1E,s1F)
	SLOT08(s20,s21,s22,s23,s24,s25,s26,s27)
	SLOT08(s28,s29,s2A,s2B,s2C,s2D,s2E,s2F)
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37)
	SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,s3F)
	SLOT08(s40,s41,s42,s43,s44,s45,s46,s47)
	SLOT08(s48,s49,s4A,s4B,s4C,s4D,s4E,s4F)
	SLOT08(s50,s51,s52,s53,s54,s55,s56,s57)
	SLOT08(s58,s59,s5A,s5B,s5C,s5D,s5E,s5F)
	SLOT08(s60,s61,s62,s63,s64,s65,s66,s67)
	virtual void s68(); virtual void s69(); virtual void s6A(); virtual void s6B();
	virtual void s6C(); virtual void s6D();
	virtual bool isIdle(); // slot 110
};

class ContainModuleInterface
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	SLOT08(s18,s19,s1A,s1B,s1C,s1D,s1E,s1F)
	SLOT08(s20,s21,s22,s23,s24,s25,s26,s27)
	virtual void s28(); virtual void s29();
	virtual void rva42(int which); // slot 42
	virtual void s2B(); virtual void s2C(); virtual void s2D(); virtual void s2E(); virtual void s2F();
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37)
	SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,s3F)
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44();
	virtual unsigned int rva69(int which); // slot 69
};

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str() { if (m_ref) m_ref->Release_Ref(); }
	OpaqueRefCounted *m_ref;
};

class Rva002390CB
{
public:
	Rva002390CB();
	Rva002390CB(const Rva002390CB &other);
	int m_0;
	Rva0036CA00Str m_4;
};

class Drawable
{
public:
	void rva00275DCE(int mode, float a, float b, float c);
	Rva002390CB rva00274CD8(const AsciiString &name); // keyed sound lookup
};

class Player;

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_pad00[0x10];
	Player *m_local; // +0x10
};

extern PlayerList *ThePlayerList;

class ModelConditionFlags
{
public:
	__forceinline unsigned int testMask(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	__forceinline void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	__forceinline void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Object
{
public:
	bool rva0006F039(int bit) const; // tests a word-run bit at +0x10C
	void rva0028AE6D();
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;

	// Inlined at its call sites; the out-of-line body is the matched row in
	// AIInternalMoveToStateOnExit.cpp, so this view must not emit a copy.
	__declspec(dllimport) __forceinline void setModelConditionState(unsigned int bit)
	{
		if (m_conditionBits.testMask(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}
	__declspec(dllimport) __forceinline void clearModelConditionState(unsigned int bit)
	{
		if (m_conditionBits.testMask(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}

	unsigned char m_pad000[0x74];
	int m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	ModelConditionFlags m_conditionBits; // +0x10C
	unsigned char m_pad158[0x250 - 0x158];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
};

class Rva002D9531
{
public:
	void rva002D9531(int objectID); // AudioEventRTS::setObjectID
};

template <int N> class DisguiseAudioSlots : public DisguiseAudioSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class DisguiseAudioSlots<0>
{
};

class AudioManager : public DisguiseAudioSlots<25>
{
public:
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event); // slot 25
};

extern AudioManager *TheAudio;

class ModuleData;

class SpecialAbilityUpdate
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();
	virtual void triggerAbilityEffect();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
	int m_state; // +0x24
};

class SpecialDisguiseUpdate : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
	void rva004B04B2(bool value);
};

// ?triggerAbilityEffect@SpecialDisguiseUpdate@@UAEXXZ @0x004B0653
void SpecialDisguiseUpdate::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();

	Object *obj = m_object;
	if (!obj->m_ai->isIdle() || m_state != 1)
		return;

	if (obj->rva0006F039(300))
	{
		obj->clearModelConditionState(300);
		rva004B04B2(true);
		return;
	}

	ContainModuleInterface *contain = obj->m_contain;
	if (contain && contain->rva69(0) > 0)
		obj->m_contain->rva42(0);

	Drawable *draw = obj->getDrawable();
	if (draw)
		draw->rva00275DCE(2, 0.2f, 0.7f, 2.0f);

	obj->setModelConditionState(300);

	Player *localPlayer = ThePlayerList->getLocalPlayer();
	bool isLocal = true;
	if (obj->getControllingPlayer() != localPlayer)
		isLocal = false;
	rva004B04B2(isLocal);

	if (isLocal && draw)
	{
		BfmeAudioEventPrefix136 sound(*(const OpaqueRefElement4 *)&draw->rva00274CD8(AsciiString("DisguiseStarted")).m_4, 0);
		reinterpret_cast<Rva002D9531 *>(&sound)->rva002D9531(obj->m_id);
		TheAudio->addAudioEvent(&sound);
	}
}
