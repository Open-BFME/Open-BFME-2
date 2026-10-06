// cl: /O1 /DNDEBUG /MD
//
// ?xfer@MonsterDockUpdate@@MAEXPAVXfer@@@Z, retail 0x004A14C2, 85 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00851D74 (class of rowed ctor
// ??0MonsterDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z at 0x004A139A in
// MonsterDockUpdateCtor.cpp): base DockUpdate xfer via rowed 0x0058A410
// then IsLightCRC early-out via Xfer slot 0x10 then bool at +0x88 via Xfer
// slot 0x90 then int at +0x8C via Xfer slot 0x7C then bool at +0x89 via Xfer
// slot 0x90 then Version1 via rowed 0x000053EE last. Layout is DockUpdate
// base 0x88 plus two bools plus int (BFME1 donor
// MonsterDockUpdateConstructor.cpp: bool m_flag88 plus bool m_flag89 plus
// int m_value8c; ctor sets 1/0/0). Donor is BFME1 plus ZH.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase
{
	float x;
	float y;
	float z;
};
class ICoord3D;
class Region3D;
class IRegion3D;
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
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

class __declspec(novtable) DockUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad[0x88 - 4];
};

class MonsterDockUpdate : public DockUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_flag88;
	bool m_flag89;
	int m_value8C;
};

void MonsterDockUpdate::xfer(Xfer *xfer)
{
	DockUpdate::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_flag88;
	*xfer == m_value8C;
	*xfer == m_flag89;
	xfer->Version1();
}
