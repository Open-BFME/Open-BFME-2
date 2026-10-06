// cl: /MD
// ?rva00531BA7@Rva00531A44@@QAEXPAVXfer@@@Z @ 0x00531BA7 (173B): __thiscall Xfer-like crc over 4 arrays; IsCRC gate via slot 0x0C; ushort arrays via slot 0x80 uchar via 0x88; caller 0x005342CB.
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
class Rva00531A44
{
public:
	void rva00531BA7(Xfer *xfer);
	unsigned short m_u0;
	unsigned short m_count;
	unsigned short *m_p4;
	unsigned char *m_p8;
	unsigned short *m_pC;
	unsigned short *m_p10;
};
void Rva00531A44::rva00531BA7(Xfer *xfer)
{
	if (!xfer->IsCRC())
		return;
	Xfer &r1 = (*xfer == m_u0);
	Xfer &r2 = (r1 == m_count);
	for (unsigned short i = 0; i < m_count; ++i)
	{
		Xfer &a = (*xfer == m_p4[i]);
		Xfer &b = (a == m_p8[i]);
		Xfer &c = (b == m_pC[i]);
		Xfer &d = (c == m_p10[i]);
		(void)d;
	}
}
