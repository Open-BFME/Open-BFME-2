// cl: /DNDEBUG /MD
//
// ?xfer@ReplaceObjectUpdate@@MAEXPAVXfer@@@Z 33B @0x004B29DE: virtual slot 3
// (offset 0x0C) of vtable 0x00856BB0 installed by the ReplaceObjectUpdate
// ctor. Base SpecialAbilityUpdate xfer via rowed 0x0044F996, IsLightCRC
// early-out via Xfer slot 0x10, then rowed Version1. No members.

class Xfer
{
public:
	Xfer();
	virtual ~Xfer();
	void Version1();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
};

class SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

class ReplaceObjectUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

void ReplaceObjectUpdate::xfer(Xfer *xfer)
{
	SpecialAbilityUpdate::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
}
