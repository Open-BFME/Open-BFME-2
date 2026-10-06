// ?loadDockPositions@DockUpdate@@IAEXXZ
// partial score=0.9595 date=2026-10-06
// ?loadDockPositions@DockUpdate@@IAEXXZ
// partial score=0.9595 date=2026-10-05
// ?loadDockPositions@DockUpdate@@IAEXXZ
// partial score=0.99 date=2026-09-28
// ?loadDockPositions@DockUpdate@@IAEXXZ
// partial score=0.99 date=2026-09-28
// cl: /O1 /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /arch:SSE /Ireference/shims/sweep
// stlport
//
// ?loadDockPositions@DockUpdate@@IAEXXZ, retail 0x005897FB, 270 bytes.
// Dock bone strings DockStart/DockAction/DockEnd/DockWaiting plus eight callers
// (0x589909 loadPostProcess wrapper tail-jumping to UpdateModule::loadPostProcess,
// 0x589972/0x58A1A1 with -0x20 this-adjustment) prove DockUpdate identity.
// Donor is BFME1 DockUpdate::loadDockPositions
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate.cpp:524,
// protected IAEXXZ) via ZH DockUpdate.cpp:491. BFME2 drops the KINDOF_IGNORE_DOCKING_BONES
// patch branch. Layout is the rowed DockUpdateCtor TU (UpdateModule base 0x20 plus
// DockUpdateInterface vptr at +0x20, enter/dock/exit at +0x24/+0x30/+0x3C,
/// number/bones/loaded at +0x48/+0x4C/+0x50, approach vector at +0x54).
#include <limits.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

struct Coord3D
{
	Coord3D();
	~Coord3D();

	float x;
	float y;
	float z;
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

#include <stl/_bvector.h>

namespace _STL
{
template <>
class vector<Coord3D, allocator<Coord3D> > : public _Vector_base<Coord3D, allocator<Coord3D> >
{
public:
	__forceinline vector() : _Vector_base<Coord3D, allocator<Coord3D> >(allocator<Coord3D>()) {}

	Int size() const
	{
		return (Int)(_M_finish - _M_start);
	}

	Coord3D &operator[](Int index)
	{
		return _M_start[index];
	}
};
}

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

// ?loadDockPositions@DockUpdate@@IAEXXZ present-unmatched
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
			Coord3D approachBones[DEFAULT_APPROACH_VECTOR_SIZE];
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
