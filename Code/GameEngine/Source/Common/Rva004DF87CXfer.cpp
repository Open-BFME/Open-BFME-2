// cl: /MD
// ?xfer@Rva004DF87C@@QAEXPAVXfer@@@Z, retail 0x004DF87C 27B: slot-3 xfer calls rowed Xfer::Version1 then rowed Rva004DF81B xfer.
// Evidence: vslot 3 of 0x007FBD98 plus 0x007FBDF0 plus 0x007FBE48 plus 0x00861588
// plus rowed callees 0x000053EE and 0x004DF81B; class unproven so honest Rva name.
class Xfer {
public:
	void Version1();
};

class Rva004DF81B {
public:
	void xfer(Xfer *xfer);
};

class Rva004DF87C {
public:
	void xfer(Xfer *xfer);
};

void Rva004DF87C::xfer(Xfer *xfer)
{
	xfer->Version1();
	((Rva004DF81B *)this)->xfer(xfer);
}
