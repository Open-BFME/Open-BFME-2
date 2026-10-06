// cl: /DNDEBUG /MD
//
// ?rva00464D02@SlaughterHordeContain@@UAEXPAVObject@@@Z, retail 0x004806D3, 41 bytes.
// Slot 23 of SlaughterHordeContain's +0x20 interface vftable 0x00C48918
// (CitadelSlaughterHordeContain's 0x00C48B38 keeps it). Runs GarrisonContain's
// slot 23 (pinned 0x00478D0A) qualified, then sets model-condition bit 10 on
// the owner (word 0 at Object+0x10C) and notifies through the pinned
// Object::rva0028AE6D when it was clear. Named after the OpenContain slot it
// replaces, as the HordeSiegeEngineContainRiders overrides are (cl 7.1 needs
// the interface's slot name to compile it with the +0x20 subobject this);
// the name itself is not established.

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

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
private:
	unsigned int m_words[20];
};

class Object
{
public:
	void rva0028AE6D();
	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
};

static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}

struct Iface00 { virtual void f00(); const void *m_moduleData; Object *m_object; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20
{
	SLOT08(g00,g01,g02,g03,g04,g05,g06,g07)
	SLOT08(g08,g09,g10,g11,g12,g13,g14,g15)
	virtual void g16(); virtual void g17(); virtual void g18(); virtual void g19();
	virtual void g20(); virtual void g21(); virtual void g22();
	virtual void rva00464D02(Object *obj) = 0;
};
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); unsigned char m_pad[0x9EC - 0x38]; };

class GarrisonContain
	: public Iface00
	, public Iface0C
	, public Iface10
	, public Iface20
	, public Iface24
	, public Iface28
	, public Iface2C
	, public Iface30
	, public Iface34
{
public:
	virtual void rva00464D02(Object *obj);
};

class HordeGarrisonContain : public GarrisonContain
{
};

class SlaughterHordeContain : public HordeGarrisonContain
{
public:
	virtual void rva00464D02(Object *obj);
};

// ?rva00464D02@SlaughterHordeContain@@UAEXPAVObject@@@Z @0x004806D3
void SlaughterHordeContain::rva00464D02(Object *obj)
{
	GarrisonContain::rva00464D02(obj);
	setModelConditionBit(m_object, 10);
}
