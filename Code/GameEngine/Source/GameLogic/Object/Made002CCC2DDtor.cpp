// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common /MD /EHsc /DNDEBUG
//
// ??1Made002CCC2D@@UAE@XZ retail 0x0050BB82 74B
// Novtable derived of Rva00507823 base rowed at 0x00507823. Destroys
// AsciiString at +0x12C via pinned ??1AsciiString at 0x00036410 EH state
// 1 then filter at +0x128 via rowed ??1Rva00360D26Member at 0x00360D26
// EH state 0 then base dtor. No derived vptr store novtable same as
// Rva00508CF7 precedent. Evidence: pinned ctor ??0Made002CCC2D at
// 0x0050BB0E builds filter at +0x128 plus nulls +0x12C plus floats
// plus vtable 0x00864EB0 plus caller deleting 0x0050BB66 calls here.
#include "ascii_string.h"
#include <math.h>
#include <string.h>
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"

// Collaborator views used by the spawn-and-fade body (0x0050B98F). Every call
// target below is a rowed or pinned retail body; only the accessed fields of
// each object are spelled.
extern GameLogic *TheGameLogic;
class Team;
class ThingTemplate;
struct CreateMask
{
	unsigned words[4];
};
enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, ObjectID flag);
};
extern ThingFactory *TheThingFactory;
#include "../../Common/Thing/thing.h"
enum DamageType { DAMAGE_UNKNOWN = 8 };
enum DeathType { DEATH_UNKNOWN = 22 };
class Object
{
public:
	int rva0028B511() const;
	void kill(DamageType damageType, DeathType deathType);
};
struct FadeObjectPrefix
{
	char unknown00[4];
	const ThingTemplate *objectTemplate;
	char unknown08[0x38 - 8];
	Coord3D position;
	float angle;
	char unknown48[0x304 - 0x48];
	Team *team;
};
class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *obj);
};
class AI;
extern AI *TheAI;
struct FadeAIView
{
	char unknown[0x10];
	Pathfinder *pathfinder;
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class FadeTerrainPrefix
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual float height(float x, float y, int layer, void *normal, bool clip);
};
struct FadeInputPrefix
{
	char unknown[8];
	ObjectID id;
};

// WWMath Vector3 subset (WB 0x10A9940 inlines Vector3::Rotate_Z, vector3.h):
// the angle form forwards sinf(angle), cosf(angle) to the X-first rotate.
struct Vector3
{
	float X, Y, Z;
	__forceinline Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	__forceinline void Rotate_Z(float angle)
	{
		Rotate_Z(sinf(angle), cosf(angle));
	}
	__forceinline void Rotate_Z(float s_angle, float c_angle)
	{
		float tmp_x = X;
		float tmp_y = Y;
		X = c_angle * tmp_x - s_angle * tmp_y;
		Y = s_angle * tmp_x + c_angle * tmp_y;
	}
};

// WB copies the source position member by member through a reloaded source
// pointer: an inlined copy, not a struct block move.
inline void copyCoord(Coord3D *dst, const Coord3D *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

class Rva00360D26Member
{
public:
	~Rva00360D26Member();
private:
	int m_x;
};

class Rva00507823
{
public:
	virtual ~Rva00507823();
private:
	unsigned char m_pad[0x128 - 4];
};

class __declspec(novtable) Made002CCC2D : public Rva00507823
{
public:
	virtual ~Made002CCC2D();
	void rva0050B98F(const FadeInputPrefix *input, int unused);
private:
	Rva00360D26Member m_filter128;
	AsciiString m_str12C;
	Coord3D m_offset;
};

Made002CCC2D::~Made002CCC2D()
{
}

// Slot 6 of vftable 0x00C64EB0 (RET 8, second argument unused): spawn the
// configured template on the source object's team at the source position
// plus m_offset rotated by its orientation, ground it, kill the source.
void Made002CCC2D::rva0050B98F(const FadeInputPrefix *input, int unused)
{
	Object *source = TheGameLogic->findObjectByID(input->id);
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(m_str12C);
	if (!thingTemplate)
		return;
	CreateMask mask;
	memset(&mask, 0, sizeof(mask));
	Team *team = ((FadeObjectPrefix *)source)->team;
	Object *made = TheThingFactory->newObject(thingTemplate, team, &mask, (ObjectID)0);
	Coord3D pos;
	copyCoord(&pos, &((FadeObjectPrefix *)source)->position);
	float angle = ((FadeObjectPrefix *)source)->angle;
	Vector3 offset(m_offset.x, m_offset.y, m_offset.z);
	offset.Rotate_Z(angle);
	pos.x += offset.X;
	pos.y += offset.Y;
	pos.z = ((FadeTerrainPrefix *)TheTerrainLogic)->height(pos.x, pos.y, source->rva0028B511(), 0, true);
	((Thing *)made)->setPosition(&pos);
	((Thing *)made)->setOrientation(angle);
	source->kill(DAMAGE_UNKNOWN, DEATH_UNKNOWN);
	if (*(const unsigned char *)((const char *)((FadeObjectPrefix *)made)->objectTemplate + 0x11D) & 0x10)
		((FadeAIView *)TheAI)->pathfinder->AddObjectToPathfindMap(made);
}
