// cl: /O1 /DNDEBUG /MD /EHsc /Oy- /G7
//
// ?rva00274176@Drawable@@QAEX_N@Z, retail 0x00274176, 104 bytes.
// Drawable apply-pending over condition state at this+0x258 via rowed helper
// 0x00271C8A plus iface vector at this+0x158/0x15C with dirty flag at +0x443.
// Evidence: BFME1 DrawableBFME.cpp applyPendingModelConditionFlags donor plus
// pending clear at +0x2A4 and pending set at +0x2F0 via caller 0x002761F3 plus
// sibling flush shapes 0x0027434D and 0x00275376 plus 27 unblocked callers.
//
class Rva00271C8A
{
public:
	void rva00271C8A(const int *a, const int *b);
	int m_bits[19];
};

class BfmeDrawableClientIface
{
public:
	virtual void replaceModelConditionState(const void *state, bool immediate, int effect);
};

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

class ElemA274445
{
public:
	virtual void _00() = 0;
	virtual void _01() = 0;
	virtual void _02() = 0;
	virtual void _03() = 0;
	virtual void _04() = 0;
	virtual void _05() = 0;
	virtual void _06() = 0;
	virtual void _07() = 0;
	virtual void _08() = 0;
	virtual void _09() = 0;
	virtual void _10() = 0;
	virtual void _11() = 0;
	virtual void _12() = 0;
	virtual void _13() = 0;
	virtual void _14() = 0;
	virtual void _15() = 0;
	virtual void _16() = 0;
	virtual void _17() = 0;
	virtual void _18() = 0;
	virtual void _19() = 0;
	virtual void _20() = 0;
	virtual void _21() = 0;
	virtual void _22() = 0;
	virtual void _23() = 0;
	virtual void _24() = 0;
	virtual void _25() = 0;
	virtual void _26() = 0;
	virtual void _27() = 0;
	virtual void _28() = 0;
	virtual void _29() = 0;
	virtual void _30() = 0;
	virtual void _31() = 0;
	virtual void _32() = 0;
	virtual void _33() = 0;
	virtual void _34() = 0;
	virtual void _35() = 0;
	virtual void _36() = 0;
	virtual void _37() = 0;
	virtual void _38() = 0;
	virtual void _39() = 0;
	virtual void _40() = 0;
	virtual void _41() = 0;
	virtual void *slot42() = 0;
};

class ElemB274445
{
public:
	virtual void _00() = 0;
	virtual void _01() = 0;
	virtual void _02() = 0;
	virtual void _03() = 0;
	virtual void _04() = 0;
	virtual void _05() = 0;
	virtual void _06() = 0;
	virtual void _07() = 0;
	virtual void _08() = 0;
	virtual void _09() = 0;
	virtual void _10() = 0;
	virtual void _11() = 0;
	virtual void _12() = 0;
	virtual void _13() = 0;
	virtual void _14() = 0;
	virtual void _15() = 0;
	virtual void _16() = 0;
	virtual void _17() = 0;
	virtual void _18() = 0;
	virtual void _19() = 0;
	virtual void slot20(float f) = 0;
};

class ElemB27434D
{
public:
	virtual void _00() = 0;
	virtual void _01() = 0;
	virtual void _02() = 0;
	virtual void _03() = 0;
	virtual void _04() = 0;
	virtual void _05() = 0;
	virtual void _06() = 0;
	virtual void _07() = 0;
	virtual void _08() = 0;
	virtual void _09() = 0;
	virtual void _10() = 0;
	virtual void _11() = 0;
	virtual void _12() = 0;
	virtual void _13() = 0;
	virtual void _14() = 0;
	virtual void _15() = 0;
	virtual void _16() = 0;
	virtual void _17() = 0;
	virtual void _18() = 0;
	virtual void _19() = 0;
	virtual void _20() = 0;
	virtual void _21() = 0;
	virtual void _22() = 0;
	virtual int slot23(int x) = 0;
};

template <int N> class BitFlags
{
public:
	unsigned m_words[7];
};

// A KindOfMaskType with two kinds set (rowed 0x0006EE7A).
struct Rva0006EE7A : public BitFlags<69>
{
	Rva0006EE7A(int unused, int b1, int b2);
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;
};

typedef int Color;

class Object : public Thing
{
public:
	Color getIndicatorColor() const;
	Color getNightIndicatorColor() const;
};

enum TimeOfDay
{
	TIME_OF_DAY_NIGHT = 4
};

class GlobalData
{
public:
	unsigned char m_pad000[0x134];
	TimeOfDay m_timeOfDay; // +0x134 (rowed GlobalData::setTimeOfDay)
};
extern GlobalData *TheGlobalData;

class GameLogic
{
public:
	unsigned char m_pad000[0x11C];
	bool m_11C; // +0x11C
	unsigned char m_pad11D[0x190 - 0x11D];
	unsigned char m_indicatorOverride; // +0x190
	Color m_indicatorColor; // +0x194
};
extern GameLogic *TheGameLogic;

class DrawModule
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05();
	virtual void onDrawableBoundToObject();
};

class Drawable
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12();
	virtual void vslot13();

	void rva00274176(bool immediate);
	void rva00274445(float f);
	int rva0027434D(int x);
	void setIndicatorColor(Color color);
	void friend_bindToObject(Object *obj);
	void changedTeam();
	void rva00270FAC(bool show);

	Object *getObject();
private:
	unsigned char m_pad0[0xFC - 4];
	Object *m_object; // +0xFC
	unsigned char m_padFC[0x14C - 0x100];
	DrawModule **m_drawModules; // +0x14C
	unsigned char m_pad150[0x158 - 0x150];
	BfmeDrawableClientIface **m_ifaceBegin;
	BfmeDrawableClientIface **m_ifaceEnd;
	unsigned char m_pad1[0x258 - 0x160];
	Rva00271C8A m_conditionState;
	Rva00271C8A m_pendingClear;
	Rva00271C8A m_pendingSet;
	unsigned char m_pad2[0x443 - 0x33C];
	bool m_isModelDirty;
	unsigned char m_pad444[0x454 - 0x444];
	Color m_indicatorColor; // +0x454, read back by rva00270FAC
};

void Drawable::rva00274176(bool immediate)
{
	if (!m_isModelDirty && !immediate) {
		return;
	}
	m_conditionState.rva00271C8A(m_pendingClear.m_bits, m_pendingSet.m_bits);
	BfmeDrawableClientIface **end = m_ifaceEnd;
	for (BfmeDrawableClientIface **p = m_ifaceBegin; p != end; ++p) {
		(*p)->replaceModelConditionState(&m_conditionState, immediate, 0);
	}
	m_isModelDirty = false;
}

#pragma optimize("y", on)
void Drawable::rva00274445(float f)
{
	void **arr = *(void ***)((char *)this + 0x14c);
	for (void **p = arr; *p != 0; ++p) {
		ElemA274445 *elem = (ElemA274445 *)*p;
		void *obj = elem->slot42();
		if (obj != 0)
			((ElemB274445 *)obj)->slot20(f);
	}
	ji_006291ae((char *)this + 0x2f0, 0, 0x4c);
	ji_006291ae((char *)this + 0x2a4, 0, 0x4c);
}
#pragma optimize("", on)

#pragma optimize("y", on)
int Drawable::rva0027434D(int x)
{
	if (m_isModelDirty) {
		m_conditionState.rva00271C8A(m_pendingClear.m_bits, m_pendingSet.m_bits);
		BfmeDrawableClientIface **end = m_ifaceEnd;
		for (BfmeDrawableClientIface **p = m_ifaceBegin; p != end; ++p) {
			(*p)->replaceModelConditionState(&m_conditionState, false, 0);
		}
		m_isModelDirty = false;
	}
	void **arr = *(void ***)((char *)this + 0x14c);
	for (void **p = arr; *p != 0; ++p) {
		ElemA274445 *elem = (ElemA274445 *)*p;
		void *obj = elem->slot42();
		int r;
		if (obj != 0)
			r = ((ElemB27434D *)obj)->slot23(x);
		else
			r = 0;
		if (r != 0)
			return r;
	}
	return 0;
}
#pragma optimize("", on)

// ?setIndicatorColor@Drawable@@QAEXH@Z, retail 0x002741DE (98B): BFME's
// Drawable::setIndicatorColor. It stores the color at +0x454 and lets the
// rowed 0x00270FAC (which broadcasts +0x454 to the draw modules when its
// flag is set, 0 otherwise) show it when the GameLogic +0x11C flag is set
// or the object is any kind of (0x78, 0xB5) - the same mask the rowed
// 0x00272414 gates on. Called by changedTeam below with the object color.
// The named local is what puts the flag in the dead argument slot.
void Drawable::setIndicatorColor(Color color)
{
	m_indicatorColor = color;
	Object *obj = m_object;
	bool show = TheGameLogic->m_11C || (obj && obj->isAnyKindOf(Rva0006EE7A(0, 0x78, 0xB5)));
	rva00270FAC(show);
}

// ?changedTeam@Drawable@@QAEXXZ, retail 0x002742AC (57B): Zero Hour's
// Drawable::changedTeam (night color when TheGlobalData's time of day is
// night) without the fake-structure decal, ending in a tail call to the
// drawable's virtual slot 13. Called by Object::setCustomIndicatorColor.
void Drawable::changedTeam()
{
	Object *object = m_object;
	if (object)
	{
		if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
			setIndicatorColor(object->getNightIndicatorColor());
		else
			setIndicatorColor(object->getIndicatorColor());
		vslot13();
	}
}

// ?friend_bindToObject@Drawable@@QAEXPAVObject@@@Z, retail 0x00274240 (108B):
// BFME's binding, transferred from Open-BFME-1's matched body (6583b3c1,
// game/GameEngine/Source/GameClient/Drawable.cpp friend_bindToObject)
// (GameLogic indicator override, else Zero Hour's night/day choice, then the
// draw modules' onDrawableBoundToObject and the drawable's slot 13). BFME2
// keeps the override flag and color at GameLogic +0x190/+0x194 and the time
// of day at GlobalData +0x134. Callers 0x00239F7E and 0x0023CD52.
#pragma optimize("y", on)
void Drawable::friend_bindToObject(Object *obj)
{
	m_object = obj;
	if (obj)
	{
		if (TheGameLogic->m_indicatorOverride == 1)
		{
			setIndicatorColor(TheGameLogic->m_indicatorColor);
		}
		else if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
		{
			setIndicatorColor(obj->getNightIndicatorColor());
		}
		else
		{
			setIndicatorColor(obj->getIndicatorColor());
		}

		for (DrawModule **dm = m_drawModules; *dm; ++dm)
			(*dm)->onDrawableBoundToObject();
		vslot13();
	}
}
#pragma optimize("", on)
