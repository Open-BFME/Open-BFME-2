// cl: /MD
//
// ?xfer@Rva004C8A95@@MAEXPAVXfer@@@Z, retail 0x004C8A95, 27 bytes. Virtual
// slot 3 (offset 0x0C) of many SpecialPower vtables (e.g. 0x0085C51C
// Invisibility, 0x0085C63C CashHack, 0x0085C7EC Defector): Xfer Version1 via
// rowed 0x53EE then Rva00493009 base xfer via rowed 0x00493009. No members.
// Identity is slot 3 plus the base xfer call; class name stays honest Rva.

class Xfer
{
public:
	void Version1();
};

class Rva00493009
{
protected:
	virtual void xfer(Xfer *xfer);
};

class Rva004C8A95 : public Rva00493009
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva004C8A95::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva00493009::xfer(xfer);
}
