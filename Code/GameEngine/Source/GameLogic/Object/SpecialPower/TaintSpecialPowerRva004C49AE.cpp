// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x004C49AE, 266B: TaintSpecialPower::rva004C49AE (name pinned: the
// location member, ret 4, called on the primary this).
// Same role as BFME 1's TaintSpecialPower::after (reference/open-bfme-1/
// game/GameEngine/Source/GameLogic/Object/SpecialPower/
// TaintSpecialPowerAfter.cpp), without its object scans: clear (0x0027F28E)
// and refresh (0x0027D1A4, radius + 50) the terrain area around the
// location, play the taint FX (module data +0x84) and OCL (+0x88, on a copy
// of the location), add the taint object named at +0x7C (addObject
// 0x004C4940), then paint taint with TheTaintManager (0x006C0AB0): radius x
// 1.25 at amount 0x80 for everyone, and, when the object exists, the plain
// radius at amount 0 for its id. Radius is module data +0x80. The two
// terrain helpers are rowed as stdcall bodies that ignore ECX while every
// retail caller loads TheTerrainLogic into ECX first, so they are called
// here through thiscall placeholder spellings pinned to the same bodies.

typedef float Real;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

struct BfmePointFC;

class AsciiString;
class Matrix3D;

class FXList
{
public:
	static void doFXPos( const FXList *fx, const Coord3D *primary,
		const Matrix3D *primaryMtx = 0, const Real primarySpeed = 0.0f,
		const Coord3D *secondary = 0 );
};

class ObjectCreationList
{
public:
	void create( void *primaryObj, void *primary, void *secondary, int createOwner );
};

class Object
{
public:
	unsigned char m_pad00[0x74];
	int m_id;
};

class Rva004C49AETerrain
{
public:
	void rva0027F28E( const Coord3D *loc, Real radius, int flag );
	void rva0027D1A4( const Coord3D *loc, Real radius, int flag );
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

class BfmeTaintManager
{
public:
	void bfmeApplyCircleWorld( const BfmePointFC *point, Real radius, int amount, bool absolute, int owner );
};

extern BfmeTaintManager *TheTaintManager;

struct TaintSpecialPowerModuleData
{
	unsigned char m_pad00[0x7C];
	unsigned char m_taintObjectName[4];
	Real m_radius;
	FXList *m_taintFX;
	ObjectCreationList *m_taintOCL;
};

class TaintSpecialPower
{
public:
	void rva004C49AE( const Coord3D *loc );
	Object *addObject( const Coord3D *loc, const AsciiString &name );
private:
	void *m_vtable;
	TaintSpecialPowerModuleData *m_moduleData;
	Object *m_object;
};

void TaintSpecialPower::rva004C49AE( const Coord3D *loc )
{
	TaintSpecialPowerModuleData *data = m_moduleData;
	Real radius = data->m_radius;
	Object *owner = m_object;

	((Rva004C49AETerrain *)TheTerrainLogic)->rva0027F28E( loc, radius, 1 );
	((Rva004C49AETerrain *)TheTerrainLogic)->rva0027D1A4( loc, radius + 50.0f, 1 );

	if( data->m_taintFX )
		FXList::doFXPos( data->m_taintFX, loc );

	ObjectCreationList *ocl = data->m_taintOCL;
	if( ocl )
	{
		Coord3D oclPoint;
		oclPoint.x = loc->x;
		oclPoint.y = loc->y;
		oclPoint.z = loc->z;
		ocl->create( owner, &oclPoint, 0, 0 );
	}

	Object *taint = addObject( loc, *(const AsciiString *)data->m_taintObjectName );
	TheTaintManager->bfmeApplyCircleWorld( (const BfmePointFC *)loc, radius * 1.25f, 0x80, true, -1 );
	if( taint )
		TheTaintManager->bfmeApplyCircleWorld( (const BfmePointFC *)loc, radius, 0, true, taint->m_id );
}
