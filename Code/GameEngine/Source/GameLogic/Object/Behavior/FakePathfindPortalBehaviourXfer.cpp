// cl: /DNDEBUG /MD
//
// ?xfer@FakePathfindPortalBehaviour@@MAEXPAVXfer@@@Z, retail 0x00461B1B, 232 bytes.
// Slot 3 of ??_7FakePathfindPortalBehaviour 0x00C42C1C (slot-2 name getter
// returns "FakePathfindPortalBehaviour"; the rowed dtor 0x004619F2 installs
// it). The rowed UpdateModule::xfer 0x0044DF9F first, the light-CRC out,
// Version(1,2), the two waypoints at +0x28 by waypoint ID (the
// DynamicPortalBehaviourXfer shape), bools at +0x30, +0x31 and +0x32, and
// when +0x32 is set on load the pinned no-argument member 0x004618AB that
// re-registers both waypoints and sets +0x32 again. Member names not
// recovered.

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

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
private:
	char m_unrecovered04[0x28 - 0x04];
};

class Rva002E9042
{
public:
	void rva002E8FE5(void *p);
};

class AI
{
public:
	char m_pad[0x10];
	Rva002E9042 *m_10;
};

extern class AI *TheAI;

class FakePathfindPortalBehaviour : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	void rva004618AB();

	enum { WAYPOINT_COUNT = 2 };
	Waypoint *m_28[WAYPOINT_COUNT];
	bool m_30;
	bool m_31;
	bool m_32;
};

// ?xfer@FakePathfindPortalBehaviour@@MAEXPAVXfer@@@Z @0x00461B1B
void FakePathfindPortalBehaviour::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

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
			m_28[i] = id == INVALID_WAYPOINT_ID ? 0 : TheTerrainLogic->getWaypointByID(id);
		}
		else
		{
			int id = m_28[i] ? m_28[i]->getID() : INVALID_WAYPOINT_ID;
			XferWaypointID(xfer, &id);
		}
	}

	*xfer == m_30;
	*xfer == m_31;
	*xfer == m_32;
	if (m_32 && xfer->IsLoading())
		rva004618AB();
}

// ?rva004618AB@FakePathfindPortalBehaviour@@AAEXXZ @0x004618AB 41B
// Re-registers both waypoints through the AI pathfinder set-twin 0x002E8FE5
// and sets +0x32 again. Called from xfer on load when +0x32 is set.
void FakePathfindPortalBehaviour::rva004618AB()
{
	TheAI->m_10->rva002E8FE5(m_28[0]);
	TheAI->m_10->rva002E8FE5(m_28[1]);
	m_32 = true;
}
