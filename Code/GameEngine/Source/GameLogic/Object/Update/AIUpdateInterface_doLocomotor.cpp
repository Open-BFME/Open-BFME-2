// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE
// stlport
//
// AIUpdateInterface::doLocomotor, retail 0x0026A3A0 (3018 bytes).
//
// Identity (target evidence): the body sits in 30+ AIUpdate-family vtables
// (e.g. 0x007FA6D4, 0x00847DEC) and WorldBuilder's AIUpdate.cpp names it
// AIUpdateInterface::doLocomotor; it opens with
// chooseGoodLocomotorFromCurrentSet (0x00263FA7), then the Zero Hour
// m_isBlocked/m_blockedFrames bookkeeping (+0x3B8/+0x16C) and a switch on
// m_locomotorGoalType (+0x1FC) over m_curLocomotor (+0x1F0).
//
// Structure carried from the Zero Hour AIUpdate.cpp doLocomotor: the
// explicit/on-path/angle/none goal cases, the max-speed clamp, the bump
// speed limiter and the final-position creep of the NONE case.
//
// BFME2 deltas read from the retail bytes: an early template bit test and a
// kind-of 0x81 test; goal type 4 shares the explicit case and validates the
// move as a horde member (0x002F06A3/0x002F6075); on-path movement consults
// the path segment record returned by TerrainLogic slot 35, whose type (+0x60)
// selects portal (8), climb (2/3/4) and exit (7) handling with inline
// model-condition updates on Object+0x10C; the loco calls take four
// arguments (no blocked pointer). Field names beyond Zero Hour's are
// address-derived.

#include <vector>
#include <math.h>
#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"

typedef float Real;
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#define FAST_AS_POSSIBLE 999999.0f
// Named constant preserves the retail SSE comparison operand order.
static const float fastSentinel = 999999.0f;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum KindOfType
{
	KINDOF_0x81 = 0x81
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_AIRBORNE_TARGET = 6
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

enum LocomotorGoalType
{
	NONE = 0,
	POSITION_ON_PATH = 1,
	POSITION_EXPLICIT = 2,
	ANGLE = 3,
	POSITION_EXPLICIT_HORDE = 4 // BFME2; validated as a horde member
};

enum ModelConditionFlagType
{
	MODELCONDITION_103 = 3 * 32 + 7,
	MODELCONDITION_131 = 4 * 32 + 3,
	MODELCONDITION_135 = 4 * 32 + 7,
	MODELCONDITION_136 = 4 * 32 + 8,
	MODELCONDITION_156 = 4 * 32 + 28
};

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

// BFME2's Coord3D sub/add/scale members, inline in retail (WorldBuilder
// calls them out of line); the canonical Coord3D view does not declare them.
inline void coordSub(Coord3D *a, const Coord3D *b)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
}

inline void coordAdd(Coord3D *a, const Coord3D *b)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}

inline void coordScale(Coord3D *a, Real scale)
{
	a->x *= scale;
	a->y *= scale;
	a->z *= scale;
}

#include "../../../../Include/GameClient/ModelConditionFlags.h"

#include "../../../../Include/Common/ThingTemplate.h"

class Rva00373EC6;
class StealthUpdate
{
public:
	void markAsDetected(UnsignedInt numFrames, Int arg2, class Object *by, Bool arg4);
	unsigned char m_pad00[0x3C];
	Int m_3C;
};

#include "../../../Common/Thing/thing.h"

#include "../../../../Include/GameLogic/Module/Rva0028B525DwordSlot.h"

class Object : public Thing
{
public:
	Bool isKindOf(KindOfType t) const;
	void setStatus(ObjectStatusTypes status, Bool set);
	void rva0028AE6D(); // model-condition change notifier
	Int rva0028B511() const; // the pathfind layer
	/* the rowed Rva0028B525DwordSlot::set */ __declspec(dllimport) __forceinline void rva0028B525(Int layer) { ((Rva0028B525DwordSlot *)this)->set(layer); }
	Rva00373EC6 *rva0028F4BC();
	void rva001E431E(const Int *flags);

	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
	__forceinline void setModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad060[0x10C - 0x60];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
};

// The locomotor template the current locomotor points at (+0x04).
class Rva001E46E1Template
{
public:
	unsigned char m_pad00[0x74];
	Int m_74; // +0x74, the locomotor appearance (6 ignores path segments)
	unsigned char m_pad78[0xC0 - 0x78];
	Int m_airborneTargetingHeight; // +0xC0 (Zero Hour's getAirborneTargetingHeight)
	unsigned char m_padC4[0xD0 - 0xC4];
	Bool m_locomotorWorksWhenDead; // +0xD0 (Zero Hour's name)
	unsigned char m_padD1[0x150 - 0xD1];
	Bool m_150; // +0x150
};

#include "../../../../Include/GameLogic/Rva0008BB38FloatField.h"

#include "../../../../Include/GameLogic/Module/Rva001E702E.h"

// Locomotor::getMaxSpeed (0x001E46E1), named by WorldBuilder.
#include "../../../../Include/GameLogic/LocomotorClass.h"

// The current locomotor (Zero Hour's Locomotor); ledger class name.
class Rva001E46E1
{
public:
	const Rva001E46E1Template *getTemplate() const { return m_template; }
	Int getAirborneTargetingHeight() const { return m_template->m_airborneTargetingHeight; }
	void rva001E53D8(Real speed, Object *obj);
	Bool rva001E543F(Object *obj);
	/* the rowed Locomotor::locoUpdate_maintainCurrentPosition */ __declspec(dllimport) __forceinline Bool rva001E84E5(Object * p0) { return ((Locomotor *)this)->locoUpdate_maintainCurrentPosition(p0); } // locoUpdate_maintainCurrentPosition
private:
	void *m_vtbl;
	const Rva001E46E1Template *m_template; // +0x04
};

struct Rva003642DFNode
{
	unsigned char m_pad00[0x20];
	Int m_20; // +0x20
};

// Zero Hour's ClosestPointOnPathInfo shape: node, then the point.
#include "../../../../Include/GameLogic/Rva003642DFResult.h"


#include "../../../../Include/GameLogic/Module/Rva001E3511.h"

class Rva001E34FA
{
public:
	Int rva001E34FA();
};

#include "../../../../Include/GameLogic/PathfindPath.h"

// The record TerrainLogic slot 35 returns for a path segment id.
struct Rva0026A3A0Segment
{
	ScienceType getScience() const { return m_04; }
	unsigned char m_pad00[0x04];
	ScienceType m_04; // +0x04
	unsigned char m_pad08[0x60 - 0x08];
	Int m_type; // +0x60
	unsigned char m_pad64[0xB0 - 0x64];
	ObjectID m_objectID; // +0xB0
};

#include "../../../../Include/GameLogic/TerrainLogic.h"

class TerrainLogicSlots : public BfmeVirtualSlots<35>
{
public:
	virtual Rva0026A3A0Segment *slot35(Int id);
};

extern TerrainLogic *TheTerrainLogic;

extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/AIGroup.h"

#include "../../../../Include/GameLogic/AI.h"

extern AI *TheAI;

// Existing data-ledger owner defined by ColdGlobalDwordGetters.cpp; initial value 5.
extern int BfmeLogicFramesPerSecond; // logic frames per second

#include "../../../../Include/GameLogic/Module/MineshaftPortalBehaviour.h"

void *Rva00372D3AFind(void *obj);

class Rva00265254
{
public:
	Rva00265254(UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt,
		UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt);
private:
	UnsignedInt m_words[19];
};

class WeaponTemplateSetHead
{
public:
	void rva000B3ED3(const WeaponTemplateSetHead &other);
};

class AIUpdateInterface : public BfmeVirtualSlots<137>
{
public:
	virtual Bool isDoingGroundMovement() const; // slot 137 (+0x224)
	Object *getObject() const { return m_object; }
	__declspec(dllimport) Path *getPath() { return m_path; }
	__declspec(dllimport) __forceinline Real getPathExtraDistance() const { return m_pathExtraDistance; }
	__declspec(dllimport) __forceinline Bool isAiInDeadState() const { return m_isAiDead; }
	void chooseGoodLocomotorFromCurrentSet();
	void rva00262D2D();
	void rva0026717B();
protected:
	virtual UpdateSleepTime doLocomotor();
private:
	unsigned char m_pad04[0x08 - 0x04];
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x44 - 0x0C];
	Real m_desiredSpeed; // +0x44
	unsigned char m_pad48[0x140 - 0x48];
	Path *m_path; // +0x140
	unsigned char m_pad144[0x168 - 0x144];
	Real m_pathExtraDistance; // +0x168
	Int m_blockedFrames; // +0x16C
	Real m_curMaxBlockedSpeed; // +0x170
	Real m_bumpSpeedLimit; // +0x174
	unsigned char m_pad178[0x17C - 0x178];
	Int m_17C; // +0x17C
	Coord3D m_finalPosition; // +0x180
	unsigned char m_pad18C[0x1F0 - 0x18C];
	Rva001E46E1 *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x1FC - 0x1F4];
	Int m_locomotorGoalType; // +0x1FC
	Coord3D m_locomotorGoalData; // +0x200
	unsigned char m_pad20C[0x290 - 0x20C];
	WeaponTemplateSetHead m_290; // +0x290
	unsigned char m_pad291[0x3B0 - 0x291];
	Bool m_doFinalPosition; // +0x3B0
	Bool m_waitingForPath; // +0x3B1
	unsigned char m_pad3B2[0x3B8 - 0x3B2];
	Bool m_isBlocked; // +0x3B8
	unsigned char m_pad3B9[0x3BB - 0x3B9];
	Bool m_onPathSegment; // +0x3BB
	unsigned char m_pad3BC;
	Bool m_isAiDead; // +0x3BD
};

UpdateSleepTime AIUpdateInterface::doLocomotor()
{
	Object *obj = getObject();
	if (obj && (obj->m_template->m_kindof[0] & (1U << (2 & 0x1f))))
		return UPDATE_SLEEP_FOREVER;
	if (obj && obj->isKindOf(KINDOF_0x81))
		return UPDATE_SLEEP_NONE;

	chooseGoodLocomotorFromCurrentSet();

	if (m_isBlocked)
	{
		++m_blockedFrames;
	}
	else
	{
		m_blockedFrames = 0;
	}
	m_isBlocked = false;
	Bool blocked = m_blockedFrames > 0;
	Bool requiresConstantCalling = true;

	if (m_curLocomotor)
	{
		if (!(isAiInDeadState() && !m_curLocomotor->getTemplate()->m_locomotorWorksWhenDead))
		{
			switch (m_locomotorGoalType)
			{
				case POSITION_EXPLICIT:
				case POSITION_EXPLICIT_HORDE:
				{
					Real speed = m_desiredSpeed;
					Real myMaxSpeed = ((Locomotor *)m_curLocomotor)->getMaxSpeed(obj);
					if (speed == FAST_AS_POSSIBLE || speed > myMaxSpeed)
						speed = myMaxSpeed;
					Coord3D oldPos;
					oldPos.x = obj->getPosition()->x;
					oldPos.y = obj->getPosition()->y;
					oldPos.z = obj->getPosition()->z;
					Coord3D *goal = &m_locomotorGoalData;
					Coord3D delta;
					delta.x = oldPos.x;
					delta.y = oldPos.y;
					delta.z = oldPos.z;
					coordSub(&delta, goal);
					Real dist = delta.length();
					((Locomotor *)m_curLocomotor)->rva001E9083(obj, goal, dist + m_pathExtraDistance, speed);
					if (m_locomotorGoalType == POSITION_EXPLICIT_HORDE &&
						!TheAI->pathfinder()->IsValidHordeMemberRegularMovement(obj, &oldPos, obj->getPosition(), goal))
					{
						obj->setPosition(&oldPos);
						if (m_path == NULL)
						{
							m_path = TheAI->pathfinder()->GetHordeUnitPath(obj, goal);
							if (m_path == NULL)
								obj->setPosition(goal);
						}
					}
					else if (m_path)
					{
						delete m_path;
						m_path = NULL;
					}
					if (m_locomotorGoalType == POSITION_EXPLICIT_HORDE && m_path)
					{
						Rva003642DFResult info = m_path->rva00364521((const Rva0008BB38FloatField *)m_curLocomotor);
						((Locomotor *)m_curLocomotor)->rva001E9083(obj, &info.m_pos,
							getPathExtraDistance() + ((Rva00363D20 *)&info)->rva00363D20(), speed);
						m_path->DoAdvanceAlongPath(&obj->m_cachedPos, true);
					}
					obj->rva0028B525(TheTerrainLogic->getLayerForDestination(obj, obj->getPosition()));
					m_doFinalPosition = false;
				}
				break;

				case POSITION_ON_PATH:
				{
					if (!getPath())
					{
						if (!m_waitingForPath)
							break;
						Real step = ((const Rva0008BB38FloatField *)m_curLocomotor)->get();
						if (m_curLocomotor->rva001E543F(obj) && m_17C == 0)
						{
							Coord3D dest;
							obj->getUnitDirectionVector2D(dest);
							Real scale = step * 2.0f;
							dest.x *= scale;
							dest.y *= scale;
							dest.z *= scale;
							const Coord3D *pos = obj->getPosition();
							dest.x = pos->x + dest.x;
							dest.y = pos->y + dest.y;
							dest.z = pos->z + dest.z;
							if (TheAI->pathfinder()->QuickDoesPathExist(obj, pos, &dest, 0))
								((Locomotor *)m_curLocomotor)->rva001E9083(obj, &dest, FAST_AS_POSSIBLE, step);
							Rva00265254 flags(0, 0x3d, 0x87, 0x88, 0x83, 0x85, 0x86, 0x89, 0x8a, 0xef, 0xf0, 0x9c);
							((WeaponTemplateSetHead *)&flags)->rva000B3ED3(m_290);
							obj->rva001E431E((const Int *)&flags);
						}
						return UPDATE_SLEEP_FOREVER;
					}

					Rva0026A3A0Segment *segment = NULL;
					Rva003642DFResult info = getPath()->rva00364521((const Rva0008BB38FloatField *)m_curLocomotor);
					if (isDoingGroundMovement())
					{
						Int id = ((Rva001E3511 *)&info)->rva001E3511();
						if (id != 0x7fffffff)
							segment = ((TerrainLogicSlots *)TheTerrainLogic)->slot35(id);
						if (segment == NULL)
						{
							Int layer = ((Rva001E34FA *)&info)->rva001E34FA();
							if (layer == LAYER_GROUND)
								layer = TheAI->pathfinder()->GetGroundLayer(&info.m_pos);
							TheAI->pathfinder()->UpdateLayer(obj, (PathfindLayerEnum)layer);
						}
					}
					m_onPathSegment = segment != NULL;

					Real speed = m_desiredSpeed;
					Real myMaxSpeed = ((Locomotor *)m_curLocomotor)->getMaxSpeed(obj);
					if (speed == fastSentinel || speed > myMaxSpeed)
						speed = myMaxSpeed;
					if (blocked && speed > m_curMaxBlockedSpeed)
					{
						speed = m_curMaxBlockedSpeed;
						if (m_bumpSpeedLimit > speed)
							m_bumpSpeedLimit = speed;
						m_bumpSpeedLimit *= 0.95f;
						speed = m_bumpSpeedLimit;
					}
					else
					{
						if (m_bumpSpeedLimit < FAST_AS_POSSIBLE)
						{
							if (speed * 0.3f > m_bumpSpeedLimit)
								m_bumpSpeedLimit = speed * 0.3f;
							m_bumpSpeedLimit *= 1.4f;
						}
						if (speed > m_bumpSpeedLimit)
							speed = m_bumpSpeedLimit;
					}

					if (m_curLocomotor && !m_curLocomotor->getTemplate()->m_150)
						obj->clearModelConditionState(MODELCONDITION_103);
					if (m_curLocomotor->getTemplate()->m_74 == 6)
						segment = NULL;

					if (segment)
					{
						m_curLocomotor->rva001E53D8(speed, obj);
						Rva003642DFResult next = m_path->rva00364521((const Rva0008BB38FloatField *)m_curLocomotor);
						Coord3D delta;
						delta.x = next.m_pos.x;
						delta.y = next.m_pos.y;
						delta.z = next.m_pos.z;
						coordSub(&delta, obj->getPosition());
						switch (segment->m_type)
						{
							case 8:
							{
								Path *path = m_path;
								if (path)
								{
									_STL::vector<ScienceType> portals;
									path->AdvancePastPortal(segment->getScience(), &portals);
									if (getPath() == NULL)
										return UPDATE_SLEEP_NONE;
									if (!portals.empty())
									{
										Rva0026A3A0Segment *portal = ((TerrainLogicSlots *)TheTerrainLogic)->slot35(getPath()->GetNextPortalID());
										if (portal)
										{
											Object *portalObj = TheGameLogic->findObjectByID(portal->m_objectID);
											MineshaftPortalBehaviour *behaviour = (MineshaftPortalBehaviour *)Rva00372D3AFind(portalObj);
											behaviour->addArrivingObject(obj);
											rva00262D2D();
											Int id = info.m_node == NULL ? 0x7fffffff : info.m_node->m_20;
											Rva0026A3A0Segment *exit = ((TerrainLogicSlots *)TheTerrainLogic)->slot35(id);
											if (exit == NULL || exit->m_type != 8)
												exit = segment;
											Object *exitObj = TheGameLogic->findObjectByID(exit->m_objectID);
											AIGroup *group = TheAI->createGroup();
											group->add(obj);
											group->rva00372BB9(exitObj, 2);
											TheAI->destroyGroup(group);
										}
										else
										{
											rva00262D2D();
										}
										return UPDATE_SLEEP_NONE;
									}
								}
							}
							// fall through
							case 3:
								obj->clearModelConditionState(MODELCONDITION_135);
								obj->clearModelConditionState(MODELCONDITION_136);
								obj->clearModelConditionState(MODELCONDITION_103);
								obj->setModelConditionState(MODELCONDITION_131);
								if (delta.length() * -0.5f > delta.z)
								{
									Coord3D target;
									target.x = obj->getPosition()->x * 2.0f - next.m_pos.x;
									target.y = obj->getPosition()->y * 2.0f - next.m_pos.y;
									target.z = info.m_pos.z;
									((Rva001E702E *)m_curLocomotor)->rva001E702E(obj, (Int)&target, 0);
									obj->setModelConditionState(MODELCONDITION_156);
									obj->setModelConditionState(MODELCONDITION_103);
									StealthUpdate *stealth = (StealthUpdate *)obj->rva0028F4BC();
									if (stealth && stealth->m_3C)
										stealth->markAsDetected(0, 1, NULL, true);
								}
								else
								{
									if (delta.z > delta.length() * 0.5f)
									{
										obj->setModelConditionState(MODELCONDITION_103);
										StealthUpdate *stealth = (StealthUpdate *)obj->rva0028F4BC();
										if (stealth && stealth->m_3C)
											stealth->markAsDetected(0, 1, NULL, true);
									}
									((Rva001E702E *)m_curLocomotor)->rva001E702E(obj, (Int)&next.m_pos, 0);
								}
								obj->setPosition(&next.m_pos);
								break;

							case 7:
								obj->clearModelConditionState(MODELCONDITION_135);
								obj->clearModelConditionState(MODELCONDITION_136);
								rva00262D2D();
								return UPDATE_SLEEP_NONE;

							case 2:
							case 4:
								obj->clearModelConditionState(MODELCONDITION_135);
								obj->clearModelConditionState(MODELCONDITION_136);
								obj->setModelConditionState(MODELCONDITION_131);
								((Rva001E702E *)m_curLocomotor)->rva001E702E(obj, (Int)&next.m_pos, 0);
								obj->setPosition(&next.m_pos);
								break;

							case 1:
								obj->setPosition(&next.m_pos);
								break;

							case 0:
								segment = NULL;
								break;
						}
						obj->rva0028B525(((Rva001E34FA *)&next)->rva001E34FA());
						m_path->DoAdvanceAlongPath(&obj->m_cachedPos, true);
					}
					else
					{
						obj->clearModelConditionState(MODELCONDITION_156);
						Real moveSpeed = blocked ? 0.0f : speed;
						((Locomotor *)m_curLocomotor)->rva001E9083(obj, &info.m_pos,
							getPathExtraDistance() + ((Rva00363D20 *)&info)->rva00363D20(), moveSpeed);
					}
					m_doFinalPosition = false;
				}
				break;

				case ANGLE:
				{
					((Locomotor *)m_curLocomotor)->locoUpdate_moveTowardsAngle(obj, m_locomotorGoalData.x);
					m_doFinalPosition = false;
				}
				break;

				case NONE:
				{
					if (m_doFinalPosition)
					{
						Coord3D pos;
						pos.x = obj->getPosition()->x;
						pos.y = obj->getPosition()->y;
						pos.z = obj->getPosition()->z;
						Bool onGround = !obj->isAboveTerrain() && obj->rva0028B511() == LAYER_GROUND;
						Real dx = m_finalPosition.x - pos.x;
						Real dy = m_finalPosition.y - pos.y;
						Real dSqr = dx * dx + dy * dy;
						const Real DARN_CLOSE = 0.25f;
						if (dSqr < DARN_CLOSE)
						{
							m_doFinalPosition = false;
							if (onGround)
								m_finalPosition.z = TheTerrainLogic->getGroundHeight(m_finalPosition.x, m_finalPosition.y, NULL);
							else
								m_finalPosition.z = pos.z;
							obj->setPosition(&m_finalPosition);
						}
						else
						{
							Real dist = sqrt(dSqr);
							if (1 > dist)
								dist = 1;
							pos.x += 20.0f * dx / (dist * BfmeLogicFramesPerSecond);
							pos.y += 20.0f * dy / (dist * BfmeLogicFramesPerSecond);
							if (onGround)
								pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y, NULL);
							obj->setPosition(&pos);
						}
					}
					requiresConstantCalling = m_curLocomotor->rva001E84E5(obj);
				}
				break;
			}
		}
		else
		{
		}

		if (!blocked && m_blockedFrames > 1)
		{
			m_blockedFrames = 1;
		}

		if (obj->getHeightAboveTerrain() > m_curLocomotor->getAirborneTargetingHeight())
			obj->setStatus(OBJECT_STATUS_AIRBORNE_TARGET, true);
		else
			obj->setStatus(OBJECT_STATUS_AIRBORNE_TARGET, false);

		m_curMaxBlockedSpeed = FAST_AS_POSSIBLE;
	}

	rva0026717B();

	if (m_curLocomotor != NULL
			&& m_locomotorGoalType == NONE
			&& m_doFinalPosition == false
			&& m_isBlocked == false
			&& requiresConstantCalling == false)
	{
		return UPDATE_SLEEP_FOREVER;
	}
	else
	{
		return UPDATE_SLEEP_NONE;
	}
}

inline __declspec(noinline) float Coord3D::length() const { return (float)sqrt(x*x+y*y+z*z); }
