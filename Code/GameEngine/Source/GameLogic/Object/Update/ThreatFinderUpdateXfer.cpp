// cl: /DNDEBUG /MD /EHsc
// ?xfer@ThreatFinderUpdate@@MAEXPAVXfer@@@Z @0x003ECED5 (143B): ThreatFinderUpdate
// xfer (vslot 3) that versions via slot 0x28 calls UpdateModule::xfer allocates
// the 0x56C heap via 0x003ECD60 when not storing registers it then xfers it.
// Evidence: vtable 0x008360CC slot 3 plus ctor 0x003ECCA2 plus dtor heap +0x20
// plus callers of 0x003ECD60 and 0x003ECBF8; Xfer decl verbatim from
// PoisonedBehaviorXfer.cpp so Version sits at 0x28 and IsStoring at 0x08.
template <class T> class StringBase
{
public:
	StringBase(const StringBase &other);

private:
	void *m_data;
};

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

struct OwnerWithName
{
	char m_pad[0x88];
	StringBase<char> m_name;
};

class UpdateModule
{
public:
	void xfer(Xfer *xfer);

protected:
	virtual void dummy() = 0;

	char m_pad04[4];
	OwnerWithName *m_owner;
	char m_pad0C[0x14];
};

class Rva003ECDB7Object
{
public:
	void registerName();
};

class Rva003ECD60Object : public Rva003ECDB7Object
{
public:
	Rva003ECD60Object(const StringBase<char> &name, bool flag);
	void xfer(Xfer *xfer);

private:
	char m_pad[0x56C];
};

class ThreatFinderUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Rva003ECD60Object *m_heap;
};

void ThreatFinderUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
	if (!xfer->IsStoring()) {
		Rva003ECD60Object *obj = new Rva003ECD60Object(m_owner->m_name, false);
		m_heap = obj;
		obj->registerName();
	}
	if (m_heap != 0)
		m_heap->xfer(xfer);
}
