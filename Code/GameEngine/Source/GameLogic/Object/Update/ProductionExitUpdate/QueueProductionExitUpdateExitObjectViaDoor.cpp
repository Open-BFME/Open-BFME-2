// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// QueueProductionExitUpdate::exitObjectViaDoor (retail 0x004A0709, 1285 B),
// slot 2 of the ExitInterface vftable at 0x00851990 (this = ExitInterface at
// module +0x20, module data at this-0x1C, object at this-0x18). Zero Hour's
// body (GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/
// QueueProductionExitUpdate.cpp) is the donor for the create-point transform,
// the airborne test, the starting kick, the pathfind registration and the exit
// path; BFME 2 grows it, all read from retail:
//  - the airborne test skips water (TerrainLogic slot 19) and needs a 1.0
//    margin over the ground (slot 6);
//  - units whose AI answers slot 90 are created 250 higher and keep the rally
//    point without adjustDestination;
//  - the placement angle adds the module data's PlacementViewAngle (+0x2C,
//    named by the FieldParse table at 0x00BF1E48, like AllowAirborneCreation
//    +0x24, ExitDelay +0x20 and NoExitPath +0x30);
//  - the kick is the producer's direction (0x0030A8EE) scaled by its speed
//    (0x0028AC7D) into the new object's +0x25C behavior;
//  - a horde whose ID the module keeps at +0x40 (xfer'd by 0x004A0057) takes
//    each new member: setProducer, the +0x11C interface's assignSpotToUnit
//    (slot 11) and its team, then an exit path through the halfway point to
//    the formation spot that interface's slot 7 gives;
//  - a new horde (KindOf 109 HORDE by the name table at 0x009BBE18) becomes
//    that ID, UNSELECTABLE and UNDER_CONSTRUCTION (status names 3 and 2 at
//    0x009A5F30), and NoExitPath leaves the unit idle with IS_LEAVING_FACTORY
//    (status 90) cleared.

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include <vector>

// Declaration-only _Construct: retail's push_back calls the pinned out-of-line
// helper (0x002CA82C) instead of inlining the element copy (row 35 family-LK3).
namespace _STL {
template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &);
}

class Object;
class ThingTemplate;
class LocomotorSet;
class Team;

enum ObjectID
{
	INVALID_ID = 0
};

enum ExitDoorType
{
	DOOR_1 = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_UNSELECTABLE = 3,
	OBJECT_STATUS_IS_LEAVING_FACTORY = 90
};

enum DisabledType
{
	DISABLED_HELD = 3
};

#define PATHFIND_CELL_SIZE_F 10.0f

enum KindOfType
{
	KINDOF_HORDE = 109
};

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float val);
};

struct Vector3
{
	Real X;
	Real Y;
	Real Z;

	Vector3() {}
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Vector3 &operator+=(const Vector3 &v) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
	Vector3 &operator*=(float k) { X = X*k; Y = Y*k; Z = Z*k; return *this; }
	void Set(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	float Length2() const { return X*X + Y*Y + Z*Z; }
	__forceinline void Normalize()
	{
		float len2 = Length2();
		if (len2 != 0.0f)
		{
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
};

class Matrix3D
{
public:
	static __forceinline void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		const Vector3 *v;
		if (out == &in) {
			tmp = in;
			v = &tmp;
		} else {
			v = &in;
		}
		out->X = (A.Row[0][0] * v->X + A.Row[0][1] * v->Y + A.Row[0][2] * v->Z + A.Row[0][3]);
		out->Y = (A.Row[1][0] * v->X + A.Row[1][1] * v->Y + A.Row[1][2] * v->Z + A.Row[1][3]);
		out->Z = (A.Row[2][0] * v->X + A.Row[2][1] * v->Y + A.Row[2][2] * v->Z + A.Row[2][3]);
	}

	Real Row[3][4];
};

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 0x1f)); }
private:
	char m_unrecovered000[0x108];
	UnsignedInt m_kindOf[4];																									///< 0x108
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getOrientation() const { return m_cachedAngle; }
	void setOrientation(Real angle);
	void rva0030A8EE(Coord3D *dir) const;

private:
	char m_unrecovered00[0x04];
	const ThingTemplate *m_template;																					///< 0x04
	Matrix3D m_transform;																											///< 0x08
	Coord3D m_cachedPos;																											///< 0x38
	Real m_cachedAngle;																												///< 0x44
};

#define VM10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class AIUpdateInterfaceBase
{
public:
	VM10(v0_)
	VM10(v1_)
	VM10(v2_)
	VM10(v3_)
	VM10(v4_)
	VM10(v5_)
	VM10(v6_)
	VM10(v7_)
	VM10(v8_)
	virtual Bool vslot90() const;																						// slot 90 -> offset 0x168
private:
	char m_unrecovered04[0x20 - 0x04];
};

// The rowed wrapper at 0x0047971C takes the exit path by reference; its
// placeholder class is this vector of points.
class Rva0035149F : public _STL::vector<Coord3D>
{
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms) = 0;
	void aiIdle(CommandSourceType cmdSource);
	void rva0047971C(const Rva0035149F &path, Object *ignoreObject, CommandSourceType cmdSource);
};

class LocomotorSet
{
private:
	char m_unrecovered00[0x04];
};

class AIUpdateInterface : public AIUpdateInterfaceBase, public AICommandInterface
{
public:
	const LocomotorSet &getLocomotorSet() const { return m_locomotorSet; }
	ObjectID getIgnoredObstacleID() const;
	void rva00262FEB(Int id);
private:
	char m_unrecovered24[0x1CC - 0x24];
	LocomotorSet m_locomotorSet;																							///< 0x1CC
};

// HordeContain's interface at +0x11C (vftable 0x00C44C58).
class HordeContainInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual Coord3D slot7(Object *obj, Real *angle);
	virtual void v08(); virtual void v09(); virtual void v10();
	virtual void assignSpotToUnit(Object *obj);
};

class ContainModuleInterface
{
public:
	VM10(v0_)
	VM10(v1_)
	VM10(v2_)
	virtual void v30();
	virtual HordeContainInterface *slot31();
};

// The +0x25C behavior; 0x003909FA takes the kick.
class Rva003909FAObj
{
public:
	void consume(void *force, Int a, Int b);
};

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	Rva003909FAObj *getPhysics() const { return m_physics; }
	Team *getTeam() const { return m_team; }
	Int get45C() const { return m_45C; }

	void rva0029660C(const Coord3D *pos, Int flag);
	Real rva0028AC7D() const;
	void setProducer(Object *obj);
	void setTeam(Team *team);
	void setStatus(ObjectStatusTypes status, bool set);
	Bool clearDisabled(DisabledType type);

private:
	char m_unrecovered48[0x74 - 0x48];
	ObjectID m_id;																														///< 0x74
	char m_unrecovered78[0x250 - 0x78];
	ContainModuleInterface *m_contain;																				///< 0x250
	char m_unrecovered254[0x258 - 0x254];
	AIUpdateInterface *m_ai;																									///< 0x258
	Rva003909FAObj *m_physics;																								///< 0x25C
	char m_unrecovered260[0x304 - 0x260];
	Team *m_team;																															///< 0x304
	char m_unrecovered308[0x45C - 0x308];
	Int m_45C;																																///< 0x45C
};

int Rva002EDE5B(void *obj, Coord3D *pos);

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void rva0023D0C2(Object *obj, Int value);
};

extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = 0, Real *terrainZ = 0, Int unused = 0);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *obj);
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest = 0);
	Int MoveAlliesAwayFromDestination(Object *obj, const Coord3D *from, const Coord3D *dest);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	char m_unrecovered00[0x10];
	Pathfinder *m_pathfinder;																									///< 0x10
};

extern AI *TheAI;

class ModuleData
{
private:
	char m_unrecovered00[0x08];
};

class QueueProductionExitUpdateModuleData : public ModuleData
{
public:
	Coord3D m_unitCreatePoint;																								///< 0x08
	Coord3D m_naturalRallyPoint;																							///< 0x14
	UnsignedInt m_exitDelayData;																							///< 0x20
	Bool m_allowAirborneCreationData;																					///< 0x24
	UnsignedInt m_initialBurst;																								///< 0x28
	Real m_placementViewAngle;																								///< 0x2C
	Bool m_noExitPath;																												///< 0x30
	Bool m_canRallyToSlaughter;																								///< 0x31
	Bool m_useReturnToFormation;																							///< 0x32
};

class UpdateModule
{
public:
	virtual void v00();
protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData;																						///< 0x04
	Object *m_object;																													///< 0x08
	char m_unrecovered0C[ 0x20 - 0x0C ];
};

class ExitInterface
{
public:
	virtual Bool isExitBusy() const = 0;
	virtual ExitDoorType reserveDoorForExit( const ThingTemplate *objType, Object *specificObject ) = 0;
	virtual void exitObjectViaDoor( Object *newObj, ExitDoorType exitDoor ) = 0;
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void setRallyPoint( const Coord3D *pos ) = 0;
	virtual const Coord3D *getRallyPoint( void ) const = 0;
	virtual Bool getNaturalRallyPoint( Coord3D& rallyPoint, Bool offset = true ) const;
	virtual Bool getExitPosition( Coord3D& exitPosition, Real& exitAngle ) const;
};

class QueueProductionExitUpdate : public UpdateModule, public ExitInterface
{
public:
	virtual void exitObjectViaDoor( Object *newObj, ExitDoorType exitDoor );
	virtual Bool getNaturalRallyPoint( Coord3D& rallyPoint, Bool offset = true ) const;
	virtual Bool getExitPosition( Coord3D& exitPosition, Real& exitAngle ) const;
protected:
	const QueueProductionExitUpdateModuleData *getQueueProductionExitUpdateModuleData() const
	{
		return (const QueueProductionExitUpdateModuleData *)getModuleData();
	}
private:
	UnsignedInt m_currentDelay;																								///< 0x24
	Coord3D m_rallyPoint;																											///< 0x28
	Bool m_rallyPointExists;																									///< 0x34
	Real m_creationClearDistance;																							///< 0x38
	UnsignedInt m_currentBurstCount;																					///< 0x3C
	ObjectID m_hordeID;																												///< 0x40
};

//-------------------------------------------------------------------------------------------------
void QueueProductionExitUpdate::exitObjectViaDoor( Object *newObj, ExitDoorType exitDoor )
{
	Object *creationObject = getObject();
	if (creationObject)
	{
		const QueueProductionExitUpdateModuleData* md = getQueueProductionExitUpdateModuleData();

		const Matrix3D *transform = creationObject->getTransformMatrix();
		Vector3 loc;
		Coord3D createPoint;

		//
		// calculate the position to create the object at, we take the coord specified
		// in INI which is in model space, rotate it to match the building angle
		// and translate for building location via a transform call
		//
		loc.Set( md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z );
		transform->Transform_Vector( *transform, loc, &loc );

		Bool creationInAir = false;
		if( TheTerrainLogic && !TheTerrainLogic->isUnderwater( loc.X, loc.Y, &loc.Z ) )
		{
			if( loc.Z > TheTerrainLogic->getGroundHeight( loc.X, loc.Y ) + 1.0f )
			{
				creationInAir = true;
				// make sure the point is on the terrain
				if( !md->m_allowAirborneCreationData )
					loc.Z = TheTerrainLogic->getGroundHeight( loc.X, loc.Y );
			}
		}

		// we need it in Coord3D form
		createPoint.x = loc.X;
		createPoint.y = loc.Y;
		createPoint.z = loc.Z;

		AIUpdateInterface *ai = newObj->getAIUpdateInterface();
		Bool raised = ai && ai->vslot90();
		if( raised )
			createPoint.z += 250.0f;

		newObj->rva0029660C( &createPoint, true );
		newObj->setOrientation( md->m_placementViewAngle + creationObject->getOrientation() );

		//
		// Objects that are created in the air get a kick that will make their
		// starting speed equal mine.
		//
		Rva003909FAObj *newObjectPhysics = newObj->getPhysics();
		Coord3D startingForce;
		creationObject->rva0030A8EE( &startingForce );
		Real speed = creationObject->rva0028AC7D();
		if( creationInAir && newObjectPhysics && speed > 0.01f )
		{
			startingForce.x *= speed;
			startingForce.y *= speed;
			startingForce.z *= speed;
			newObjectPhysics->consume( &startingForce, 0, 0 );
		}

		TheGameLogic->rva0023D0C2( newObj, creationObject->get45C() );

		// tell the AI about it
		TheAI->pathfinder()->AddObjectToPathfindMap( newObj );

		Object *hordeObj = TheGameLogic->findObjectByID( m_hordeID );
		HordeContainInterface *horde = NULL;
		if( hordeObj )
		{
			horde = hordeObj->getContain() ? hordeObj->getContain()->slot31() : NULL;
			if( horde )
			{
				newObj->setProducer( hordeObj );
				horde->assignSpotToUnit( newObj );
				newObj->setTeam( hordeObj->getTeam() );
			}
		}

		if( ai )
		{
			Rva0035149F exitPath;
			Coord3D tmp;
			if( horde )
			{
				Coord3D halfway;
				getNaturalRallyPoint( halfway );
				Real dx = halfway.x - createPoint.x;
				Real dy = halfway.y - createPoint.y;
				Real dz = halfway.z - createPoint.z;
				halfway.x = dx * 0.5f + createPoint.x;
				halfway.y = dy * 0.5f + createPoint.y;
				halfway.z = dz * 0.5f + createPoint.z;
				exitPath.push_back( halfway );
				Real angle;
				tmp = horde->slot7( newObj, &angle );
				exitPath.push_back( tmp );
				exitPath.push_back( tmp );
			}
			else
			{
				getNaturalRallyPoint( tmp );
				Rva002EDE5B( newObj, &tmp );
				exitPath.push_back( tmp );
			}

			Bool useRallyPoint = !newObj->isKindOf( KINDOF_HORDE ) && hordeObj == NULL;
			if( m_rallyPointExists && useRallyPoint )
			{
				tmp = m_rallyPoint;
				if( raised )
					exitPath.push_back( tmp );
				else if( TheAI->pathfinder()->adjustDestination( newObj, ai->getLocomotorSet(), &tmp, NULL ) )
					exitPath.push_back( tmp );
			}

			if( md->m_noExitPath && !(m_rallyPointExists && useRallyPoint) )
			{
				newObj->setStatus( OBJECT_STATUS_IS_LEAVING_FACTORY, false );
				ai->aiIdle( CMD_FROM_AI );
			}
			else
			{
				newObj->clearDisabled( DISABLED_HELD );
				ai->rva0047971C( exitPath, NULL, CMD_FROM_AI );
				ObjectID ignored = ai->getIgnoredObstacleID();
				if( hordeObj )
					ai->rva00262FEB( hordeObj->getID() );
				TheAI->pathfinder()->MoveAlliesAwayFromDestination( newObj, newObj->getPosition(), &tmp );
				ai->rva00262FEB( ignored );
			}
		}

		if( newObj->isKindOf( KINDOF_HORDE ) )
		{
			Coord3D pos;
			getNaturalRallyPoint( pos );
			Rva002EDE5B( newObj, &pos );
			newObj->rva0029660C( &pos, false );
			m_hordeID = newObj->getID();
			newObj->setStatus( OBJECT_STATUS_UNSELECTABLE, true );
			newObj->setStatus( OBJECT_STATUS_UNDER_CONSTRUCTION, true );
		}

		m_currentDelay = md->m_exitDelayData;

		if (m_currentBurstCount)
			m_currentBurstCount--; // fewer and fewer units to burst
	}
}

//-------------------------------------------------------------------------------------------------
Bool QueueProductionExitUpdate::getNaturalRallyPoint( Coord3D& rallyPoint, Bool offset ) const
{
	const QueueProductionExitUpdateModuleData *data = getQueueProductionExitUpdateModuleData();
	Vector3 p;

	//
	// get the natural rally point from the INI definition, this coord is in model space relative
	// to the model (0,0,0)
	//
	const Coord3D *nrp = &data->m_naturalRallyPoint;
	p.Set( nrp->x, nrp->y, nrp->z );

	if ( offset )
	{
		Vector3 offset = p;
		offset.Normalize();
		offset *= (2*PATHFIND_CELL_SIZE_F);
		p+=offset;
	}

	// transform the point into world space
	const Matrix3D *transform = getObject()->getTransformMatrix();
	transform->Transform_Vector( *transform, p, &p );
	rallyPoint = *(const Coord3D *)&p;
	return true;
}

//-------------------------------------------------------------------------------------------------
Bool QueueProductionExitUpdate::getExitPosition( Coord3D& exitPosition, Real& exitAngle ) const
{
	const Object *obj = getObject();
	if (!obj)
		return false;

	const Matrix3D *transform = obj->getTransformMatrix();

	const QueueProductionExitUpdateModuleData *md = getQueueProductionExitUpdateModuleData();

	Vector3 loc;
	loc.Set( md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z );
	transform->Transform_Vector( *transform, loc, &loc );

	exitPosition = *(const Coord3D *)&loc;
	exitAngle = md->m_placementViewAngle + getObject()->getOrientation();

	return true;
}
