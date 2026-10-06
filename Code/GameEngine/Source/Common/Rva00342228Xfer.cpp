// cl: /MD /Ireference/shims/moduledata
//
// ?xfer@Rva00342228@@MAEXPAVXfer@@@Z, retail 0x00342283, 108 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00811900 (class of ??1Rva00342228@@UAE@XZ,
// rowed in Rva00342228Dtor.cpp) and also of twin vtable 0x008118B0 (class of
// ??1Rva00342157@@UAE@XZ); both slots share this one body. It sits directly
// after the Rva00342228 dtor (0x00342228+91). Shape is the PoisonedBehavior /
// Rva003424B1 slot-3 recipe: IsLightCRC early-out (Xfer slot 0x10), Version1
// (rowed 0x000053EE), a stack bool streaming m_ptr20 presence via ==(bool&)
// (slot 0x90), on-demand m_ptr20 creation through m_ptr18 slot 0x24, the
// pointee streamed via ==(Snapshot&) (slot 0x30, so the member is modelled
// Snapshot*), then m_24 via ==(unsigned int&) (slot 0x78). Xfer declaration
// copied verbatim from Rva003424B1Xfer.cpp; member offsets from the matched
// Rva00342228 ctor/slot-4 TUs.

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

#include "Common/Snapshot.h"

class Rva00342228Ref18
{
public:
	virtual void _pad00();
	virtual void _pad01();
	virtual void _pad02();
	virtual void _pad03();
	virtual void _pad04();
	virtual void _pad05();
	virtual void _pad06();
	virtual void _pad07();
	virtual void _pad08();
	virtual Snapshot *getPtr20();
};

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class Rva00342228 : public Rva0049B47C
{
protected:
	virtual void _slot01();
	virtual void _slot02();
	virtual void xfer(Xfer *xfer);

private:
	char m_pad0C[0x18 - 0x0C];
	Rva00342228Ref18 *m_ptr18;
	char m_pad1C[0x20 - 0x1C];
	Snapshot *m_ptr20;
	unsigned int m_24;
};

void Rva00342228::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	bool hasPtr = (m_ptr20 != 0);
	*xfer == hasPtr;
	if (hasPtr) {
		if (m_ptr20 == 0)
			m_ptr20 = m_ptr18->getPtr20();
	}
	if (hasPtr)
		*xfer == *m_ptr20;
	*xfer == m_24;
}
