// ?rva001F55A8@ParticleSystem@@QAEXPAURva001F55A8Info@@HH@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva001F55A8@ParticleSystem@@QAEXPAURva001F55A8Info@@HH@Z, retail 0x001F55A8, 812 bytes.
// ParticleSystem per-particle start values (BFME2 trim of ZH ParticleSystem::generateParticleInfo:
// position, velocity, emission adjustment, lifetime, accumulated size bonus, emitter position,
// up-towards-emitter flag). Donor: GeneralsMD ParticleSys.cpp; layout facts are retail-measured.
// Position helper 0x001F553F and velocity helper 0x001F54C5 are rowed; max size bonus 50.0f is
// the retail constant at 0x00BD5E50.

struct Rva003AFA0BVector
{
	Rva003AFA0BVector() {}
	float x, y, z;
};

struct Coord3D
{
	float x, y, z;
};

struct Rva001F55A8Info
{
	char pad00[0x10];
	Rva003AFA0BVector vel;
	Rva003AFA0BVector pos;
	Rva003AFA0BVector emitterPos;
	int lifetime;
	char upTowardsEmitter;
};

struct Matrix3DView
{
	float m[3][4];
	__forceinline void mulVector3(const Rva003AFA0BVector &v, Rva003AFA0BVector &o) const
	{
		o.x = m[0][2] * v.z + m[0][1] * v.y + m[0][0] * v.x + m[0][3];
		o.y = m[1][2] * v.z + m[1][1] * v.y + m[1][0] * v.x + m[1][3];
		o.z = m[2][2] * v.z + m[2][1] * v.y + m[2][0] * v.x + m[2][3];
	}
	__forceinline void rotateVector(const Rva003AFA0BVector &v, Rva003AFA0BVector &o) const
	{
		o.x = m[0][2] * v.z + m[0][1] * v.y + m[0][0] * v.x;
		o.y = m[1][2] * v.z + m[1][1] * v.y + m[1][0] * v.x;
		o.z = m[2][2] * v.z + m[2][1] * v.y + m[2][0] * v.x;
	}
};

class GameClientRandomVariable
{
public:
	float getValue(void) const;
	char data[0x20];
};

class Rva001F553F
{
public:
	Coord3D *rva001F553F(Coord3D *out, unsigned int num, unsigned int count);
};

class ParticleSystem
{
public:
	Rva003AFA0BVector rva001F54C5(const Rva003AFA0BVector *pos);
	void rva001F55A8(Rva001F55A8Info *info, int particleNum, int particleCount);

	char pad00[0x14];
	GameClientRandomVariable lifetime;
	GameClientRandomVariable sizeBonusRate;
	char pad54[0x82 - 0x54];
	char upFlag82;
	char pad83[0xec - 0x83];
	Matrix3DView xform;
	char pad11c[0x144 - 0x11c];
	Coord3D pos;
	Coord3D lastPos;
	char pad15c[0x180 - 0x15c];
	float accumulatedSizeBonus;
	char pad184[0x1a1 - 0x184];
	bool isIdentity;
	char pad1a2[3];
	bool isFirstPos;
};

void ParticleSystem::rva001F55A8(Rva001F55A8Info *info, int particleNum, int particleCount)
{
	if (particleCount)
	{
		{
			Coord3D p0;
			*(Coord3D *)&info->pos = *((Rva001F553F *)this)->rva001F553F(&p0, (unsigned)particleNum, (unsigned)particleCount);
		}
		info->vel = rva001F54C5(&info->pos);
		Rva003AFA0BVector *vp = &info->vel;

		if (!isIdentity)
		{
			if (isFirstPos)
			{
				lastPos = pos;
				isFirstPos = false;
			}
			float fcount = (float)particleCount;
			Coord3D emissionAdjustment;
			emissionAdjustment.x = (1 - ((float)particleNum / fcount)) * (pos.x - lastPos.x);
			emissionAdjustment.y = (1 - ((float)particleNum / fcount)) * (pos.y - lastPos.y);
			emissionAdjustment.z = (1 - ((float)particleNum / fcount)) * (pos.z - lastPos.z);
			Rva003AFA0BVector p, pr;
			p.x = info->pos.x;
			p.y = info->pos.y;
			p.z = info->pos.z;
			xform.mulVector3(p, pr);
			info->pos.x = pr.x - emissionAdjustment.x;
			info->pos.y = pr.y - emissionAdjustment.y;
			info->pos.z = pr.z - emissionAdjustment.z;
			Rva003AFA0BVector vv, vr;
			vv.x = vp->x;
			vv.y = vp->y;
			vv.z = vp->z;
			xform.rotateVector(vv, vr);
			vp->x = vr.x;
			vp->y = vr.y;
			vp->z = vr.z;
		}

		info->lifetime = (int)lifetime.getValue();
		accumulatedSizeBonus += sizeBonusRate.getValue();
		if (accumulatedSizeBonus)
		{
			const float maxBonus = 50.0f;
			accumulatedSizeBonus = accumulatedSizeBonus < maxBonus ? accumulatedSizeBonus : maxBonus;
		}

		Rva003AFA0BVector e, z0;
		z0.x = 0.0f;
		z0.y = 0.0f;
		z0.z = 0.0f;
		xform.mulVector3(z0, e);
		info->emitterPos = e;
		info->upTowardsEmitter = upFlag82;
	}
}
