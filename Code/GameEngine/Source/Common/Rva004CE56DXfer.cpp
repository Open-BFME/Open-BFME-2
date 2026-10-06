// cl: /MD
// ?xfer@Rva004CE56D@@QAEXPAVXfer@@@Z, retail 0x004CE56D 27B: slot-3 xfer calls rowed Xfer::Version1 then rowed BehaviorModule::xfer.
// Evidence: vslot 3 for DamageModule/DieModule/WargBehavior/RunOffMapBehavior/CollideModule plus 9 callers incl 0x004BACA4
// plus rowed callees 0x000053EE and 0x004C9C7D; class unproven so honest Rva name.
class Xfer {
public:
	void Version1();
};

class BehaviorModule {
public:
	void xfer(Xfer *xfer);
};

class Rva004CE56D {
public:
	void xfer(Xfer *xfer);
};

void Rva004CE56D::xfer(Xfer *xfer)
{
	xfer->Version1();
	((BehaviorModule *)this)->xfer(xfer);
}
