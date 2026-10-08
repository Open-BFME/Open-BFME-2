// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00456A49, 470B: BridgeBehavior::resolveFX.
// Body: Zero Hour's resolveFX (GeneralsMD GameEngine/Source/GameLogic/Object/
// Behavior/BridgeBehavior.cpp). Target evidence: the bridge is found through
// TerrainLogic slot 0xA4 from the object at this+8, the template through
// TheTerrainRoads->findBridge (0x002DB4DA), and the four name getters
// (getDamageToOCLString 0x002DACF4 and the address-named damage-FX,
// repaired-OCL and repaired-FX getters 0x00456725/0x0045674D/0x00456774)
// feed TheObjectCreationListStore / TheFXListStore lookups, ending with the
// resolved flag at +0xFC. BFME 2 deltas: four body states by three effects,
// the OCL/FX tables at +0x3C/+0x6C/+0x9C/+0xCC, and no sound resolution.

#include "ascii_string.h"

typedef int Int;

enum BodyDamageType
{
	BODY_PRISTINE = 0
};

struct Coord3D;
class ObjectCreationList;
class FXList;

class Object
{
public:
	const Coord3D *getPosition() const { return (const Coord3D *)m_pos; }
	unsigned char m_pad00[0x38];
	unsigned char m_pos[12];
};

class TerrainRoadType
{
public:
	AsciiString getDamageToOCLString(BodyDamageType state, Int index);
};

// Address-named TerrainRoadType name getters (ZH getDamageToFXString,
// getRepairedToOCLString and getRepairedToFXString).
class Rva00456725
{
public:
	AsciiString rva00456725(Int state, Int index);
};

class Rva0045674D
{
public:
	AsciiString rva0045674D(Int state, Int index);
};

class Rva00456774
{
public:
	AsciiString rva00456774(Int state, Int index);
};

struct Rva002DB4DANode;

// TheTerrainRoads->findBridge.
struct Rva002DB4DA
{
	Rva002DB4DANode *rva002DB4DA(AsciiString name);
};

extern Rva002DB4DA *TheTerrainRoads;

class Bridge
{
public:
	AsciiString rva000AF1DD() const;
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v0a();
	virtual void v0b();
	virtual void v0c();
	virtual void v0d();
	virtual void v0e();
	virtual void v0f();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v1a();
	virtual void v1b();
	virtual void v1c();
	virtual void v1d();
	virtual void v1e();
	virtual void v1f();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual Bridge *findBridgeAt(const Coord3D *loc) const;
};

extern TerrainLogic *TheTerrainLogic;

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList(const char *name) const;
};

extern ObjectCreationListStore *TheObjectCreationListStore;

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};

extern FXListStore *TheFXListStore;

enum
{
	BODYDAMAGETYPE_COUNT = 4,
	MAX_BRIDGE_BODY_FX = 3
};

class BridgeBehavior
{
protected:
	void resolveFX();
	Object *getObject() const { return m_object; }

private:
	void *m_vtable;
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x3C - 0x0C];
	const ObjectCreationList *m_damageToOCL[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	const FXList *m_damageToFX[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	const ObjectCreationList *m_repairToOCL[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	const FXList *m_repairToFX[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	bool m_fxResolved;
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeBehavior::resolveFX( void )
{
	Object *us = getObject();
	Bridge *bridge = TheTerrainLogic->findBridgeAt( us->getPosition() );

	// sanity
	if( bridge == 0 )
		return;

	// get the bridge template name
	AsciiString bridgeTemplateName = bridge->rva000AF1DD();

	// find the bridge template
	TerrainRoadType *bridgeTemplate = (TerrainRoadType *)TheTerrainRoads->rva002DB4DA( bridgeTemplateName );

	// sanity
	if( bridgeTemplate == 0 )
		return;

	AsciiString name;
	for( Int bodyState = BODY_PRISTINE; bodyState < BODYDAMAGETYPE_COUNT; ++bodyState )
	{

		// initialize the fx and ocl lists
		for( Int i = 0; i < MAX_BRIDGE_BODY_FX; ++i )
		{

			name = bridgeTemplate->getDamageToOCLString( (BodyDamageType)bodyState, i );
			m_damageToOCL[ bodyState ][ i ] = TheObjectCreationListStore->findObjectCreationList( name.str() );

			name = ((Rva00456725 *)bridgeTemplate)->rva00456725( bodyState, i );
			m_damageToFX[ bodyState ][ i ] = TheFXListStore->findFXList( name.str() );

			name = ((Rva0045674D *)bridgeTemplate)->rva0045674D( bodyState, i );
			m_repairToOCL[ bodyState ][ i ] = TheObjectCreationListStore->findObjectCreationList( name.str() );

			name = ((Rva00456774 *)bridgeTemplate)->rva00456774( bodyState, i );
			m_repairToFX[ bodyState ][ i ] = TheFXListStore->findFXList( name.str() );

		}  // end for i

	}  // end for, bodyState

	// fx are now "resolved"
	m_fxResolved = true;

}  // end resolveFX
