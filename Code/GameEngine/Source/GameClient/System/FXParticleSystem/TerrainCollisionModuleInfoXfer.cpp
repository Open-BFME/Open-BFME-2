// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva0056445E@TerrainCollisionModuleInfo@FXParticleSystem@@QAEXPAVXfer@@@Z, retail 0x0056445E, 57 bytes.
// Subobject xfer at overall+0x20: Version1 plus RandomVariable at +0x8 via rowed xferRandomVariable plus AsciiString at +0x4 via Xfer slot 0x6C plus bool at +0x14 via Xfer slot 0x90. Caller at 0x005644BC; unblocks 0x005644A9.
// Xfer declaration with reverse-order overloads gives 0x6C AsciiString 0x90 bool 0x78 uint; pattern from Rva003AF22E xfer 0x0055EA8E.
#include "ascii_string.h"

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

class GameClientRandomVariable
{
public:
	int m_type;
	float m_low;
	float m_high;
};

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

namespace FXParticleSystem {

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

class TerrainCollisionModuleInfo : public Snapshot
{
public:
	void rva0056445E(Xfer *xfer);
private:
	AsciiString m_04;
	GameClientRandomVariable m_08;
	bool m_14;
	int m_18;
};

void TerrainCollisionModuleInfo::rva0056445E(Xfer *xfer)
{
	xfer->Version1();
	xferRandomVariable(*xfer, m_08);
	*xfer == m_04;
	*xfer == m_14;
}

} // namespace FXParticleSystem
