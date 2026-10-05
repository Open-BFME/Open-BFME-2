// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?xfer@Rva00340BDC@@MAEXPAVXfer@@@Z, retail 0x00340AE8, 244 bytes.
// Slot 3 (0x0C) of vtable 0x00812150 (class Rva00340BDC): xfer with Version(1,3),
// base Rva0033FF2B::xfer, IsLightCRC early-out, Coord+ICoord2D+uint+bool members,
// version>1 new Rva0033F483 sub-state plus int temp and Snapshot xfer, version>2
// uint+bool. Layout from retail offsets; Xfer decl copied verbatim from
// PoisonedBehaviorXfer.cpp for slot order (overloads reversed by MSVC 7.1).
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
class StateMachine;

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

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct ICoord2D
{
	int x;
	int y;
};

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
private:
	unsigned char m_pad04[0x20 - 4];
};

class Rva0033F483 : public State
{
public:
	Rva0033F483(StateMachine *machine, int arg0);
private:
	int m_20;
	bool m_24;
	char m_pad25[0x28 - 0x25];
};

class Rva0033FF2B
{
protected:
	virtual void xfer(Xfer *xfer);
	StateMachine *getMachine() { return m_machine18; }
public:
	char m_pad04[0x18 - 0x04];
	StateMachine *m_machine18;
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3DBase m_20;
	float m_2C;
	int m_30;
	Coord3DBase m_34;
	unsigned int m_40;
	unsigned int m_44;
	bool m_48;
	bool m_49;
	char m_pad4A;
	bool m_4B;
};

class Rva00340BDC : public Rva0033FF2B
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Rva0033F483 *m_ptr4C;
	int m_50;
	unsigned int m_54;
	Coord3DBase m_58;
	ICoord2D m_64;
	unsigned int m_6C;
	bool m_70;
	bool m_71;
	char m_pad72[0x74 - 0x72];
	int m_74;
};

void Rva00340BDC::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	Rva0033FF2B::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_58;
	*xfer == m_64;
	*xfer == m_54;
	*xfer == m_71;
	if (version.m_minimum > 1) {
		if (m_ptr4C == 0)
			m_ptr4C = new Rva0033F483(getMachine(), m_74);
		int tmp = m_50;
		*xfer == tmp;
		m_50 = tmp;
		*xfer == *(Snapshot *)m_ptr4C;
	}
	if (version.m_minimum > 2) {
		*xfer == m_6C;
		*xfer == m_70;
	}
}
