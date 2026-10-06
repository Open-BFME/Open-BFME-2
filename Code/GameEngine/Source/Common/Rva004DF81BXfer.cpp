// cl: /MD
// ?xfer@Rva004DF81B@@QAEXPAVXfer@@@Z, retail 0x004DF81B 27B: slot-3 xfer calls rowed Xfer::Version1 then rowed UpdateModule::xfer.
// Evidence: vslot 3 of 0x007FBCF0 plus 0x0084867C plus 0x0084AF64 plus 0x0084B2F8 plus 0x0084BF90
// plus callers 0x004DE913 0x004DF777 0x004DF88E plus rowed callees 0x000053EE and 0x0044DF9F;
// class unproven so honest Rva name.
class Xfer {
public:
	void Version1();
};

class UpdateModule {
public:
	void xfer(Xfer *xfer);
};

class Rva004DF81B {
public:
	void xfer(Xfer *xfer);
};

void Rva004DF81B::xfer(Xfer *xfer)
{
	xfer->Version1();
	((UpdateModule *)this)->xfer(xfer);
}
