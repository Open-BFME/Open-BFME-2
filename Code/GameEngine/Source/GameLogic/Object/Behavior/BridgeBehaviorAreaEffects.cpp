// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /ICode/Libraries/Include
// BridgeBehavior::getRandomSurfacePosition (retail 0x004565BD, 360B) and
// BridgeBehavior::doAreaEffects (retail 0x0045685D, 143B), Zero Hour
// GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp bodies.
// Target facts: both are thiscall members (ret 0xC / ret 0x10) built /O1
// with an EBP frame; doAreaEffects calls 0x004565BD twice, the static
// FXList::doFXPos at 0x00094C29 and the OCL member at 0x001F0878. The random
// calls pass retail's __FILE__ string and lines 502/511/525, reproduced with
// #line. Offsets: BridgeInfo from/to corners at +0x1C/+0x28/+0x34 (ZH order),
// Bridge::peekBridgeInfo at bridge+0xC, TerrainRoadType transition-effects
// height +0x144 and FX-per-type count +0x148, owning Object at this+8.
// The minimal views keep only these witnessed offsets.

typedef float Real;
typedef int Int;

#include "Lib/Coord3D.h"

class Matrix3D;
class Object;

Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, int line);
#define GameLogicRandomValueReal(lo, hi) GetGameLogicRandomValueReal((lo), (hi), __FILE__, __LINE__)

class TerrainRoadType
{
public:
	Real getTransitionEffectsHeight(void) const { return m_transitionEffectsHeight; }
	Int getNumFXPerType(void) const { return m_numFXPerType; }

private:
	unsigned char m_unmodelled000[0x144];
	Real m_transitionEffectsHeight;
	Int m_numFXPerType;
};

class BridgeInfo
{
public:
	unsigned char m_unmodelled00[0x1C];
	Coord3D fromLeft;
	Coord3D fromRight;
	Coord3D toLeft;
};

class Bridge
{
public:
	const BridgeInfo *peekBridgeInfo(void) const { return &m_bridgeInfo; }

private:
	unsigned char m_unmodelled00[0xC];
	BridgeInfo m_bridgeInfo;
};

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary,
		const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary);
};

class ObjectCreationList
{
public:
	void create(void *primaryObject, void *primary, void *secondary, int lifetimeFrames);
};

class BridgeBehavior
{
public:
	Object *getObject(void) const { return m_object; }

protected:
	void getRandomSurfacePosition(TerrainRoadType *bridgeTemplate,
		const BridgeInfo *bridgeInfo, Coord3D *pos);
	void doAreaEffects(TerrainRoadType *bridgeTemplate, Bridge *bridge,
		const ObjectCreationList *ocl, const FXList *fx);

private:
	void *m_vtable;
	void *m_moduleData;
	Object *m_object;
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
#line 483 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Behavior\\BridgeBehavior.cpp"
void BridgeBehavior::getRandomSurfacePosition( TerrainRoadType *bridgeTemplate,
																							 const BridgeInfo *bridgeInfo,
																							 Coord3D *pos )
{

	// sanity
	if( bridgeInfo == 0 || pos == 0 )
		return;

	//
	// pick the spot by finding vectors along the edge of the bridge region, scaling
	// them and then adding them together
	//
	Real scale;

	Coord3D v1;
	v1.x = bridgeInfo->toLeft.x - bridgeInfo->fromLeft.x;
	v1.y = bridgeInfo->toLeft.y - bridgeInfo->fromLeft.y;
	v1.z = bridgeInfo->toLeft.z - bridgeInfo->fromLeft.z;
	scale = GameLogicRandomValueReal( 0.0f, 1.0f );
	v1.x *= scale;
	v1.y *= scale;
	v1.z *= scale;

	Coord3D v2;
	v2.x = bridgeInfo->fromRight.x - bridgeInfo->fromLeft.x;
	v2.y = bridgeInfo->fromRight.y - bridgeInfo->fromLeft.y;
	v2.z = bridgeInfo->fromRight.z - bridgeInfo->fromLeft.z;
	scale = GameLogicRandomValueReal( 0.0f, 1.0f );
	v2.x *= scale;
	v2.y *= scale;
	v2.z *= scale;

	// set the position
	pos->x = v1.x + v2.x + bridgeInfo->fromLeft.x;
	pos->y = v1.y + v2.y + bridgeInfo->fromLeft.y;
	pos->z = v1.z + v2.z + bridgeInfo->fromLeft.z;

	//
	// we now have a position picked, the last thing to do is add in an additional
	// Z component so that effects can be created in a "cube" area on and above the bridge
	//
	pos->z += GameLogicRandomValueReal( 0.0f, bridgeTemplate->getTransitionEffectsHeight() );

}  // end getRandomSurfacePosition

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeBehavior::doAreaEffects( TerrainRoadType *bridgeTemplate,
																		Bridge *bridge,
																		const ObjectCreationList *ocl,
																		const FXList *fx )
{

	// sanity
	if( bridge == 0 )
		return;

	// if no effects, don't bother
	if( ocl == 0 && fx == 0 )
		return;

	// get the bridge info
	const BridgeInfo *bridgeInfo = bridge->peekBridgeInfo();

	// how many effects of each type
	Int maxEffects = bridgeTemplate->getNumFXPerType();

	Coord3D pos;
	for( Int i = 0; i < maxEffects; ++i )
	{

		// do the fx
		if( fx )
		{

			// pick a position
			getRandomSurfacePosition( bridgeTemplate, bridgeInfo, &pos );

			// do the effect
			FXList::doFXPos( fx, &pos, 0, 0.0f, 0 );

		}  // end if

		// do the ocl
		if( ocl )
		{

			// pick a position
			getRandomSurfacePosition( bridgeTemplate, bridgeInfo, &pos );

			// do the ocl
			const_cast<ObjectCreationList *>( ocl )->create( getObject(), &pos, 0, 0 );

		}  // end if

	}  // end for i

}  // end doAreaEffects
