// cl: /MD
//
// ?xfer@Rva0049B2A2@@MAEXPAVXfer@@@Z, retail 0x0049B421, 91 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x00850B40 (class of rowed dtor
// ??1Rva0049B2A2@@UAE@XZ in Rva0024A797Derived.cpp): base UpdateModule
// xfer via rowed 0x44DF9F then IsLightCRC early-out via Xfer slot 0x10 then
// Version(1,2) via Xfer slot 0x28 then two uints at +0x20/+0x24 via Xfer
// slot 0x78 then version-gated int at +0x28 via Xfer slot 0x7C. Layout is
// UpdateModule base 0x20. Identity is slot 3 plus the UpdateModule base
// call; class name stays honest Rva address name.

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

class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual ~ObjectModule();
protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModuleInterface { public: virtual UpdateSleepTime update(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class Rva0049B2A2 : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
public:
	virtual UpdateSleepTime update();
	unsigned char rva0049B3D2();
	void rva0049B3F3();

private:
	unsigned int m_20;
	unsigned int m_24;
	int m_28;
};

#include "../../../Libraries/Include/Lib/Coord3D.h"

class ObjectCreationList
{
public:
	void create(void *primary, void *primaryPos, void *secondaryPos, int lifetimeFrames);
	static void create(ObjectCreationList *ocl, const Object *primary, const Coord3D *primaryPos, const Coord3D *secondaryPos, int lifetimeFrames)
	{
		if (ocl)
			ocl->create((void *)primary, (void *)primaryPos, (void *)secondaryPos, lifetimeFrames);
	}
};

// The OCLUpdate module data as these bodies read it: the OCL at +0x08, the
// min/max delay at +0x0C/+0x10, a creation limit at +0x14 and the
// create-at-edge flag at +0x18.
class ModuleData
{
public:
	char m_pad[0x08];
	ObjectCreationList *m_ocl;
	int m_0C;
	int m_10;
	int m_14;
	unsigned char m_18;
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12();
	virtual Coord3D findClosestEdgePoint(const Coord3D *pos) const; // slot 13 (+0x34)
};

extern TerrainLogic *TheTerrainLogic;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

enum ObjectStatusTypes
{
	OBJECT_STATUS_0 = 0,
	OBJECT_STATUS_1 = 1,
	OBJECT_STATUS_2 = 2
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes s) const;
	const Coord3D *getPosition() const { return &m_position; }
private:
	char m_pad00[0x38];
	Coord3D m_position; // +0x38
};

class GameLogic
{
public:
	char m_pad[0x40];
	unsigned m_40;
};

extern GameLogic *TheGameLogic;

unsigned char Rva0049B2A2::rva0049B3D2()
{
	if (TheGameLogic->m_40 < m_20) {
		return 0;
	}
	return (unsigned char)!m_object->testStatus(OBJECT_STATUS_2);
}

void Rva0049B2A2::rva0049B3F3()
{
	int r = GetGameLogicRandomValue(m_moduleData->m_0C, m_moduleData->m_10, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\OCLUpdate.cpp", 123);
	unsigned cur = TheGameLogic->m_40;
	m_24 = cur;
	m_20 = cur + r;
}

void Rva0049B2A2::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	*xfer == m_20;
	*xfer == m_24;
	if (version.m_minimum >= 2) {
		*xfer == m_28;
	}
}

// ?update@Rva0049B2A2@@UAE?AW4UpdateSleepTime@@XZ, retail 0x0049B483, 148
// bytes: slot 0 of the UpdateModuleInterface vftable 0x00850B34 (this is
// +0x10). The module is BFME 2's OCLUpdate (the timer helpers above cite
// OCLUpdate.cpp); BFME 1's OCLUpdate::update (Open-BFME-1
// OCLUpdateUpdate.cpp) is the donor shape: wait for the creation frame,
// schedule the next one, create the OCL at the object or the nearest map
// edge. BFME 2 adds a creation limit (+0x14) counted at +0x28, after which
// the module sleeps forever.
UpdateSleepTime Rva0049B2A2::update()
{
	if (rva0049B3D2())
	{
		if (m_20 == 0)
		{
			rva0049B3F3();
			return UPDATE_SLEEP_NONE;
		}

		rva0049B3F3();

		Coord3D creationCoord;
		if (getModuleData()->m_18)
			creationCoord = TheTerrainLogic->findClosestEdgePoint(getObject()->getPosition());
		else
			creationCoord = *getObject()->getPosition();

		const ModuleData *data = getModuleData();
		ObjectCreationList::create(data->m_ocl, getObject(), &creationCoord, getObject()->getPosition(), 0);

		if (data->m_14 > 0 && ++m_28 >= data->m_14)
			return UPDATE_SLEEP_FOREVER;
	}

	return UPDATE_SLEEP_NONE;
}
