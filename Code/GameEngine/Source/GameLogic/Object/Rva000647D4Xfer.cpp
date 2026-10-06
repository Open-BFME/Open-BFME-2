// cl: /MD
//
// ?xfer@Rva000647D4@@MAEXPAVXfer@@@Z, retail 0x000647E6, 27 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x007C5A5C (class of rowed dtor
// ??1Rva000647D4@@UAE@XZ in LocomotorDerivedDtors.cpp, same primary; gap
// between 0x000647D4/18 and 0x00064809/28). Body is Version1 via rowed
// 0x000053EE then base Locomotor xfer via pinned 0x00341E2D (ICF twin of
// rowed Rva00341E22 xfer 27B; IsLightCRC-plus-Version1 root). Identity is
// slot 3 plus the Version1-plus-base shape; flags copy the neighbour
// LocomotorDerivedDtors.cpp (/O1 /MD).

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

class Locomotor
{
protected:
	virtual ~Locomotor();
	virtual void xfer(Xfer *xfer);
};

class Rva000647D4_B
{
public:
	virtual void f();
};

class Rva000647D4 : public Locomotor, public Rva000647D4_B
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva000647D4::xfer(Xfer *xfer)
{
	xfer->Version1();
	Locomotor::xfer(xfer);
}
