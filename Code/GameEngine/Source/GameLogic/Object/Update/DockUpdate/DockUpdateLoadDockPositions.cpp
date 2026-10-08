// cl: /ICode/Libraries/Include/Lib /O1 /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /arch:SSE /Ireference/shims/sweep
// stlport
//
// ?loadDockPositions@DockUpdate@@IAEXXZ, retail 0x005897FB, 270 bytes.
// Dock bone strings DockStart/DockAction/DockEnd/DockWaiting plus eight callers
// (0x589909 loadPostProcess wrapper tail-jumping to UpdateModule::loadPostProcess,
// 0x589972/0x58A1A1 with -0x20 this-adjustment) prove DockUpdate identity.
// Donor is BFME1 DockUpdate::loadDockPositions
// (BFME1 revision 9cbfb551fe20dae985f91f2319d8997287b6a705, game engine DockUpdate.cpp:524,
// protected IAEXXZ) via ZH DockUpdate.cpp:491. BFME2 drops the KINDOF_IGNORE_DOCKING_BONES
// patch branch. Layout is the rowed DockUpdateCtor TU (UpdateModule base 0x20 plus
// DockUpdateInterface vptr at +0x20, enter/dock/exit at +0x24/+0x30/+0x3C,
// number/bones/loaded at +0x48/+0x4C/+0x50, approach vector at +0x54).
#include <limits.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#include "Coord3D.h"

// This array's construction/destruction is witnessed in the native unwind
// graph; the data view uses the canonical Coord3D layout. The lifetime-only
// adapter callbacks are byte-and-relocation twins of the folded native
// constructor at 0x0047A6A9 (8b c1 c3) and destructor at 0x000B3FD0 (c3).
// These offsets prove lifetime machinery, not an independent class identity.
struct Rva005897FBCoordLifetime : Coord3D
{
    Rva005897FBCoordLifetime() {}
    ~Rva005897FBCoordLifetime() {}
};

class Matrix3D
{
	float m[12];
};

class Drawable
{
public:
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
};

class ModuleData;
class Thing;

class BehaviorModuleBase
{
public:
	virtual void unused();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	virtual void update();
};

class DockUpdateInterface
{
public:
	virtual void dockAnchor() = 0;
};

#include <vector>

typedef _STL::vector<Coord3D, _STL::allocator<Coord3D> > VecCoord3D;

class DockUpdate : public UpdateModule, public DockUpdateInterface
{
public:
	DockUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DockUpdate();

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();
	virtual void dockAnchor();

protected:
	void loadDockPositions();

	Coord3D m_enterPosition;
	Coord3D m_dockPosition;
	Coord3D m_exitPosition;
	Int m_numberApproachPositions;
	Int m_numberApproachPositionBones;
	Bool m_positionsLoaded;
	VecCoord3D m_approachPositions;
};

enum
{
	DEFAULT_APPROACH_VECTOR_SIZE = 10,
	DYNAMIC_APPROACH_VECTOR_FLAG = -1
};

// ?loadDockPositions@DockUpdate@@IAEXXZ
void DockUpdate::loadDockPositions()
{
	Object *obj = m_object;
	Drawable *myDrawable = obj->getDrawable();

	if (myDrawable != NULL)
	{
		myDrawable->getPristineBonePositions("DockStart", 0, &m_enterPosition, NULL, 1, 0);
		myDrawable->getPristineBonePositions("DockAction", 0, &m_dockPosition, NULL, 1, 0);
		myDrawable->getPristineBonePositions("DockEnd", 0, &m_exitPosition, NULL, 1, 0);
		if (m_numberApproachPositions != DYNAMIC_APPROACH_VECTOR_FLAG)
		{
			Rva005897FBCoordLifetime approachBones[DEFAULT_APPROACH_VECTOR_SIZE];
			m_numberApproachPositionBones = myDrawable->getPristineBonePositions("DockWaiting", 1, approachBones, NULL, m_numberApproachPositions, 0);
			if (m_numberApproachPositions == m_approachPositions.size())
			{
				for (Int copyIndex = 0; copyIndex < m_numberApproachPositions; ++copyIndex)
				{
					m_approachPositions[copyIndex] = approachBones[copyIndex];
				}
			}
		}
		else
		{
			m_numberApproachPositionBones = 0;
		}

		m_positionsLoaded = TRUE;
	}
}
