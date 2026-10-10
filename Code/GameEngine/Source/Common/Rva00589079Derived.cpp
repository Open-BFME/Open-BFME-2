// cl: /MD
//
// Opaque five-vptr MI destructor tail-calling the pinned 0x24A797 base.
// Retail 0x00589079 (39B) stores four vptrs plus the const 0xC70108 at +0x24,
// then tail-jumps to the 0x24A797 middle. Same model as the landed Rva00494A97
// body (which tail-calls this one); the fifth slot carries a const, not a
// zero. Identity unproven (opaque Rva name); the shape (vptr stores plus a
// tail-jump into a rowed/pinned MI dtor) is the dtor evidence.

class Xfer;

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	char m_pad04[8];
};

class Rva00589079_S1
{
public:
	virtual void f1();
};

class Rva00589079_S2
{
public:
	virtual void f2() = 0;

private:
	char m_pad04[12];
};

class Rva00589079_S3
{
public:
	virtual void f3();
};

class Rva00589079_S4
{
public:
	virtual void f4();
};

class Rva00589079 : public UpdateModule, public Rva00589079_S1, public Rva00589079_S2, public Rva00589079_S3, public Rva00589079_S4
{
public:
	virtual ~Rva00589079()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00589079_Anchor(Rva00589079 *p)
{
	p->Rva00589079::~Rva00589079();
}

class Rva00481F82_S1
{
public:
	virtual void f1();
};

class Rva00481F82_S2
{
public:
	virtual void f2();

private:
	char m_pad04[12];
};

class Rva00481F82_S3
{
public:
	virtual void f3();
};

class Rva00481F82_S4
{
public:
	virtual void f4();
};

class Rva00481F82 : public UpdateModule, public Rva00481F82_S1, public Rva00481F82_S2, public Rva00481F82_S3, public Rva00481F82_S4
{
public:
	virtual ~Rva00481F82()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00481F82_Anchor(Rva00481F82 *p)
{
	p->Rva00481F82::~Rva00481F82();
}

class Rva00482E96_S1
{
public:
	virtual void f1();
};

class Rva00482E96_S2
{
public:
	virtual void f2();

private:
	char m_pad04[12];
};

class Rva00482E96_S3
{
public:
	virtual void f3();

private:
	char m_pad18[4];
};

class Rva00482E96_S4
{
public:
	virtual void f4();
};

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
class Thing;
class ModuleData;
class Object;

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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer *xfer);
};

class BehaviorModule : public ObjectModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer *xfer);
};


class Rva00482E96;

class UpgradeMux
{
	friend class Rva00482E96;
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);
};

class Member2C
{
public:
	virtual void xfer(Xfer *xfer);
};

class Rva00482E96 : public UpdateModule, public Rva00482E96_S1, public Rva00482E96_S2, public Rva00482E96_S3, public Rva00482E96_S4
{
public:
	virtual ~Rva00482E96()
	{
	}
	virtual void rva00482C39();
	virtual void s02();
protected:
	virtual void xfer(Xfer *xfer);
private:
	Member2C m_m2C;
	char m_pad30[0x78];
	int m_iA8;
};

template <typename T> class StringBase
{
	friend class Rva00482E96;
	void validate() const;
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00482E96_Anchor(Rva00482E96 *p)
{
	p->Rva00482E96::~Rva00482E96();
}

// ?rva00482C39@Rva00482E96@@UAEXXZ retail 0x00482C39 17 bytes.
// Slot 1 (offset 0x4) of vtable 0x008497B4 (class of ??1Rva00482E96@@UAE@XZ).
// Validates wide strings at +0 and +0x20, second as tail-jmp to rowed
// ?validate@?$StringBase@G@@ABEXXZ at 0x000B3FD0. No other callees.
// Honest address name: identity is class+slot only (opaque Rva).
void Rva00482E96::rva00482C39()
{
	((StringBase<unsigned short>*)this)->validate();
	((StringBase<unsigned short>*)((char*)this + 0x20))->validate();
}

void Rva00482E96::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	if (version.m_minimum >= 2)
		((UpdateModule *)this)->UpdateModule::xfer(xfer);
	else
		((BehaviorModule *)this)->BehaviorModule::xfer(xfer);
	((UpgradeMux *)((char *)this + 0x20))->UpgradeMux::upgradeMuxXfer(xfer);
	if (version.m_minimum >= 3) {
		m_m2C.xfer(xfer);
		*xfer == m_iA8;
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00019565FlatBase@@UAE@XZ=??1Rva00589079@@UAE@XZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva00589079_S1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?f4@Rva00481F82_S4@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?f1@Rva00481F82_S1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?f3@Rva00482E96_S3@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?f1@Rva00482E96_S1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?s02@Rva00482E96@@UAEXXZ=?Rva00482E4BGet@@YAHXZ")
