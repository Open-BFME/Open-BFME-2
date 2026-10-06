// cl: /MD
//
// ??0Rva0033FE65@@QAE@PAVStateMachine@@H@Z, retail 0x0033FE65, 56 bytes.
// State-derived ctor forwarding (machine, 0x8821F22E) to the unsigned-hash
// twin ??0State@@QAE@PAVStateMachine@@I@Z at 0x004D73FC then installing
// vtable 0x00811E08. Sets word at +0x20 via OR FFFF, byte at +0x24 to
// (val==0), word at +0x22 to 5, byte at +0x25 to 0. Callers pass 0 as val
// (0x00342FCD) plus machine pointers. Recipe is StateDerivedCtors_muse-a7a4
// hash-plus-vtable with the extra word/bool tail.

class StateMachine;

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();

	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
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

// Rva0033FE65_vftable: matched references place it at VA 0xc11e08 (retail .rdata value 7).
extern "C" char Rva0033FE65_vftable = 7;

class __declspec(novtable) Rva0033FE65 : public State
{
public:
	Rva0033FE65(StateMachine *machine, int val);

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned short m_20;
	unsigned short m_22;
	bool m_24;
	bool m_25;
};

Rva0033FE65::Rva0033FE65(StateMachine *machine, int val) : State(machine, 0x8821F22Eu)
{
	m_20 |= 0xFFFF;
	*reinterpret_cast<char **>(this) = &Rva0033FE65_vftable;
	m_24 = (val == 0);
	m_22 = 5;
	m_25 = 0;
}

void Rva0033FE65::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_25;
	if (version.m_minimum >= 2) {
		*xfer == m_22;
	}
}
