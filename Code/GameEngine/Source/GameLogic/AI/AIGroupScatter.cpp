// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// platformsdk
// stlport
// AIGroup::groupRotateFiringarc, native 003706C8..00370795 (205 bytes).
// groupScatter (0x0036F757) lives in AIGroupRva00372571.cpp beside the strong
// getMinMaxAndCenter it calls.
#include <windows.h>
#include <list>

// Keep the typed node comparison local; these flags otherwise emit an
// incompatible external STLport base-iterator comparison.
namespace _STL {
template <class T, class L, class R>
static inline bool operator!=(const _List_iterator<T, L> &a,
                              const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}

// Coord3D: shared header/view; no private copy.
#include "../../../../Libraries/Include/Lib/Coord3DInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

inline Real sqr(Real x) { return x * x; }

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

// Only the word computeGroundPath reads: Object::m_ai+0x1DC is handed to
// Pathfinder::IsLineBlocked as its second argument (Zero Hour passes the
// locomotor set's valid surfaces there to isLinePassable).
class AICommandInterface
{
public:
	virtual void aiDoCommand(const struct AICommandParms *parms);
	void aiIdle(CommandSourceType cmdSource);
	void rva0036F6A7(float angle, CommandSourceType cmdSource);
	// Zero Hour's aiGoProne (0x0036F400: AICMD 0x1D copying the DamageInfo
	// into the command block at +0x3C), rowed under a placeholder whose
	// parameter class Rva003427DD is that DamageInfo.
	void aiGoProne(const class Rva003427DD *info, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	void *getValidSurfaces() const { return m_validSurfaces; }
	AICommandInterface *getCommands() { return &m_commands; }

private:
	char m_pad0[0x20];
	AICommandInterface m_commands;
	char m_pad21[0x1DC-0x24];
	void *m_validSurfaces;	// +0x1DC
};

class ThingTemplate
{
public:
	UnsignedInt isKindOf(UnsignedInt mask) const { return m_kindOf & mask; }

private:
	char m_pad0[0x108];
	UnsignedInt m_kindOf;	// +0x108
};

#include "../Object/object.h"

class AIGroup
{
public:
	void groupRotateFiringarc(const Coord3D *pos, CommandSourceType cmdSource);

private:
	virtual ~AIGroup();
	void recompute();

	std::list<Object *> m_memberList;	// +0x04
	Real m_speed;						// +0x08
	Bool m_dirty;						// +0x0C
	char m_pad0D[0x14 - 0x0D];
	void *m_groundPath;					// +0x14
	Coord3D m_pathStart;				// +0x18
	Coord3D m_pathEnd;					// +0x24
};

#include <math.h>
// Both levels must remain visible: the length helper proves that the address
// passed to Normalize2D does not escape. This lets MSVC eliminate the initial
// coordinate stores before the subtraction in groupRotateFiringarc.
inline float Coord3D::GetLength2D() const
{
	float xValue = x;
	float yValue = y;
	return (float)sqrt(xValue * xValue + yValue * yValue);
}

__declspec(noinline) inline float Coord3D::Normalize2D()
{
	float len = GetLength2D();
	float scale = 1.0f / len;
	x *= scale;
	y *= scale;
	return len;
}

// The canonical coordinate is a plain layout view. WB EEBCC0 shows a copied
// three-float local with an empty destructor, then sub and GetLengthSqrd2D.
struct RotateCoord : Coord3D
{
	RotateCoord(const Coord3D &p) { x = p.x; y = p.y; z = p.z; }
	~RotateCoord() {}
	void sub(const Coord3D *p) { x -= p->x; y -= p->y; z -= p->z; }
	float GetLengthSqrd2D() const { return x * x + y * y; }
};

float ACos(float x);

// Native 003706C8..00370795 (205 bytes), WB EEBCC0, AIGroup.cpp:4256.
void AIGroup::groupRotateFiringarc(const Coord3D *pos, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		if (!obj)
			continue;
		AIUpdateInterface *ai = obj->getAI();
		if (!ai)
			continue;
		RotateCoord dir(*pos);
		dir.sub(obj->getPosition());
		if (dir.GetLengthSqrd2D() < 1.0f)
			continue;
		dir.Normalize2D();
		float angle;
		if (dir.y < 0.0f)
			angle = -ACos(dir.x);
		else
			angle = ACos(dir.x);
		ai->getCommands()->rva0036F6A7(angle, cmdSource);
	}
}
