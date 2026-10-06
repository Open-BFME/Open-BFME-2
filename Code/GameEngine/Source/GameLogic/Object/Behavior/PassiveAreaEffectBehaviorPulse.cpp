// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// PassiveAreaEffectBehavior's per-object pulse virtuals (primary vftable
// 0x00C4A448, slot-2 name getter "PassiveAreaEffectBehavior", installed by
// the rowed ctor 0x00484A67; slot 3 is the rowed xfer). Names are address
// names: the class and slots are proven, the method identities are not.
//
// ?rva004848E6@PassiveAreaEffectBehavior@@UAEXPAVObject@@@Z, retail 0x004848E6, 40 bytes.
// Slot 14: for a live object (Object+0x438 bit 0 clear) run slots 15 and 16.
//
// ?rva0048491F@PassiveAreaEffectBehavior@@UAEXPAVObject@@@Z, retail 0x0048491F, 233 bytes.
// Slot 15: the heal pulse. Skips an object the rowed Object::rva0028C264
// gate (delay 4) refuses; with a positive module-data rate at +0x0C and a
// body (+0x254) below its maximum (body slots 4 and 6), optionally gated by
// the body's slot-17 frame plus the delay at +0x10 against TheGameLogic's
// frame when the bool at +0x28 is set, heals max * rate / LOGICFRAMES (times
// the delay when set) through the rowed Object::rva0028FEA7 with this
// module's object as the source, then plays the FXList at +0x34.
//
// ?rva00484A08@PassiveAreaEffectBehavior@@UAEXPAVObject@@@Z, retail 0x00484A08, 95 bytes.
// Slot 16: the attribute pulse. Runs the pinned Object::rva0028EA91(-1) on
// every name of the module data's AsciiString vector at +0x14, then gives the
// object's AttributeModifierPoolUpdate (rowed finder 0x0028BDD7) the entry at
// +0x2C until the current frame plus the delay at +0x10 (rowed 0x00403415),
// then plays the FXList at +0x30.

#include "ascii_string.h"

class Object;
class FXList;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	char m_pad00[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;
extern const int g_009BA4E4;

class BodyModule
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual float getHealth() const;
	virtual void s05();
	virtual float getMaxHealth() const;
	virtual void s07(); virtual void s08(); virtual void s09(); virtual void s10();
	virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16();
	virtual unsigned int getLastDamageFrame() const;
};

class AttributeModifierPoolUpdate
{
public:
	void rva00403415(int *entry, int untilFrame);
};

class PassiveAreaEffectBehavior;

class Object
{
	friend class PassiveAreaEffectBehavior;
public:
	bool rva0028C264(int *out, int frames);
	bool rva0028FEA7(float amount, const Object *source, unsigned int delay);
	bool rva0028EA91(const AsciiString &name, int value);
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	BodyModule *getBodyModule() const { return m_body; }
private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;

	char m_pad00[0x254];
	BodyModule *m_body;
	char m_pad258[0x438 - 0x258];
	unsigned char m_438;
};

struct PassiveAreaEffectBehaviorModuleData
{
	char m_pad00[0x0C];
	float m_0C;
	unsigned int m_10;
	const AsciiString *m_14Begin;
	const AsciiString *m_14End;
	char m_pad1C[0x28 - 0x1C];
	bool m_28;
	int m_2C;
	const FXList *m_30;
	const FXList *m_34;
};

class UpdateModule
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
protected:
	const PassiveAreaEffectBehaviorModuleData *m_moduleData;
	Object *m_object;
};

class PassiveAreaEffectBehavior : public UpdateModule
{
public:
	virtual void rva004848E6(Object *obj);
	virtual void rva0048491F(Object *obj);
	virtual void rva00484A08(Object *obj);
};

// ?rva004848E6@PassiveAreaEffectBehavior@@UAEXPAVObject@@@Z @0x004848E6
void PassiveAreaEffectBehavior::rva004848E6(Object *obj)
{
	if (obj && !obj->isEffectivelyDead())
	{
		rva0048491F(obj);
		rva00484A08(obj);
	}
}

// ?rva0048491F@PassiveAreaEffectBehavior@@UAEXPAVObject@@@Z @0x0048491F
void PassiveAreaEffectBehavior::rva0048491F(Object *obj)
{
	if (obj == 0)
		return;

	int gate;
	if (obj->rva0028C264(&gate, 4))
		return;

	const PassiveAreaEffectBehaviorModuleData *d = m_moduleData;
	if (d->m_0C > 0.0f)
	{
		BodyModule *body = obj->getBodyModule();
		if (body && body->getHealth() != body->getMaxHealth())
		{
			if (d->m_28)
			{
				unsigned int now = TheGameLogic->getFrame();
				if (body->getLastDamageFrame() + d->m_10 > now)
					return;
			}

			float rate = d->m_0C;
			float amount = body->getMaxHealth() * (rate / g_009BA4E4);
			if (d->m_10)
				amount *= d->m_10;
			obj->rva0028FEA7(amount, m_object, d->m_10);

			if (d->m_34)
				FXList::doFXObj(d->m_34, obj, 0);
		}
	}
}

// ?rva00484A08@PassiveAreaEffectBehavior@@UAEXPAVObject@@@Z @0x00484A08
void PassiveAreaEffectBehavior::rva00484A08(Object *obj)
{
	if (obj == 0)
		return;

	const PassiveAreaEffectBehaviorModuleData *d = m_moduleData;
	for (const AsciiString *it = d->m_14Begin; it != d->m_14End; ++it)
		obj->rva0028EA91(*it, -1);

	AttributeModifierPoolUpdate *pool = obj->findAttributeModifierPoolUpdate();
	if (pool)
	{
		pool->rva00403415((int *)&d->m_2C, TheGameLogic->getFrame() + d->m_10);
		if (d->m_30)
			FXList::doFXObj(d->m_30, obj, 0);
	}
}
