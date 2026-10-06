// cl: /O1 /MD
// ?xfer@Rva0034103B@@MAEXPAVXfer@@@Z @0x0034103B 217B: Rva0034103B xfer slot 3.
// Version1 via rowed 0x000053EE then base Rva0033FF2B xfer via rowed 0x0033FF76 then IsLightCRC early-out via Xfer slot 0x10 then Coord2D at +0x4C via slot 0x50 plus float at +0x54 via slot 0x70 plus int at +0x58 via slot 0x7C plus two TerrainLogic ID refs at +0x5C/+0x60 via slot 0x78 plus IsLoading plus slot 0x8C plus bool at +0x64 via slot 0x90.
// Precedent Rva00458AAE xfer (Version1 base float int) plus DockUpdate 0x7fffffff ID shape plus Rva00573A00 TheTerrainLogic at 0x00DFEC50.
// Unblocks 0x0034117C and 0x00341205.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
#include "../../../Libraries/Include/Lib/Coord2D.h"
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
class Rva0033FF2B
{
public:
	virtual ~Rva0033FF2B();
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad04[0x4C - 0x04];
};
struct TerrainObj
{
	int m_00;
	int m_id;
};
class TerrainLogic
{
	public:
	virtual void _00(); virtual void _01(); virtual void _02(); virtual void _03();
	virtual void _04(); virtual void _05(); virtual void _06(); virtual void _07();
	virtual void _08(); virtual void _09(); virtual void _10(); virtual void _11();
	virtual void _12(); virtual void _13(); virtual void _14(); virtual void _15();
	virtual void _16(); virtual void _17(); virtual void _18(); virtual void _19();
	virtual void _20(); virtual void _21(); virtual void _22(); virtual void _23();
	virtual void _24(); virtual void _25(); virtual void _26(); virtual void _27();
	virtual void _28(); virtual void _29(); virtual void _30(); virtual void _31();
	virtual void _32(); virtual void _33(); virtual void _34();
	virtual TerrainObj *findObj(unsigned int id);
};
extern TerrainLogic *TheTerrainLogic;
class Rva0034103B : public Rva0033FF2B
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Coord2D m_4C;
	float m_54;
	int m_58;
	TerrainObj *m_5C;
	TerrainObj *m_60;
	bool m_64;
};
void Rva0034103B::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva0033FF2B::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_4C;
	*xfer == m_54;
	*xfer == m_58;
	unsigned int id;
	id = 0x7fffffff;
	if (m_5C)
		id = m_5C->m_id;
	*xfer == id;
	if (xfer->IsLoading())
		m_5C = TheTerrainLogic->findObj(id);
	id = 0x7fffffff;
	if (m_60)
		id = m_60->m_id;
	*xfer == id;
	if (xfer->IsLoading())
		m_60 = TheTerrainLogic->findObj(id);
	*xfer == m_64;
}
