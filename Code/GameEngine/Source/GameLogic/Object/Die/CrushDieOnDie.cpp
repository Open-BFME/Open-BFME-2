// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0048619A (327B) crushLocationCheck and 0x00486327 (387B)
// CrushDie::onDie.
// Bodies: Zero Hour's CrushDie.cpp (GeneralsMD GameEngine/Source/GameLogic/
// Object/Die/CrushDie.cpp); the BFME 1 port of the static helper is
// reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Die/
// crushLocationCheck_Thunk.cpp. The helper is file-static: retail calls it
// with the crusher in EBX and the victim in EAX (the compiler's custom
// convention for a local function), returning the CrushEnum in EAX.
// BFME 2 target evidence: body module Object+0x254 (getFrontCrushed/
// getBackCrushed slots 0x4C/0x50, setFrontCrushed/setBackCrushed 0x60/0x64),
// template geometry major radius Object+0xB8, position +0x38, id +0x74;
// onDie is entered through the DieModuleInterface at +0x10 (isDieApplicable
// on this-0x10, module data this-0x0C, object this-0x08); crush damage is
// type 1; module data crush sound references +0x38 and percentages +0x48
// (indexed by CrushEnum); GameLogicRandomValue carries retail's
// CrushDie.cpp __FILE__ and line 167; the audio event is the shared
// BfmeAudioEventPrefix136 view; the new 0x4C condition flags are zeroed
// inline and set through 0x000B3FA5, the clear mask built by 0x001E4912,
// and both applied with Object 0x0028CFB2.

#include <string.h>
#include "Common/BfmeAudioEventPrefix136.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

#define CRUSHDIE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Die\\CrushDie.cpp"

Int GetGameLogicRandomValue( Int lo, Int hi, char *file, Int line );

#include "../../../Common/GameLogicObjectLookupView.h"

enum DamageType
{
	DAMAGE_CRUSH = 1
};

enum CrushEnum
{
	TOTAL_CRUSH,
	BACK_END_CRUSH,
	FRONT_END_CRUSH,
	NO_CRUSH,

	CRUSH_COUNT
};

enum
{
	MODELCONDITION_FRONTCRUSHED = 1,
	MODELCONDITION_BACKCRUSHED = 2
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class DamageInfo
{
public:
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID;
	unsigned char m_pad0C[0x10 - 0x0C];
	DamageType m_damageType;
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual Bool getFrontCrushed() const = 0;
	virtual Bool getBackCrushed() const = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void setFrontCrushed( Bool v ) = 0;
	virtual void setBackCrushed( Bool v ) = 0;
};

class GeometryInfo
{
public:
	Real getMajorRadius() const { return m_majorRadius; }
	unsigned char m_pad00[0x10];
	Real m_majorRadius;
};

// ModelConditionFlags view (0x4C bytes); set( bit, value ) is 0x000B3FA5.
class ModelConditionFlags
{
public:
	ModelConditionFlags() { memset( m_bits, 0, sizeof( m_bits ) ); }
	void rva000B3FA5( Int bit, Int value );
	unsigned int m_bits[ 0x4C / 4 ];
};

// MAKE_MODELCONDITION_MASK2 worker, address-named as rowed.
class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912( int a, unsigned int b, unsigned int c );
	unsigned int m_bits[ 0x4C / 4 ];
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};

class Object : public Thing
{
public:
	BodyModuleInterface *getBodyModule() const { return m_body; }
	const Coord3D *getPosition() const { return &m_pos; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	ObjectID getID() const { return m_id; }
	void rva0028CFB2( const int *clr, const int *set );
	unsigned char m_pad00[0x38];
	Coord3D m_pos;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_pad78[0xA8 - 0x78];
	GeometryInfo m_geometryInfo;
	unsigned char m_padBC[0x254 - 0xBC];
	BodyModuleInterface *m_body;
};

extern GameLogic *TheGameLogic;

class AudioManager
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual int addAudioEvent( const BfmeAudioEventPrefix136 *event );
};

extern AudioManager *TheAudio;

// The audio event's object-id setter, address-named as rowed.
class Rva002D9531
{
public:
	void rva002D9531( int value );
};

struct CrushDieModuleData
{
	unsigned char m_pad00[0x38];
	OpaqueRefElement4 m_crushSounds[ CRUSH_COUNT ];
	Int m_crushSoundPercent[ CRUSH_COUNT ];
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	Object *getObject() const { return m_object; }
	const CrushDieModuleData *getCrushDieModuleData() const { return m_moduleData; }
private:
	const CrushDieModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x10 - 0x0C];
};

class DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
};

class DieModule : public BehaviorModule, public DieModuleInterface
{
protected:
	Bool isDieApplicable( const DamageInfo *damageInfo ) const;
};

class CrushDie : public DieModule
{
public:
	virtual void onDie( const DamageInfo *damageInfo );
};

//-------------------------------------------------------------------------------------------------
// Figure out which crush point was hit so the correct crushed object can be swapped in
//-------------------------------------------------------------------------------------------------
static CrushEnum crushLocationCheck( Object* crusherObject, Object* victimObject )
{
	if( (crusherObject == 0)  ||  (victimObject == 0) )
		return NO_CRUSH;

	Bool frontCrushed = victimObject->getBodyModule()->getFrontCrushed();
	Bool backCrushed = victimObject->getBodyModule()->getBackCrushed();
	const Coord3D *otherDir = victimObject->getUnitDirectionVector2D();
	const Coord3D *pos = crusherObject->getPosition();
	const Coord3D *otherPos = victimObject->getPosition();

	Real crushPointOffsetDistance = victimObject->getGeometryInfo().getMajorRadius() * 0.5;
	Coord3D crushPointOffset;
	crushPointOffset.x = otherDir->x * crushPointOffsetDistance;
	crushPointOffset.y = otherDir->y * crushPointOffsetDistance;
	crushPointOffset.z = 0;

	Coord3D comparisonCoord;
	Real dx, dy;
	CrushEnum retval = NO_CRUSH;
	Real bestDist = 99999;

	// PhysicsCollide has already done the logic of which point to smoosh and waited until we crossed that point
	// so at this point we just need to know which crush point is closest.
	if( !frontCrushed && !backCrushed )
	{
		// Check the middle crush point
		comparisonCoord = *otherPos;//copy so can move to each crush point
		dx = comparisonCoord.x - pos->x;
		dy = comparisonCoord.y - pos->y;
		Real dist = (Real)( dx*dx + dy*dy );
		//otherwise we want to make sure we get the closest valid crush point
		retval = TOTAL_CRUSH;
		bestDist = dist;
	}

	if( !frontCrushed )
	{
		// Check the front point.
		comparisonCoord = *otherPos;
		comparisonCoord.x += crushPointOffset.x;
		comparisonCoord.y += crushPointOffset.y;
		dx = comparisonCoord.x - pos->x;
		dy = comparisonCoord.y - pos->y;
		Real dist = (Real)( dx*dx + dy*dy );
		if( dist < bestDist )//closer
		{
			if( backCrushed )
			{
				retval = TOTAL_CRUSH;
				bestDist = dist;
			}
			else
			{
				retval = FRONT_END_CRUSH;
				bestDist = dist;
			}
		}
	}

	if( !backCrushed )
	{
		// Check back point
		comparisonCoord = *otherPos;
		comparisonCoord.x -= crushPointOffset.x;
		comparisonCoord.y -= crushPointOffset.y;
		dx = comparisonCoord.x - pos->x;
		dy = comparisonCoord.y - pos->y;
		Real dist = (Real)( dx*dx + dy*dy );
		if( dist < bestDist )//closer
		{
			if( frontCrushed )
			{
				retval = TOTAL_CRUSH;
				bestDist = dist;
			}
			else
			{
				retval = BACK_END_CRUSH;
				bestDist = dist;
			}
		}
	}

	return retval;
}

//-------------------------------------------------------------------------------------------------
/** The die callback. */
//-------------------------------------------------------------------------------------------------
void CrushDie::onDie( const DamageInfo * damageInfo )
{
	if (!isDieApplicable(damageInfo))
		return;

	if (damageInfo->m_damageType != DAMAGE_CRUSH)
		return;

	Object *damageDealer = TheGameLogic->findObjectByID( damageInfo->m_sourceID );

	CrushEnum crushType = damageDealer ? crushLocationCheck(damageDealer, getObject()) : TOTAL_CRUSH;

	if (crushType != NO_CRUSH)
	{
		if (getCrushDieModuleData()->m_crushSounds[crushType].referent != 0)
		{
			// be sure that 0==never, 100==always
			if (GetGameLogicRandomValue(0, 99, CRUSHDIE_FILE, 167) < getCrushDieModuleData()->m_crushSoundPercent[crushType])
			{
				BfmeAudioEventPrefix136 crushSound(getCrushDieModuleData()->m_crushSounds[crushType], 0);
				reinterpret_cast<Rva002D9531 *>(&crushSound)->rva002D9531(getObject()->getID());
				TheAudio->addAudioEvent(&crushSound);
			}
		}

		{
			Object *me = getObject();
			if (me)
			{
				me->getBodyModule()->setFrontCrushed(crushType == TOTAL_CRUSH || crushType == FRONT_END_CRUSH);
				me->getBodyModule()->setBackCrushed(crushType == TOTAL_CRUSH || crushType == BACK_END_CRUSH);

				ModelConditionFlags newCrushed;
				newCrushed.rva000B3FA5(MODELCONDITION_FRONTCRUSHED, (crushType == TOTAL_CRUSH || crushType == FRONT_END_CRUSH));
				newCrushed.rva000B3FA5(MODELCONDITION_BACKCRUSHED, crushType == TOTAL_CRUSH || crushType == BACK_END_CRUSH);
				Rva001E4912 clearMask;
				me->rva0028CFB2(
					(const int *)clearMask.rva001E4912(0, MODELCONDITION_BACKCRUSHED, MODELCONDITION_FRONTCRUSHED),
					(const int *)&newCrushed);
			}
		}
	}
}
