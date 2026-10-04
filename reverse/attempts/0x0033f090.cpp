// ?getAllPoints@ProjectileStreamUpdate@@QAEXPAVVector3@@PAH@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /G7 /GX /DNDEBUG /MD /arch:SSE
//
// ?getAllPoints@ProjectileStreamUpdate@@QAEXPAVVector3@@PAH@Z @0x0033F090, 143B.
// ProjectileStreamUpdate::getAllPoints BFME2 version: unrolls circular
// projectile-ID buffer (20 at +0x20, indices at +0x70/+0x74), resolves each
// via rowed GameLogic::findObjectByID, then via pinned Thing::getDrawable
// (ICF twin of rowed getDesiredGatherers at 0x005508E2) and pinned
// BFMERopeDrawable::getPosition, copying xyz via movss or zeroing via xorps.
// Evidence: gap between considerDying 0x0033F06B and update 0x0033F11F in the
// same TU; donor ZH getAllPoints proves Vector3*/Int* signature and MAX=20
// circular logic; retail replaces vehicle-roof branch with drawable check.
typedef int Int;

enum ObjectID
{
	INVALID_ID = -1
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class Object;
class Drawable;
class GameLogic;

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class ProjectileStreamUpdate
{
public:
	void getAllPoints(Vector3 *points, Int *count);

private:
	char m_pad[0x20];
	ObjectID m_projectileIDs[20];
	int m_firstValidOrNextFree70;
	int m_firstValidOrNextFree74;
};

// ?getAllPoints@ProjectileStreamUpdate@@QAEXPAVVector3@@PAH@Z present-unmatched
void ProjectileStreamUpdate::getAllPoints(Vector3 *points, Int *count)
{
	Int pointCount = 0;
	Int pointIndex = m_firstValidOrNextFree74;
	Vector3 *out = points;
	while (pointIndex != m_firstValidOrNextFree70) {
		float x, y, z;
		Object *projectile = TheGameLogic->findObjectByID(m_projectileIDs[pointIndex]);
		if (projectile) {
			Drawable *drawable = projectile->getDrawable();
			if (drawable) {
				const Coord3D *pos = ((BFMERopeDrawable *)drawable)->getPosition();
				y = pos->y;
				z = pos->z;
				x = pos->x;
				out->Y = y;
				out->Z = z;
			}
			else {
				out->Y = 0;
				out->Z = 0;
				x = 0;
			}
		}
		else {
			out->Y = 0;
			out->Z = 0;
			x = 0;
		}
		pointIndex = (pointIndex + 1) % 20;
		pointCount++;
		out->X = x;
		++out;
	}
	*count = pointCount;
}
