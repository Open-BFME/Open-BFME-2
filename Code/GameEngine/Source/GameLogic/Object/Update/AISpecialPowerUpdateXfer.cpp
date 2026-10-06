// cl: /DNDEBUG /MD
//
// ?xfer@AISpecialPowerUpdate@@MAEXPAVXfer@@@Z, retail 0x004B3352, 153 bytes.
// Slot 3 of ??_7AISpecialPowerUpdate 0x00C56E1C (slot-2 name getter returns
// "AISpecialPowerUpdate"; the rowed dtor 0x004B2E79 installs it).
// Version(1,3), the rowed UpdateModule::xfer 0x0044DF9F, from version 3 a
// bool at +0x21; on load with that bool set (or from an older save) the
// pinned no-argument member 0x004B303F; a bool at +0x20; then, when the
// object at +0x24 exists, its slot-1 transfer, gated before version 2 on
// the rowed g_00DFEEF8 record lookup for the controlling player. Member
// names not recovered.

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

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva004B3352State
{
public:
	virtual void s00();
	virtual void xfer(Xfer *xfer);
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	Object *getObject() const { return m_object; }
private:
	void *m_moduleData;
	Object *m_object;
	char m_unrecovered0C[0x20 - 0x0C];
};

class AISpecialPowerUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	void postInitAISpecialPower();

	bool m_20;
	bool m_21;
	Rva004B3352State *m_24;
};

// ?xfer@AISpecialPowerUpdate@@MAEXPAVXfer@@@Z @0x004B3352
void AISpecialPowerUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;

	UpdateModule::xfer(xfer);

	if (version.m_minimum >= 3)
		*xfer == m_21;

	if (xfer->IsLoading() && (m_21 || version.m_minimum < 3))
		postInitAISpecialPower();

	*xfer == m_20;

	if (m_24)
	{
		if (version.m_minimum >= 2 || g_00DFEEF8->rva002A8AB1(getObject()->getControllingPlayer()))
			m_24->xfer(xfer);
	}
}
