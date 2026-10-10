// ?setDisabledUntil@Object@@QAEXW4DisabledType@@I@Z
// partial score=0.93 date=2026-10-10
// cl: /O2 /G7 /arch:SSE /MD /EHsc /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii
#include "Common/BfmeAudioEventPrefix136.h"
// ?rva002900E0@Object@@QAEXH@Z retail 0x002900E0 26B.
// Object status-plus-frame setter: setStatus(0x4A true) then store frame at +0x42C.
// Evidence: same-this call to rowed ?setStatus@Object@@QAEXW4ObjectStatusTypes@@_N@Z at 0x002900E7;
// neighbours ?healCompletely@Object (0x0028FF9E) and ?isAbleToAttack@Object (0x00290B73);
// callers pass Object* in ecx plus GameLogic frame in stack e.g. 0x00492BC0 mov ecx edi,
// 0x00379228 mov ecx esi push frame, 0x00492E04 mov ecx ebx; status 0x4A per Rva004AD9B0 TU.
//
// ?rva00290357@Object@@QAEXXZ @0x00290357 108B chain via rowed rva001E4A4E.
// Thiscall void, 11-iteration disabled clear: if rva001E4A4E(i) and frame >=
// m_1cc[i] then clearDisabled(i) plus bit clear in m_1c8 plus for i==1 the
// 0x14e bit2 clear with rva0028AE6D. Evidence: TheGameLogic+0x40 frame,
// rowed 0x001E4A4E plus pin clearDisabled 0x00291CAC plus pin rva0028AE6D,
// callers 0x00245CE0 0x00291E81, neighbours 0x002900FA 0x002903C3.
enum ObjectStatusTypes
{
	STATUS_04 = 4,
	STATUS_4A = 0x4A
};

class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;


enum DisabledType
{
	DISABLED_DEFAULT,
	DISABLED_HACKED,
	DISABLED_EMP,
	DISABLED_HELD,
	DISABLED_PARALYZED,
	DISABLED_UNMANNED,
	DISABLED_UNDERPOWERED,
	DISABLED_FREEFALL,
	DISABLED_AWESTRUCK,
	DISABLED_BRAINWASHED,
	DISABLED_SUBDUED,
	DISABLED_SCRIPT_DISABLED,
	DISABLED_SCRIPT_UNDERPOWERED,
	DISABLED_COUNT
};

class Rva001E4A4E
{
public:
	int rva001E4A4E(int bit);
};

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_VEHICLE = 11,
	KINDOF_DRONE = 73
};

enum TintStatus
{
	TINT_STATUS_DISABLED = 1
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Drawable
{
public:
	void setTintStatus(int statusBits) const { m_tintStatus |= statusBits; }
private:
	unsigned char m_pad[0x118];
	mutable unsigned int m_tintStatus; // +0x118
};

class ThingTemplate
{
public:
	__forceinline unsigned int isKindOf(int k) const { return m_kindOf[k >> 5] & (1U << (k & 0x1f)); }
private:
	char m_pad000[0x108];
	unsigned int m_kindOf[8];
};

template <int N>
class BitFlags
{
public:
	bool any() const;
	void set(int i, int val);
	unsigned int m_words[(N + 31) / 32];
};

class Object;

class ContainModuleInterface
{
public:
	virtual void cslot00(); virtual void cslot01(); virtual void cslot02(); virtual void cslot03();
	virtual void cslot04(); virtual void cslot05(); virtual void cslot06(); virtual void cslot07();
	virtual void cslot08(); virtual void cslot09(); virtual void cslot10(); virtual void cslot11();
	virtual void cslot12(); virtual void cslot13(); virtual void cslot14(); virtual void cslot15();
	virtual void cslot16(); virtual void cslot17(); virtual void cslot18(); virtual void cslot19();
	virtual void cslot20(); virtual void cslot21(); virtual void cslot22(); virtual void cslot23();
	virtual void cslot24(); virtual void cslot25(); virtual void cslot26(); virtual void cslot27();
	virtual void cslot28(); virtual void cslot29(); virtual void cslot30(); virtual void cslot31();
	virtual void cslot32(); virtual void cslot33(); virtual void cslot34(); virtual void cslot35();
	virtual void cslot36(); virtual void cslot37(); virtual void cslot38(); virtual void cslot39();
	virtual void cslot40(); virtual void cslot41(); virtual void cslot42(); virtual void cslot43();
	virtual void cslot44(); virtual void cslot45(); virtual void cslot46(); virtual void cslot47();
	virtual void cslot48(); virtual void cslot49(); virtual void cslot50(); virtual void cslot51();
	virtual void cslot52(); virtual void cslot53(); virtual void cslot54(); virtual void cslot55();
	virtual void cslot56(); virtual void cslot57(); virtual void cslot58(); virtual void cslot59();
	virtual void cslot60(); virtual void cslot61(); virtual void cslot62(); virtual void cslot63();
	virtual void cslot64(); virtual void cslot65(); virtual void cslot66(); virtual void cslot67();
	virtual void cslot68(); virtual void cslot69(); virtual void cslot70(); virtual void cslot71();
	virtual const Object *friend_getRider() const;
};

static ContainModuleInterface *getRetailContain(const Object *obj) { return *(ContainModuleInterface * const *)((const char *)obj + 0x250); }

struct MiscAudio
{
	char m_pad00[0x40];
	OpaqueRefElement4 m_buildingDisabled; // +0x40
	int m_buildingDisabledVal;
	OpaqueRefElement4 m_vehicleDisabled; // +0x48
	int m_vehicleDisabledVal;
	OpaqueRefElement4 m_splatterVehiclePilotsBrain; // +0x50
	int m_splatterVehiclePilotsBrainVal;
};

class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void audioSlot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03)
	AUDIO_SLOT(04) AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07)
	AUDIO_SLOT(08) AUDIO_SLOT(09) AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23)
	AUDIO_SLOT(24)
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);
	AUDIO_SLOT(26) AUDIO_SLOT(27) AUDIO_SLOT(28) AUDIO_SLOT(29)
	AUDIO_SLOT(30) AUDIO_SLOT(31) AUDIO_SLOT(32) AUDIO_SLOT(33)
	AUDIO_SLOT(34) AUDIO_SLOT(35) AUDIO_SLOT(36) AUDIO_SLOT(37)
	AUDIO_SLOT(38) AUDIO_SLOT(39) AUDIO_SLOT(40) AUDIO_SLOT(41)
	AUDIO_SLOT(42) AUDIO_SLOT(43) AUDIO_SLOT(44) AUDIO_SLOT(45)
	AUDIO_SLOT(46) AUDIO_SLOT(47) AUDIO_SLOT(48) AUDIO_SLOT(49)
	AUDIO_SLOT(50) AUDIO_SLOT(51) AUDIO_SLOT(52) AUDIO_SLOT(53)
	AUDIO_SLOT(54) AUDIO_SLOT(55) AUDIO_SLOT(56) AUDIO_SLOT(57)
	AUDIO_SLOT(58) AUDIO_SLOT(59) AUDIO_SLOT(60) AUDIO_SLOT(61)
	AUDIO_SLOT(62) AUDIO_SLOT(63) AUDIO_SLOT(64) AUDIO_SLOT(65)
	AUDIO_SLOT(66) AUDIO_SLOT(67) AUDIO_SLOT(68) AUDIO_SLOT(69)
	AUDIO_SLOT(70) AUDIO_SLOT(71) AUDIO_SLOT(72) AUDIO_SLOT(73)
	AUDIO_SLOT(74) AUDIO_SLOT(75) AUDIO_SLOT(76) AUDIO_SLOT(77)
#undef AUDIO_SLOT
	virtual MiscAudio *getMiscAudio();
};
extern AudioManager *TheAudio;

class Rva002D9508
{
public:
	void rva002D9508(const void *src);
};

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool flag);
	void rva002900E0(int frame);
	void rva002900FA(int frame);
	void rva002903C3();
	void rva002903EF();
	bool clearDisabled(DisabledType type);
	void rva0028AE6D();
	void rva00290357();
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline unsigned int isKindOf(int k) const { return getTemplate()->isKindOf(k); }
	const Coord3D *getPosition() const { return &m_position; }
	void rva0028B292(int v) const;
	void rva0028B8A6(bool becomingDisabled);
	void setDisabledUntil(DisabledType type, unsigned int frame);

private:
	char m_pad00[4];
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	char m_pad44[0x84 - 0x44];
	Drawable *m_drawable; // +0x84
	char m_pad88[0x14C - 0x88];
	unsigned int m_condition14C;
	char m_pad150[0x1C8 - 0x150];
	BitFlags<11> m_disabledMask; // +0x1C8
	unsigned int m_disabledTillFrame[11]; // +0x1CC
	char m_pad1F8[0x42C - 0x1F8];
	unsigned int m_frame42C;
	unsigned int m_frame430;
};

void Object::rva002900E0(int frame)
{
	setStatus(STATUS_4A, true);
	m_frame42C = frame;
}

void Object::rva002900FA(int frame)
{
	setStatus(STATUS_04, true);
	m_frame430 = frame;
}

void Object::rva002903C3()
{
	unsigned int f = m_frame42C;
	if (f <= 0)
		return;
	if (TheGameLogic->m_frame <= f)
		return;
	setStatus(STATUS_4A, false);
	m_frame42C = 0;
}

void Object::rva002903EF()
{
	unsigned int f = m_frame430;
	if (f <= 0)
		return;
	if (TheGameLogic->m_frame <= f)
		return;
	setStatus(STATUS_04, false);
	m_frame430 = 0;
}

void Object::rva00290357()
{
	unsigned int frame = TheGameLogic->m_frame;
	for (int i = 0; i < 11; ++i)
	{
		if ((unsigned char)((Rva001E4A4E *)this)->rva001E4A4E(i) == 0)
			continue;
		if (frame < m_disabledTillFrame[i])
			continue;
		clearDisabled((DisabledType)i);
		m_disabledMask.m_words[(unsigned int)i >> 5] &= ~(1U << (i & 31));
		if (i != 1)
			continue;
		if ((((const unsigned char*)&m_condition14C)[2] & 2) == 0)
			continue;
		m_condition14C &= ~0x20000U;
		rva0028AE6D();
	}
}

// Native 290357..2903C3; disabled-mask/timer offsets measured independently.
// Mixed byte test and dword clear preserve the native model-condition access.

// ?setDisabledUntil@Object@@QAEXW4DisabledType@@I@Z retail 0x00290114 576B.
// ZH Object::setDisabledUntil donor with BFME2 changes: stale-frame early
// out, 11-entry timer bound, power sounds only for EMP/UNDERPOWERED, the
// HACKED set of m_condition14C bit 0x20000 with rva0028AE6D, the drawable
// tint as a +0x118 flag OR for all but HELD/BRAINWASHED/UNMANNED/PARALYZED/
// HACKED/AWESTRUCK, rider recursion through the +0x250 contain slot 72, the
// edge case to rva0028B8A6, and no spawn-behavior or carbomb tail. Evidence:
// rowed rva001E4A4E bit test, rowed rva0028B292 module scan, rowed
// rva0028B8A6 onDisabledEdge analog, BitFlags<11> mask/timers shared with
// rva00290357 above, SlavedUpdateRepair audio slots/entries, PoisonedBehavior
// +0x118 tint, ObjectInitObject inlined kindOf and KINDOF_STRUCTURE 7.
void Object::setDisabledUntil(DisabledType type, unsigned int volatile frame)
{
	unsigned int now = TheGameLogic->m_frame;
	if (frame > now)
	{
	const BitFlags<11> &mask = m_disabledMask;
	bool edgeCase = !mask.any();

	if (type < 0 || type >= 11)
		return;

	if (type == DISABLED_UNMANNED && !isKindOf(KINDOF_DRONE))
	{
		BfmeAudioEventPrefix136 sound(TheAudio->getMiscAudio()->m_splatterVehiclePilotsBrain, 0);
		((Rva002D9508 *)&sound)->rva002D9508(getPosition());
		TheAudio->addAudioEvent(&sound);
	}
	else if (type == DISABLED_UNDERPOWERED || type == DISABLED_EMP)
	{
		if ((mask.m_words[0] & 0x44) == 0)
		{
			if (isKindOf(KINDOF_STRUCTURE))
			{
				BfmeAudioEventPrefix136 sound(TheAudio->getMiscAudio()->m_buildingDisabled, 0);
				((Rva002D9508 *)&sound)->rva002D9508(getPosition());
				TheAudio->addAudioEvent(&sound);
			}
			else if (isKindOf(KINDOF_VEHICLE))
			{
				BfmeAudioEventPrefix136 sound(TheAudio->getMiscAudio()->m_vehicleDisabled, 0);
				((Rva002D9508 *)&sound)->rva002D9508(getPosition());
				TheAudio->addAudioEvent(&sound);
			}
		}
	}

	if (m_disabledTillFrame[type] != frame)
	{
		if (type != DISABLED_HELD && !((Rva001E4A4E *)this)->rva001E4A4E(type))
			rva0028B292(1);

		m_disabledTillFrame[type] = frame;
		m_disabledMask.set(type, frame > TheGameLogic->m_frame);

		if (type == DISABLED_HACKED)
		{
			if ((m_condition14C & 0x20000U) == 0)
			{
				m_condition14C |= 0x20000U;
				rva0028AE6D();
			}
		}

		Drawable *drawable = *(Drawable *volatile *)&m_drawable;
		if (m_drawable && m_disabledMask.any() && type != DISABLED_HELD && type != DISABLED_BRAINWASHED && type != DISABLED_UNMANNED && type != DISABLED_PARALYZED && type != DISABLED_HACKED && type != DISABLED_AWESTRUCK)
			((const Drawable *)drawable)->setTintStatus(TINT_STATUS_DISABLED);

		ContainModuleInterface *contain = getRetailContain(this);
		if (contain)
		{
			Object *rider = (Object *)contain->friend_getRider();
			if (rider)
				rider->setDisabledUntil(type, frame);
		}
	}

	if (edgeCase)
		rva0028B8A6(true);
	}
}
