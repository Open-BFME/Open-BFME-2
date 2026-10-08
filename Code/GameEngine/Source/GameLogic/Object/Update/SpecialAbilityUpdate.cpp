// cl: /O1 /DNDEBUG /MD
// SpecialAbilityUpdate.cpp: bodies retail links from this TU (tu_map approved),
// folded from three split units with these exact flags. The two
// address-named helper classes keep their names (their rows are mangled with
// them); Object and Overridable are shared views: object model-condition
// words at +0x10C and the status-base pointer at +0x04, final-override kind
// at +0x1C.

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
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
class Object
{
public:
	void rva0028AE6D();
	void setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames);
	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}

	unsigned char m_pad000[4];
	unsigned char *m_base4; // +0x04 status base (bytes +0x108/+0x114 read)
	unsigned char m_pad008[0x10C - 8];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
};
struct Rva004CE41ECondition
{
	ModelConditionFlagType m_type; // +0x00
	unsigned int m_frames; // +0x04
};
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_pad[0x18];
	ModelConditionFlagType m_18; // +0x18
	unsigned int m_1C; // +0x1C
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
class Rva0044E9C7
{
public:
	Rva0044E9C7 *rva0044E9C7(int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g, unsigned int h, unsigned int i, unsigned int j, unsigned int k, unsigned int l, unsigned int m, unsigned int n, unsigned int o);
	unsigned int m_bits[19];
};
class Rva0028F59A
{
public:
	Rva0028F59A(int a, int bit);
	unsigned int m_bits[19];
};
class Rva001E42F2
{
public:
	void rva001E42F2(const int *mask);
};
class SpecialAbilityUpdate : public BehaviorModule
{
public:
	void rva0044EE07();
	void rva0044EE80();
private:
	unsigned char m_pad0C[0x84 - 0x0C];
	int m_84; // +0x84
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	unsigned char m_pad00[0x1C];
	int m_val1C;
};

struct Rva0044EF2CHolder
{
	char m_pad[0x38];
	Overridable *m_over38;
};

class Rva0044EF2C
{
public:
	char m_pad0[4];
	Rva0044EF2CHolder *m_holder04;
	int rva0044EF2C();
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva0044F633Inner
{
public:
	char m_pad0[0x38];
	Overridable *m_override38;
	char m_pad1[0x74 - 0x38 - 4];
	void *m_fallback74;
};

class Rva0044F633
{
public:
	void *rva0044F633();

private:
	char m_pad0[4];
	Rva0044F633Inner *m_inner4;
	char m_pad1[0x40 - 8];
	ObjectID m_target40;
};

// Retail 0x0044EE07 (121 bytes): SpecialAbilityUpdate::rva0044EE07, the
// partner of rva0044EE80 below (same module data +0x18/+0x1C pair). Clears the
// fourteen ability model conditions (0x60 0x5E 0x29 0x76 0x5F 0x84 0x61..0x63
// 0x249..0x24B 0x6E 0x6F) on the Object through the rowed mask clear 0x001E42F2
// with the rowed 0x0044E9C7 mask builder, then, for an untimed module-data
// condition, clears that one through the one-bit mask ctor 0x0028F59A and
// zeroes +0x84. Called by 0x004500A3 with the module as this.
void SpecialAbilityUpdate::rva0044EE07()
{
	{
		Rva0044E9C7 mask;
		((Rva001E42F2 *)getObject())->rva001E42F2((const int *)mask.rva0044E9C7(0,
			0x60, 0x5e, 0x29, 0x76, 0x5f, 0x84, 0x61, 0x62, 0x63,
			0x249, 0x24a, 0x24b, 0x6e, 0x6f));
	}
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	if (data->m_18 != MODELCONDITION_INVALID && data->m_1C == 0)
	{
		((Rva001E42F2 *)getObject())->rva001E42F2((const int *)&Rva0028F59A(0, data->m_18));
		m_84 = 0;
	}
}

// Retail 0x0044EE80 (74 bytes): SpecialAbilityUpdate::rva0044EE80, a
// non-virtual helper called with the module as this by the SpecialAbilityUpdate
// slot-22 base 0x004508B7 and by 0x00451FA2 (SpecialAbilityUpdate block). Name
// by address. Sets the model condition named by the module data +0x18 on the
// Object (directly, notifier as a tail jump) or times it through the matched
// Object::setSpecialModelConditionState 0x0028AEB2 when the +0x1C frames are
// non-zero. Object condition words at +0x10C, masked-word accessors.
void SpecialAbilityUpdate::rva0044EE80()
{
	Object *object = m_object;
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	ModelConditionFlagType mc = data->m_18;
	if (mc == MODELCONDITION_INVALID)
		return;
	if (data->m_1C == 0)
		object->setModelConditionState(mc);
	else
		object->setSpecialModelConditionState(mc, data->m_1C);
}

// ?rva0044EF2C@Rva0044EF2C@@QAEHXZ @0x0044EF2C 22B
// Null-checked final-override int forward. Retail is mov eax [ecx+4]
// mov ecx [eax+0x38] test ecx jne call rowed
// Overridable::friend_getFinalOverride at 0x00288609 then mov eax [eax+0x1C].
// Evidence: unlock lane; caller at 0x0028BDBA in 0x0028BD92 which cmps the
// result; unblocks 0x0028BD92; flags copied from prev TU
// ModuleDataBuildFieldParseChained.cpp. Owner unproven so the name stays
// address-derived.
int Rva0044EF2C::rva0044EF2C()
{
	Overridable *o = m_holder04->m_over38;
	if (o == 0)
		return 0;
	const Overridable *f = o->friend_getFinalOverride();
	return f->m_val1C;
}

// ?rva0044F633@Rva0044F633@@QAEPAXXZ, retail 0x0044F633, 70 bytes.
// Leaf __thiscall: reads this+4 (holder) and this+0x40 (ObjectID), resolves
// the object via TheGameLogic->findObjectByID (rowed 0x00049DC5), then checks
// the holder's Overridable final override (rowed friend_getFinalOverride
// 0x00288609) for kind 0x27 and the target's status bytes at +0x108/+0x114.
// Returns null when all checks pass, else holder+0x74. Evidence: packet
// disassembly, callee rows, TheGameLogic extern in use, SpecialAbilityUpdate
// m_40 ObjectID at +0x40 in neighbour SpecialAbilityUpdateXfer.cpp.
void *Rva0044F633::rva0044F633()
{
	Rva0044F633Inner *inner = m_inner4;
	Object *obj = TheGameLogic->findObjectByID(m_target40);
	const Overridable *ov = inner->m_override38->friend_getFinalOverride();
	if (ov->m_val1C == 0x27) {
		if (obj) {
			unsigned char *base = obj->m_base4;
			if ((base[0x108] & 0x40) == 0) {
				if ((base[0x114] & 8) == 0)
					return 0;
			}
		}
	}
	return inner->m_fallback74;
}
