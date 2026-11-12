// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common
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

#include "ascii_string.h"
#include "Lib/Coord3D.h"

typedef unsigned int UnsignedInt;

class Matrix3D;

Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, int line);
#define GameLogicRandomValueReal(lo, hi) GetGameLogicRandomValueReal((lo), (hi), __FILE__, __LINE__)

#include "../../../../Include/GameClient/TerrainRoadType.h"

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
	void *m_vtable;
	Bridge *m_next;
	AsciiString m_templateName;
	BridgeInfo m_bridgeInfo;
};

#include "../../../../Include/Common/TerrainType.h"

#include "../../../../Include/GameClient/TerrainRoadCollection.h"
extern TerrainRoadCollection *TheTerrainRoads;

#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Object
{
public:
	const Coord3D *getPosition(void) const { return &m_pos; }
	bool getSingleLogicalBonePosition(const char *boneName, Coord3D *position, Matrix3D *transform) const;

private:
	unsigned char m_unmodelled00[0x38];
	Coord3D m_pos;
};

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary,
		const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary);
};

#include "../../../../Include/GameLogic/ObjectCreationListClass.h"

struct TimeAndLocationInfo
{
	UnsignedInt delay;
	AsciiString boneName;
};

// STLport list<BridgeFXInfo> / list<BridgeOCLInfo> nodes: next, prev, value.
struct BridgeFXNode
{
	BridgeFXNode *next;
	BridgeFXNode *prev;
	const FXList *fx;
	TimeAndLocationInfo timeAndLocationInfo;
};

struct BridgeOCLNode
{
	BridgeOCLNode *next;
	BridgeOCLNode *prev;
	const ObjectCreationList *ocl;
	TimeAndLocationInfo timeAndLocationInfo;
};

class BridgeBehaviorModuleData
{
public:
	unsigned char m_unmodelled00[0x10];
	BridgeFXNode *m_fx;
	BridgeOCLNode *m_ocl;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class BridgeBehavior : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();

protected:
	const BridgeBehaviorModuleData *getBridgeBehaviorModuleData(void) const { return reinterpret_cast<const BridgeBehaviorModuleData *>(getModuleData()); }

	void getRandomSurfacePosition(TerrainRoadType *bridgeTemplate,
		const BridgeInfo *bridgeInfo, Coord3D *pos);
	void doAreaEffects(TerrainRoadType *bridgeTemplate, Bridge *bridge,
		const ObjectCreationList *ocl, const FXList *fx);

private:
	unsigned char m_unmodelled14[0x104 - 0x14];
	UnsignedInt m_deathFrame;
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

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
UpdateSleepTime BridgeBehavior::update( void )
{

	// if we're dead, we need to possibly throw off some effects
	if( m_deathFrame != 0 )
	{
		AsciiString boneName;

		// get object
		Object *us = getObject();

		// get module data
		const BridgeBehaviorModuleData *modData = getBridgeBehaviorModuleData();

		// get bridge information
		Bridge *bridge = TheTerrainLogic->findBridgeAt( us->getPosition() );
		const BridgeInfo *bridgeInfo = 0;
		TerrainRoadType *bridgeTemplate = 0;
		if ( bridge )
		{

			// get bridge info
			bridgeInfo = bridge->peekBridgeInfo();

			// get the bridge template info
			// ZH: bridge->getBridgeTemplateName(), which copies m_templateName (+8).
			// Retail calls its ICF-folded 27B body 0x000AF1DD (the dup_000af1dd
			// row); the REL32 resolver knows that body only by the admitted
			// TerrainType::getTexture pin, the spelling Rva003967A5Notify.cpp
			// uses for the same fold.
			AsciiString bridgeTemplateName = ((const TerrainType *)bridge)->getTexture();
			bridgeTemplate = TheTerrainRoads->findBridge( bridgeTemplateName );

		}

		// how much time has passed between now and our destruction frame
		UnsignedInt deathTime = TheGameLogic->getFrame() - m_deathFrame;

		// see if there are any fx visuals we need to execute
		BridgeFXNode *fxIt;
		for( fxIt = modData->m_fx->next; fxIt != modData->m_fx; fxIt = fxIt->next )
		{

			// we'll launch an fx list if our death time is equal to exactly the delay
			// we're waiting for to launch the list
			if( deathTime == fxIt->timeAndLocationInfo.delay )
			{
				Coord3D pos;

				// if a bone name is present, we'll use the bone position, otherwise we'll pick a
				// spot somewhere on the bridge surface
				boneName = fxIt->timeAndLocationInfo.boneName;
				if( boneName.isEmpty() == false )
					us->getSingleLogicalBonePosition( boneName.str(), &pos, 0 );
				else if ( bridge && bridgeTemplate && bridgeInfo )
					getRandomSurfacePosition( bridgeTemplate, bridgeInfo, &pos );
				else
				{
					pos.x = getObject()->getPosition()->x;
					pos.y = getObject()->getPosition()->y;
					pos.z = getObject()->getPosition()->z;
				}

				// launch the fx list
				FXList::doFXPos( fxIt->fx, &pos, 0, 0.0f, 0 );

			}  // end if

		}  // end for, fxIt

		// see if there are any ocl visuals we need to execute
		BridgeOCLNode *oclIt;
		for( oclIt = modData->m_ocl->next; oclIt != modData->m_ocl; oclIt = oclIt->next )
		{

			// we'll launch an ocl list if our death time is equal to exactly the delay
			// we're waiting for to launch the list
			if( deathTime == oclIt->timeAndLocationInfo.delay )
			{
				Coord3D pos;

				boneName = oclIt->timeAndLocationInfo.boneName;
				if( boneName.isEmpty() == false )
				{

					// special case for creating an OCL using the bridge object parent center location
					if( boneName.compare( "ParentObject" ) == 0 )
					{
						if( oclIt->ocl )
							const_cast<ObjectCreationList *>( oclIt->ocl )->create( us, 0, 0 );
						continue;
					}

					// get bone position
					us->getSingleLogicalBonePosition( boneName.str(), &pos, 0 );

				}  // end if, bone name not empty
				else if ( bridge && bridgeTemplate && bridgeInfo )
					getRandomSurfacePosition( bridgeTemplate, bridgeInfo, &pos );
				else
				{
					pos.x = getObject()->getPosition()->x;
					pos.y = getObject()->getPosition()->y;
					pos.z = getObject()->getPosition()->z;
				}

				// launch the ocl
				if( oclIt->ocl )
					const_cast<ObjectCreationList *>( oclIt->ocl )->create( us, &pos, 0, 0 );

			}  // end if

		}  // end for, oclIt

	}  // end if

	return UPDATE_SLEEP_NONE;

}  // end update
