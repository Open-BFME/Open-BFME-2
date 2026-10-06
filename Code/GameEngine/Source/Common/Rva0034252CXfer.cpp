// cl: /MD
// ?xfer@Rva0034252C@@MAEXPAVXfer@@@Z @ 0x0034252C 27B: chain xfer calling Version1
// via rowed 0x000053EE then base ?xfer@Rva00340D1F via rowed 0x00340CB0. No
// members. Evidence: rowed Version1 plus rowed base xfer 0x00340CB0.
class Xfer
{
public:
	void Version1();
};

class Rva00340D1F
{
protected:
	virtual void xfer(Xfer *xfer);
};

class Rva0034252C : public Rva00340D1F
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva0034252C::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva00340D1F::xfer(xfer);
}
