// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva005DABD5@Rva005DAAB6@@QAE_N_N@Z @0x005DABD5 94B evidence: vslot 15 of 008765A8 class Rva005DAAB6 via dtor row; layout from Rva0055AED6Xfer base+derived m_2C/m_30/m_3C; callees rva002D06CA findObjectByID rowed plus global slot14 virtual; globals VA 0xDFF000 0xDFE78C 0xE027B8

extern class ThingFactory *TheThingFactory;
extern class GameLogic *TheGameLogic;
extern class Rva00A027B8 *g_00A027B8;
// g_00A027B8: matched references place it at VA 0xe027b8 (zero-filled .bss).
class Rva00A027B8 * g_00A027B8;

enum ObjectID
{
	INVALID_ID = 0
};

#include "ascii_string.h"

class Object;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *s);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class Rva00A027B8
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual int slot14(Object *a1, void *a2, void *a3, float a4, bool a5);
};

class Rva0055B0CC
{
	friend class Rva005DAAB6;
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void Slot6(void *arg1, bool arg2);
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void Rva0055AED6(void *xfer, void *arg2);
private:
	float m_04;
	ObjectID m_08;
	AsciiString m_0C;
	unsigned int m_10;
	int m_pad14;
	float m_18;
	int m_pad1C;
	bool m_20;
	bool m_21;
	ObjectID m_24;
	bool m_28;
};

class Rva005DAAB6 : public Rva0055B0CC
{
public:
	bool rva005DABD5(bool arg);
private:
	bool m_2C;
	struct Coord3D
	{
		float x;
		float y;
		float z;
	};
	Coord3D m_30;
	float m_3C;
};

bool Rva005DAAB6::rva005DABD5(bool arg)
{
	void *p1 = ((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)&m_0C);
	Object *o2 = TheGameLogic->findObjectByID(m_08);
	if (p1 == 0 || o2 == 0)
		return false;
	float f = m_3C;
	int r = g_00A027B8->slot14(o2, p1, &m_30, f, arg);
	if (r == 0)
		return false;
	m_24 = *(ObjectID *)((char *)r + 0x74);
	return true;
}
