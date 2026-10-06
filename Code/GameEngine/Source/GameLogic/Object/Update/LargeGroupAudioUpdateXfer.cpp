// cl: /O1 /DNDEBUG /MD
//
// ?xfer@LargeGroupAudioUpdate@@MAEXPAVXfer@@@Z, retail 0x004AB9EA, 135 bytes.
// Slot 3 of ??_7LargeGroupAudioUpdate 0x00C549BC (slot-2 name getter
// returns "LargeGroupAudioUpdate"). The rowed UpdateModule::xfer 0x0044DF9F,
// the light-CRC out, Version(1,2), a Coord2D at +0x28 (Xfer slot 0x50), the
// members at +0x30 and +0x7C through their pinned non-virtual transfers
// (0x000BB710, 0x00292550), a bool at +0x8C, from version 2 an int at
// +0x90, and a bool at +0x8D. Member names not recovered.

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

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

class Rva000BB710
{
public:
	void xfer(Xfer *xfer);
private:
	char m_unrecovered00[0x4C];
};

class Rva00292550
{
public:
	void xfer(Xfer *xfer);
private:
	char m_unrecovered00[0x10];
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
private:
	char m_unrecovered04[0x28 - 0x04];
};

class LargeGroupAudioUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Coord2D m_28;
	Rva000BB710 m_30;
	Rva00292550 m_7C;
	bool m_8C;
	bool m_8D;
	int m_90;
};

// ?xfer@LargeGroupAudioUpdate@@MAEXPAVXfer@@@Z @0x004AB9EA
void LargeGroupAudioUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	*xfer == m_28;
	m_30.xfer(xfer);
	m_7C.xfer(xfer);
	*xfer == m_8C;
	if (version.m_minimum >= 2)
		*xfer == m_90;
	*xfer == m_8D;
}
