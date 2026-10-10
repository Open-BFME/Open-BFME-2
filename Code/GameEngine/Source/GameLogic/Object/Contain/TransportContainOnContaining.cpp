// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /DNDEBUG /MD /D_CRTIMP= /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7
// stlport
// ?rva0046781F@Rva0046781F@@QAEXPAVObject@@_N@Z retail 0x0046781F..0x00467AB8
// (665 bytes) under the pinned placeholder spelling. WorldBuilder twin
// 0x1158AE0 is TransportContain::onContaining(Object *rider and Bool
// wasSelected) (TransportContain.cpp asserts "Hmm and this object isnt
// transportable" and "Hmm and bad slot count"); 0x0047BA10 calls it as its base.
// Compiled with the ContainModuleInterface subobject this: module data at
// this-0x1C and the owning Object at this-0x18. Body: OpenContain::onContaining
// (0x00463097) first; rider->setDisabled(DISABLED_HELD); optional clear of
// model condition 89; slot count bookkeeping at this+0xE0 through
// Object::rva0028FBBE; model condition 87 on the container when it holds one
// rider; model condition 88 or 90 on the rider (by interface slot 45 and KindOf
// 103) and Drawable::rva00274176(false); slots 59 and 27 (the latter fed status
// bit 61 of the slot-44 mask returned by value); the module temp weapon fired
// at non-allied riders with status 0x3C held around it; the frame stamp at
// this+0xE8; and the filtered fade-in or fade-out of the rider (or of the riders
// it contains when it has KindOf 109 and a contain) over fadeTime * 0.03
// (g_00DBA500) frames. Slot numbers count dwords of the interface vtable.
// The contained-rider list is viewed as list<int>: its base ctor/dtor
// 0x004EC36C/0x004EC395 and the unwind ~list 0x00200667 are the folded
// list<int> bodies.
#include <list>
#include "Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

#define NULL 0

typedef unsigned int UnsignedInt;

enum DisabledType { DISABLED_HELD = 3 };
enum ObjectStatusTypes { OBJECT_STATUS_RVA0046781F = 0x3c };
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };

class Player;
class WeaponTemplate;

class ObjectStatusMaskType
{
public:
	__forceinline bool test(int i) const { return (m_bits[i >> 5] & (1 << (i & 0x1f))) != 0; }
	UnsignedInt m_bits[4];
};

class ModelConditionFlags
{
public:
	__forceinline UnsignedInt test(int i) const { return m_bits[i >> 5] & (1 << (i & 0x1f)); }
	__forceinline void set(int i) { m_bits[i >> 5] |= (1 << (i & 0x1f)); }
	__forceinline void clear(int i) { m_bits[i >> 5] &= ~(1 << (i & 0x1f)); }
	UnsignedInt m_bits[4];
};

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(int k) const { return m_kindOf[k >> 5] & (1 << (k & 0x1f)); }
	unsigned char m_unmodelled000[0x108];
	UnsignedInt m_kindOf[4];							///< +0x108
};

class Drawable
{
public:
	void fadeOut(UnsignedInt frames);
	void fadeIn(UnsignedInt frames);
	void rva00274176(bool flag);
};

class Object
{
public:
	void setDisabled(DisabledType type);
	void rva0028AE6D();
	int rva0028FBBE();
	Drawable *getDrawable() const;
	Relationship getRelationship(const Object *that) const;
	void setStatus(ObjectStatusTypes status, bool set);
	void *rva0028C197() const;

	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline UnsignedInt isKindOf(int k) const { return getTemplate()->isKindOf(k); }
	const Coord3D *getPosition() const { return &m_pos; }
	__forceinline void setModelConditionState(int a)
	{
		if (!m_modelConditionFlags.test(a))
		{
			m_modelConditionFlags.set(a);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(int a)
	{
		if (m_modelConditionFlags.test(a))
		{
			m_modelConditionFlags.clear(a);
			rva0028AE6D();
		}
	}

	void *m_vtbl;
	const ThingTemplate *m_template;					///< +0x04
	unsigned char m_unmodelled008[0x30];
	Coord3D m_pos;										///< +0x38
	unsigned char m_unmodelled044[0xc8];
	ModelConditionFlags m_modelConditionFlags;			///< +0x10C
};

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, const Coord3D *pos);
};
extern WeaponStore *TheWeaponStore;

extern GameLogic *TheGameLogic;

extern float g_00DBA500;	// logic frames per millisecond (0.03)

struct TransportContainModuleData
{
	unsigned char m_unmodelled000[0x144];
	const WeaponTemplate *m_tempWeapon;					///< +0x144
	bool m_tempWeaponKeepsStatus;						///< +0x148
	unsigned char m_unmodelled149[7];
	bool m_useFrameStamp;								///< +0x150
	unsigned char m_unmodelled151[3];
	UnsignedInt m_frameStampDelay;						///< +0x154
	unsigned char m_unmodelled158[0x10];
	Rva2225E0Filter m_fadeFilter;						///< +0x168
	unsigned char m_unmodelled169[3];
	bool m_fadeRiders;									///< +0x16C
	unsigned char m_unmodelled16D[3];
	float m_fadeTime;									///< +0x170
	unsigned char m_unmodelled174[4];
	bool m_fadeOut;										///< +0x178
};

class OpenContain
{
public:
	virtual void onContaining(Object *rider, bool wasSelected);
};

class Rva0028C197Contain
{
public:
	virtual void gap00();
	virtual void gap01();
	virtual void gap02();
	virtual void gap03();
	virtual void gap04();
	virtual void gap05();
	virtual void gap06();
	virtual void gap07();
	virtual void gap08();
	virtual void gap09();
	virtual void gap10();
	virtual void gap11();
	virtual void gap12();
	virtual void gap13();
	virtual void gap14();
	virtual void gap15();
	virtual void gap16();
	virtual void gap17();
	virtual void gap18();
	virtual void gap19();
	virtual void gap20();
	virtual void gap21();
	virtual void gap22();
	virtual void gap23();
	virtual void gap24();
	virtual void gap25();
	virtual void gap26();
	virtual void gap27();
	virtual void gap28();
	virtual void gap29();
	virtual void gap30();
	virtual void gap31();
	virtual void gap32();
	virtual void gap33();
	virtual void gap34();
	virtual void gap35();
	virtual void gap36();
	virtual void gap37();
	virtual void gap38();
	virtual void gap39();
	virtual void gap40();
	virtual void gap41();
	virtual void gap42();
	virtual void gap43();
	virtual void gap44();
	virtual void gap45();
	virtual void gap46();
	virtual void gap47();
	virtual void gap48();
	virtual void gap49();
	virtual void gap50();
	virtual void gap51();
	virtual void gap52();
	virtual void gap53();
	virtual void gap54();
	virtual void gap55();
	virtual void gap56();
	virtual void gap57();
	virtual void gap58();
	virtual void gap59();
	virtual void gap60();
	virtual void gap61();
	virtual void gap62();
	virtual void gap63();
	virtual void gap64();
	virtual void gap65();
	virtual void gap66();
	virtual void slot67(_STL::list<int> *list);
};

class Rva0046781F
{
public:
	virtual void gap00();
	virtual void gap01();
	virtual void gap02();
	virtual void gap03();
	virtual void gap04();
	virtual void gap05();
	virtual void gap06();
	virtual void gap07();
	virtual void gap08();
	virtual void gap09();
	virtual void gap10();
	virtual void gap11();
	virtual void gap12();
	virtual void gap13();
	virtual void gap14();
	virtual void gap15();
	virtual void gap16();
	virtual void gap17();
	virtual void gap18();
	virtual void gap19();
	virtual void gap20();
	virtual void gap21();
	virtual void gap22();
	virtual void gap23();
	virtual void gap24();
	virtual void gap25();
	virtual void gap26();
	virtual void slot27(Object *rider, bool flag);
	virtual void gap28();
	virtual void gap29();
	virtual void gap30();
	virtual void gap31();
	virtual void gap32();
	virtual void gap33();
	virtual void gap34();
	virtual void gap35();
	virtual void gap36();
	virtual void gap37();
	virtual void gap38();
	virtual void gap39();
	virtual void gap40();
	virtual void gap41();
	virtual void gap42();
	virtual void gap43();
	virtual ObjectStatusMaskType slot44(int which);
	virtual bool slot45();
	virtual void gap46();
	virtual void gap47();
	virtual void gap48();
	virtual void gap49();
	virtual void gap50();
	virtual void gap51();
	virtual void gap52();
	virtual void gap53();
	virtual void gap54();
	virtual void gap55();
	virtual void gap56();
	virtual void gap57();
	virtual void gap58();
	virtual void slot59(Object *rider);
	virtual void gap60();
	virtual void gap61();
	virtual void gap62();
	virtual void gap63();
	virtual void gap64();
	virtual void gap65();
	virtual void gap66();
	virtual void gap67();
	virtual void gap68();
	virtual int slot69(int which);

	void rva0046781F(Object *rider, bool wasSelected);

	TransportContainModuleData *getTransportContainModuleData() const
	{
		return *(TransportContainModuleData *const *)((const char *)this - 0x1c);
	}
	Object *getObject() const { return *(Object *const *)((const char *)this - 0x18); }

	unsigned char m_unmodelled004[0xdc];
	int m_extraSlotsInUse;								///< +0xE0
	unsigned char m_unmodelled0E4[4];
	UnsignedInt m_frameStamp;							///< +0xE8
	bool m_clearRiderCondition;							///< +0xEC
};

void Rva0046781F::rva0046781F(Object *rider, bool wasSelected)
{
	((OpenContain *)this)->OpenContain::onContaining(rider, wasSelected);

	TransportContainModuleData *d = getTransportContainModuleData();

	rider->setDisabled(DISABLED_HELD);

	if (m_clearRiderCondition)
		rider->clearModelConditionState(89);

	m_extraSlotsInUse += rider->rva0028FBBE() - 1;

	if (slot69(0) == 1)
		getObject()->setModelConditionState(87);

	Drawable *draw = rider->getDrawable();
	if (draw)
	{
		if (!slot45())
			rider->setModelConditionState(88);
		else if (rider->isKindOf(103))
			rider->setModelConditionState(88);
		else
			rider->setModelConditionState(90);
		draw->rva00274176(false);
	}

	slot59(rider);
	slot27(rider, slot44(0).test(61));

	if (d->m_tempWeapon && getObject()->getRelationship(rider) != ALLIES)
	{
		if (!d->m_tempWeaponKeepsStatus)
			rider->setStatus(OBJECT_STATUS_RVA0046781F, true);
		TheWeaponStore->createAndFireTempWeapon(d->m_tempWeapon, getObject(), getObject()->getPosition());
		if (!d->m_tempWeaponKeepsStatus)
			rider->setStatus(OBJECT_STATUS_RVA0046781F, false);
	}

	if (d->m_useFrameStamp)
		m_frameStamp = TheGameLogic->getFrame() + d->m_frameStampDelay;

	if (d->m_fadeRiders && draw && d->m_fadeTime != 0.0f && d->m_fadeFilter.accepts(rider, NULL))
	{
		if (rider->isKindOf(109) && rider->rva0028C197())
		{
			_STL::list<int> riders;
			((Rva0028C197Contain *)rider->rva0028C197())->slot67(&riders);
			for (_STL::list<int>::iterator it = riders.begin(); it != riders.end(); ++it)
			{
				const Object *obj = (const Object *)*it;
				if (obj)
				{
					Drawable *riderDraw = obj->getDrawable();
					if (riderDraw)
					{
						if (d->m_fadeOut)
							riderDraw->fadeOut((UnsignedInt)(g_00DBA500 * d->m_fadeTime));
						else
							riderDraw->fadeIn((UnsignedInt)(g_00DBA500 * d->m_fadeTime));
					}
				}
			}
		}
		else
		{
			if (d->m_fadeOut)
				draw->fadeOut((UnsignedInt)(g_00DBA500 * d->m_fadeTime));
			else
				draw->fadeIn((UnsignedInt)(g_00DBA500 * d->m_fadeTime));
		}
	}
}
