// cl: /MD /EHsc
// ??0Rva005F6941@@QAE@XZ, RVA 0x005F6924, 29B. Unlock lane ctor stores vtable plus zeroes.
// Calls: none. Evidence: vtable 0x00879790 at [this] plus zeroes at +4 +8 +0xC +0x10 +0x14 plus byte +0x18, caller 0x005F7776, next dtor 0x005F6941 59B.
class Rva005F6941
{
public:
	virtual unsigned char rva004C9990() const;	// retail slot 0; the destructor is not virtual
	// Slots 1-9 as Rva005F6941Dtor.cpp declares them: its base table 0x00BFBCBC is
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
	~Rva005F6941();
	Rva005F6941();
private:
	void *m04;
	int m08;
	int m0C;
	int m10;
	int m14;
	bool m18;
};
Rva005F6941::Rva005F6941() : m04(0), m08(0), m0C(0), m10(0), m14(0), m18(false) {}
