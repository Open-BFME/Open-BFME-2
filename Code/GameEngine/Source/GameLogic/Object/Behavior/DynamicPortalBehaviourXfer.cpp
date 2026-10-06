// cl: /DNDEBUG /MD
//
// ?xfer@DynamicPortalBehaviour@@MAEXPAVXfer@@@Z, retail 0x004609BC, 201 bytes.
// Slot 3 of ??_7DynamicPortalBehaviour 0x00C428C4 (slot-2 name getter
// returns "DynamicPortalBehaviour"). The rowed UpgradeModule::xfer 0x004CE3F9
// first, then the light-CRC out, Version(1,2), six waypoints at +0x24 by
// waypoint ID (the rowed XferWaypointID 0x00305C62; 0x7FFFFFFF is no
// waypoint; on load resolved through TheTerrainLogic slot 35, on save read
// from Waypoint+0x04), a bool at +0x3C and, from version 2, a bool at +0x3D.
// Member names not recovered.

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

enum { INVALID_WAYPOINT_ID = 0x7fffffff };

void XferWaypointID(Xfer *xfer, int *id);

class Waypoint
{
public:
	int getID() const { return m_id; }
private:
	void *m_unknown00;
	int m_id;
};

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34();
	virtual Waypoint *getWaypointByID(int waypointID);
};

extern TerrainLogic *TheTerrainLogic;

class UpgradeModule
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x24 - 0x04];
};

class DynamicPortalBehaviour : public UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	enum { WAYPOINT_COUNT = 6 };
	Waypoint *m_24[WAYPOINT_COUNT];
	bool m_3C;
	bool m_3D;
};

// ?xfer@DynamicPortalBehaviour@@MAEXPAVXfer@@@Z @0x004609BC
void DynamicPortalBehaviour::xfer(Xfer *xfer)
{
	UpgradeModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	for (int i = 0; i < WAYPOINT_COUNT; ++i)
	{
		if (xfer->IsLoading())
		{
			int id;
			XferWaypointID(xfer, &id);
			m_24[i] = id == INVALID_WAYPOINT_ID ? 0 : TheTerrainLogic->getWaypointByID(id);
		}
		else
		{
			int id = m_24[i] ? m_24[i]->getID() : INVALID_WAYPOINT_ID;
			XferWaypointID(xfer, &id);
		}
	}

	*xfer == m_3C;
	if (version.m_minimum >= 2)
		*xfer == m_3D;
}
