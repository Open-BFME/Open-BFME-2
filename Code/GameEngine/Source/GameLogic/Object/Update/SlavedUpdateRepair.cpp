// cl: /DNDEBUG /MD
//
// SlavedUpdate methods, Zero Hour SlavedUpdate.cpp transferred: endRepair
// (retail 0x004A1C10, 73 bytes) and setRepairModelConditionStates (retail
// 0x004A197D, 236 bytes). Identity: both sit in the retail SlavedUpdate.cpp
// block (matched pool key 0x004A1875, ctor 0x004A18C5, xfer 0x004A1B54), the
// former calls the latter with MODELCONDITION_PACKING, and both bodies follow
// the Zero Hour source statement for statement.
// BFME2 deltas: model conditions live on the Object (word array at +0x10C) with
// the BFME2 indexes read from these bodies (PACKING 94, UNPACKING 96, FIRING_B
// 47, FIRING_C 53, BETWEEN_FIRING_SHOTS_B 50 / C 56, RELOADING_B 51 / C 57) and
// are updated through masked-word accessors around the pinned notifier
// 0x0028AE6D (unsigned index for the variable one); SLAVED_UPDATE_RATE is the
// int global at VA 0x00E03BBC, assigned before the repair state is reset (the
// load precedes that store in retail); chooseLocomotorSet is AIUpdateInterface
// slot 142 and m_curLocomotor sits at +0x1F0; the two inline Locomotor flag
// clears fold into one and of ~0x48 (PRECISE_Z_POS bit 3, ULTRA_ACCURATE bit 6).

// BFME2 model-condition indexes read from this body (Object word array at
// +0x10C): the Zero Hour names it clears, in the Zero Hour order.
enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1,
	MODELCONDITION_FIRING_B = 47,
	MODELCONDITION_BETWEEN_FIRING_SHOTS_B = 50,
	MODELCONDITION_RELOADING_B = 51,
	MODELCONDITION_FIRING_C = 53,
	MODELCONDITION_BETWEEN_FIRING_SHOTS_C = 56,
	MODELCONDITION_RELOADING_C = 57,
	MODELCONDITION_PACKING = 94,
	MODELCONDITION_UNPACKING = 96
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
class AIUpdateInterface;
class Object
{
public:
	void rva0028AE6D();
	__forceinline void setModelConditionState(ModelConditionFlagType flag)
	{
		if (m_modelConditionFlags.test(flag) == 0)
		{
			m_modelConditionFlags.set(flag);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(ModelConditionFlagType flag)
	{
		if (m_modelConditionFlags.test(flag) != 0)
		{
			m_modelConditionFlags.clear(flag);
			rva0028AE6D();
		}
	}
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
private:
	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
};
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
enum RepairStates
{
	REPAIRSTATE_NONE = 0
};
enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0
};
class Locomotor
{
public:
	enum LocoFlag
	{
		PRECISE_Z_POS = 3,
		ULTRA_ACCURATE = 6
	};
	inline void setUsePreciseZPos(bool u) { setFlag(PRECISE_Z_POS, u); }
	inline void setUltraAccurate(bool u) { setFlag(ULTRA_ACCURATE, u); }
private:
	inline void setFlag(LocoFlag f, bool b) { if (b) m_flags |= (1 << f); else m_flags &= ~(1 << f); }
	unsigned char m_pad[0x44];
	unsigned int m_flags; // +0x44
};
template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};
// AIUpdateInterface: chooseLocomotorSet is primary slot 142 in BFME2.
class AIUpdateInterface : public AIUpdateSlots<142>
{
public:
	virtual bool chooseLocomotorSet(LocomotorSetType wst) = 0;
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
private:
	unsigned char m_pad004[0x1F0 - 4];
	Locomotor *m_curLocomotor; // +0x1F0
};
extern int g_Va00E03BBC; // SLAVED_UPDATE_RATE
// g_Va00E03BBC: matched references place it at VA 0xe03bbc (zero-filled .bss).
int g_Va00E03BBC;
class SlavedUpdate : public BehaviorModule
{
public:
	void endRepair();
	void setRepairModelConditionStates(ModelConditionFlagType flag);
private:
	unsigned char m_pad0C[0x34 - 0x0C];
	int m_framesToWait; // +0x34
	RepairStates m_repairState; // +0x38
	bool m_repairing; // +0x3C
};
void SlavedUpdate::setRepairModelConditionStates(ModelConditionFlagType flag)
{
	Object *obj = getObject();
	obj->clearModelConditionState(MODELCONDITION_PACKING);
	obj->clearModelConditionState(MODELCONDITION_UNPACKING);
	obj->clearModelConditionState(MODELCONDITION_FIRING_B);
	obj->clearModelConditionState(MODELCONDITION_FIRING_C);
	obj->clearModelConditionState(MODELCONDITION_BETWEEN_FIRING_SHOTS_B);
	obj->clearModelConditionState(MODELCONDITION_BETWEEN_FIRING_SHOTS_C);
	obj->clearModelConditionState(MODELCONDITION_RELOADING_B);
	obj->clearModelConditionState(MODELCONDITION_RELOADING_C);
	obj->setModelConditionState(flag);
}
void SlavedUpdate::endRepair()
{
	if (m_repairState != REPAIRSTATE_NONE)
	{
		m_framesToWait = g_Va00E03BBC;
		m_repairState = REPAIRSTATE_NONE;
		m_repairing = false;
		setRepairModelConditionStates(MODELCONDITION_PACKING);
	}
	AIUpdateInterface *ai = getObject()->getAIUpdateInterface();
	if (ai)
	{
		ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
		Locomotor *locomotor = ai->getCurLocomotor();
		if (locomotor)
		{
			locomotor->setUltraAccurate(false);
			locomotor->setUsePreciseZPos(false);
		}
	}
}
