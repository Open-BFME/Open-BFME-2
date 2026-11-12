// cl: /MD /EHsc
// ??0Rva005F69F5@@QAE@XZ, RVA 0x005F69D8, 29B. Unlock lane ctor stores vtable plus zeroes.
// Calls: none. Evidence: vtable 0x008797C4 at [this] plus zeroes at +4 +8 +0xC +0x10 +0x14 plus byte +0x18, caller 0x005F7B3D, next dtor 0x005F69F5 59B sibling of 0x005F6924.
// Slots 10 and 11 of the class's table 0x00C797C4 are __purecall and slot 0 is a byte
// getter: no virtual dtor. One pure placeholder keeps the view polymorphic.
class Rva005F69F5
{
public:
	~Rva005F69F5();
	Rva005F69F5();
	virtual void vslot10() = 0;
	// Slots 1-9 as Rva005F69F5Dtor.cpp declares them: its base table 0x00BFBCBC is
	// __purecall throughout, so both units emit the same table.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
private:
	void *m04;
	int m08;
	int m0C;
	int m10;
	int m14;
	bool m18;
};
Rva005F69F5::Rva005F69F5() : m04(0), m08(0), m0C(0), m10(0), m14(0), m18(false) {}
