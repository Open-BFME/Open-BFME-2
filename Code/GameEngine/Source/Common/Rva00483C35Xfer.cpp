// cl: /O1 /MD
//
// ?xfer@Rva00483C35@@MAEXPAVXfer@@@Z, retail 0x00483E0A, 27 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x00849E4C (class of rowed dtor
// ??1Rva00483C35@@UAE@XZ in Rva0045D39EDerived.cpp): Xfer Version1 via rowed
// 0x53EE then SlowDeathBehavior base xfer via rowed 0x45D3CB. No members
// (cf. Rva00499F45Xfer minimal shape). Identity is slot 3 plus the base
// SlowDeathBehavior xfer call; class name stays honest Rva address name.

class Xfer
{
public:
	void Version1();
};

class SlowDeathBehavior
{
protected:
	virtual void xfer(Xfer *xfer);
};

class Rva00483C35 : public SlowDeathBehavior
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva00483C35::xfer(Xfer *xfer)
{
	xfer->Version1();
	SlowDeathBehavior::xfer(xfer);
}
