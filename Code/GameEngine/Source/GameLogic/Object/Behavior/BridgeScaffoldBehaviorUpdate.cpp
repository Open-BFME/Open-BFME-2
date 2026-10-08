// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00458422, 534B: BridgeScaffoldBehavior::update, entered through
// the UpdateModuleInterface subobject at BridgeScaffoldBehavior+0x10 (object
// this-0x08; BridgeScaffoldBehaviorInterface at +0x20 whose slot 1 is
// setMotion; target motion +0x24, create/rise/build positions +0x28/+0x34/
// +0x40, lateral/vertical speeds +0x4C/+0x50, target position +0x54).
// Body: Zero Hour's update (GeneralsMD GameEngine/Source/GameLogic/Object/
// Behavior/BridgeScaffoldBehavior.cpp); the BFME 1 port
// (reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Behavior/
// BridgeScaffoldBehavior.cpp) is the same source. Coord3D::normalize/length
// are the out-of-line 0x000035B6/0x00003571, the sink case destroys the
// object through GameLogic::destroyObject 0x00242C09 and the new position is
// set with Thing::setPosition 0x0030AA80.

typedef float Real;

// class-gate: allow Coord3D the canonical data-only header cannot declare ZH's inline set(const Coord3D *) that update copies the direction through (explicit member copies compile to 529B, set() to retail's 534B); normalize/length stay the out-of-line 0x000035B6/0x00003571; same three floats
struct Coord3D
{
	Real x;
	Real y;
	Real z;
	Real length() const;
	void normalize();
	void set( const Coord3D *other ) { x = other->x; y = other->y; z = other->z; }
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum ScaffoldTargetMotion
{
	STM_STILL,
	STM_RISE,
	STM_BUILD_ACROSS,
	STM_TEAR_DOWN_ACROSS,
	STM_SINK
};

class Thing
{
public:
	void setPosition( const Coord3D *pos );
};

class Object : public Thing
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	unsigned char m_pad00[0x38];
	Coord3D m_pos;
};

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	Object *getObject() const { return m_object; }
private:
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x10 - 0x0C];
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	unsigned char m_pad14[0x20 - 0x14];
};

class BridgeScaffoldBehaviorInterface
{
public:
	virtual void setPositions( const Coord3D *createPos, const Coord3D *riseToPos, const Coord3D *buildPos ) = 0;
	virtual void setMotion( ScaffoldTargetMotion targetMotion ) = 0;
};

class BridgeScaffoldBehavior : public UpdateModule, public BridgeScaffoldBehaviorInterface
{
public:
	virtual void setPositions( const Coord3D *createPos, const Coord3D *riseToPos, const Coord3D *buildPos );
	virtual void setMotion( ScaffoldTargetMotion targetMotion );
	virtual UpdateSleepTime update();

private:
	ScaffoldTargetMotion m_targetMotion;
	Coord3D m_createPos;
	Coord3D m_riseToPos;
	Coord3D m_buildPos;
	Real m_lateralSpeed;
	Real m_verticalSpeed;
	Coord3D m_targetPos;
};

// ------------------------------------------------------------------------------------------------
/** The update method */
// ------------------------------------------------------------------------------------------------
UpdateSleepTime BridgeScaffoldBehavior::update( void )
{

	// do nothing if we're not in motion
	if( m_targetMotion == STM_STILL )
		return UPDATE_SLEEP_NONE;

	// get our info
	Object *us = getObject();
	const Coord3D *ourPos = us->getPosition();

	// compute direction vector from our position to the target position
	Coord3D dirV;
	dirV.x = m_targetPos.x - ourPos->x;
	dirV.y = m_targetPos.y - ourPos->y;
	dirV.z = m_targetPos.z - ourPos->z;

	// use normalized direction vector "v" to do the pulling movement
	Coord3D v;
	v.set( &dirV );
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

			case STM_RISE: setMotion( STM_BUILD_ACROSS ); break;
			case STM_BUILD_ACROSS: setMotion( STM_STILL ); break;
			case STM_TEAR_DOWN_ACROSS: setMotion( STM_SINK ); break;

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
