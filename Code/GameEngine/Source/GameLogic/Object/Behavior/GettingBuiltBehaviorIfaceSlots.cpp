// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// Overrides in the vtables the matched GettingBuiltBehavior ctor 0x004542FA
// installs at +0x20 (0x00C403C8, over the all-purecall 27-slot base
// 0x00C40020 rowed as GettingBuiltBehaviorInterface) and at +0x0C (0x00C40440,
// the BehaviorModuleInterface). Each is compiled with its subobject this.
// Layout from the ctor: +0x24 int (1), +0x28 float, +0x2C int, bytes
// +0x30..+0x36, +0x38 int, bytes +0x3C..+0x3E, the BfmePod20 list at +0x40.
// Method identities are not established; names are by address.

#include <math.h>

class Object;
class ModuleData;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

template <int N> class Rva00454430Slots : public Rva00454430Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00454430Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(int bit)
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
	void setStatus(ObjectStatusTypes bit, bool set);

	unsigned char m_pad000[0x74];
	int m_74; // +0x74 (ID)
	unsigned char m_pad078[0x94 - 0x78];
	unsigned int m_94; // +0x94
	unsigned char m_pad098[0x10C - 0x98];
	Rva0010CBits m_conditionBits; // +0x10C
};

class AudioManager : public Rva00454430Slots<27>
{
public:
	virtual void rva004535B7Slot27(int handle) = 0;
};

extern AudioManager *TheAudio;

extern const int g_009BA4E4;

template <class T> class StringBase
{
public:
	bool isEmpty() const;
private:
	T *m_data;
};

struct GettingBuiltBehaviorModuleData
{
	unsigned char m_pad00[0x14];
	StringBase<char> m_14; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	float m_24; // +0x24
};

struct BfmePod20Node
{
	BfmePod20Node *m_next;
	BfmePod20Node *m_prev;
	int m_a[5];
};

template <class T> inline const T &rva00454430Max(const T &a, const T &b)
{
	return a < b ? b : a;
}

__forceinline float fast_float_ceil(float f)
{
	return (float)ceil((double)f);
}

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_CEIL(x) (fast_float2long_round(fast_float_ceil(x)))

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface : public Rva00454430Slots<45>
{
public:
	virtual void rva004543CA(int a1) = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_updateState; // +0x1C
};

class GettingBuiltBehaviorInterface : public Rva00454430Slots<2>
{
public:
	virtual void rva00454430() = 0;
	virtual void gap3() = 0;
	virtual void gap4() = 0;
	virtual void rva004535B7() = 0;
	virtual bool rva004535B7Slot6() = 0;
	virtual bool rva0045314E(Object *obj) = 0;
	virtual void gap8() = 0;
	virtual bool rva004533A7() = 0;
	virtual void rva004543D5(bool value) = 0;
	virtual void gap11() = 0;
	virtual float rva0045314ESlot12(Object *obj) = 0;
	virtual void gap13() = 0; virtual void gap14() = 0; virtual void gap15() = 0;
	virtual void gap16() = 0; virtual void gap17() = 0; virtual void gap18() = 0;
	virtual void gap19() = 0;
	virtual float rva004531E4Slot20(Object *obj) = 0;
	virtual void gap21() = 0;
	virtual bool rva004531E4(Object *obj) = 0;
	virtual bool rva0045362B(int id) = 0;
};

class GettingBuiltBehavior : public UpdateModule, public GettingBuiltBehaviorInterface
{
public:
	virtual void rva004543CA(int a1);
	virtual void rva00454430();
	virtual void rva004535B7();
	virtual bool rva0045314E(Object *obj);
	virtual bool rva004533A7();
	virtual void rva004543D5(bool value);
	virtual bool rva004531E4(Object *obj);
	virtual bool rva0045362B(int id);
private:
	const GettingBuiltBehaviorModuleData *data() const { return (const GettingBuiltBehaviorModuleData *)m_moduleData; }
	int m_24; // +0x24
	float m_28; // +0x28
	unsigned int m_2C; // +0x2C
	bool m_30; // +0x30
	bool m_31; // +0x31
	bool m_32; // +0x32
	bool m_33; // +0x33
	bool m_34; // +0x34
	bool m_35; // +0x35
	bool m_36; // +0x36
	int m_38; // +0x38
	bool m_3C; // +0x3C
	bool m_3D; // +0x3D
	bool m_3E; // +0x3E
	BfmePod20Node *m_40; // +0x40 (list head)
};

static const int GETTING_BUILT_CONDITION_A = 2 * 32 + 4;
static const int GETTING_BUILT_CONDITION_B = 2 * 32 + 5;

// ?rva004543CA@GettingBuiltBehavior@@UAEXH@Z, retail 0x004543CA, 11 bytes:
// slot 45 of the +0x0C vtable 0x00C40440; runs slot 2 of the +0x20 interface,
// the argument unread.
void GettingBuiltBehavior::rva004543CA(int)
{
	rva00454430();
}

// ?rva00454430@GettingBuiltBehavior@@UAEXXZ, retail 0x00454430, 66 bytes: slot 2
// of the +0x20 vtable; +0x2C becomes the module data's +0x24 float times
// g_009BA4E4 (logic frames), at least 1.
void GettingBuiltBehavior::rva00454430()
{
	float frames = (float)g_009BA4E4 * data()->m_24;
	m_2C = (unsigned int)rva00454430Max(frames, 1.0f);
}

// ?rva004535B7@GettingBuiltBehavior@@UAEXXZ, retail 0x004535B7, 116 bytes: slot 5
// of the +0x20 vtable; when slot 6 answers, drops +0x32, clears condition bits
// 2*32+4 and 2*32+5 (notifying per bit), clears statuses 0x14 and 2 and hands
// the +0x24 handle to TheAudio slot 27, resetting it to 1.
void GettingBuiltBehavior::rva004535B7()
{
	if (!rva004535B7Slot6())
		return;
	Object *obj = m_object;
	m_32 = false;
	if (obj->m_conditionBits.test(GETTING_BUILT_CONDITION_A))
	{
		obj->m_conditionBits.clear(GETTING_BUILT_CONDITION_A);
		obj->rva0028AE6D();
	}
	if (obj->m_conditionBits.test(GETTING_BUILT_CONDITION_B))
	{
		obj->m_conditionBits.clear(GETTING_BUILT_CONDITION_B);
		obj->rva0028AE6D();
	}
	obj->setStatus((ObjectStatusTypes)0x14, false);
	obj->setStatus((ObjectStatusTypes)2, false);
	if (TheAudio)
	{
		TheAudio->rva004535B7Slot27(m_24);
		m_24 = 1;
	}
}

// ?rva0045314E@GettingBuiltBehavior@@UAE_NPAVObject@@@Z, retail 0x0045314E, 61
// bytes: slot 7 of the +0x20 vtable; whether the Object's +0x94 count reaches
// slot 12's figure for it rounded up (ZH REAL_TO_INT_CEIL shape: ceil import,
// then fld/fistp).
bool GettingBuiltBehavior::rva0045314E(Object *obj)
{
	if (!obj)
		return false;
	unsigned int count = obj->m_94;
	return count >= (unsigned int)REAL_TO_INT_CEIL(rva0045314ESlot12(obj));
}

// ?rva004533A7@GettingBuiltBehavior@@UAE_NXZ, retail 0x004533A7, 11 bytes: slot 9
// of the +0x20 vtable; whether the module data's +0x14 string is empty.
bool GettingBuiltBehavior::rva004533A7()
{
	return ((const GettingBuiltBehaviorModuleData *)m_moduleData)->m_14.isEmpty();
}

// ?rva004543D5@GettingBuiltBehavior@@UAEX_N@Z, retail 0x004543D5, 10 bytes: slot
// 10 of the +0x20 vtable; stores +0x36.
void GettingBuiltBehavior::rva004543D5(bool value)
{
	m_36 = value;
}

// ?rva004531E4@GettingBuiltBehavior@@UAE_NPAVObject@@@Z, retail 0x004531E4, 61
// bytes: slot 22 of the +0x20 vtable; slot 7's test against slot 20's figure.
bool GettingBuiltBehavior::rva004531E4(Object *obj)
{
	if (!obj)
		return false;
	unsigned int count = obj->m_94;
	return count >= (unsigned int)REAL_TO_INT_CEIL(rva004531E4Slot20(obj));
}

// ?rva0045362B@GettingBuiltBehavior@@UAE_NH@Z, retail 0x0045362B, 39 bytes: slot
// 23 of the +0x20 vtable; false for the owner's own ID, else whether an entry
// of the +0x40 list starts with the ID.
bool GettingBuiltBehavior::rva0045362B(int id)
{
	if (id == m_object->m_74)
		return false;
	for (BfmePod20Node *node = m_40->m_next; node != m_40; node = node->m_next)
	{
		if (id == node->m_a[0])
			return true;
	}
	return false;
}
