// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?rva004C3B17@ElvenWoodSpecialPower@@QAEXPBUCoord3D@@@Z
// Retail 0x004C3B17..0x004C3C36 (287 bytes): ElvenWoodSpecialPower's
// location member (ret 4; WorldBuilder twin 0x0125E7C0 by callgraph score
// 2.0 calls ElvenWoodSpecialPower::addObject 0x0125EB20 = retail 0x004C397F).
// Same shape as TaintSpecialPower::rva004C49AE (0x004C49AE): clear
// (0x0027F28E) and refresh (0x0027D1A4 at radius + 50) the terrain area
// with flag 2; play the module data's FX (+0x94) and OCL (+0x98 on a copy
// of the location); add the wood object named at +0x88; give it status
// 0x54 (Object::setStatus 0x0023DB0E); then paint TheTaintManager
// (0x006C0AB0): radius x 1.25 at 0x80 for everyone and when the object
// exists the plain radius at 0xFF for its id (+0x74). Radius is +0x90.

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

enum ObjectStatusTypes
{
	OBJECT_STATUS_0x54 = 0x54
};

class Object
{
public:
	void setStatus( ObjectStatusTypes status, bool set );
	unsigned char m_pad00[0x74];
	int m_id;
};

class TerrainLogic
{
public:
	void rva0027F28E( const Coord3D *loc, Real radius, int flag );
	void rva0027D1A4( const Coord3D *loc, Real radius, int flag );
};

extern TerrainLogic *TheTerrainLogic;

class BfmeTaintManager
{
public:
	void bfmeApplyCircleWorld( const BfmePointFC *point, Real radius, int amount, bool absolute, int owner );
};

extern BfmeTaintManager *TheTaintManager;

struct ElvenWoodSpecialPowerModuleData
{
	unsigned char m_pad00[0x88];
	unsigned char m_objectName[8];
	Real m_radius;						// +0x90
	FXList *m_fx;						// +0x94
	ObjectCreationList *m_ocl;				// +0x98
};

class ElvenWoodSpecialPower
{
public:
	void rva004C3B17( const Coord3D *loc );
	Object *addObject( const Coord3D *loc, const AsciiString *name );	// 0x004C397F
private:
	void *m_vtable;
	ElvenWoodSpecialPowerModuleData *m_moduleData;
	Object *m_object;
};

void ElvenWoodSpecialPower::rva004C3B17( const Coord3D *loc )
{
	ElvenWoodSpecialPowerModuleData *data = m_moduleData;
	Real radius = data->m_radius;
	Object *owner = m_object;

	TheTerrainLogic->rva0027F28E( loc, radius, 2 );
	TheTerrainLogic->rva0027D1A4( loc, radius + 50.0f, 2 );

	if( data->m_fx )
		FXList::doFXPos( data->m_fx, loc );

	ObjectCreationList *ocl = data->m_ocl;
	if( ocl )
	{
		Coord3D oclPoint;
		oclPoint.x = loc->x;
		oclPoint.y = loc->y;
		oclPoint.z = loc->z;
		ocl->create( owner, &oclPoint, 0, 0 );
	}

	Object *wood = addObject( loc, (const AsciiString *)data->m_objectName );
	if( wood )
		wood->setStatus( OBJECT_STATUS_0x54, true );
	TheTaintManager->bfmeApplyCircleWorld( (const BfmePointFC *)loc, radius * 1.25f, 0x80, true, -1 );
	if( wood )
		TheTaintManager->bfmeApplyCircleWorld( (const BfmePointFC *)loc, radius, 0xff, true, wood->m_id );
}
