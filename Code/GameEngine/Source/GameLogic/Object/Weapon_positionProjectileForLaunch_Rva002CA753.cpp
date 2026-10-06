// cl: /Oy- /MD /DNDEBUG
//
// ?positionProjectileForLaunch@Weapon@@SAXPAVObject@@PBV2@W4WeaponSlotType@@H@Z
// retail 0x002CA753, 187 bytes (Ghidra FUN_006ca753).
//
// Target evidence: BezierProjectileBehavior (0x0045B9A4) calls it cdecl with
// projectile, launcher, slot and barrel; the body opens with Zero Hour's
// null-launcher TheGameLogic->destroyObject, builds an identity Matrix3D and
// passes it with a Coord3D to the 5-argument cdecl 0x002C9E48
// (calcProjectileLaunchPosition), then unhides the drawable, sets transform
// and position and the experience sink to the launcher's ID.
//
// Donor: GeneralsMD Weapon.cpp Weapon::positionProjectileForLaunch (the
// verbatim port in Weapon.cpp keeps the Zero Hour layout). BFME 2 drops the
// physics velocity transfer. Layouts are TU-local views: Object drawable via
// the out-of-line getDrawable (0x005508E2), ID +0x74, experience tracker
// +0x264.

typedef int Int;
typedef bool Bool;

enum WeaponSlotType
{
	PRIMARY_WEAPON
};

enum ObjectID
{
	INVALID_ID = 0
};

class Matrix3D
{
public:
	__forceinline explicit Matrix3D(bool init)
	{
		if (init)
		{
			m_row[0][0] = 1.0f; m_row[0][1] = 0.0f; m_row[0][2] = 0.0f; m_row[0][3] = 0.0f;
			m_row[1][0] = 0.0f; m_row[1][1] = 1.0f; m_row[1][2] = 0.0f; m_row[1][3] = 0.0f;
			m_row[2][0] = 0.0f; m_row[2][1] = 0.0f; m_row[2][2] = 1.0f; m_row[2][3] = 0.0f;
		}
	}
private:
	float m_row[3][4];
};

struct Coord3D
{
	float x, y, z;
};

class Drawable
{
public:
	void setDrawableHidden(Bool hidden);
};

class ExperienceTracker
{
public:
	void setExperienceSink(ObjectID sink);
};

class Thing
{
public:
	void setTransformMatrix(const Matrix3D *mtx);
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	Drawable *getDrawable() const;
	ObjectID getID() const { return m_id; }
	ExperienceTracker *getExperienceTracker() { return m_experienceTracker; }
private:
	char m_pad00[0x74];
	ObjectID m_id;
	char m_pad78[0x264 - 0x78];
	ExperienceTracker *m_experienceTracker;
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class Weapon
{
public:
	static void calcProjectileLaunchPosition(const Object *launcher, WeaponSlotType wslot, Int specificBarrelToUse, Matrix3D &worldTransform, Coord3D &worldPos);
	static void positionProjectileForLaunch(Object *projectile, const Object *launcher, WeaponSlotType wslot, Int specificBarrelToUse);
};

/*static*/ void Weapon::positionProjectileForLaunch(
	Object* projectile,
	const Object* launcher,
	WeaponSlotType wslot,
	Int specificBarrelToUse
)
{
	// if our launch vehicle is gone, destroy ourselves
	if (launcher == 0)
	{
		TheGameLogic->destroyObject( projectile );
		return;
	}

	Matrix3D worldTransform(true);
	Coord3D worldPos;

	Weapon::calcProjectileLaunchPosition(launcher, wslot, specificBarrelToUse, worldTransform, worldPos);

	projectile->getDrawable()->setDrawableHidden(false);
	projectile->setTransformMatrix(&worldTransform);
	projectile->setPosition(&worldPos);
	projectile->getExperienceTracker()->setExperienceSink( launcher->getID() );
}
