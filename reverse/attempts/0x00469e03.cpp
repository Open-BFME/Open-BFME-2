// ?onRemoving@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.98 date=2026-10-08
// cl: /DNDEBUG /MD
//
// HordeContain overrides in the contain interface its pinned ctor 0x0046F543
// installs at +0x20 (vtable 0x00C44EC8; the slots below 0x00468000 there are
// OpenContain's and TransportContain's). Compiled with the +0x20 subobject
// this: [ecx-0x18] is the owning Object at +0x08. Names are by address.
//
// Slots 11, 26 and 45 hand the same slot of the contain interface (Object
// +0x250) of the Object our Object's +0x274 names, when there is one; slot 11
// answers true and slot 45 false without it. Slots 30 and 31 (one folded body)
// answer the +0x11C interface of this object, null-checked as cl converts.

class Object;

template <int N> class Rva00469626Slots : public Rva00469626Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00469626Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva2225E0Filter;
class Rva00469626HordeIface : public Rva00469626Slots<96>
{
public:
 virtual int rva0046D3FC(Rva2225E0Filter *filter) = 0;
};

class ContainModuleInterface : public Rva00469626Slots<11>
{
public:
	virtual bool rva00469626() = 0;
	virtual void gap12() = 0; virtual void gap13() = 0; virtual void gap14() = 0;
	virtual void gap15() = 0; virtual void gap16() = 0; virtual void gap17() = 0;
	virtual void gap18() = 0; virtual void gap19() = 0; virtual void gap20() = 0;
	virtual void gap21() = 0; virtual void gap22() = 0; virtual void onRemoving(Object *object) = 0;
	virtual void gap24() = 0; virtual void gap25() = 0;
	virtual void rva004697A8(int a1, int a2, int a3) = 0;
	virtual void gap27() = 0; virtual void gap28() = 0; virtual void gap29() = 0;
	virtual Rva00469626HordeIface *rva0046F7B9() = 0;
	virtual Rva00469626HordeIface *rva0046F7B9Slot31() = 0;
	virtual void gap32() = 0; virtual void gap33() = 0; virtual void gap34() = 0;
	virtual void gap35() = 0; virtual void gap36() = 0; virtual void gap37() = 0;
	virtual void gap38() = 0; virtual void gap39() = 0; virtual void gap40() = 0;
	virtual void gap41() = 0; virtual void gap42() = 0; virtual void gap43() = 0;
	virtual void gap44() = 0;
	virtual bool rva00469602() = 0;
};

class Drawable
{
public:
 void rva00272945(int value);
 void rva00272BE7();
 bool rva00469E03Flag() const { return m_43C; }
 unsigned char m_pad000[0x43C];
 unsigned char m_43C;
};
class Thing
{
public:
 Drawable *getDrawable() const;
};
class Rva00469E03Template
{
public:
 unsigned char m_pad000[0x109];
 unsigned char m_109;
 unsigned char m_pad10A[0x113 - 0x10A];
 unsigned char m_113;
};
class BodyModule : public Rva00469626Slots<13>
{
public:
 virtual void rva00469E03Slot13(int value) = 0;
};
class AIUpdateInterface : public Rva00469626Slots<142>
{
public:
 virtual void slot142(int value) = 0;
};
class Rva00469E03Bits
{
public:
 unsigned int test(int bit) const { return m_words[bit >> 5] & (1U << (bit & 31)); }
 void clear(int bit) { m_words[bit >> 5] &= ~(1U << (bit & 31)); }
 const unsigned int *word(int index) const { return m_words + index; }
private:
 unsigned int m_words[20];
};
enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
class Object : public Thing
{
public:
 void setStatus(ObjectStatusTypes status, bool set);
 void rva0028AE6D();
 void rva0029130C(int mode);
 Object *rva002931F5(bool flag);
 unsigned char m_pad000[4];
 const Rva00469E03Template *m_template;
 unsigned char m_pad008[0x10C - 8];
 Rva00469E03Bits m_conditions;
 unsigned char m_pad15C[0x250 - 0x15C];
 ContainModuleInterface *m_contain; // +0x250
 BodyModule *m_body;
 AIUpdateInterface *m_ai;
 unsigned char m_pad25C[0x274 - 0x25C];
 Object *m_274; // +0x274
};
class ModuleData
{
public:
 unsigned char m_pad000[0x234];
 int m_234;
};
class GlobalData
{
public:
 unsigned char m_pad000[0x9A6];
 bool m_9A6;
};
extern GlobalData *TheWritableGlobalData;

class UpdateModuleView
{
public:
	virtual ~UpdateModuleView();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

class OpenContain : public UpdateModuleView, public ContainModuleInterface
{
public:
 virtual void onRemoving(Object *object);
private:
 unsigned char m_pad24[0x11C - 0x24];
};
class TransportContainView : public OpenContain {};

class HordeContain : public TransportContainView, public Rva00469626HordeIface
{
public:
 virtual void onRemoving(Object *object);
	virtual bool rva00469626();
	virtual void rva004697A8(int a1, int a2, int a3);
	virtual Rva00469626HordeIface *rva0046F7B9();
	virtual bool rva00469602();
};

// ?rva00469626@HordeContain@@UAE_NXZ @0x00469626: slot 11.
bool HordeContain::rva00469626()
{
	Object *other = m_object->m_274;
	if (other)
	{
		ContainModuleInterface *contain = other->m_contain;
		if (contain)
			return contain->rva00469626();
	}
	return true;
}

// ?rva004697A8@HordeContain@@UAEXHHH@Z @0x004697A8: slot 26 (argument types not
// established).
void HordeContain::rva004697A8(int a1, int a2, int a3)
{
	Object *me = m_object;
	if (me)
	{
		Object *other = me->m_274;
		if (other)
		{
			ContainModuleInterface *contain = other->m_contain;
			if (contain)
				contain->rva004697A8(a1, a2, a3);
		}
	}
}

// ?rva0046F7B9@HordeContain@@UAEPAVRva00469626HordeIface@@XZ @0x0046F7B9: slots
// 30 and 31.
Rva00469626HordeIface *HordeContain::rva0046F7B9()
{
	return this;
}

// ?rva00469602@HordeContain@@UAE_NXZ @0x00469602: slot 45.
bool HordeContain::rva00469602()
{
	Object *other = m_object->m_274;
	if (other)
	{
		ContainModuleInterface *contain = other->m_contain;
		if (contain)
			return contain->rva00469602();
	}
	return false;
}

// ?onRemoving@HordeContain@@UAEXPAVObject@@@Z @0x00469E03: slot 23 of
// the +0x20 interface in vtables 0x00844EC8 and 0x008458D8. The direct
// OpenContain::onRemoving base call, the ctor-installed HordeContain vtable,
// and WB's corresponding base-call/condition-clear body establish identity.
// All offsets and masks below are retail reads; unnamed members retain them.
void HordeContain::onRemoving(Object *object)
{
 OpenContain::onRemoving(object);
 if ((object->m_template->m_109 & 8) || (object->m_template->m_113 & 0x24))
  object->setStatus(static_cast<ObjectStatusTypes>(0x26), false);
 const unsigned int *conditions = object->m_conditions.word(7);
 if (*conditions & 0x40000000U)
 {
  object->m_conditions.clear(254);
  object->rva0028AE6D();
 }
 if (*conditions & 0x80000000U)
 {
  object->m_conditions.clear(255);
  object->rva0028AE6D();
 }
 object->m_body->rva00469E03Slot13(5);
 object->rva0029130C(2);
 if (m_moduleData && m_moduleData->m_234 != -1)
 {
  AIUpdateInterface *ai = object->m_ai;
  if (ai) ai->slot142(0);
 }
 if (m_object)
 {
  Drawable *ownerDraw = m_object->getDrawable();
  if (ownerDraw && ownerDraw->m_43C)
  {
   if (TheWritableGlobalData->m_9A6)
    ownerDraw->rva00272945(rva0046D3FC(0));
   else
   {
    Drawable *draw = object->getDrawable();
    if (draw && static_cast<unsigned char>(draw->rva00469E03Flag()) == 0)
    {
     Object *related = object->rva002931F5(false);
     if (related && related->getDrawable() && related->getDrawable()->m_43C)
      return;
     draw->rva00272BE7();
    }
   }
  }
 }
}
