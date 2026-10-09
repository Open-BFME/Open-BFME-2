// ?Rva004DA57A@@YAXHPAURva004DA57ATarget@@_NPAHPAVRva004D97B0@@2@Z
// partial score=0.99 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// DRAFT (not landable as is): PickAndPlayUnitVoiceResponse.cpp statics.
//
// ?Rva004DA36A@@YA_NPAVObject@@PBUCoord3D@@@Z  retail 0x004DA36A 528 bytes
//   WB moveRequiresClimbingWalls (PickAndPlayUnitVoiceResponse.cpp asserts
//   353..396). File static; MSVC same-TU custom convention: Object in ECX
//   and the Coord3D on the stack with caller cleanup. Builds a temporary
//   LocomotorSet of "TempVoiceMoveOverWallTesting_" template copies and
//   asks Pathfinder::QuickDoesPathExist with and without it.
// ?Rva004DA57A@@YAXHPAURva004DA57ATarget@@_NPAHPAVRva004D97B0@@2@Z
//   retail 0x004DA57A 1316 bytes; WB doPickAndPlayForMoveCommand (asserts
//   653..666). File static; custom convention: the voice record arrives in
//   EDI and the other five arguments on the stack with caller cleanup.
// ?rva004D9596@Rva004D9596@@QAE_NXZ retail 0x004D9596 28 bytes (already
//   rowed in Code/GameEngine/Source/Common/Rva004D9596Check.cpp) must be
//   defined in this unit before 0x004DA57A: retail keeps ECX=record live
//   across its calls (no mov ecx,edi before the 0x004D97B0 calls at
//   0x004DA903 and 0x004DAA7F); declared-only gives 4 extra bytes.
//
// Both bodies verify exact (explain_mismatch; eh_verify verify_row EXACT for
// both .xdata) but only with the scaffold driver at the bottom. The only
// retail caller of 0x004DA57A is 0x004DAAFD (pickAndPlayUnitVoiceResponse,
// 5078 bytes, unrowed) at 0x004DBA0D; that body also needs the same-TU
// custom-convention statics 0x004D9453 (76 B, EAX/ESI/ECX) and 0x004D9CF3
// (642 B, ESI). Landing therefore means writing 0x004DAAFD into this unit
// in place of DriverRva004DA57A.
#include "ascii_string.h"
#include "Coord3D.h"

struct BfmeE16;
struct BfmePod340;
struct Rva004DA181Element;

namespace _STL {
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a);
	char *m_start;
	char *m_finish;
	char *m_end;
};
template <class T, class A> class vector : public _Vector_base<BfmeE16, allocator<BfmeE16> >
{
public:
	vector(const allocator<BfmeE16> &a = allocator<BfmeE16>()) : _Vector_base<BfmeE16, allocator<BfmeE16> >(a) {}
	~vector();
	void reserve(unsigned int n);
	void push_back(const T &x);
};
}

typedef _STL::vector<Rva004DA181Element, _STL::allocator<Rva004DA181Element> > TempTemplateVector;
typedef _STL::vector<BfmePod340, _STL::allocator<BfmePod340> > TempTemplatePushView;

class Overridable
{
public:
	Overridable *friend_getFinalOverride();
};

class LocomotorTemplate;

class Rva001E4DB0
{
public:
	Rva001E4DB0(const Rva001E4DB0 &o);
	virtual ~Rva001E4DB0();
	Rva001E4DB0 rva001E67BF();
	Overridable *m_next;
	char m_pad08[0x08];
	AsciiString m_name;
	char m_pad14[0x154 - 0x14];
};

inline Rva001E4DB0 *finalOverrideOf(Rva001E4DB0 *t)
{
	if (t->m_next)
		return (Rva001E4DB0 *)t->m_next->friend_getFinalOverride();
	return t;
}

class LocomotorSet
{
public:
	void addLocomotor(const LocomotorTemplate *t, bool b);
};

class BfmeTmpCF
{
public:
	BfmeTmpCF();
	~BfmeTmpCF();
private:
	char m_pad[0x24];
};

struct LocoTemplateFlags
{
	char m_pad[0x150];
	bool m_canScaleWalls;
	bool getCanScaleWalls() const { return m_canScaleWalls; }
};

struct Rva0028AC4EEntry
{
	void *m_vtbl;
	const LocoTemplateFlags *m_template;
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class LocomotorStore
{
public:
	LocomotorTemplate *findLocomotorTemplate(int key);
};
extern LocomotorStore *TheLocomotorStore;

class Locomotor
{
public:
	AsciiString getTemplateName() const;
};

struct LocomotorVectorView
{
	int size() const { return m_end - m_begin; }
	Locomotor **begin() const { return m_begin; }
	Locomotor *const &operator[](unsigned int i) const { return *(begin() + i); }
	Locomotor **m_begin;
	Locomotor **m_end;
	Locomotor **m_cap;
};

class AIUpdateInterface
{
public:
	bool isMoving() const;
	char m_pad[0x1D0];
	LocomotorVectorView m_locomotors;
	char m_pad1DC[0x3B1 - 0x1DC];
	bool m_3B1;
};
typedef AIUpdateInterface AIUpdateView;

class Player
{
public:
	char m_pad[0x54];
	int m_playerIndex;
	char m_pad58[0x750 - 0x58];
	int m_750;
};

class Object
{
public:
	const Rva0028AC4EEntry *rva0028AC4E() const;
	Object *rva002931F5(bool b);
	Player *getControllingPlayer() const;
	bool rva0029493F(Object *other, int kind);
	char m_pad00[0x38];
	Coord3D m_pos;
	char m_pad44[0x258 - 0x44];
	AIUpdateView *m_ai;
};

class Pathfinder
{
public:
	bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, int locoSet);
};

class AI
{
public:
	Pathfinder *getPathfinder() { return m_pathfinder; }
	char m_pad[0x10];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

extern unsigned char g_00E01EA8;

struct Rva002226E5TextPlusString
{
	Rva002226E5TextPlusString() {}
	operator AsciiString();
	const char *m_text;
	int m_len;
	const AsciiString *m_right;
};
Rva002226E5TextPlusString operator+(const char *left, const AsciiString &right);


class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct OpaqueRefElement4
{
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &o);
	OpaqueRefCounted *m_ptr;
};

class Rva002390CB
{
public:
	Rva002390CB();
	Rva002390CB(const Rva002390CB &o);
	~Rva002390CB()
	{
		if (m_ref.m_ptr)
			m_ref.m_ptr->Release_Ref();
	}
	bool isBound() const { return m_ref.m_ptr != 0; }
	int m_id;
	OpaqueRefElement4 m_ref;
};

struct Rva002C99FB
{
	int m_id;
	OpaqueRefCounted *m_ref;
};
inline const Rva002C99FB &asStruct(const Rva002390CB &v) { return *(const Rva002C99FB *)&v; }

class Rva004D977D
{
public:
	void rva004D977D(const Rva002C99FB &a, const Rva002C99FB &b);
};

class Rva004D9750
{
public:
	Rva002390CB rva004D9750(int index);
};

struct DrawableTemplateView
{
	float getMaxHeight() const { return m_524; }
	char m_pad[0x524];
	float m_524;
};

class Drawable
{
public:
	bool rva00276805(int index);
	Rva002390CB rva0027675F(int index);
	const Coord3D *getPosition() const;
	const DrawableTemplateView *getTemplate() const { return m_template; }
	void *m_vtbl;
	const DrawableTemplateView *m_template;
};

class Rva004D9596
{
public:
	bool rva004D9596();

private:
	int m_00;
	int m_04;
	char m_pad08[4];
	int m_0c;
	char m_pad10[8];
	int m_18;
};

class Rva004D97B0
{
public:
	void rva004D97B0(int index);
	void rva004D9874(const AsciiString &name);
	bool isFilled() { return ((Rva004D9596 *)this)->rva004D9596(); }
	int m_00;
	int m_04;
	char m_pad08[8];
	Object *m_obj;
	Drawable *m_drawable;
	Rva004D9750 *m_extra;
};

class Rva004D99FF
{
public:
	~Rva004D99FF();
	int m_ids[6];
	AsciiString m_crush;
	AsciiString m_salvage;
};

struct MiscAudioView
{
	char m_pad[0xE0];
	OpaqueRefElement4 m_E0;
};

#define SLOT(n) virtual void slot##n();
class AudioManager
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
	SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71)
	SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77)
	virtual const MiscAudioView *getMiscAudio();
};
#undef SLOT
extern AudioManager *TheAudio;

class InGameUI
{
public:
	char m_pad[0x8B0];
	bool m_8B0;
	char m_pad8B1[8];
	bool m_8B9;
};
extern InGameUI *TheInGameUI;

struct Rva004DA57AVictimSource
{
	char m_pad[0xFC];
	Object *m_FC;
};

struct Rva004DA57ATarget
{
	char m_pad[4];
	Rva004DA57AVictimSource *m_04;
	char m_pad08[0x0C];
	Coord3D m_pos;
};

struct Coord3DBase;
extern Coord3DBase g_bfmeCoordDefault;

struct BfmePointFD;
bool __cdecl Rva004D933BIs(int command);
bool __cdecl rva004D94FC(Object *obj);
unsigned char __cdecl countsAsMoveIntoCamp(unsigned int mask, const BfmePointFD *from, const BfmePointFD *to);
void __cdecl Rva004D990E(int command, Object *obj, Rva004D97B0 *out, const Coord3D *location);

bool Rva004D9596::rva004D9596()
{
	if (m_00 != -1 || (m_04 != 0 && (m_18 == 0 || m_0c != 0)))
		return true;
	return false;
}

static bool Rva004DA36A(Object *obj, const Coord3D *pos)
{
	if (!obj->rva0028AC4E() || !obj->rva0028AC4E()->m_template->getCanScaleWalls())
		return false;
	Object *horde = obj->rva002931F5(true);
	if (!horde)
		horde = obj;
	if (!horde->rva0028AC4E())
		return false;
	if (!TheAI->getPathfinder()->QuickDoesPathExist(horde, &horde->m_pos, pos, 0))
		return false;
	AIUpdateView *ai = horde->m_ai;
	if (!ai)
		return false;

	BfmeTmpCF locoSet;
	TempTemplateVector temps;
	int count = ai->m_locomotors.size();
	temps.reserve(count);
	g_00E01EA8 = 1;
	for (int i = 0; i < count; ++i)
	{
		Locomotor *loco = ai->m_locomotors[i];
		Rva001E4DB0 *lt = (Rva001E4DB0 *)TheLocomotorStore->findLocomotorTemplate(TheNameKeyGenerator->nameToKey(loco->getTemplateName()));
		if (!lt)
			continue;
		lt = finalOverrideOf(lt);
		((TempTemplatePushView *)&temps)->push_back((const BfmePod340 &)lt->rva001E67BF());
		((Rva001E4DB0 *)temps.m_finish - 1)->m_name = "TempVoiceMoveOverWallTesting_" + lt->m_name;
		((LocomotorSet *)&locoSet)->addLocomotor((const LocomotorTemplate *)((Rva001E4DB0 *)temps.m_finish - 1), true);
	}
	g_00E01EA8 = 0;
	if (!TheAI->getPathfinder()->QuickDoesPathExist(horde, &horde->m_pos, pos, (int)&locoSet))
		return true;
	return false;
}


static void Rva004DA57A(int command, Rva004DA57ATarget *target, bool forced, int *pending, Rva004D97B0 *record, int *voiceType)
{
	Rva004D99FF ids;
	Object *obj = record->m_obj;
	Drawable *drawable = record->m_drawable;
	Player *player = obj->getControllingPlayer();
	Rva004D9750 *extra = record->m_extra;
	bool isSiege = Rva004D933BIs(command);
	if (isSiege)
	{
		ids.m_ids[0] = 0x1B;
		ids.m_ids[1] = 0x1E;
		ids.m_ids[2] = 0x1F;
		ids.m_ids[3] = 0x20;
		ids.m_ids[4] = 0x1C;
		ids.m_ids[5] = 0x1D;
	}
	else
	{
		ids.m_ids[0] = 3;
		ids.m_ids[1] = 0x10;
		ids.m_ids[2] = 0x11;
		ids.m_ids[3] = 0x14;
		ids.m_ids[4] = 4;
		ids.m_ids[5] = 5;
		ids.m_crush = "VoiceCrush";
		ids.m_salvage = "VoiceSalvage";
	}

	if (!isSiege && player && player->m_750 == 2 && !forced)
	{
		Rva002390CB sound;
		sound.m_ref = TheAudio->getMiscAudio()->m_E0;
		((Rva004D977D *)record)->rva004D977D(asStruct(sound), asStruct(Rva002390CB()));
		return;
	}

	if (!isSiege && TheInGameUI->m_8B9 && !(player && player->m_750 == 2))
	{
		if (target && target->m_04)
		{
			Object *victim = target->m_04->m_FC;
			if (victim && obj->rva0029493F(victim, 2))
			{
				record->rva004D9874(ids.m_crush);
				if (record->m_04 != 0)
					*voiceType = 1;
			}
		}
	}
	else if (command == 0x442)
	{
		record->rva004D9874(ids.m_salvage);
		if (record->m_04 != 0)
			*voiceType = 2;
	}

	int garrison = 2;
	bool hasPos = target && !(target->m_pos == *(const Coord3D *)&g_bfmeCoordDefault);
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return;
	bool moving = ai->isMoving() || ai->m_3B1;
	if (!isSiege && TheInGameUI->m_8B0 && moving)
		return;
	if (*pending > 0)
		return;

	if (hasPos)
	{
		Rva004D990E(command, obj, record, &target->m_pos);
		if (!record->isFilled())
		{
			Object *container = obj->rva002931F5(false);
			if (container)
				Rva004D990E(command, container, record, &target->m_pos);
		}
	}

	if (!record->isFilled() && hasPos)
	{
		bool hasMoveCamp = drawable->rva00276805(ids.m_ids[2]);
		bool hasGarrison = drawable->rva00276805(ids.m_ids[1]);
		if (extra)
		{
			hasMoveCamp = hasMoveCamp || extra->rva004D9750(ids.m_ids[2]).isBound();
			hasGarrison = hasGarrison || extra->rva004D9750(ids.m_ids[1]).isBound();
		}
		if ((hasMoveCamp || hasGarrison) && player
			&& countsAsMoveIntoCamp(1 << player->m_playerIndex, (const BfmePointFD *)&obj->m_pos, (const BfmePointFD *)&target->m_pos))
		{
			if (hasGarrison)
			{
				if (garrison == 2)
					garrison = rva004D94FC(obj) ? 1 : 0;
				if (garrison == 1)
					record->rva004D97B0(ids.m_ids[1]);
			}
			if (!record->isFilled())
				record->rva004D97B0(ids.m_ids[2]);
		}
		if (!record->isFilled())
		{
			const DrawableTemplateView *tmpl = drawable->getTemplate();
			if (tmpl && tmpl->getMaxHeight() > 0.0f)
			{
				float heightDiff = target->m_pos.z - drawable->getPosition()->z;
				if (heightDiff > tmpl->getMaxHeight())
					record->rva004D97B0(ids.m_ids[4]);
			}
		}
	}

	if (!record->isFilled())
	{
		Rva002390CB first = drawable->rva0027675F(ids.m_ids[3]);
		Rva002390CB second;
		if (extra)
			extra->rva004D9750(ids.m_ids[3]);
		if (first.isBound() || second.isBound())
		{
			if (garrison == 2)
				garrison = rva004D94FC(obj) ? 1 : 0;
			if (garrison == 1)
				((Rva004D977D *)record)->rva004D977D(asStruct(first), asStruct(second));
		}
	}

	if (!record->isFilled() && hasPos)
	{
		bool hasClimb = drawable->rva00276805(ids.m_ids[5]);
		if (extra)
			hasClimb = hasClimb || extra->rva004D9750(ids.m_ids[5]).isBound();
		if (hasClimb && Rva004DA36A(obj, &target->m_pos))
			record->rva004D97B0(ids.m_ids[5]);
	}

	if (!record->isFilled())
		record->rva004D97B0(ids.m_ids[0]);
}

// SCAFFOLD ONLY: stands in for the real caller 0x004DAAFD so cl compiles the
// statics with their private conventions. Must be replaced, never landed.
void DriverRva004DA57A(int command, Rva004DA57ATarget *target, bool forced, int *pending, int *voiceType)
{
	Rva004D97B0 record;
	Rva004DA57A(command, target, forced, pending, &record, voiceType);
}
