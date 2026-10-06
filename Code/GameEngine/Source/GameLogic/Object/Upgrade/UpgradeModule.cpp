// cl: /O1 /MD
// UpgradeModule.cpp: bodies retail links from this TU (tu_map approved), folded
// from three split units with these exact flags: UpgradeModule::xfer and the
// two mask checks at 0x004CE2B0/0x004CE342 that directly precede the
// UpgradeMux xfer (0x004CE397) in retail. The mask helper views are shared.
//
// ?xfer@UpgradeModule@@MAEXPAVXfer@@@Z, retail 0x004CE3F9, 37 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00842768 (class of rowed UpgradeModule
// ctor 0x00460AEC). Version1 via rowed 0x000053EE then base BehaviorModule
// xfer via rowed 0x004C9C7D then UpgradeMux member at +0x10 via just-rowed
// 0x004CE397. Donor ZH UpgradeModule.cpp xfer verbatim (version plus base
// plus upgradeMuxXfer). Called by 6 derived xfers.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class UpgradeModule;

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0xC];
};

class UpgradeMux
{
	friend class UpgradeModule;
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class UpgradeModule : public BehaviorModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	UpgradeMux m_mux10;
};

void UpgradeModule::xfer(Xfer *xfer)
{
	xfer->Version1();
	BehaviorModule::xfer(xfer);
	m_mux10.UpgradeMux::upgradeMuxXfer(xfer);
}

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();
private:
	char m_pad[0x80];
};

class Rva00406F9C
{
public:
	bool rva00406F9C(const void *other);
	unsigned m_data[32];
};

// ?rva004CE2B0@Rva004CE2B0@@QAE_NPAVRva00406F9C@@@Z @0x004CE2B0 146B: dual mask check.
// Clears two 0x80 buffers via rowed 0x001EAE6F, fills via virtual +0x2C,
// returns false if buf80 all zero or byte at +4 set, then dispatches on
// virtual +0x38 with mask as this and buf100 as other via rowed 0x002AA292
// or 0x00406F9C (false if true), then dispatches on virtual +0x34 with mask
// as this and buf80 as other returning result. Slot 2 of many vtables.
// Chain from 0x00406F9C. Sibling of 0x004B4130.
class Rva002AA292
{
public:
	bool rva002AA292(const int *mask) const;
private:
	int m_bits[32];
};

class Rva004CE2B0
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11(void *a, void *b);
	virtual void v12();
	virtual bool v13();
	virtual bool v14();
	bool rva004CE2B0(Rva00406F9C *mask);
private:
	bool m_b04;
};

bool Rva004CE2B0::rva004CE2B0(Rva00406F9C *mask)
{
	Rva00406F9C buf100;
	Rva00406F9C buf80;
	((Rva001EAE6FHelper *)&buf80)->clear80();
	((Rva001EAE6FHelper *)&buf100)->clear80();
	v11(&buf80, &buf100);
	for (unsigned i = 0; i < 32; ++i) {
		if (buf80.m_data[i] != 0)
			goto haveBits;
	}
	return false;
haveBits:
	if (m_b04)
		return false;
	bool disp1;
	if (v14())
		disp1 = ((Rva002AA292 *)mask)->rva002AA292((const int *)&buf100);
	else
		disp1 = mask->rva00406F9C(&buf100);
	if (disp1)
		return false;
	if (v13())
		return ((Rva002AA292 *)mask)->rva002AA292((const int *)&buf80);
	return mask->rva00406F9C(&buf80);
}

// ?rva004CE342@Rva004CE342@@QAE_NPAVRva00406F9C@@@Z @0x004CE342 85B: consume-once mask check.
// Clears two 0x80 buffers via rowed 0x001EAE6F, fills via virtual +0x2C,
// returns false if buf80 vs mask via rowed 0x00406F9C is false or byte at
// +4 is zero, else clears byte and returns true. Slot 3 of many Update
// vtables. Chain from 0x00406F9C. Sibling of 0x004B4130 0x004CE2B0.
class Rva004CE342
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11(void *a, void *b);
	bool rva004CE342(Rva00406F9C *mask);
private:
	bool m_b04;
};

bool Rva004CE342::rva004CE342(Rva00406F9C *mask)
{
	Rva00406F9C buf100;
	Rva00406F9C buf80;
	((Rva001EAE6FHelper *)&buf80)->clear80();
	((Rva001EAE6FHelper *)&buf100)->clear80();
	v11(&buf80, &buf100);
	if (!buf80.rva00406F9C(mask))
		return false;
	if (m_b04) {
		m_b04 = false;
		return true;
	}
	return false;
}
