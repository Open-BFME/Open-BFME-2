// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Retail 0x0047BD4C (161 bytes): SiegeEngineContain rider override, slot 13 of
// the primary vtable 0x00C470F8 that the matched SiegeEngineContain dtor
// installs (the vtable 0x00C47A00 of the matched RiderChangeContain ctor holds
// the same body in its slot 13). Same shape as the HordeSiegeEngineContain
// slot 13 with the list and count at +0x11C/+0x120 (TransportContain ends at
// +0x11C), plus a call of slot 142 (arg 0) on the rider +0x258 interface after a
// successful removal.
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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

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
template <int N> class AISlots : public AISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AISlots<0>
{
};
// The rider's +0x258 interface (AI): slots 0..141 placeholders, slot 142 below.
class Rva0047BD4CAI : public AISlots<142>
{
public:
	virtual void rva0047BD4CSlot142(int arg) = 0;
};
class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Player *getControllingPlayer() const;
	void setWeaponSetFlag(WeaponSetType wst);
	void clearWeaponSetFlag(WeaponSetType wst);
	bool rva0029091E(unsigned int i) const;
	void rva0028AE6D();
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x10C - 8];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad15C[0x258 - 0x15C];
	Rva0047BD4CAI *m_258; // +0x258
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
class SiegeEngineContain : public TransportContain
{
public:
	virtual void removeFromContainList(Object *rider);
private:
	_STL::list<int> m_list11C; // +0x11C
	int m_120; // +0x120
};
void SiegeEngineContain::removeFromContainList(Object *rider)
{
	SiegeEngineContainModuleData *data = (SiegeEngineContainModuleData *)m_moduleData;
	if (data->m_18C.bfmeHas1026((int)rider, (int)m_object->getControllingPlayer()) && data->m_190 > 0)
	{
		m_list11C.remove(reinterpret_cast<const int &>(rider));
		--m_120;
		rider->clearWeaponSetFlag((WeaponSetType)0x14);
		clearModelConditionBit(rider, 7 * 32 + 18);
		Rva0047BD4CAI *ai = rider->m_258;
		if (ai)
			ai->rva0047BD4CSlot142(0);
		return;
	}
	clearModelConditionBit(rider, 6 * 32 + 17);
	TransportContain::removeFromContainList(rider);
}
