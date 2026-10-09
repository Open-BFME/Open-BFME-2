// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// stlport
// BaseUpgrade::upgradeImplementation; native4B37CA..4B39F5/555.
// Identity: owned ctor4B371C installs C570D8 at+10; native slot10 is this body.
// Clean semantic donor: BF1 f98983a7d BaseUpgradeUpgradeImplementation.cpp.
// Target module-data strings118/11C/index120; Object matrix8/position38;
// Player team2EC and AI pathfinder10 are independently read from native/WB1236AA0.
// The previously unowned bone-transform helper30A528 is verified separately.
// Rva004B37CAPosition is an emitter scope over canonical Coord3D's12B layout:
// the target requires user-defined empty array ctor/dtor semantics. It makes
// no claim to a second retail coordinate class or an owned function address.
// Actual emitted callback bodies are byte-and-relocation twins of the existing
// empty coordinate ctor/dtor; the reference Matrix3D/Vector4 rows are48/16B.
// Explicit inline Matrix3D ctor restores the native3-row iterator; real128-bit
// zero mask and post-initialization team lookup preserve native register homes.
#include <bitset>

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;


static const char *inlineStr(const AsciiString &s)
{
	const char *text = *reinterpret_cast<const char *const *>(&s);
	return text ? text + 8 : "";
}

#include "Lib/Coord3D.h"
struct Rva004B37CAPosition : Coord3D {
 Rva004B37CAPosition() {}
 ~Rva004B37CAPosition() {}
 void set(float ax,float ay,float az) {x=ax;y=ay;z=az;}
};
class Vector4
{
public:
	Vector4() {}

	Real X;
	Real Y;
	Real Z;
	Real W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	Real Get_X_Translation() const { return Row[0].W; }
	Real Get_Y_Translation() const { return Row[1].W; }
	Real Get_Z_Translation() const { return Row[2].W; }
	Real Get_Z_Rotation() const;

private:
	Vector4 Row[3];
};

struct WorldMatrix
{
	Real m[12];
};

class BaseUpgradeModuleData
{
public:
	virtual ~BaseUpgradeModuleData();

	unsigned char m_pad[0x114];
	AsciiString m_buildingTemplateName;
	AsciiString m_placementPrefix;
	Int m_placementIndex;
};

class ThingTemplate;
class Team;
class Object;

template <Int NUMBITS>
class BitFlags
{
public:
	BitFlags() {}

private:
	_STL::bitset<NUMBITS> m_bits;
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
	__forceinline const Coord3D *getPosition() const
	{
		return &m_cachedPos;
	}
	__forceinline const Matrix3D *getTransformMatrix() const
	{
		return &m_transform;
	}
	void convertBonePosToWorldPos(const Coord3D *bonePos,
		const Matrix3D *boneTransform, Coord3D *worldPos,
		Matrix3D *worldTransform) const;
	void setOrientation(Real angle);
	void setPosition(const Coord3D *position);

private:
	unsigned char m_head[8];
	Matrix3D m_transform;
	Coord3D m_cachedPos;
};

class Player
{
public:
	void onStructureCreated(Object *,Object *);
	__forceinline Team *team230() const
	{
		return const_cast<Team *>(*reinterpret_cast<Team * const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x2EC));
	}
};

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	Drawable *getDrawable() const;

	Player *getControllingPlayer() const;
	void setProducer(Object *producer);
	void rva0028AFE7(Object *builder);
	
};

struct CreateMask {_STL::bitset<128> bits;};
class ThingFactory {public:
 const ThingTemplate *findTemplate(const AsciiString &name);
 Object *newObject(const ThingTemplate *,Team *,const CreateMask *,Bool);
};
class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
};

class AI
{
private:
	unsigned char m_pad[0x10];

public:
	Pathfinder *m_pathfinder;
};

extern ThingFactory *TheThingFactory;
extern AI *TheAI;
class BaseUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void BaseUpgrade::upgradeImplementation()
{
	unsigned char *self = reinterpret_cast<unsigned char *>(this);
	BaseUpgradeModuleData *moduleData =
		*reinterpret_cast<BaseUpgradeModuleData **>(self - 0xc);
	Object *object = *reinterpret_cast<Object **>(self - 8);
	if (object == 0)
		return;
	Player *player = object->getControllingPlayer();
	if (player == 0)
		return;

	Drawable *drawable = object->getDrawable();
	if (drawable == 0)
		return;

	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(
		moduleData->m_buildingTemplateName);
	if (thingTemplate == 0)
		return;

	Rva004B37CAPosition bonePositions[32];
	Matrix3D boneTransforms[32];
	Int placementIndex = moduleData->m_placementIndex;
	const char *prefix = inlineStr(moduleData->m_placementPrefix);
	Int boneCount = drawable->getPristineBonePositions(
		prefix, 1, bonePositions, boneTransforms, 32, 0);

	Rva004B37CAPosition position;
	Real orientation;
	WorldMatrix worldTransform;
	if (placementIndex > 0 && placementIndex < boneCount)
	{
		worldTransform.m[0] = 1.0f;
		worldTransform.m[1] = 0.0f;
		worldTransform.m[2] = 0.0f;
		worldTransform.m[3] = 0.0f;
		worldTransform.m[4] = 0.0f;
		worldTransform.m[5] = 1.0f;
		worldTransform.m[6] = 0.0f;
		worldTransform.m[7] = 0.0f;
		worldTransform.m[8] = 0.0f;
		worldTransform.m[9] = 0.0f;
		worldTransform.m[10] = 1.0f;
		worldTransform.m[11] = 0.0f;
		(reinterpret_cast<const Thing *>(object))->convertBonePosToWorldPos(
			0, &boneTransforms[placementIndex], 0,
			reinterpret_cast<Matrix3D *>(&worldTransform));
		position.set(worldTransform.m[3], worldTransform.m[7], worldTransform.m[11]);
		orientation = reinterpret_cast<const Matrix3D *>(&worldTransform)->Get_Z_Rotation();
	}
	else
	{
		const Thing *thing = reinterpret_cast<const Thing *>(object);
		const Coord3D *objectPosition = thing->getPosition();
		position.set(objectPosition->x, objectPosition->y, objectPosition->z);
		orientation = thing->getTransformMatrix()->Get_Z_Rotation();
	}

	CreateMask status;
	Team *team230 = player->team230();
	Object *newObject = TheThingFactory->newObject(
		thingTemplate, team230, &status, false);
	newObject->setProducer(object);
	newObject->rva0028AFE7(object);
	reinterpret_cast<Thing *>(newObject)->setPosition(&position);
	reinterpret_cast<Thing *>(newObject)->setOrientation(orientation);
	TheAI->m_pathfinder->AddObjectToPathfindMap(newObject);
	player->onStructureCreated(object,newObject);
}
