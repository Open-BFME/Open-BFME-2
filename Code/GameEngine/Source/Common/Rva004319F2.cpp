// cl: /MD
// ?Rva004319F2Update@@YAXXZ @0x004319F2 66B.
// Evidence: chain via 0x0029AA3F; TheInGameUI virtuals 0xCC and 0xD8 plus byte 0x9B4;
// rowed Rva0029AA3F 0x0029AA3F and 0x0029A9FF; callers 0x00431E5A 0x00431E95;
// prev Rva004319D4 next Rva00431A34.
#include "../../../Libraries/Include/Lib/Coord3D.h"

class Rva0029AA3F
{
public:
	void rva0029AA3F();
	void rva0029A9FF(const Coord3D *src);
};

class InGameUI
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual bool slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
private:
	char m_pad[0x9B4 - 4 - 55 * 0];
public:
	unsigned char m_9b4;
};

extern InGameUI *TheInGameUI;

void __cdecl Rva004319F2Update()
{
	if (TheInGameUI->slot51())
		TheInGameUI->slot54();
	if (TheInGameUI->m_9b4 != 0)
	{
		((Rva0029AA3F *)TheInGameUI)->rva0029AA3F();
		((Rva0029AA3F *)TheInGameUI)->rva0029A9FF(0);
	}
}
