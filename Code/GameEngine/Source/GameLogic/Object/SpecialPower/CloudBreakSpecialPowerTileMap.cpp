// WorldBuilder 0x01260230 uses integer loop counters and independent point
// locals in the FX and tiling scopes. Those native lifetimes reproduce the
// full body without scheduling intrinsics. Original entry spelling remains
// unproved; target offsets and callees are independently read from native.
// cl: /I. /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x004C4621, 377B: CloudBreakSpecialPower::rva004C4621 (name pinned:
// the member called with the location, ret 4; the location is not read).
// Target evidence: the map extent comes from TheTerrainLogic slot 0x20; the
// module data FX (+0x80) plays at the map centre on the ground (slot 0x18
// ground height), then, when the spacing (+0x88) exceeds 1, the whole map is
// tiled at that spacing inside a one-spacing border, each grid coordinate
// truncated to a whole unit, creating the object named at +0x84 on the
// ground at every point through the 0x004C45CF helper (rowed as a stdcall
// body; retail loads ECX with this before calling it, so it is called here
// through a thiscall placeholder spelling pinned to the same body).

typedef float Real;
typedef int Int;

#include "Code/Libraries/Include/Lib/Coord3D.h"

#include "../../../../../Libraries/Include/Lib/Region3D.h"

class AsciiString;
class Matrix3D;

class FXList
{
public:
	static void doFXPos( const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx = 0, const float primarySpeed = 0.0f, const Coord3D *secondary = 0 );
};

class ThingTemplate;
class Matrix3D;
struct Coord3D;
struct Region3D;
class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual float getGroundHeight( float x, float y, Coord3D *normal ) const;
	virtual void v07();
	virtual void getExtent( Region3D *extent ) const;
	void addTree(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva00280176(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva0027D3D9(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva0027F28E(const Coord3D *loc, float radius, int flag);
	void rva0027D1A4(const Coord3D *loc, float radius, int flag);
};

extern TerrainLogic *TheTerrainLogic;

struct CloudBreakSpecialPowerModuleData
{
	unsigned char m_pad00[0x80];
	const FXList *m_fx;
	unsigned char m_objectName[4];
	Real m_spacing;
};

class Thing;
class ModuleData;
class Object;
enum NameKeyType;
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );

	// Public: the rowed dtor at 0x00493DEF is ??1SpecialPowerModule@@UAE@XZ.
	virtual ~SpecialPowerModule();
protected:
	unsigned char m_pad14[0x34 - 0x14];
};

class CloudBreakSpecialPower : public SpecialPowerModule
{
public:
	CloudBreakSpecialPower( Thing *thing, const ModuleData *moduleData );
	virtual NameKeyType getModuleNameKey() const;

	void rva004C4582();

	void rva004C4621(const Coord3D *position);
	void rva004C45CF(const Coord3D *position, const AsciiString *name);

protected:
	virtual ~CloudBreakSpecialPower();
};

void CloudBreakSpecialPower::rva004C4621( const Coord3D * )
{
	const CloudBreakSpecialPowerModuleData *data = (const CloudBreakSpecialPowerModuleData *)m_moduleData;
	Region3D extent;
	TheTerrainLogic->getExtent( &extent );

	if( data->m_fx )
	{
		Coord3D pos;
		pos.x = ( extent.lo.x + extent.hi.x ) * 0.5f;
		pos.y = ( extent.lo.y + extent.hi.y ) * 0.5f;
		pos.z = TheTerrainLogic->getGroundHeight( pos.x, pos.y, 0 );
		FXList::doFXPos( data->m_fx, &pos );
	}

	Real spacing = data->m_spacing;
	if( spacing > 1.0f )
	{
		for( Int y = (Int)( extent.lo.y + spacing ); y < extent.hi.y - spacing; y = (Int)( y + spacing ) )
		{
			for( Int x = (Int)( extent.lo.x + spacing ); x < extent.hi.x - spacing; x = (Int)( x + spacing ) )
			{
				Coord3D pos;
				pos.x = (Real)x;
				pos.y = (Real)y;
				pos.z = TheTerrainLogic->getGroundHeight( pos.x, pos.y, 0 );
				rva004C45CF( &pos, (const AsciiString *)data->m_objectName );
			}
		}
	}
}
