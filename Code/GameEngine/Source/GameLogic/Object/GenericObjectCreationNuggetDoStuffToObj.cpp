// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /ICode/Libraries/Include
#define COORD3D_VIEW_INLINE
#include "Lib/Coord3DCtorView.h"
#include "wwmath.h"
#include "vector3.h"
#include "matrix3d.h"
#include "../../Common/GameLogicObjectLookupView.h"
#include "ascii_string.h"
#include <string.h>

// GenericObjectCreationNugget::doStuffToObj, retail 0x001F22A8..0x001F2EAB
// (3075 B, ret 0x20; eight arguments: BFME 2 adds the radial index used by
// the 0x4000 disposition). WorldBuilder 0x00B06AE0 (ObjectCreationList.cpp,
// asserts 1199..1564) names the function and gives the statement order: the
// model-condition reset, LifetimeUpdate range, debris draw modules, the AI
// command, offset/particle/health/slave setup and the BFME 2 disposition
// chain; retail's GameLogicRandomValue line literals are that file's lines.
// Zero Hour's ObjectCreationList.cpp is the semantic guide. Nugget offsets
// come from the constructor 0x001F0E32 and destructor 0x001F31C6; module key
// strings and float constants are retail's.
// Two same-unit facts shape the frame: calcRandomForce (0x001F0247) sits
// before this body in the retail unit, so its visible body shows the force
// it fills does not escape (its slot shares with the other block vectors),
// while adjustVector (0x001F2EAB) follows it and stays opaque.
// The four static NameKey guards are this function's compiler guards (bits
// 1/2/4/8 at VA 0x00DFDCF4); their reset funclets 0x0076B1DF/20F/21C/229 are
// this parent's unwind actions.

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Player;
class FXList;
class ParticleSystemTemplate;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ModelConditionFlagType
{
	MODELCONDITION_DA = 0xDA
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum AICommandType
{
	AICMD_31 = 0x31
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/Common/Module.h"

class LifetimeUpdate
{
public:
	void setLifetimeRange(UnsignedInt minFrames, UnsignedInt maxFrames);
};

class HijackerUpdate
{
public:
	void setTargetObject(const Object *object);
};

// SpawnedModelConditionCreate's source hook (0x003A45D2).
class Rva003A45D2
{
public:
	void rva003A45D2(void *source);
};

struct FloatUpdateView
{
	char m_pad[0x20];
	bool m_enabled; // +0x20
};

class DebrisDrawInterface
{
public:
	virtual void setModelName(AsciiString name, Int color, Int shadowType) = 0;
	virtual void setAnimNames(AsciiString initial, AsciiString flying, AsciiString final, const FXList *finalFX) = 0;
};

template <int N> class OclDrawModuleSlots : public OclDrawModuleSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};
template <> class OclDrawModuleSlots<0>
{
};

class DrawModule : public OclDrawModuleSlots<44>
{
public:
	virtual DebrisDrawInterface *getDebrisDrawInterface() = 0; // +0xB0
};

class SlavedUpdateInterface
{
public:
	virtual void v00() = 0;
	virtual void onEnslave(const Object *slaver) = 0;
};

template <int N> class OclBehaviorSlots : public OclBehaviorSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template <> class OclBehaviorSlots<0>
{
};

class BehaviorModuleInterface : public OclBehaviorSlots<26>
{
public:
	virtual SlavedUpdateInterface *getSlavedUpdateInterface(); // +0x68
};

class BehaviorModule
{
public:
	BehaviorModuleInterface *getBehaviorModuleInterface() { return &m_interface; }
private:
	char m_pad[0x0C];
	BehaviorModuleInterface m_interface; // +0x0C
};

class BodyModuleInterface : public OclBehaviorSlots<21>
{
public:
	virtual void setInitialHealth(Real initialPercent, Int unused) = 0; // +0x54
};

template <int N> class OclContainSlots : public OclContainSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};
template <> class OclContainSlots<0>
{
};

class ContainModuleInterface : public OclContainSlots<38>
{
public:
	virtual bool isValidContainerFor(const Object *obj, bool checkCapacity, Int unused) = 0; // +0x98
	virtual void addToContain(Object *obj) = 0; // +0x9C
};

// Coord3D::scale is retail's out-of-line 0x000036D1 (region.cpp); this body
// inlines it. Scaling through this TU-local helper keeps the inline expansion
// without emitting a non-retail ?scale@Coord3D COMDAT copy.
static inline void scaleInPlace(Coord3D &c, float s)
{
	c.x *= s;
	c.y *= s;
	c.z *= s;
}

// The physics force consumer (0x003909FA): (force, 0, 0).
class Rva003909FAObj
{
public:
	void consume(void *force, int a, int b);
};

struct PhysicsBehaviorView
{
	char m_pad[0x5D];
	bool m_allowBouncing; // +0x5D
};

class Drawable
{
public:
	void setDrawableHidden(bool hidden);
};

class Rva002B224BDwordField
{
public:
	int get() const;
};

class Rva00270260
{
public:
	bool rva00270260();
};

class Thing
{
public:
	Drawable *getDrawable() const;
	void setTransformMatrix(const Matrix3D *mtx);
	void setOrientation(Real angle);
	void setPosition(const Coord3D *pos);
	void getUnitDirectionVector3D(Coord3D &dir) const;
};

class AICommandParms
{
public:
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
	~AICommandParms();

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	char m_pad08[0x34 - 0x08];
	Int m_intValue; // +0x34
	char m_pad38[0xC0 - 0x38];
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
	__forceinline void aiCommand31(UnsignedInt value, CommandSourceType cmdSource)
	{
		AICommandParms parms(AICMD_31, cmdSource);
		parms.m_intValue = value;
		aiDoCommand(&parms);
	}
};

class AIUpdateInterface
{
public:
	AICommandInterface *getCommands() { return &m_commands; }
private:
	char m_pad[0x20];
	AICommandInterface m_commands; // +0x20
};

struct ObjectStatusBits
{
	unsigned int m_bits;
	bool test(int bit) const { return (m_bits & (1u << bit)) != 0; }
	void set(int bit) { m_bits |= 1u << bit; }
};

class Object : public Thing
{
	friend class GenericObjectCreationNugget;
public:
	void rva0028CFB2(const int *clear, const int *set);
	Int getIndicatorColor() const;
	void setSpecialModelConditionState(ModelConditionFlagType type, UnsignedInt frames);
	Player *getControllingPlayer() const;
	void rva0028BFF9(UnsignedInt frames);
	void rva0028AE6D();
	void setLayer(PathfindLayerEnum layer);
	Real rva0028AC7D() const;

	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	ContainModuleInterface *getContain() const { return m_contain; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAI() const { return m_ai; }
	PhysicsBehaviorView *getPhysics() const { return m_physics; }
	Real getOrientation() const { return m_angle; }

protected:
	Module *findModule(NameKeyType key) const;

public:
	char m_pad000[0x44];
	Real m_angle; // +0x44
	char m_pad048[0x10C - 0x48];
	ObjectStatusBits m_status; // +0x10C
	char m_pad110[0x1C0 - 0x110];
	Real m_orientation; // +0x1C0
	char m_pad1C4[0x244 - 0x1C4];
	BehaviorModule **m_behaviors; // +0x244
	char m_pad248[0x250 - 0x248];
	ContainModuleInterface *m_contain; // +0x250
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	PhysicsBehaviorView *m_physics; // +0x25C
};

class PlayerList
{
public:
	__declspec(dllimport) Player *getLocalPlayer() { return m_local; }
private:
	char m_pad[0x10];
	Player *m_local; // +0x10
};
extern PlayerList *ThePlayerList;

struct ParticleSystemTemplateView
{
	char m_pad[0x84];
	bool m_localPlayerOnly; // +0x84
};

struct Rva001F3C43Arg;
class Rva001F3C43Slot
{
public:
	void set(const Rva001F3C43Arg *arg);
};

class ParticleSystem
{
public:
	void attachToObject(const Object *obj)
	{
		((Rva001F3C43Slot *)this)->set((const Rva001F3C43Arg *)obj);
	}
};
ParticleSystem *Make001FCBD7();

class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
};
class BfmeParticleSystemHandleBase
{
public:
	~BfmeParticleSystemHandleBase()
	{
		if (m_system)
			((RvaSmartPtr12 *)this)->rva0004CBC0();
	}
	ParticleSystem *m_system;
	BfmeParticleSystemHandleBase *m_previous;
	BfmeParticleSystemHandleBase *m_next;
};
class BfmeParticleSystemHandle : public BfmeParticleSystemHandleBase
{
public:
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make001FCBD7();
	}
};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves);
};
extern ParticleSystemManager *TheParticleSystemManager;

template <int N> class OclTerrainSlots : public OclTerrainSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};
template <> class OclTerrainSlots<0>
{
};

class TerrainLogic : public OclTerrainSlots<6>
{
public:
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) = 0; // +0x18
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, bool clip = true) = 0; // +0x1C
	virtual void v20() = 0;
	virtual void v24() = 0;
	virtual void v28() = 0;
	virtual void v2C() = 0;
	virtual void v30() = 0;
	virtual void v34() = 0;
	virtual void v38() = 0;
	virtual void v3C() = 0;
	virtual void v40() = 0;
	virtual void v44() = 0;
	virtual void v48() = 0;
	virtual bool isUnderwater(Real x, Real y, Real *waterZ = 0, Real *terrainZ = 0, Int unused = 0) = 0; // +0x4C
	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, bool onlyHealthyBridges = false);
};
extern TerrainLogic *TheTerrainLogic;

extern GameLogic *TheGameLogic;

Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, Int line);
Real normalizeAngle(Real angle);
void adjustVector(Coord3D *vec, const Matrix3D *mtx);

#define OCL_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp"
// Retail passes ObjectCreationList.cpp's own __LINE__ values; the calls below
// spell them as literals.
#define GameLogicRandomValue(lo, hi, line) GetGameLogicRandomValue((lo), (hi), OCL_FILE, (line))
#define GameLogicRandomValueReal(lo, hi, line) GetGameLogicRandomValueReal((lo), (hi), OCL_FILE, (line))

// Retail 0x001F0247, defined earlier in the same retail unit (the row stays
// with ObjectCreationList.cpp): its body tells the compiler the force it fills
// does not escape.
static void calcRandomForce(Real minMag, Real maxMag, Real minPitch, Real maxPitch, Coord3D *force)
{
	Real angle = GameLogicRandomValueReal(0, 2 * 3.14159265359f, 581);
	Real pitch = GameLogicRandomValueReal(minPitch, maxPitch, 582);
	Real mag = GameLogicRandomValueReal(minMag, maxMag, 583);

	Matrix3D mtx(1);
	mtx.Scale(mag);
	mtx.Rotate_Z(angle);
	mtx.Rotate_Y(-pitch);

	Vector3 v = mtx.Get_X_Vector();

	Coord3D result;
	result.x = v.X;
	result.y = v.Y;
	result.z = v.Z;
	*force = result;
}

struct AnimSet
{
	AsciiString m_animInitial;
	AsciiString m_animFlying;
	AsciiString m_animFinal;
};

template <class T> struct OclVectorView
{
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
	UnsignedInt size() const { return (UnsignedInt)(m_finish - m_start); }
	T *begin() const { return m_start; }
	T &operator[](UnsignedInt n) const { return *(begin() + n); }
};

class ObjectCreationNugget
{
public:
	virtual ~ObjectCreationNugget();
};

class GenericObjectCreationNugget : public ObjectCreationNugget
{
protected:
	void doStuffToObj(Object *obj, const AsciiString &modelName, const Coord3D *pos,
		const Matrix3D *mtx, Real orientation, const Object *sourceObj,
		UnsignedInt lifetimeFrames, Int radialIndex) const;

private:
	OclVectorView<AsciiString> m_names; // +0x04
	AsciiString m_putInContainer; // +0x10
	OclVectorView<AnimSet> m_animSets; // +0x14
	const FXList *m_fxFinal; // +0x20
	AsciiString m_particleSysName; // +0x24
	Int m_debrisToGenerate; // +0x28
	Real m_mass; // +0x2C
	Real m_extraBounciness; // +0x30
	Coord3D m_offset; // +0x34
	UnsignedInt m_disposition; // +0x40
	Real m_dispositionIntensity; // +0x44
	Real m_spinRate; // +0x48
	Real m_forceScale; // +0x4C
	Real m_minMag; // +0x50
	Real m_maxMag; // +0x54
	Real m_minPitch; // +0x58
	Real m_maxPitch; // +0x5C
	UnsignedInt m_minFrames; // +0x60
	UnsignedInt m_maxFrames; // +0x64
	Int m_shadowType; // +0x68
	UnsignedInt m_invulnerableTime; // +0x6C
	Real m_minHealth; // +0x70
	Real m_maxHealth; // +0x74
	char m_pad78[0x94 - 0x78];
	bool m_specialModelCondition; // +0x94
	UnsignedInt m_specialModelConditionFrames; // +0x98
	bool m_containInsideSourceObject; // +0x9C
	char m_pad9D[0xA4 - 0x9D];
	UnsignedInt m_aiCommandValue; // +0xA4
	bool m_nameAreObjects; // +0xA8
	bool m_okToChangeModelColor; // +0xA9
	bool m_orientInForceDirection; // +0xAA
	char m_padAB[0xB4 - 0xAB];
	int m_modelConditions[19]; // +0xB4
};

void GenericObjectCreationNugget::doStuffToObj(Object *obj, const AsciiString &modelName, const Coord3D *pos,
	const Matrix3D *mtx, Real orientation, const Object *sourceObj,
	UnsignedInt lifetimeFrames, Int radialIndex) const
{
	if (obj == 0)
		return;

	int clearFlags[19];
	memset(clearFlags, 0, sizeof(clearFlags));
	obj->rva0028CFB2(clearFlags, m_modelConditions);

	static NameKeyType key_LifetimeUpdate = TheNameKeyGenerator->nameToKey("LifetimeUpdate");
	LifetimeUpdate *lup = (LifetimeUpdate *)obj->findModule(key_LifetimeUpdate);
	if (lup)
	{
		if (lifetimeFrames)
			lup->setLifetimeRange(lifetimeFrames, lifetimeFrames);
		else if (m_maxFrames > 0)
			lup->setLifetimeRange(m_minFrames, m_maxFrames);
	}

	if (!m_nameAreObjects)
	{
		for (DrawModule **dm = (DrawModule **)((const Rva002B224BDwordField *)obj->getDrawable())->get(); *dm; ++dm)
		{
			DebrisDrawInterface *di = (*dm)->getDebrisDrawInterface();
			if (di)
			{
				di->setModelName(modelName, m_okToChangeModelColor ? obj->getIndicatorColor() : 0, m_shadowType);
				if (m_animSets.size() > 0)
				{
					Int which = GameLogicRandomValue(0, m_animSets.size() - 1, 1236);
					di->setAnimNames(m_animSets[which].m_animInitial, m_animSets[which].m_animFlying, m_animSets[which].m_animFinal, m_fxFinal);
				}
			}
		}
	}

	if (m_specialModelCondition)
		obj->setSpecialModelConditionState(MODELCONDITION_DA, m_specialModelConditionFrames);

	if (m_aiCommandValue > 0 && obj->getAI())
		obj->getAI()->getCommands()->aiCommand31(m_aiCommandValue, CMD_FROM_AI);

	Coord3D offset = m_offset;
	if (mtx)
		adjustVector(&offset, mtx);

	Coord3D chunkPos;
	chunkPos.x = pos->x + offset.x;
	chunkPos.y = pos->y + offset.y;
	chunkPos.z = pos->z + offset.z;

	if (!m_particleSysName.isEmpty())
	{
		const ParticleSystemTemplate *particleSystemTemplate = TheParticleSystemManager->findTemplate(m_particleSysName);
		if (particleSystemTemplate && ((const ParticleSystemTemplateView *)particleSystemTemplate)->m_localPlayerOnly
			&& obj->getControllingPlayer() != ThePlayerList->getLocalPlayer())
			particleSystemTemplate = 0;
		if (particleSystemTemplate)
			TheParticleSystemManager->createParticleSystem(particleSystemTemplate, true)->attachToObject(obj);
	}

	BodyModuleInterface *body = obj->getBodyModule();
	Real healthPercent = GameLogicRandomValueReal(m_minHealth, m_maxHealth, 1281);
	if (body)
		body->setInitialHealth(healthPercent * 100.0f, 0);

	for (BehaviorModule **update = obj->getBehaviorModules(); *update; ++update)
	{
		SlavedUpdateInterface *sdu = (*update)->getBehaviorModuleInterface()->getSlavedUpdateInterface();
		if (sdu != 0)
		{
			sdu->onEnslave(sourceObj);
			break;
		}
	}

	if (m_invulnerableTime > 0)
		obj->rva0028BFF9(m_invulnerableTime);

	PhysicsBehaviorView *physics = obj->getPhysics();
	Coord3D totalForce;
	totalForce.zero();

	if ((m_disposition & 0x10000) && sourceObj)
	{
		static NameKeyType key_SpawnedModelConditionCreate = TheNameKeyGenerator->nameToKey("SpawnedModelConditionCreate");
		Rva003A45D2 *spawned = (Rva003A45D2 *)obj->findModule(key_SpawnedModelConditionCreate);
		if (spawned)
			spawned->rva003A45D2((void *)sourceObj);
	}

	if (m_disposition & 0x1)
	{
		if (mtx)
			obj->setTransformMatrix(mtx);
		else
			obj->setOrientation(orientation);
		obj->m_orientation = orientation;
		obj->setPosition(&chunkPos);
	}
	else if (m_disposition & 0x2000)
	{
		obj->setOrientation(m_spinRate);
		obj->setPosition(&chunkPos);
	}
	else if ((m_disposition & 0x8000) && sourceObj)
	{
		Real angle = m_spinRate + sourceObj->getOrientation();
		angle = normalizeAngle(angle);
		obj->setOrientation(angle);
		obj->setPosition(&chunkPos);
	}
	else if (m_disposition & 0x4000)
	{
		Real angle = (Real)radialIndex * m_spinRate;
		Vector3 radial(m_dispositionIntensity, 0.0f, 0.0f);
		radial.Rotate_Z(angle);
		Coord3D dest = chunkPos;
		dest.x += radial.X;
		dest.y += radial.Y;
		dest.z += radial.Z;
		obj->setOrientation(angle);
		obj->setPosition(&dest);
	}

	if (m_disposition & 0x1000)
	{
		if (!obj->m_status.test(5))
		{
			obj->m_status.set(5);
			obj->rva0028AE6D();
		}
		return;
	}

	if ((m_disposition & 0x80) && sourceObj && physics)
	{
		Coord3D dir;
		sourceObj->getUnitDirectionVector3D(dir);
		scaleInPlace(dir, sourceObj->rva0028AC7D());
		totalForce.add(&dir);
	}

	if ((m_disposition & 0x100) && sourceObj && sourceObj->getPhysics() && physics)
	{
		Coord3D dir;
		sourceObj->getUnitDirectionVector3D(dir);
		scaleInPlace(dir, sourceObj->rva0028AC7D() * m_forceScale);
		((Rva003909FAObj *)physics)->consume(&dir, 0, 0);
	}

	if ((m_disposition & 0x200) && sourceObj && sourceObj->getPhysics() && physics)
	{
		Coord3D dir;
		sourceObj->getUnitDirectionVector3D(dir);
		scaleInPlace(dir, sourceObj->rva0028AC7D() * m_forceScale * -1.0f);
		((Rva003909FAObj *)physics)->consume(&dir, 0, 0);
	}

	if ((m_disposition & 0x400) && physics)
	{
		Coord3D dir = offset;
		dir.z = 0.0f;
		dir.normalize();
		scaleInPlace(dir, m_dispositionIntensity * m_forceScale);
		((Rva003909FAObj *)physics)->consume(&dir, 0, 0);
	}

	if (m_disposition & 0x800)
	{
		static NameKeyType key_FadeAndDieOrnamentUpdate = TheNameKeyGenerator->nameToKey("FadeAndDieOrnamentUpdate");
		HijackerUpdate *fade = (HijackerUpdate *)obj->findModule(key_FadeAndDieOrnamentUpdate);
		if (fade)
			fade->setTargetObject(sourceObj);
	}

	if (m_disposition & 0x2)
	{
		chunkPos.z = 99999.0f;
		PathfindLayerEnum layer = TheTerrainLogic->getHighestLayerForDestination(&chunkPos);
		obj->setOrientation(GameLogicRandomValueReal(0.0f, 2 * 3.14159265359f, 1453));
		if (!(m_disposition & 0x20000) || !TheTerrainLogic->isUnderwater(chunkPos.x, chunkPos.y, &chunkPos.z))
			chunkPos.z = TheTerrainLogic->getLayerHeight(chunkPos.x, chunkPos.y, layer);
		if (layer != LAYER_GROUND)
			chunkPos.z += 1.0f;
		obj->setLayer(layer);
		obj->setPosition(&chunkPos);
	}

	if (m_disposition & 0x10)
	{
		obj->setOrientation(GameLogicRandomValueReal(0.0f, 2 * 3.14159265359f, 1468));
		chunkPos.z = TheTerrainLogic->getGroundHeight(chunkPos.x, chunkPos.y);
		obj->setPosition(&chunkPos);
		Coord3D force;
		Real horizForce = 4.0f * m_dispositionIntensity;
		force.x = GameLogicRandomValueReal(-horizForce, horizForce, 1474);
		force.y = GameLogicRandomValueReal(-horizForce, horizForce, 1475);
		force.z = 0.0f;
		totalForce.add(&force);
		if (m_orientInForceDirection)
			orientation = (Real)atan2((double)force.y, (double)force.x);
	}

	if (m_disposition & 0x2C)
	{
		if (mtx)
			obj->setTransformMatrix(mtx);
		obj->setPosition(&chunkPos);
		if (physics)
		{
			physics->m_allowBouncing = true;
			Coord3D force;
			if (m_disposition & 0x4)
			{
				Real horizForce = 4.0f * m_dispositionIntensity;
				Real vertForce = 3.0f * m_dispositionIntensity;
				force.x = GameLogicRandomValueReal(-horizForce, horizForce, 1502);
				force.y = GameLogicRandomValueReal(-horizForce, horizForce, 1503);
				force.z = GameLogicRandomValueReal(vertForce * 0.33f, vertForce, 1504);
			}
			else if (m_disposition & 0x8)
			{
				Real horizForce = 2.0f * m_dispositionIntensity;
				Real vertForce = 4.0f * m_dispositionIntensity;
				force.x = GameLogicRandomValueReal(-horizForce, horizForce, 1514);
				force.y = GameLogicRandomValueReal(-horizForce, horizForce, 1515);
				force.z = GameLogicRandomValueReal(vertForce * 0.75f, vertForce, 1516);
			}
			else
			{
				calcRandomForce(m_minMag, m_maxMag, m_minPitch, m_maxPitch, &force);
			}
			totalForce.add(&force);
			if (m_orientInForceDirection)
				orientation = (Real)atan2((double)force.y, (double)force.x);
		}
	}

	if (m_disposition & 0x40)
	{
		static NameKeyType key_FloatUpdate = TheNameKeyGenerator->nameToKey("FloatUpdate");
		FloatUpdateView *fu = (FloatUpdateView *)obj->findModule(key_FloatUpdate);
		if (fu)
			fu->m_enabled = true;
	}

	if (totalForce.lengthSqr() > 0.0f && physics)
		((Rva003909FAObj *)physics)->consume(&totalForce, 0, 0);

	if (m_containInsideSourceObject)
	{
		if (sourceObj && sourceObj->getContain() && sourceObj->getContain()->isValidContainerFor(obj, true, 0))
		{
			sourceObj->getContain()->addToContain(obj);
			if (sourceObj->getDrawable() && obj->getDrawable()
				&& ((Rva00270260 *)sourceObj->getDrawable())->rva00270260())
				obj->getDrawable()->setDrawableHidden(true);
		}
		else
		{
			TheGameLogic->destroyObject(obj);
		}
	}
}
