// cl: /O1 /arch:SSE /DNDEBUG /MD

// ?rva004A7551@MissileUpdate@@QAEXPAVObject@@PBUCoord3D@@0HHPBURva0045B936Arg@@PAVRva002CBA7C@@PBVMatrix3D@@@Z @0x004A7551 47B: MissileUpdate gap forward to Bezier rva0045B936 with victim id to m74.
// Target evidence: gap between Rva004A7530Set and rva004A7580 in MissileUpdateCtor TU plus copy [eax+0x74] to [ecx+0x74] plus call Bezier rva0045B936 0x0045B936; callees rowed.

class Object;
struct Coord3D;
struct Rva0045B936Arg;
class Rva002CBA7C;
class Matrix3D;

class BezierProjectileBehavior
{
public:
	virtual void rva0045B936(Object *victim, const Coord3D *victimPos, Object *launcher, int wslot, int specificBarrel, const Rva0045B936Arg *arg6, Rva002CBA7C *helper, const Matrix3D *mtx);
protected:
	char m_pad04[0x74 - 4];
	unsigned int m_74;
};

struct Rva0045B936Arg
{
	int m_00;
	int m_04;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	unsigned char m_pad00[0x74];
	int m_id;
};

class Rva002CBA7C;
class Matrix3D;

class MissileUpdate : public BezierProjectileBehavior
{
public:
	void rva004A7551(Object *victim, const Coord3D *victimPos, Object *launcher, int wslot, int specificBarrel, const Rva0045B936Arg *arg6, Rva002CBA7C *helper, const Matrix3D *mtx);
};

void MissileUpdate::rva004A7551(Object *victim, const Coord3D *victimPos, Object *launcher, int wslot, int specificBarrel, const Rva0045B936Arg *arg6, Rva002CBA7C *helper, const Matrix3D *mtx)
{
	if (victim != 0)
		m_74 = victim->m_id;
	BezierProjectileBehavior::rva0045B936(victim, victimPos, launcher, wslot, specificBarrel, arg6, helper, mtx);
}
