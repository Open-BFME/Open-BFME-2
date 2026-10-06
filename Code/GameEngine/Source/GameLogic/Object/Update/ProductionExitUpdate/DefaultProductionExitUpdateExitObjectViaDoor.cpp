// cl: /DNDEBUG /MD /GX /O1 /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// ?exitObjectViaDoor@DefaultProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z @0x00488099 463B
// Evidence: VTABLE slot 2 of 0x0084B1B0 (DefaultProductionExitUpdate, ctor stores it);
// donor Zero Hour DefaultProductionExitUpdate.h + BFME1 isolated exitObjectViaDoor TU;
// callers none (ref lane, table slot); ret 8 matches (Object*, ExitDoorType).
#define __PLACEMENT_VEC_NEW_INLINE
#include "matrix3d.h"
#include <vector>
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

enum ExitDoorType { DOOR_1 = 0 };
enum PathfindLayerEnum { LAYER_GROUND = 1, LAYER_INVALID = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_AI = 2 };

class Object;
class LocomotorSet;

class Pathfinder
{
public:
	bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest = 0);
};

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *object);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

class TerrainLogic
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, bool clip = true) const;
};
extern TerrainLogic *TheTerrainLogic;

class Rva0035149F
{
public:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms) = 0;
	void rva0047971C(const Rva0035149F &info, Object *target, CommandSourceType cmdSource);
};

template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};

class AIUpdateInterface : public AIUpdateSlots<137>
{
public:
	virtual Bool isDoingGroundMovement(void) const = 0;
	const LocomotorSet &getLocomotorSet(void) const { return *(const LocomotorSet *)m_locomotorSet; }
private:
	unsigned char m_pad004[0x1CC - 0x04];
	unsigned char m_locomotorSet[0x1F0 - 0x1CC];
	unsigned char m_pad1F0[0x258 - 0x1F0];
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
};

class Object : public Thing
{
public:
	int rva0028B511(void) const;
	void rva0028B4CE(PathfindLayerEnum layer);
	Real getOrientation(void) const { return *(const Real *)((const unsigned char *)this + 0x44); }
	const Matrix3D *getTransformMatrix(void) const { return (const Matrix3D *)((const unsigned char *)this + 8); }
	AIUpdateInterface *getAIUpdateInterface(void) const { return *(AIUpdateInterface *const *)((const unsigned char *)this + 0x258); }
};

class ModuleData;

class DefaultProductionExitUpdateModuleData
{
public:
	unsigned char pad[8];
	Coord3D m_unitCreatePoint;
};

class DPEU_DeepBase
{
public:
	virtual ~DPEU_DeepBase();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class DPEU_Iface1 { public: virtual void slot(void); };
class DPEU_Iface2 { public: virtual void slot(void); };

class UpdateModule : public DPEU_DeepBase, public DPEU_Iface1, public DPEU_Iface2
{
protected:
	Object *getObject(void) const { return m_object; }
	const ModuleData *getModuleData(void) const { return m_moduleData; }
private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class ExitInterface
{
public:
	virtual Bool isExitBusy(void) const = 0;
	virtual ExitDoorType reserveDoorForExit(const void *, Object *) = 0;
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor) = 0;
	virtual void exitObjectByBudding(Object *, Object *) = 0;
	virtual void unreserveDoorForExit(ExitDoorType) = 0;
	virtual void exitObjectInAHurry(Object *) {}
	virtual void setRallyPoint(const Coord3D *) = 0;
	virtual const Coord3D *getRallyPoint(void) const = 0;
	virtual Bool useSpawnRallyPoint(void) const { return 0; }
	virtual Bool getNaturalRallyPoint(Coord3D &rallyPoint, Bool offset = 1) const = 0;
	virtual Bool getExitPosition(Coord3D &) const = 0;
};

class DefaultProductionExitUpdate : public UpdateModule, public ExitInterface
{
public:
	virtual Bool isExitBusy(void) const { return 0; }
	virtual ExitDoorType reserveDoorForExit(const void *, Object *) { return DOOR_1; }
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor);
	virtual void exitObjectByBudding(Object *, Object *) {}
	virtual void unreserveDoorForExit(ExitDoorType) {}
	virtual void setRallyPoint(const Coord3D *) {}
	virtual const Coord3D *getRallyPoint(void) const { return 0; }
	virtual Bool getNaturalRallyPoint(Coord3D &rallyPoint, Bool offset = 1) const;
	virtual Bool getExitPosition(Coord3D &) const { return 0; }

	const DefaultProductionExitUpdateModuleData *getDefaultProductionExitUpdateModuleData(void) const
	{
		return (const DefaultProductionExitUpdateModuleData *)getModuleData();
	}
private:
	Coord3D m_rallyPoint;
	bool m_rallyPointExists;
};

// ?exitObjectViaDoor@DefaultProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z
void DefaultProductionExitUpdate::exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor)
{
	(void)exitDoor;

	Object *creationObject = getObject();
	if (creationObject)
	{
		const DefaultProductionExitUpdateModuleData *md = getDefaultProductionExitUpdateModuleData();

		Real exitAngle = creationObject->getOrientation();
		const Matrix3D *transform = creationObject->getTransformMatrix();
		Coord3D createPoint;
		Vector3 loc;

		loc.Set(md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z);
		transform->Transform_Vector(*transform, loc, &loc);

		loc.Z = TheTerrainLogic ? TheTerrainLogic->getLayerHeight(loc.X, loc.Y, (PathfindLayerEnum)creationObject->rva0028B511(), 0, 1) : 0.0f;

		createPoint = *(const Coord3D *)&loc;
		newObj->setPosition(&createPoint);
		newObj->setOrientation(exitAngle);
		newObj->rva0028B4CE((PathfindLayerEnum)creationObject->rva0028B511());

		((BFMEPathfinderMapShim *)TheAI->pathfinder())->addObjectToPathfindMap(newObj);
		Coord3D tmp;
		getNaturalRallyPoint(tmp);
		{
			std::vector<Coord3D> exitPath;
			exitPath.push_back(tmp);

			AIUpdateInterface *ai = newObj->getAIUpdateInterface();
			if (m_rallyPointExists)
			{
				tmp = m_rallyPoint;
				if (ai && ai->isDoingGroundMovement())
				{
					if (TheAI->pathfinder()->adjustDestination(newObj, ai->getLocomotorSet(), &tmp, 0))
						exitPath.push_back(tmp);
				}
			}
			if (ai)
			{
				((AICommandInterface *)((unsigned char *)ai + 0x20))->rva0047971C((const Rva0035149F &)exitPath, creationObject, CMD_FROM_AI);
			}
		}
	}
}
