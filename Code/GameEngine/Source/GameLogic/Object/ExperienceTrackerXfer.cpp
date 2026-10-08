// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP=
//
// ?xfer@ExperienceTracker@@MAEXPAVXfer@@@Z @0x0039AFC8 257B (pinned): slot 3
// of vtable 0x0081AD20; also called by the ExperienceTrackerAutoResolve xfer
// 0x005DB074. BFME 2 reworked Zero Hour's ExperienceTracker::xfer (version
// 5): the version struct goes through Xfer slot 0x28; version >= 2 xfers the
// float at +0x10 directly, older loads read an int and convert it; the
// AsciiString at +0x08 (slot 0x6C) is re-keyed into +0x0C on load; then the
// float +0x1C, ints +0x14, a dropped int before version 4, +0x24, the bool
// +0x20 (slot 0x90) and +0x18; version >= 2 xfers the snapshot at +0x2C
// (its slot 2), version >= 3 the NameKeyType at +0x30 through the helper
// 0x00149101, version >= 5 the int at +0x28. Field names are unknown, so
// they stay offset-named.
#include "ascii_string.h"
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
struct RGBColor
{
	float red;
	float green;
	float blue;
};
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class ThingTemplate;

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
	Version(unsigned char minimum, unsigned char current) : m_minimum(minimum), m_current(current) {}
	unsigned char m_minimum;
	unsigned char m_current;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

Xfer &Rva00149101XferNameKey( Xfer &xfer, NameKeyType &key );

class ExperienceTrackerSnapshot
{
public:
	virtual void v0();
	virtual void v1();
	virtual void xfer(Xfer *xfer) = 0; // slot 2
};

// The two-dword level handle ExperienceLevelStore hands out (full view in
// ExperienceLevelSystem.cpp); not POD, so it comes back through a hidden pointer.
class ExperienceLevelList;
struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelList *m_list;
	void *m_iter;
};

class ExperienceTracker;
class ExperienceLevelStore
{
public:
	ExperienceLevelHandle FindCurrentLevel( const ExperienceTracker *tracker ) const;	// 0x00288D2F
	ExperienceLevelList *FindExperienceLevelList( const ExperienceTracker *tracker ) const;	// 0x00288C34
	int rva00288CA6( const ExperienceTracker *tracker, int rank, int *pastEnd ) const;	// 0x00288CA6
};
class Overridable;
// The store as the rowed 0x002897A8 names it: the next level of a list
// above the one keyed by the given NameKeyType.
class Rva0028951F
{
public:
	const Overridable *rva002897A8( void *list, int key );	// 0x002897A8
};
// An experience level as read here: required experience at +0x18 and the
// value at +0xFC this tracker reports.
struct ExperienceTrackerLevelView
{
	char m_unrecovered00[ 0x18 ];
	int m_18;
	char m_unrecovered1C[ 0xFC - 0x1C ];
	int m_FC;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

// The base whose destructor the constructor's first EH state unwinds.
class ExperienceTrackerBaseView
{
public:
	virtual ~ExperienceTrackerBaseView();
};

class ExperienceTracker : public ExperienceTrackerBaseView
{
public:
	ExperienceTracker( const ThingTemplate *thingTemplate );
	ExperienceLevelHandle rva0039AC0C() const;
	int rva0039AC23( bool notify );
	void rva0039AD45();
	float rva0039ADB9( float experience, int rank ) const;
	virtual ~ExperienceTracker();
	virtual void crc(Xfer *xfer);
	virtual void v2() = 0;
	// ?isTrainable@ExperienceTracker@@QBE_NXZ, the rowed byte getter 0x0039ADAF
	// (pinned), inlined by its callers here: the template's byte at +0x5E7.
	bool isTrainable() const { return *((const unsigned char *)m_04 + 0x5E7) != 0; }
protected:
	virtual void xfer(Xfer *xfer);
	virtual void rvaSlot4( const Overridable *level, bool notify );	// slot 4 (+0x10)
private:
	const ThingTemplate *m_04;
	AsciiString m_08;
	NameKeyType m_0C;
	float m_10;
	int m_14;
	int m_18;
	float m_1C;
	bool m_20;
	int m_24;
	int m_28;
	ExperienceTrackerSnapshot *m_2C;
	NameKeyType m_30;
};

// ??0ExperienceTracker@@QAE@PAVObject@@@Z @0x0039AEBC 158B: stores vftable
// 0x00C1AD20 (the one whose slot 3 is the xfer above), keeps the argument at
// +0x04, defaults every field, keys +0x30 from the AsciiString at the
// argument's +0x64 through the rowed NameKeyGenerator::nameToKey 0x0009FA65,
// and news the 0x14-byte Rva0039AE75 (rowed ctor 0x0039AE30) into +0x2C with
// itself as owner. Callers 0x0039B0D4 and 0x005DB0A7. The argument is a
// ThingTemplate: the derived constructor 0x0039B0C9 passes its Object's raw
// +0x04 (Thing's template pointer, no override walk) and keeps the Object at
// +0x34 for Object::testStatus. Only AsciiStrings at +0x64 and +0x9C and a
// byte at +0x5E7 are read from it, here through a view.
// WorldBuilder's call-graph lead names this body
// ExperienceTrackerBase::ExperienceTrackerBase (ExperienceTracker.cpp line 56);
// retail's three EH states (a destructible base, the AsciiString +0x08, the
// new) are what ExperienceTrackerBaseView stands for. The 0x0039AE30 owner
// object's shape comes from the Open-BFME-1 BfmeThingEFECtor.cpp donor
// (revision 177ae72da).
struct ExperienceTrackerParentView
{
	char m_unrecovered00[ 0x64 ];
	AsciiString m_64;
};
struct Rva0039AE75Owner;
class Rva0039AE75
{
public:
	Rva0039AE75( Rva0039AE75Owner *owner );
	virtual ~Rva0039AE75();
private:
	char m_unrecovered04[ 0x14 - 0x04 ];	// full layout in SnapshotXfersBfme.cpp
};

ExperienceTracker::ExperienceTracker( const ThingTemplate *thingTemplate ) :
	m_04( thingTemplate ),
	m_0C( (NameKeyType)0 ),
	m_10( 0.0f ),
	m_14( 0 ),
	m_18( -1 ),
	m_1C( 1.0f ),
	m_20( false ),
	m_24( 0 ),
	m_28( 0 ),
	m_2C( 0 ),
	m_30( (NameKeyType)0 )
{
	m_30 = TheNameKeyGenerator->nameToKey( ((const ExperienceTrackerParentView *)thingTemplate)->m_64 );
	m_2C = (ExperienceTrackerSnapshot *)new Rva0039AE75( (Rva0039AE75Owner *)this );
}

// ?rva0039AC0C@ExperienceTracker@@QBE?AUExperienceLevelHandle@@XZ @0x0039AC0C
// 23B (pinned name): the tracker's current level from the rowed
// ExperienceLevelStore::FindCurrentLevel 0x00288D2F; nine callers, among them
// 0x005C3192 and 0x0036D8C0. WorldBuilder's unnamed counterpart 0xF9FB80
// (score 7, call graph) is the same single call.
ExperienceLevelHandle ExperienceTracker::rva0039AC0C() const
{
	return reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->FindCurrentLevel( this );
}

// ?rva0039AC23@ExperienceTracker@@QAEH_N@Z @0x0039AC23 121B: walks the
// tracker's level list (rowed FindExperienceLevelList 0x00288C34) up from the
// current level key +0x0C through the rowed 0x002897A8, handing each level the
// experience +0x10 reaches to virtual slot 4 with the flag, and returns the
// last such level's +0xFC, or +0x24 when none was reached (0 without a list).
// Callers 0x0039B1D9, 0x0039B411, 0x005DB0D6. WorldBuilder's unnamed
// counterpart 0xF9FC60 (call graph) has the same loop.
int ExperienceTracker::rva0039AC23( bool notify )
{
	ExperienceLevelList *list = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->FindExperienceLevelList( this );
	if( list == 0 )
		return 0;
	int experience = (int)m_10;
	bool more = true;
	const ExperienceTrackerLevelView *reached = 0;
	while( more )
	{
		const ExperienceTrackerLevelView *level = (const ExperienceTrackerLevelView *)
			((Rva0028951F *)TheExperienceLevelSystem)->rva002897A8( list, m_0C );
		if( level == 0 )
			break;
		if( experience >= level->m_18 )
		{
			rvaSlot4( (const Overridable *)level, notify );
			reached = level;
		}
		else
			more = false;
	}
	if( reached )
		return reached->m_FC;
	return m_24;
}

// ?rva0039AD45@ExperienceTracker@@QAEXXZ @0x0039AD45 17B: clears the
// AsciiString +0x08 (AsciiString::clear, the releaseBuffer worker 0x00036410)
// and its key +0x0C, the pair the xfer above re-keys on load. No direct
// caller or absolute reference in game.dat; placed by the tracker's layout.
void ExperienceTracker::rva0039AD45()
{
	m_08.clear();
	m_0C = (NameKeyType)0;
}

// ?rva0039ADB9@ExperienceTracker@@QBEMMH@Z @0x0039ADB9 51B: the experience
// clamped to the requirement of the given rank in this tracker's list (rowed
// ExperienceLevelStore 0x00288CA6), min-by-reference the way STLport's min
// picks. No direct caller or absolute reference in game.dat; WorldBuilder's
// unnamed counterpart 0xF9FAE0 (call graph) makes the same call.
static inline const float &trackerMin( const float &a, const float &b )
{
	return b < a ? b : a;
}

float ExperienceTracker::rva0039ADB9( float experience, int rank ) const
{
	float required = (float)reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->rva00288CA6( this, rank, 0 );
	return trackerMin( experience, required );
}

void ExperienceTracker::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 5 );
	*xfer == version;

	if( version.m_current >= 2 )
		*xfer == m_10;
	else if( xfer->IsLoading() )
	{
		int oldValue = 0;
		*xfer == oldValue;
		m_10 = (float)oldValue;
	}

	*xfer == m_08;
	if( xfer->IsLoading() )
		m_0C = TheNameKeyGenerator->nameToKey( m_08 );

	*xfer == m_1C;
	*xfer == m_14;
	if( version.m_current < 4 )
	{
		int unused = 0;
		*xfer == unused;
	}
	*xfer == m_24;
	*xfer == m_20;
	*xfer == m_18;
	if( version.m_current >= 2 )
		m_2C->xfer( xfer );
	if( version.m_current >= 3 )
		Rva00149101XferNameKey( *xfer, m_30 );
	if( version.m_current >= 5 )
		*xfer == m_28;
}

// ?xfer@Rva0039ADF3@@MAEXPAVXfer@@@Z @0x0039B10D 56B: slot 3 of vtable
// 0x0081AD34 (class of the rowed ??_GRva0039ADF3 0x0039B0F1, whose dtor
// 0x0039ADF3 chains to the tracker's): version 1, the tracker's xfer, then
// the ObjectID at +0x38 through the rowed XferObjectID 0x003060B2.
enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7fffffff
};
void XferObjectID( Xfer *xfer, ObjectID *id );

enum ObjectStatusTypes
{
	OBJECT_STATUS_3E = 0x3E
};

class Object
{
public:
	bool testStatus( ObjectStatusTypes bit ) const;	// 0x0004E536
	// Thing's raw template pointer at +0x04 (no override walk).
	const ThingTemplate *rawTemplate() const { return m_template; }
private:
	void *m_vtable;
	const ThingTemplate *m_template;
};

class Rva0039ADF3 : public ExperienceTracker
{
public:
	Rva0039ADF3( Object *object );
	bool rva0039AE04() const;
protected:
	virtual void xfer(Xfer *xfer);
private:
	Object *m_34;
	ObjectID m_38;
	bool m_3C;
};

// ??0Rva0039ADF3@@QAE@PAVObject@@@Z @0x0039B0C9 40B: builds the tracker on the
// Object's raw template pointer (rowed ctor 0x0039AEBC), keeps the Object at
// +0x34, clears the ObjectID +0x38, sets the bool +0x3C and stores vftable
// 0x0081AD34. Caller 0x00299BA8 (BFME 2's Object constructor region; the
// tracker Object +0x264 holds).
Rva0039ADF3::Rva0039ADF3( Object *object ) :
	ExperienceTracker( object->rawTemplate() ),
	m_34( object ),
	m_38( INVALID_ID ),
	m_3C( true )
{
}

// ?rva0039AE04@Rva0039ADF3@@QBE_NXZ @0x0039AE04 44B: false while the Object
// has status bit 0x3E; else the inlined isTrainable or a nonzero ObjectID
// +0x38. Callers include LevelGrantSpecialPower (0x004C2B8A) on the tracker
// at Object +0x264; WorldBuilder's unnamed counterpart 0xFA04E0 has the same
// shape with isTrainable out of line.
bool Rva0039ADF3::rva0039AE04() const
{
	if( m_34->testStatus( OBJECT_STATUS_3E ) )
		return false;
	return isTrainable() || m_38 != INVALID_ID;
}

void Rva0039ADF3::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	ExperienceTracker::xfer( xfer );
	XferObjectID( xfer, &m_38 );
}
