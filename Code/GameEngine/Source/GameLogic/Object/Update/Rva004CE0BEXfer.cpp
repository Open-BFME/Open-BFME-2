// cl: /MD
// ?xfer@Rva004CE0BE@@MAEXPAVXfer@@@Z @0x004CE0BE 27B: xfer Version1 plus base.
// Version1 via rowed 0x53EE then base SpecialAbilityUpdate xfer via rowed
// 0x0044F996. Slot 3 of many Update vtables. No IsLightCRC early-out.
// Chain lane. Sibling of Rva004B4CDF xfer.
class Xfer
{
public:
	void Version1();
};

class SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

class Rva004CE0BE : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva004CE0BE::xfer(Xfer *xfer)
{
	xfer->Version1();
	SpecialAbilityUpdate::xfer(xfer);
}
