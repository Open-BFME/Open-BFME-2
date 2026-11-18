// cl: /O1 /arch:SSE /G7 /EHsc /MD
// ?rva004D6FC4@Rva00263653@@UAEXPAX@Z @0x004D6FC4 273B: the single slot of vftable 0x007F91FC,
// which the damage-record ctor 0x00263653 and copy ctor 0x0028C62B install. xfer of the record: nothing for a
// light CRC; then a version block (1, 3), an ObjectID at +4, the +8 field, the damage,
// damage-FX, damage sub and death type enums at +0xC..+0x18, fields at +0x1C..+0x48 (+0x30 through
// the 0x60 slot), the byte flag at +0x21 from version 2 and the +0x64 field from version 3.
// Every call chains the xfer returned by the previous one; the labelled-enum helpers return it
// in EAX. Field types behind the numbered slots are not established.
#include "../../../Include/Common/ScalarTypes.h"


enum ObjectID { INVALID_ID = 0 };

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(UnsignedByte first, UnsignedByte version) : m_first(first), m_version(version) {}
	UnsignedByte m_first;
	UnsignedByte m_version;
};

void XferObjectID(Xfer *xfer, ObjectID *id);
void XferDamageFXType(Xfer *xfer, int *value);
void XferDamageType(Xfer *xfer, int *value);
void XferDamageSubType(Xfer *xfer, int *value);
void XferDeathType(Xfer *xfer, int *value);
void XferFXTrigger(Xfer *xfer, int *value);

typedef Xfer *(*XferHelperFn)(Xfer *, void *);

class Rva00263653
{
public:
	virtual void rva004D6FC4(void *context);
private:
	ObjectID m_04;
	int m_08;
	int m_0C, m_10, m_14, m_18;
	int m_1C;
	UnsignedByte m_20, m_21, m_pad22[2];
	int m_24;
	int m_28;
	ObjectID m_2C;
	int m_30;
	int m_pad34[2];
	int m_3C, m_40, m_44, m_48;
	int m_pad4C[6];
	int m_64;
};

void Rva00263653::rva004D6FC4(void *context)
{
	Xfer *xfer = static_cast<Xfer *>(context);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 3);
	Xfer *x = ((XferHelperFn)XferDeathType)(
		((XferHelperFn)XferDamageSubType)(
			((XferHelperFn)XferDamageFXType)(
				((XferHelperFn)XferDamageType)(
					&((XferHelperFn)XferObjectID)(&xfer->operator==(version), &m_04)->operator==(reinterpret_cast<unsigned &>(m_08)),
					&m_0C),
				&m_10),
			&m_14),
		&m_18);
	x = &x->operator==(reinterpret_cast<float &>(m_1C));
	x = &x->operator==(reinterpret_cast<bool &>(m_20));
	x = ((XferHelperFn)XferObjectID)(((XferHelperFn)XferFXTrigger)(&x->operator==(reinterpret_cast<float &>(m_24)), &m_28), &m_2C);
	x = &x->operator==(reinterpret_cast<Coord3DBase &>(m_30));
	x = &x->operator==(reinterpret_cast<float &>(m_3C));
	x = &x->operator==(reinterpret_cast<float &>(m_40));
	x = &x->operator==(reinterpret_cast<float &>(m_44));
	x = &x->operator==(reinterpret_cast<float &>(m_48));
	if (version.m_version >= 2)
		xfer->operator==(reinterpret_cast<bool &>(m_21));
	if (version.m_version >= 3)
		xfer->operator==(reinterpret_cast<float &>(m_64));
}
