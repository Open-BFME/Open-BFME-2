// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ?isValidContainerFor@RiderChangeContain@@UAE_NPAVObject@@_N1@Z, retail
// 0x0047E520, 126 bytes: slot 38 of RiderChangeContain's +0x20 table
// (0x00847834 run), so `this` is the module +0x20 (module data at -0x1C, the
// owner at -0x18). Zero Hour's RiderChangeContain::isValidContainerFor: the
// base check is the rowed SiegeEngineContain-side 0x0047BA69 (address named;
// called on the same interface pointer, capacity not checked). BFME 2 returns
// that answer unchanged for a non-allied rider; for an ally it also needs the
// +0x140 slot clear and the rider's template to match one of the eight rider
// template names in the module data (+0x1B8, 0x18 apart).
#include "ascii_string.h"

typedef bool Bool;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class ThingTemplate
{
public:
	Bool isEquivalentTo(const ThingTemplate *tmplate) const;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class Object
{
public:
	Relationship getRelationship(const Object *that) const;
	const ThingTemplate *getTemplate() const { return m_template; }
private:
	void *m_vtable;
	const ThingTemplate *m_template;	// +0x04
};

struct RiderChangeRiderInfo
{
	AsciiString m_templateName;		// +0x00
	char m_pad04[0x18 - 0x04];
};

struct RiderChangeContainModuleData
{
	char m_pad000[0x1B8];
	RiderChangeRiderInfo m_riders[8];	// +0x1B8
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

struct Iface00 { virtual void f00(); const RiderChangeContainModuleData *m_moduleData; Object *m_object; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
// The +0x20 interface; its slot-38 base check is the rowed 0x0047BA69, named
// by address on this interface.
struct Rva0047BA69
{
	bool rva0047BA69(Object *obj, int a2, int a3);
	SLOT08(g00,g01,g02,g03,g04,g05,g06,g07)
	SLOT08(g08,g09,g10,g11,g12,g13,g14,g15)
	SLOT08(g16,g17,g18,g19,g20,g21,g22,g23)
	SLOT08(g24,g25,g26,g27,g28,g29,g30,g31)
	virtual void g32(); virtual void g33(); virtual void g34(); virtual void g35();
	virtual void g36(); virtual void g37();
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);
};

class RiderChangeContain : public Iface00, public Iface0C, public Iface10, public Rva0047BA69
{
public:
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);
private:
	char m_pad24[0x140 - 0x24];
	int m_140;				// +0x140
};

bool RiderChangeContain::isValidContainerFor(Object *rider, bool checkCapacity, bool testPath)
{
	//Don't check capacity because our rider will kick the other rider out!
	// The base takes the caller's test-path argument word as is (rowed with int parameters).
	bool valid = rva0047BA69(rider, 0, *(const int *)&testPath);
	if (m_object->getRelationship(rider) != ALLIES)
		return valid;
	if (valid && m_140 == 0)
	{
		const RiderChangeContainModuleData *data = m_moduleData;
		for (int i = 0; i < 8; i++)
		{
			if (data->m_riders[i].m_templateName.isEmpty() == true)
				continue;
			const ThingTemplate *thing = TheThingFactory->findTemplate(data->m_riders[i].m_templateName);
			if (thing && thing->isEquivalentTo(rider->getTemplate()))
			{
				//We found a valid rider, so return true.
				return true;
			}
		}
	}
	return false;
}
