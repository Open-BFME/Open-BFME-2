// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// HordeSiegeEngineContain rider overrides (retail HordeSiegeEngineContain.cpp):
// Retail 0x0047CD0D (139 bytes): slot 13 of the primary vtable 0x00C474A0 that the
// matched HordeSiegeEngineContain dtor 0x0047CFB2 installs. When the module
// data table accepts the rider for our controlling player and the data count at
// +0x190 is positive, drop the rider from the +0x128 list, decrement +0x12C,
// clear its weapon set flag 0x14 and condition bit 7*32+18; otherwise clear
// condition bit 6*32+17 and run the OpenContain slot.
// Retail 0x0047D0E7 (181 bytes): slot 40 of the vtable 0x00C47328 that the same
// dtor installs at +0x20. The mirror image: push the rider, increment +0x12C and,
// when the matched Object::rva0029091E(0x14) gate passes, set weapon set flag 0x14
// and condition bit 7*32+18; otherwise set bit 6*32+17, run the OpenContain
// slot and raise the +0x130 flag (zeroed by the matched ctor 0x0047D247) for a
// rider whose template has kind-of bit 23.
//
// Slot names: each override is named after the OpenContain implementation it
// replaces and calls (OpenContain vtable 0x00C435E8, installed by the OpenContain
// dtor 0x00464692 with the matched ??_GOpenContain in slot 0): primary slot 13 is
// 0x00462F75 and slot 40 of the +0x20 interface is 0x004638F1 (pinned here).
// A non-primary-base override must share the interface's slot name for cl 7.1 to
// compile it with the +0x20 subobject this, as retail does; the names themselves
// are not established. The rider is pushed as int to the pinned
// BfmeTab1026::bfmeHas1026(int, int) on the module data and stored by value in
// the list<int> member (matched list<int> remove 0x0047BAF7 / push_back
// 0x0005548F), hence the casts.
// Model-condition bits on the rider: word array at Object+0x10C, masked-word
// accessors in a free __forceinline helper calling the pinned notifier
// 0x0028AE6D on a change (bits 6*32+17 and 7*32+18). The template kind-of test
// is inlined in retail (test byte [template+0x10E], 0x80: kind-of mask at
// ThingTemplate+0x10C) and also returns the masked word.
#include <list>
class Thing;
class ModuleData;
class Player;
enum WeaponSetType
{
	WEAPONSET_NONE = 0
};
enum KindOfType
{
	KINDOF_INVALID = -1
};
enum ObjectStatusTypes;
class Rva0047C07FAI;
class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};
class ThingTemplate
{
public:
	__forceinline unsigned int isKindOf(KindOfType t) const { return m_kindOf.test(t); }
private:
	unsigned char m_pad[0x10C];
	Rva0010CBits m_kindOf; // +0x10C
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Player *getControllingPlayer() const;
	bool testStatus(ObjectStatusTypes bit) const;
	void setWeaponSetFlag(WeaponSetType wst);
	void clearWeaponSetFlag(WeaponSetType wst);
	bool rva0029091E(unsigned int i) const;
	void rva0028AE6D();
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x10C - 8];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad15C[0x258 - 0x15C];
	Rva0047C07FAI *m_258; // +0x258
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}
class BfmeTab1026
{
public:
	char bfmeHas1026(int a, int b);
};
class SiegeEngineContainModuleData
{
public:
	unsigned char m_pad[0x18C];
	BfmeTab1026 m_18C; // +0x18C
	int m_190; // +0x190
};
struct Iface00 { virtual void f00(); const ModuleData *m_moduleData; Object *m_object; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
template <int N> class Iface20Slots : public Iface20Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Iface20Slots<0>
{
};
// The +0x20 interface: slots 0..39 placeholders, slot 40 below.
struct Iface20 : public Iface20Slots<40>
{
	virtual void rva004638F1(Object *rider) = 0;
};
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); unsigned char m_pad[0xFC - 0x38]; };
struct IfaceFC { virtual void fFC(); };
class OpenContain
	: public Iface00
	, public Iface0C
	, public Iface10
	, public Iface20
	, public Iface24
	, public Iface28
	, public Iface2C
	, public Iface30
	, public Iface34
	, public IfaceFC
{
public:
	virtual void removeFromContainList(Object *rider);
	virtual void rva004638F1(Object *rider);
};
class TransportContain : public OpenContain
{
private:
	unsigned char m_pad100[0x11C - 0x100];
};
class HordeTransportContain : public TransportContain
{
private:
	unsigned char m_pad11C[0x128 - 0x11C];
};
class HordeSiegeEngineContain : public HordeTransportContain
{
public:
	virtual void removeFromContainList(Object *rider);
	virtual void rva004638F1(Object *rider);
private:
	_STL::list<int> m_list128; // +0x128
	int m_12C; // +0x12C
	bool m_130; // +0x130
};
void HordeSiegeEngineContain::removeFromContainList(Object *rider)
{
	SiegeEngineContainModuleData *data = (SiegeEngineContainModuleData *)m_moduleData;
	if (data->m_18C.bfmeHas1026((int)rider, (int)m_object->getControllingPlayer()) && data->m_190 > 0)
	{
		m_list128.remove(reinterpret_cast<const int &>(rider));
		--m_12C;
		rider->clearWeaponSetFlag((WeaponSetType)0x14);
		clearModelConditionBit(rider, 7 * 32 + 18);
		return;
	}
	clearModelConditionBit(rider, 6 * 32 + 17);
	HordeTransportContain::removeFromContainList(rider);
}
void HordeSiegeEngineContain::rva004638F1(Object *rider)
{
	SiegeEngineContainModuleData *data = (SiegeEngineContainModuleData *)m_moduleData;
	if (data->m_18C.bfmeHas1026((int)rider, (int)m_object->getControllingPlayer()) && data->m_190 > 0)
	{
		m_list128.push_back(reinterpret_cast<const int &>(rider));
		++m_12C;
		if (rider->rva0029091E(0x14))
		{
			rider->setWeaponSetFlag((WeaponSetType)0x14);
			setModelConditionBit(rider, 7 * 32 + 18);
		}
		return;
	}
	setModelConditionBit(rider, 6 * 32 + 17);
	HordeTransportContain::rva004638F1(rider);
	if (rider->getTemplate()->isKindOf((KindOfType)23))
		m_130 = true;
}
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *context);
};
class Rva0047C07FModuleData
{
public:
	unsigned char m_pad[0x18C];
	Rva2225E0Filter m_18C; // +0x18C
	int m_190; // +0x190
};
template <int N> class Rva0047C07FAISlots : public Rva0047C07FAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0047C07FAISlots<0>
{
};
class Rva0047C07FAI : public Rva0047C07FAISlots<142>
{
public:
	// AIUpdateInterface's slot 142 is chooseLocomotorSet(Int), returning Bool.
	// The table at VA 0x00C47B98 selects 0x00268B20; the admitted rider's
	// caller ignores the result, but the interface still returns bool.
	virtual bool rva0047C07FSlot142(int arg) = 0;
};
class Rva0047C07FContain : public TransportContain
{
public:
	virtual void rva004638F1(Object *rider);
private:
	_STL::list<int> m_listFC; // primary+0x11C = secondary+0xFC
	int m_100; // secondary+0x100
	bool m_104; // secondary+0x104
};
void Rva0047C07FContain::rva004638F1(Object *rider)
{
	if (!rider)
		return;
	if (m_object->testStatus((ObjectStatusTypes)0))
		return;
	if (rider->testStatus((ObjectStatusTypes)0))
		return;
	Rva0047C07FModuleData *data = (Rva0047C07FModuleData *)m_moduleData;
	Player *player = m_object->getControllingPlayer();
	if (data->m_18C.accepts(rider, player) && data->m_190 > 0)
	{
		m_listFC.push_back(reinterpret_cast<const int &>(rider));
		++m_100;
		if (rider->rva0029091E(0x14))
		{
			rider->setWeaponSetFlag((WeaponSetType)0x14);
			setModelConditionBit(rider, 7 * 32 + 18);
		}
		Rva0047C07FAI *ai = rider->m_258;
		if (ai)
			ai->rva0047C07FSlot142(0xA);
		return;
	}
	setModelConditionBit(rider, 6 * 32 + 17);
	TransportContain::rva004638F1(rider);
	if (rider->getTemplate()->isKindOf((KindOfType)23))
		m_104 = true;
}
