// cl: /MD
// ?xfer@GhostObjectManager@@MAEXPAVXfer@@@Z @0x0030594D 31B via Xfer Version1 plus int operator== slot 0x7c
// Retail Version1 then Xfer virtual at +0x7c with this+4; reverse-overload layout puts int at 0x7c.
//
// Identity: slot 3 of ??_7GhostObjectManager@@6B@ (0x008078F0, the base
// table whose manager slots 6-8 are pure), and the rowed
// W3DGhostObjectManager::xfer (0x000642F1) calls it first as its base class
// transfer. Zero Hour's GhostObjectManager::xfer (GameLogic/Object/
// GhostObject.cpp) sends m_localPlayer, the int at +0x04 that
// getLocalPlayerIndex reads. Donor-carried: the names.
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
class DamageInfo;
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
// BFME 2 GhostObjectManager table (0x008078F0): the Snapshot entries are the
// destructor, crc, the name getter 0x00305947, xfer and loadPostProcess.
class GhostObjectManager
{
public:
	virtual ~GhostObjectManager();
protected:
	virtual void crc(Xfer *xfer);
	virtual const char *v02() const;
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

	int m_localPlayer; // +0x04
};
void GhostObjectManager::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_localPlayer;
}
