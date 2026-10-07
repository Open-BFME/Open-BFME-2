// ?update@BridgeScaffoldBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9 date=2026-10-07
// Banked BFME1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20 reconstruction.
// Original donor: game/GameEngine/Source/GameLogic/Object/Behavior/BridgeScaffoldBehavior.cpp.
// Target facts: ctor45831C has UpdateModule size20 and scaffold interface+20;
// native update receives update interface+10, reads Object at this-8, motion+14,
// create/rise/build+18/+24/+30, speeds+3C/+40 and target+44. Object position+38,
// Coord3D normalize35B6/length3571, sink destruction242C09 and Thing setPosition30AA80.
// Needed canonical API declarations: Coord3D::normalize and length()const,
// already matched providers (86/69 bytes). Full donor caller is exact534 but
// its generated normalize COMDAT is wrong; this minimal unit emits no such copy.
// This body529: min-speed/speed XMM colour and later expression shape differ.
// v's explicit fields preserve native initial store shape; late assignment is
// native's three MOVSD block copy. Unknown full class fields remain unasserted.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
#include "Coord3D.h"
typedef float Real;
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };
enum ScaffoldTargetMotion { STM_STILL,STM_RISE,STM_BUILD_ACROSS,STM_TEAR_DOWN_ACROSS,STM_SINK };
class Thing { public: void setPosition(const Coord3D *); };
class Object : public Thing {};
class GameLogic { public: void destroyObject(Object *); };
extern GameLogic *TheGameLogic;
class ScaffoldMotionInterface { public: virtual void slot0(); virtual void setMotion(ScaffoldTargetMotion); };
class BridgeScaffoldBehavior { public:
 virtual UpdateSleepTime update();
 char pad04[0xc];
 ScaffoldMotionInterface m_motionInterface;
 ScaffoldTargetMotion m_targetMotion;
 Coord3D m_createPos,m_riseToPos,m_buildPos;
 float m_lateralSpeed,m_verticalSpeed;
 Coord3D m_targetPos;
};
UpdateSleepTime BridgeScaffoldBehavior::update( void )
{

	// do nothing if we're not in motion
	if( m_targetMotion == STM_STILL )
		return UPDATE_SLEEP_NONE;

	// get our info
	Object *us = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8);
	const Coord3D *ourPos = reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(us) + 0x38);

	// compute direction vector from our position to the target position
	Coord3D dirV;
	dirV.x = m_targetPos.x - ourPos->x;
	dirV.y = m_targetPos.y - ourPos->y;
	dirV.z = m_targetPos.z - ourPos->z;

	// use normalized direction vector "v" to do the pulling movement
	Coord3D v;
	v.x = dirV.x; v.y = dirV.y; v.z = dirV.z;
	v.normalize();

	// depending on our motion type, we move at different speeds
	Real topSpeed = 1.0f;
	Coord3D *start, *end;
	switch( m_targetMotion )
	{

		case STM_RISE:
			topSpeed = m_verticalSpeed;
			start = &m_createPos;
			end = &m_riseToPos;
			break;

		case STM_SINK:
			topSpeed = m_verticalSpeed;
			start = &m_riseToPos;
			end = &m_createPos;
			break;

		case STM_BUILD_ACROSS:
			topSpeed = m_lateralSpeed;
			start = &m_riseToPos;
			end = &m_buildPos;
			break;

		case STM_TEAR_DOWN_ACROSS:
			topSpeed = m_lateralSpeed;
			start = &m_buildPos;
			end = &m_riseToPos;
			break;

		default:
			return UPDATE_SLEEP_NONE;

	}  // end switch

	// adjust speed so it's slower at the end of motion
	Coord3D speedVector;
	speedVector.x = end->x - start->x;
	speedVector.y = end->y - start->y;
	speedVector.z = end->z - start->z;
	Real totalDistance = speedVector.length() * 0.25f;
	speedVector.x = end->x - ourPos->x;
	speedVector.y = end->y - ourPos->y;
	speedVector.z = end->z - ourPos->z;
	Real ourDistance = speedVector.length();
	Real speed = (ourDistance / totalDistance) * topSpeed;
	Real minSpeed = topSpeed * 0.08f;
	if( speed < minSpeed )
		speed = minSpeed;
	if( speed > topSpeed )
		speed = topSpeed;

	//
	// make sure that speed can't get so incredibly small that we never finish our
	// movement no matter what the speed and distance are
	//
	if( speed < 0.001f )
		speed = 0.001f;

	// compute the new position given the speed
	Coord3D newPos;
	newPos.x = v.x * speed + ourPos->x;
	newPos.y = v.y * speed + ourPos->y;
	newPos.z = v.z * speed + ourPos->z;

	//
	// will this new position push us beyond our target destination, we will take the vector
	// from the new position to the destination and the vector from our current present position
	// tot he destination and dot them togehter ... if the result is < 0 then we have will
	// overshoot the distance if we use the new position
	//
	Coord3D tooFarVector;
	tooFarVector.x = m_targetPos.x - newPos.x;
	tooFarVector.y = m_targetPos.y - newPos.y;
	tooFarVector.z = m_targetPos.z - newPos.z;
	if( tooFarVector.x * dirV.x + tooFarVector.y * dirV.y + tooFarVector.z * dirV.z <= 0.0f )
	{

		// use the destination position
		newPos = m_targetPos;

		//
		// we have reached our target position, switch motion to the next position in 
		// the chain (which may be stay still and don't move anymore)
		//
		switch( m_targetMotion )
		{

			case STM_RISE: m_motionInterface.setMotion( STM_BUILD_ACROSS ); break;
			case STM_BUILD_ACROSS: m_motionInterface.setMotion( STM_STILL ); break;
			case STM_TEAR_DOWN_ACROSS: m_motionInterface.setMotion( STM_SINK ); break;

			case STM_SINK:
			{

				// we are done with a sinking motion, destroy the scaffold object as our job is done
				TheGameLogic->destroyObject( us );
				break;

			}  // end case

		}  // end switch

	}  // end if

	// set the new position
	us->setPosition( &newPos );

	// do not sleep
	return UPDATE_SLEEP_NONE;

}  // end update
