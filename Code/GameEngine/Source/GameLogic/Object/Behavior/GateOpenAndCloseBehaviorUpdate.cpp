// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX
//
// GateOpenAndCloseBehavior::update (BFME 2), slot 0 of the UpdateModuleInterface
// vftable 0x00C50138 that the rowed ctor 0x0049889C installs at +0x14, so
// `this` is that subobject and the whole gate is at this-0x14 (vptrs in
// GateOpenAndCloseBehaviorSlots.cpp).
//
// Target facts, from the retail body and the rowed helpers around it:
// - m_state (+0x28) runs 0 opening, 1 open, 2 closing, 3 closed: open() and
//   close() set 0 and 2 through 0x00498AB2, and update moves 0 to 1 and 2 to 3
//   once the percentage (+0x34) reaches 100.
// - The pathfinding state (+0x2C) is switched by the rowed helpers 0x0049924B
//   (to 1) and 0x004992D5 (to 2). Retail calls 0x0049924B but expands
//   0x004992D5 inline at all three of its sites here, with the first flag
//   clear and the second set; rva004992D5Inline repeats that body.
// - +0x40 is a pending request (negative when none; 0 is cleared after use),
//   applied through slot 9 when slot 6 disagrees with it. +0x44/+0x48 are
//   the sound handle and played flag of 0x004989F5 (BFME 1's playSound,
//   0x001FC6B0: remove the old event, start the open or close sound by state,
//   set the flag).
// - Module data: reset time +0x0C and open percentage +0x10 (both unsigned),
//   the two flag-name vectors at +0x2C and +0x38 used by 0x004992D5.
// - The closing case's data getter 0x00498716 is defined here, ahead of
//   update, as in retail's unit: the closing case keeps `elapsed` in edx
//   across the call to it, which the compiler does only for a callee it has
//   already compiled and knows leaves edx alone. Its opening sibling 0x00498707
//   gives no such evidence and stays in Rva00498707Get.cpp.
// - Model-condition bits 21 and 22 of the word at Object+0x10C: the opening
//   states set 21 and clear 22, the closing states the reverse.
//   The test/clear/set and the rowed notifier 0x0028AE6D are the
//   clearAndSetModelConditionState view of RadarUpdate.cpp.
// - The owner of the object at 0x0028BD17 gets its vftable slot 2 each frame;
//   TheAudio's slot 27 removes the gate's sound when the owner dies.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Thing;
class ModuleData
{
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_2 = 2
};

enum ModelConditionFlagType
{
	MODELCONDITION_GATE_OPENING = 21,
	MODELCONDITION_GATE_CLOSING = 22
};

class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class BfmeStrF9
{
public:
	unsigned char m_pad[4];
};

class BfmeObjF9
{
public:
	void setFlag(const BfmeStrF9 &name, char flag);
};

class Rva0028BD17Owner
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
};

class Object
{
public:
	void *rva0028BD17() const;
	Bool testStatus(ObjectStatusTypes bit) const;
	void rva0028B78A(int v);
	void rva0028AB75(bool v);
	void rva0028AE6D();
	Bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	__forceinline void clearAndSetModelConditionState(ModelConditionFlagType clr, ModelConditionFlagType set)
	{
		if (m_modelConditionFlags.test(clr) || !m_modelConditionFlags.test(set))
		{
			m_modelConditionFlags.clear(clr);
			m_modelConditionFlags.set(set);
			rva0028AE6D();
		}
	}

private:
	unsigned char m_pad000[0xA8];
public:
	BfmeObjF9 m_objA8; // +0xA8
private:
	unsigned char m_pad0AC[0x10C - 0xAC];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x438 - 0x158];
	unsigned char m_438; // +0x438
};

class Pathfinder
{
public:
	void RemoveObjectFromPathfindMapKeepingGateFlags(Object *object);
	void AddObjectToPathfindMap(Object *object);
};

class AI
{
public:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void removeAudioEvent(UnsignedInt handle);
};
extern AudioManager *TheAudio;

class GateOpenBehaviorList
{
public:
	void rva004E908C(void *item);
};

class Rva002A8F24
{
public:
	unsigned char m_pad[0x940];
	GateOpenBehaviorList *m_gateList; // +0x940
};
extern Rva002A8F24 *g_00DFEEF8;

struct GateVec
{
	BfmeStrF9 *m_begin;
	BfmeStrF9 *m_end;
	BfmeStrF9 *m_cap;
};

class GateOpenAndCloseBehaviorModuleData : public ModuleData
{
public:
	unsigned char m_pad00[0x0C];
	UnsignedInt m_resetTime; // +0x0C
	UnsignedInt m_percentOpen; // +0x10
	unsigned char m_pad14[0x2C - 0x14];
	GateVec m_vec2C; // +0x2C
	GateVec m_vec38; // +0x38
};

// Data getters by address; 0x00498707 is in Rva00498707Get.cpp.
class Rva00498707
{
public:
	int rva00498707();
};
class Rva00498716
{
	char m_pad0[0xC];
	int m_0C;
	char m_pad1[0x38];
	int m_48;
public:
	int rva00498716();
};
extern int g_00DCB4CC;

// ?rva00498716@Rva00498716@@QAEHXZ @0x00498716 15B
int Rva00498716::rva00498716()
{
	int v = m_48;
	if (v == g_00DCB4CC)
		v = m_0C;
	return v;
}

class GatePrimary
{
public:
	virtual void gap0() = 0;
	virtual void gap1() = 0;
	virtual void gap2() = 0;
	virtual void gap3() = 0;
	virtual void gap4() = 0;
	virtual void gap5() = 0;
	virtual bool slot6() const = 0;
	virtual void open() = 0;
	virtual void close() = 0;
	virtual void rva00498806() = 0;
	virtual unsigned char slot10() const = 0;
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};
struct BehaviorModuleInterface { virtual void f0C() {} };
struct UpdateModuleInterface { virtual UpdateSleepTime update() = 0; };
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class GateOpenAndCloseBehavior : public GatePrimary, public UpdateModule
{
public:
	virtual UpdateSleepTime update();

private:
	void rva00498FAA();
	void rva00498AB2(int state);
	void rva0049924B(bool flag);
	void rva004989F5();

	__forceinline void rva004992D5Inline(bool a, bool b)
	{
		if (m_2C == 2)
		{
			if (!a)
				return;
		}
		if (b)
			rva00498FAA();
		Pathfinder *shim = TheAI->m_pathfinder;
		Object *obj = m_object;
		shim->RemoveObjectFromPathfindMapKeepingGateFlags(obj);
		m_2C = 2;
		obj->rva0028B78A(9);
		const GateOpenAndCloseBehaviorModuleData *data = getGateModuleData();
		for (BfmeStrF9 *p = data->m_vec2C.m_begin; p != data->m_vec2C.m_end; ++p)
			(&obj->m_objA8)->setFlag(*p, 1);
		for (BfmeStrF9 *p = data->m_vec38.m_begin; p != data->m_vec38.m_end; ++p)
			(&obj->m_objA8)->setFlag(*p, 0);
		obj->rva0028AB75(true);
		TheAI->m_pathfinder->AddObjectToPathfindMap(obj);
	}

	const GateOpenAndCloseBehaviorModuleData *getGateModuleData() const
	{
		return static_cast<const GateOpenAndCloseBehaviorModuleData *>(m_moduleData);
	}
	Object *getObject() const { return m_object; }

	int m_linkedObjectId; // +0x24
	int m_state; // +0x28
	int m_2C; // +0x2C
	bool m_30; // +0x30
	Real m_percent; // +0x34
	Real m_38;
	UnsignedInt m_stateFrame; // +0x3C
	int m_request; // +0x40
	UnsignedInt m_soundHandle; // +0x44
	bool m_soundPlayed; // +0x48
};

// ?update@GateOpenAndCloseBehavior@@UAE?AW4UpdateSleepTime@@XZ @0x0049947A 1210B
UpdateSleepTime GateOpenAndCloseBehavior::update()
{
	Object *obj = getObject();
	if (obj == 0)
		return UPDATE_SLEEP_NONE;

	if (obj->rva0028BD17())
		((Rva0028BD17Owner *)obj->rva0028BD17())->slot2();

	if (obj->testStatus(OBJECT_STATUS_2))
		m_30 = false;

	if (obj->isEffectivelyDead())
	{
		if (m_state != 1)
		{
			m_state = 0;
			m_percent = 100.0f;
		}
		rva004992D5Inline(false, true);
		TheAudio->removeAudioEvent(m_soundHandle);
		g_00DFEEF8->m_gateList->rva004E908C(this);
		m_30 = false;
		return UPDATE_SLEEP_NONE;
	}

	const GateOpenAndCloseBehaviorModuleData *data = getGateModuleData();
	if (m_request >= 0)
	{
		if (slot10())
		{
			if (slot6() != (m_request > 0))
			{
				rva00498806();
				if (m_request == 0)
					m_request = -1;
			}
		}
	}

	switch (m_state)
	{
	case 3:
		m_percent = 100.0f;
		m_30 = true;
		obj->clearAndSetModelConditionState(MODELCONDITION_GATE_OPENING, MODELCONDITION_GATE_CLOSING);
		rva0049924B(true);
		break;

	case 2:
	{
		Int elapsed = TheGameLogic->getFrame() - m_stateFrame;
		Real elapsedFrames = (Real)elapsed;
		m_percent = elapsedFrames / (Real)data->m_resetTime * 100.0f;
		if (m_percent >= 100.0f)
			rva00498AB2(3);
		if (m_percent > (Real)(100 - data->m_percentOpen))
			rva0049924B(true);
		if ((UnsignedInt)elapsed > (UnsignedInt)((Rva00498716 *)data)->rva00498716() && !m_soundPlayed)
			rva004989F5();
		m_30 = false;
		obj->clearAndSetModelConditionState(MODELCONDITION_GATE_OPENING, MODELCONDITION_GATE_CLOSING);
		break;
	}

	case 1:
		m_percent = 100.0f;
		m_30 = true;
		obj->clearAndSetModelConditionState(MODELCONDITION_GATE_CLOSING, MODELCONDITION_GATE_OPENING);
		rva004992D5Inline(false, true);
		break;

	case 0:
	{
		Int elapsed = TheGameLogic->getFrame() - m_stateFrame;
		Real elapsedFrames = (Real)elapsed;
		m_percent = elapsedFrames / (Real)data->m_resetTime * 100.0f;
		if (m_percent >= 100.0f)
			rva00498AB2(1);
		if (m_percent > (Real)data->m_percentOpen)
			rva004992D5Inline(false, true);
		if ((UnsignedInt)elapsed > (UnsignedInt)((Rva00498707 *)data)->rva00498707() && !m_soundPlayed)
			rva004989F5();
		m_30 = false;
		obj->clearAndSetModelConditionState(MODELCONDITION_GATE_CLOSING, MODELCONDITION_GATE_OPENING);
		break;
	}
	}

	if (obj->testStatus(OBJECT_STATUS_2))
		m_30 = false;

	return UPDATE_SLEEP_NONE;
}
