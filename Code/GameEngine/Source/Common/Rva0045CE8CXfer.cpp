// cl: /MD
// ?xfer@Rva0045CE8C@@QAEXPAVXfer@@@Z, retail 0x0045CE8C 27B: slot-3 xfer calls rowed Xfer::Version1 then rowed Rva004CE56D xfer.
// Evidence: vslot 3 of DieModuleDerived vtables (Rva0045CE6D plus 15 siblings incl Rva004851FE/Rva00485425/Rva0048593D)
// plus caller 0x00485BF5; callees rowed 0x000053EE and 0x004CE56D; class unproven so honest Rva name.
class Xfer {
public:
	void Version1();
};

class Rva004CE56D {
public:
	void xfer(Xfer *xfer);
};

class Rva0045CE8C {
public:
	void xfer(Xfer *xfer);
};

void Rva0045CE8C::xfer(Xfer *xfer)
{
	xfer->Version1();
	((Rva004CE56D *)this)->xfer(xfer);
}
