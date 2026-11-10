// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /GX /MD /D_CRTIMP=
// Split from ExperienceTrackerXfer.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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
#include "../../../../Libraries/Include/Lib/RGBColor.h"
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class ThingTemplate;

#include "../../../Include/Common/BfmeXfer.h"


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

#include "../../../Include/Common/NameKeyGenerator.h"
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
#include "../../../Include/GameLogic/ExperienceLevelStore.h"
class Overridable;
// The store as the rowed 0x002897A8 names it: the next level of a list
// above the one keyed by the given NameKeyType.
#include "../../../Include/GameLogic/Module/Rva0028951F.h"
// An experience level as read here: required experience at +0x18 and the
// value at +0xFC this tracker reports.
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

// The first unwind action restores the canonical Snapshot table.
#include "Common/Snapshot.h"

class ExperienceTracker : public Snapshot
{
public:
	ExperienceTracker( const ThingTemplate *thingTemplate );
	ExperienceLevelHandle rva0039AC0C() const;
	int rva0039AC23( bool notify );
	void rva0039AD45();
	float rva0039ADB9( float experience, int rank ) const;
	virtual ~ExperienceTracker();
	// ?isTrainable@ExperienceTracker@@QBE_NXZ, the rowed byte getter 0x0039ADAF
	// (pinned), inlined by its callers here: the template's byte at +0x5E7.
	__declspec(dllimport) __forceinline bool isTrainable() const { return *((const unsigned char *)m_04 + 0x5E7) != 0; }
protected:
	virtual void xfer(Xfer *xfer);
	virtual void rvaSlot4( const Overridable *level, bool notify ) = 0;	// slot 4 (+0x10)
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
// retail's three EH states destroy Snapshot, the AsciiString +0x08 and
// the new allocation. The 0x0039AE30 owner
// object's shape comes from the Open-BFME-1 BfmeThingEFECtor.cpp donor
// (revision 177ae72da).
struct ExperienceTrackerParentView
{
	char m_unrecovered00[ 0x64 ];
	AsciiString m_64;
};
struct Rva0039AE75Owner;
#include "../../../Include/Common/Rva0039AE75.h"

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




// ?rva0039ADB9@ExperienceTracker@@QBEMMH@Z @0x0039ADB9 51B: the experience
// clamped to the requirement of the given rank in this tracker's list (rowed
// ExperienceLevelStore 0x00288CA6), min-by-reference the way STLport's min
// picks. No direct caller or absolute reference in game.dat; WorldBuilder's
// unnamed counterpart 0xF9FAE0 (call graph) makes the same call.
static inline const float &trackerMin( const float &a, const float &b )
{
	return b < a ? b : a;
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

enum Relationship
{
	ENEMIES,
	NEUTRAL,
	ALLIES
};
class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
	Relationship getRelationship(Object const *that) const;
	bool testStatus( ObjectStatusTypes bit ) const; // 0x0004E536
	// Thing's raw template pointer at +0x04 (no override walk).
	const ThingTemplate *rawTemplate() const { return m_template; }
private:
	void *m_vtbl; // +0x00
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x25C];
	ExperienceTracker *m_experienceTracker; // +0x264
};

class Rva0039ADF3 : public ExperienceTracker
{
public:
	~Rva0039ADF3();	// rowed out of line; this view must not emit its own
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


