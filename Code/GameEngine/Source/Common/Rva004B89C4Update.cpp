// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// The update slots of the module whose destructor is rowed as OathbreakersFadeAwayBehavior
// (Rva0024A797Derived.cpp; xfer 0x004B8A28 gives the bool at +0x20 and the
// float at +0x24). Address-derived names; this view emits no vtables.
//
// ?update@OathbreakersFadeAwayBehavior@@UAE?AW4UpdateSleepTime@@XZ, retail 0x004B8B41
// (205 bytes): slot 0 of the +0x10 update table 0x00859280, so `this` is the
// module +0x10. For an Object of kind 0xD7 the first update runs the rowed
// 0x004B8B0F (AI command 0x31, unselectable) and marks it done; then the
// +0x24 fraction falls by one over the module data's frame count (+0x08,
// at least 1, unsigned). Spent, it is clamped to zero, the Object whose ID it
// holds at +0x78 is told through its +0x250 interface (slot +0x7C, then
// +0x34) when its template's +0x115 byte has bit 0x20, and the Object is
// destroyed; otherwise the fraction is copied to the drawable's +0xB0. Either
// way it tail-calls the sleep helper below.
//
// ?calcSleepTime@OathbreakersFadeAwayBehavior@@QAE?AW4UpdateSleepTime@@XZ, retail 0x004B8AE1
// (46 bytes): sleep forever once the Object is effectively dead (+0x438 bit
// 0), every frame while it is of kind 0xD7, else one logic second
// (BfmeLogicFramesPerSecond frames).
#include "GameLogicObjectLookupView.h"

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum KindOfType
{
	KINDOF_D7 = 0xD7
};

extern int BfmeLogicFramesPerSecond;	// logic frames per second
extern GameLogic *TheGameLogic;

struct Rva004B89C4Template
{
	unsigned char m_pad000[0x115];
	unsigned char m_115;
};

class Rva004B89C4Listener
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12();
	virtual void rva004B8B41Notify(Object *obj);	// +0x34
};

class Rva004B89C4Owner
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual Rva004B89C4Listener *getListener();	// +0x7C
};

class Drawable
{
public:
	unsigned char m_pad000[0xB0];
	Real m_B0;
};

#include "Thing/thing.h"

class Object
{
public:
	Bool isKindOf(KindOfType t) const;
	// LINK: TU-unique name (identical inlined bytes); the Object::getDrawable copy loses to the first-in-order copy. No flags touched.
	Drawable *bfme_getDrawable_b3f60() const { return ((const Thing *)this)->getDrawable(); }
	unsigned char m_pad000[0x04];
	const Rva004B89C4Template *m_template;	// +0x04
	unsigned char m_pad008[0x78 - 0x08];
	ObjectID m_78;				// +0x78
	unsigned char m_pad07C[0x250 - 0x7C];
	Rva004B89C4Owner *m_250;		// +0x250
	unsigned char m_pad254[0x438 - 0x254];
	unsigned char m_privateStatus;		// +0x438
};

struct Rva004B89C4ModuleData
{
	unsigned char m_pad00[0x08];
	UnsignedInt m_frames;	// +0x08
};

class Rva004B89C4Primary
{
public:
	virtual ~Rva004B89C4Primary();
protected:
	const Rva004B89C4ModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
};
class Rva004B89C4Mi1
{
public:
	virtual void f1();
};
class Rva004B89C4UpdateIface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class OathbreakersFadeAwayBehavior : public Rva004B89C4Primary, public Rva004B89C4Mi1, public Rva004B89C4UpdateIface
{
public:
	virtual UpdateSleepTime update();
	UpdateSleepTime calcSleepTime();
	void rva004B8B0F(); // fade start, rowed in Rva004B8B0F.cpp
private:
	unsigned char m_pad14[0x20 - 0x14];
	Bool m_started;		// +0x20
	Real m_fraction;	// +0x24
};

UpdateSleepTime OathbreakersFadeAwayBehavior::calcSleepTime()
{
	if (m_object->m_privateStatus & 1)
		return UPDATE_SLEEP_FOREVER;
	if (m_object && m_object->isKindOf(KINDOF_D7))
		return UPDATE_SLEEP_NONE;
	return (UpdateSleepTime)BfmeLogicFramesPerSecond;
}

UpdateSleepTime OathbreakersFadeAwayBehavior::update()
{
	const Rva004B89C4ModuleData *data = m_moduleData;
	Object *obj = m_object;
	if (obj->isKindOf(KINDOF_D7))
	{
		if (!m_started)
		{
			rva004B8B0F();
			m_started = true;
		}
		UnsignedInt frames = data->m_frames;
		if (frames == 0)
			frames = 1;
		m_fraction -= 1.0f / (Real)frames;
		if (m_fraction < 0.0f)
		{
			m_fraction = 0.0f;
			Object *other = TheGameLogic->findObjectByID(obj->m_78);
			if (other && (other->m_template->m_115 & 0x20))
				other->m_250->getListener()->rva004B8B41Notify(obj);
			TheGameLogic->destroyObject(obj);
		}
		else
		{
			Drawable *draw = obj->bfme_getDrawable_b3f60();
			if (draw)
				draw->m_B0 = m_fraction;
		}
	}
	return calcSleepTime();
}
