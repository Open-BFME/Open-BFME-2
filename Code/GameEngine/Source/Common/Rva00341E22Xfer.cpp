// cl: /MD
//
// ?xfer@Rva00341E22@@MAEXPAVXfer@@@Z, retail 0x00341E2D, 27 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x00811798 (class of rowed dtor
// ??1Rva00341E22@@UAE@XZ in Rva0049B47CDerived.cpp, same primary; prev row
// 0x00341E22/11 abuts); ICF-twin slot 3 of GODupBase vtable 0x00807D2C.
// Body is IsLightCRC early-out via Xfer slot 0x10 then Version1 via rowed
// 0x000053EE; no members, no base call (root versioning only). Identity is
// slot 3 plus Xfer* arg plus the IsLightCRC-plus-Version1 shape proven by
// ShipSlowDeathBehavior::xfer 0x0045ED0E precedent. Flags copy the neighbour
// Rva0049B47CDerived.cpp (/O1 /MD).

class Xfer
{
public:
	virtual ~Xfer();
	void Version1();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
};

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();
};

class Rva00341E22 : public Rva0049B47C
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva00341E22::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
}
