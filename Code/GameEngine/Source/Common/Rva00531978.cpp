// cl: /MD
// ?rva00531978@Rva00531978@@QAEXPAVXfer@@@Z @ 0x00531978 (204B): __thiscall unpack 20-bit field via Xfer ushort slot 0x80; IsCRC gate slot 0x0C; caller 0x005343BC.
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
class Rva00531978
{
public:
	void rva00531978(Xfer *xfer);
	unsigned int m_val;
};
void Rva00531978::rva00531978(Xfer *xfer)
{
	if (!xfer->IsCRC())
		return;
	unsigned short t0 = (unsigned short)(m_val & 7u);
	*xfer == t0;
	unsigned short t1 = (unsigned short)((m_val >> 3) & 0x3fu);
	*xfer == t1;
	unsigned short t2 = (unsigned short)((m_val >> 9) & 0x3fu);
	*xfer == t2;
	unsigned short t3 = (unsigned short)((m_val >> 15) & 1u);
	*xfer == t3;
	unsigned short t4 = (unsigned short)((m_val >> 16) & 1u);
	*xfer == t4;
	unsigned short t5 = (unsigned short)((m_val >> 17) & 3u);
	*xfer == t5;
	unsigned short t6 = (unsigned short)((m_val >> 19) & 1u);
	*xfer == t6;
}
