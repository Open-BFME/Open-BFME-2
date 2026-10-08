// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ProductionQueueHordeContain primary slots 29 and 30 (vtable 0x00C49040),
// over the HordeGarrisonContain slot-29/30 bases (0x00479B7F rowed,
// 0x00479ADA pinned by address; HordeGarrisonContain 0x00C46570 and
// TunnelContain 0x00C47740 carry the same two). Both then hand the Object's ID
// and the Object to the class's 0x004813B3 (pinned by address) when the
// answer of an Object's +0x250 module (its slot 31 result's slot 61) holds:
//   slot 29, retail 0x004814D1 (67 bytes): the Object's own module, asked
//            only when its template has kindOf bit 0x115:0x20.
//   slot 30, retail 0x00481439 (67 bytes): the module of the Object at the
//            argument's +0x274, whose ID is passed.
// Named by the bases' addresses.
#include "ascii_string.h"

class BfmeTab1026
{
public:
	char bfmeHas1026(int a, int b);
};

class Object;
class Player;
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

struct Rva0048130E
{
	BfmeTab1026 m_tab;
	AsciiString m_str;
};

class ProductionQueueHordeContainModuleData
{
public:
	unsigned char m_pad[0xD4];
	Rva0048130E *m_begin;
	Rva0048130E *m_end;
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

class Rva0028BC58Ret
{
public:
	virtual void s00();
	virtual void s01();
	virtual int s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08(void *p1, int p2, int p3, int p4, int p5, const AsciiString *p6, int p7);
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14(int a, int b);
};
template <int N> class Rva004814D1Slots : public Rva004814D1Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004814D1Slots<0>
{
};
class Rva004814D1Answer : public Rva004814D1Slots<61>
{
public:
	virtual bool rvaSlot61() = 0;
};
class Rva004814D1Module : public Rva004814D1Slots<31>
{
public:
	virtual Rva004814D1Answer *rvaSlot31() = 0;
};
enum ObjectID
{
	INVALID_ID = 0
};
class ThingTemplate
{
public:
	bool testKindOf115Bit5() const { return (m_kindOf115 & 0x20) != 0; }
private:
	unsigned char m_pad000[0x115];
	unsigned char m_kindOf115;	// +0x115
};
class Object
{
public:
	void *rva0028BC58(int a);
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad008[0x74 - 0x08];
	ObjectID m_id;			// +0x74
	unsigned char m_pad078[0x250 - 0x78];
	Rva004814D1Module *m_250;	// +0x250
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_274;			// +0x274
};
class ModuleData;
class HordeGarrisonContain
{
public:
	virtual ~HordeGarrisonContain();
	virtual void rva00479B7F(Object *obj);
	virtual void rva00479ADA(Object *obj);
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class ProductionQueueHordeContain : public HordeGarrisonContain
{
public:
	virtual void rva00479B7F(Object *obj);
	virtual void rva00479ADA(Object *obj);
	void CreateTemplate(ObjectID id, Object *obj);
};
void ProductionQueueHordeContain::rva00479B7F(Object *obj)
{
	HordeGarrisonContain::rva00479B7F(obj);
	if (!obj->m_template->testKindOf115Bit5() || obj->m_250->rvaSlot31()->rvaSlot61())
		CreateTemplate(obj->m_id, obj);
}
void ProductionQueueHordeContain::rva00479ADA(Object *obj)
{
	HordeGarrisonContain::rva00479ADA(obj);
	if (obj->m_274->m_250->rvaSlot31()->rvaSlot61())
		CreateTemplate(obj->m_274->m_id, obj);
}

void ProductionQueueHordeContain::CreateTemplate(ObjectID id, Object *obj)
{
	void *ret = m_object->rva0028BC58(0);
	if (!ret)
		return;
	Rva0028BC58Ret *r = (Rva0028BC58Ret *)ret;
	const ProductionQueueHordeContainModuleData *md = (const ProductionQueueHordeContainModuleData *)m_moduleData;
	int slot2 = r->s02();
	for (Rva0048130E *p = md->m_begin; p != md->m_end; ++p)
	{
		if (((Rva2225E0Filter *)&p->m_tab)->accepts(obj, (Player *)0))
		{
			void *thing = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&p->m_str);
			r->s08(thing, -1, slot2, -1, 0, &AsciiString::TheEmptyString, 0);
			r->s14(slot2, id);
			return;
		}
	}
}
