// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include /ICode/GameEngine/Source/Common
//
// ?update@AutoAbilityBehavior@@UAE?AW4UpdateSleepTime@@XZ, retail 0x0045A963, 1118 bytes
// (RET 0): the UpdateModuleInterface slot of AutoAbilityBehavior (its receiver is the
// +0x10 subobject, the behavior itself is `this - 0x10`). Evidence: WorldBuilder
// 0x0117C9B0 debug body for statement order (the BitFlags::test name is only an
// inlined helper); target facts from the rowed siblings 0x0045A57C (readiness),
// 0x0045A447 (target pick), 0x0045A8C2, 0x0045A413 and 0x0045A748.
// Looks the command button up by the behavior's name, clears the behavior when the
// button is missing, the owner is dead or the model/kind gates refuse; with the
// button's cooldown handled it either issues a target-less command or scans for a
// target: the data's six {count, spec} rows each query the partition manager through
// the alive / not-self / kind / status / range filter chain plus the row's spec
// filter, the first row with enough hits that yields a pick wins, else the AI's
// closest enemy; the command is then issued at the target (position, object or plain).
// Filter class names and vftables follow the other units that build the same chain
// (ReplenishUnitsBehaviorUpdate.cpp, PropagandaTowerBehaviorDoScan.cpp).
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "Lib/Coord3DCtorView.h"
#include "ascii_string.h"
#include "PartitionRangeQueryCallView.h"
// A by-value re-read of a data member: the retail range pick loads the module data's
// value again for the store instead of reusing the compare's register.
template<class T> static __forceinline T __cp(const T &x) { T t = x; return t; }
#include <string.h>

class Player;
class Object;
class CommandButton;
class LocomotorSet;
class ModuleData;
class AttackPriorityInfo;
class PartitionFilter;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C0719C, allow 0x00261513: +0x08 an object, +0x0C a flag, +0x10 a float.
class Rva00261513Filter : public Rva000421C8
{
public:
	Rva00261513Filter(const Object *obj, bool flag, float value)
		: m_obj(obj), m_flag(flag), m_value(value) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
	bool m_flag;
	float m_value;
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a player, +0x10 a flag.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *spec, Player *player, bool flag)
		: m_spec(spec), m_player(player), m_flag(flag) {}
	virtual bool allow(Object *obj);
	const void *m_spec;
	Player *m_player;
	bool m_flag;
};

// The 224-bit KindOf mask; the (unused, bit) constructor is 0x00045411.
struct Rva00045411BitSet
{
	unsigned m_bits[7];
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the first mask
// and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

// The 128-bit status masks: 0x00391F4E builds one from three bit indices and the
// out-of-line filter constructor 0x003685CF takes the must / must-not pair.
class Rva00391F4E
{
public:
	Rva00391F4E(int a, int b, int c) throw();	// 0x00391F4E
	unsigned int m_bits[4];
};
class BfmeObject872Header
{
public:
	unsigned int m_words[4];
};
class BfmeZeroHeader : public BfmeObject872Header
{
public:
	BfmeZeroHeader() { memset(m_words, 0, sizeof m_words); }
};
class Rva003685CF : public Rva000421C8
{
public:
	Rva003685CF(const BfmeObject872Header &must, const BfmeObject872Header &mustNot) throw();	// 0x003685CF
	virtual bool allow(Object *obj);
	unsigned int m_must[4];
	unsigned int m_mustNot[4];
};

// 0x0065D1C0 clears a list head's +0x04 link (AABTreeIterator::Reset shares its 8 bytes).
class AABTreeIterator
{
public:
	void Reset();
};

class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;	// 0x00263546: any common bit
	unsigned int m_words[19];
};
class ModelConditionFlags
{
public:
	bool rva000B3EB3() const;	// 0x000B3EB3: any bit set
	unsigned int m_words[19];
};

class AIUpdateInterface
{
public:
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual void s016();
	virtual void s017();
	virtual void s018();
	virtual void s019();
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void s090();
	virtual void s091();
	virtual void s092();
	virtual void s093();
	virtual void s094();
	virtual void s095();
	virtual void s096();
	virtual void s097();
	virtual void s098();
	virtual void s099();
	virtual void s100();
	virtual void s101();
	virtual void s102();
	virtual void s103();
	virtual void s104();
	virtual void s105();
	virtual void s106();
	virtual void s107();
	virtual void s108();
	virtual void s109();
	virtual bool s110();
	int rva002632B3() const;	// 0x002632B3
	char m_pad04[0x48 - 4];
};

static inline float readFloat(const float *p) { return *p; }
class CommandButton
{
public:
	char m_pad00[0x1C];
	unsigned int m_flags1C;
	char m_pad20[0x12C - 0x20];
	bool m_noTarget;		// +0x12C
	char m_pad12D[3];
	float m_range130;
	float m_delay134;
	char m_pad138[0x194 - 0x138];
	ModelConditionFlags m_required;	// +0x194
	Rva00263546 m_forbidden;	// +0x1E0
};

class Object
{
public:
	float getVisionRange() const;	// 0x0028DDE0
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void doCommandButton(const CommandButton *button, int source, bool flag);	// 0x00296749
	void rva00297000(const CommandButton *button, Object *target, int a, int b);	// 0x00297000
	void doCommandButtonAtPosition(const CommandButton *button, const Coord3D *pos, int a, int b);	// 0x00297149
	char m_pad00[0x38];
	Coord3D m_position;	// +0x38
	char m_pad44[0x10C - 0x44];
	Rva00263546 m_model;	// +0x10C
	char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai;	// +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_status438;
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};
extern ControlBar *TheControlBar;

class Pathfinder
{
public:
	bool adjustToMeleeDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest);
};
class AI
{
public:
	Object *findClosestEnemy(const Object *me, float range, unsigned int qualifiers,
		const AttackPriorityInfo *info, PartitionFilter *filter, int unk);
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;
extern PartitionManager *ThePartitionManager;
extern int BfmeLogicFramesPerSecond;

struct AutoAbilityEntry
{
	int m_count;		// +0x00
	unsigned int m_spec;	// +0x04
};
struct AutoAbilityData
{
	char m_pad00[8];
	float m_range;		// +0x08
	char m_pad0C[0x14 - 0x0C];
	float m_idleSleep;	// +0x14
	char m_pad18[0x2C - 0x18];
	AutoAbilityEntry m_entry[6];	// +0x2C
	char m_pad5C;
	bool m_rememberPosition;	// +0x5D
	bool m_meleeAdjust;		// +0x5E
};

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	char m_pad14[0x20 - 0x14];
};

struct Rva0045A8C2Options;
struct WideRange
{
	unsigned int count() const { return (m_end - m_begin) >> 3; }
	char *m_begin;
	char *m_end;
};

class AutoAbilityBehavior : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	bool rva0045A57C();
	Object *rva0045A447(BfmeWideResult *items, const CommandButton *button);
	void rva0045A413();
	void rva0045A8C2(Object *source, Object *target, const Rva0045A8C2Options *options);
private:
	AsciiString m_command;	// +0x20
	Coord3D m_memo;		// +0x24
	bool m_hasMemo;		// +0x30
};

UpdateSleepTime AutoAbilityBehavior::update()
{
	Object *obj = m_object;
	const CommandButton *button = TheControlBar->findCommandButton(m_command);
	if (button == 0 || (obj->m_status438 & 1) != 0 || obj->m_model.rva00263546(&button->m_forbidden)
		|| (button->m_required.rva000B3EB3()
			&& !((const Rva00263546 *)&button->m_required)->rva00263546(&obj->m_model)))
	{
		rva0045A413();
		return UPDATE_SLEEP_FOREVER;
	}
	unsigned int kinds = button->m_flags1C;
	bool flagged = ((obj->m_model.m_words[6] >> 22) & 1) != 0;
	if (((kinds & 0x4000000) != 0 && !flagged) || ((kinds & 0x8000000) != 0 && flagged))
	{
		rva0045A413();
		return UPDATE_SLEEP_FOREVER;
	}
	const AutoAbilityData *data = (const AutoAbilityData *)m_moduleData;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai != 0 && data->m_idleSleep > 0.0f && (!ai->s110() || (unsigned char)ai->rva002632B3() != 0))
		return (UpdateSleepTime)(int)((float)BfmeLogicFramesPerSecond * data->m_idleSleep);
	if (!rva0045A57C())
		return (UpdateSleepTime)(BfmeLogicFramesPerSecond + 1);
	int delay = BfmeLogicFramesPerSecond * 10;
	const float &delayRef = button->m_delay134;
	if (delayRef > 0.0f)
	{
		float delayScale = delayRef;
		delay = (int)((float)BfmeLogicFramesPerSecond * delayScale);
	}
	if (button->m_noTarget)
	{
		obj->doCommandButton(button, 2, false);
		return (UpdateSleepTime)delay;
	}
	float range = obj->getVisionRange();
	float dataRange = data->m_range;
	if (dataRange > 0.0f)
		range = __cp(data->m_range);
	else
	{
		const float &buttonRange = button->m_range130;
		if (buttonRange > 0.0f)
			range = buttonRange;
	}
	Coord3D pos = obj->m_position;
	Object *target = 0;
	if (data->m_rememberPosition)
	{
		if (!m_hasMemo)
		{
			m_hasMemo = true;
			m_memo = pos;
		}
		pos = m_memo;
	}
	Rva0026119DFilter alive;
	Rva002611BFFilter notSelf(obj);
	Rva00261513Filter inRange(obj, true, range);
	Rva003685CF status(BfmeZeroHeader(), *(const BfmeObject872Header *)&Rva00391F4E(0, 0x3C, 0x3A));
	Rva0004584D kindFilter(*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
		*(const BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x36));
	alive.link(notSelf.link(kindFilter.link(status.link(&inRange))));
	bool anyEntry = false;
	for (int i = 0; i < 6; i++)
	{
		if (data->m_entry[i].m_count >= 0)
		{
			anyEntry = true;
			BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&pos, range, 0,
				alive.link(&Rva002614ECFilter(&data->m_entry[i].m_spec, obj->getControllingPlayer(), true)), 1);
			if (((const WideRange *)hits.m_value)->count() >= (unsigned int)data->m_entry[i].m_count)
			{
				target = rva0045A447(&hits, button);
				if (target != 0)
					break;
			}
			((AABTreeIterator *)&inRange)->Reset();
		}
	}
	if (!anyEntry && target == 0)
		target = TheAI->findClosestEnemy(obj, range, 0x4A, 0, 0, 0);
	if (target != 0)
	{
		if (ai != 0)
			*(int *)((char *)ai + 0x48) = 2;
		rva0045A8C2(obj, target, (const Rva0045A8C2Options *)button);
		Coord3D dest = target->m_position;
		if (ai != 0 && data->m_meleeAdjust && *(unsigned char *)((char *)target + 0xAC) == 0)
			TheAI->m_pathfinder->adjustToMeleeDestination(obj, *(const LocomotorSet *)((char *)ai + 0x1CC), &dest);
		unsigned int buttonFlags = button->m_flags1C;
		_ReadWriteBarrier();
		unsigned char flagBit = (unsigned char)(buttonFlags >> 5);
		if ((flagBit & 1) != 0)
			obj->doCommandButtonAtPosition(button, &dest, 2, 1);
		else if ((buttonFlags & 7) != 0)
			obj->rva00297000(button, target, 2, 1);
		else
			obj->doCommandButton(button, 2, true);
		return (UpdateSleepTime)delay;
	}
	return (UpdateSleepTime)(BfmeLogicFramesPerSecond + 1);
}
