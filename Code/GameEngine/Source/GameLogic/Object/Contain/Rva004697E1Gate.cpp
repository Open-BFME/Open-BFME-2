// cl: /O1 /DNDEBUG /MD /arch:SSE /EHsc
//
// Retail 0x004697E1, 59 bytes, RET.
// Virtual slot 33 on this (argument 0), a direct call to an unnamed member
// (0x004783D7, address-derived pin), then a comparison between this +0x2C5 and
// the owner's +0x1D8 byte; on mismatch it tail-jumps slot 24 of the subobject at +0x11C.
// Class and owner names are address-derived; the slots are shims.
class Rva004697E1Owner
{
public:
	char unknown00[0x1D8];
	bool flag;
};
class Rva004697E1Tail
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
};
class Rva004697E1Contain
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
	virtual void slot33(int value);
	void rva004697E1();
	void rva004783D7();
private:
	Rva004697E1Owner *owner;
	char unknown08[0x11C-0x08];
	Rva004697E1Tail tail;
	char unknown120[0x2C5-0x120];
	bool flag;
};
void Rva004697E1Contain::rva004697E1()
{
	slot33(0);
	rva004783D7();
	unsigned char zero = 0;
	int mine = flag;
	int ownerClear = owner->flag == zero;
	if (mine != ownerClear)
		tail.slot24();
}
