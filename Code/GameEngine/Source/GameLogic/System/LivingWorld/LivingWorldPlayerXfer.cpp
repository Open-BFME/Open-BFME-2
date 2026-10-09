// cl: /O1 /Ob1 /G7 /EHsc /MD /arch:SSE /DNDEBUG
// Native2E07FA..2E0856 RET0 and WBDE9400 establish count4 followed by
// four unsigned transfers through Xfer+78; failure throws the independently
// recovered XferException at CFFD18. The complete virtual declaration follows
// the verified UnitRevivalTracker transfer. The original helper name is unknown.
// ?Rva002E07FAXfer@@YAPAVXfer@@PAV1@PAI@Z
class AsciiString; class UnicodeString; class PooledString; class Coord3DBase; class ICoord3D; class Region3D; class IRegion3D; class Coord2D; class ICoord2D; class Region2D; class IRegion2D; class RealRange; class RGBColor; class RGBAColorReal; class RGBAColorInt; class Snapshot; class XferUnknown11;
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


class XferException {
public:
 XferException(int,const char*,...);
 XferException(const XferException&);
 ~XferException();
 char *text; int tag;
};
Xfer *Rva002E07FAXfer(Xfer *xfer, unsigned int *values) {
 unsigned int count=4;
 *xfer == count;
 if(count != 4) throw XferException(0,0);
 for(unsigned int i=0;i<4;++i) *xfer == values[i];
 return xfer;
}
