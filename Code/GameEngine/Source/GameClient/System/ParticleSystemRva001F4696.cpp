// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva001F4696@ParticleSystem@@QAEXPAX0_N0@Z, retail 0x001F4696, 354 bytes.
// ParticleSystem slave-chain promotion: same slave slot +0x15C and factory pin as
// ParticleSystem::destroy neighbour; offsets measured from retail disassembly.
// Evidence: slave wrapper +0x15C with Make001FCBD7 pin, burst vars +0x44/+0x50 via
// ?getValue@GameClientRandomVariable@@QBEMXZ rows, virtual +0x24 on holder +0xA4.

class ParticleSystem;

ParticleSystem *Make001FCBD7(void);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeParticleSystemPtr
{
public:
	operator ParticleSystem *(void) const
	{
		return m_target;
	}

	ParticleSystem *operator->(void) const
	{
		ParticleSystem *target = m_target;
		if (!target)
			target = Make001FCBD7();
		return target;
	}

public:
	ParticleSystem *m_target;
};

class GameClientRandomVariable
{
public:
	float getValue(void) const;
private:
	float m_min;
	float m_max;
	int m_dist;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct FortyEight
{
	int v[12];
};

class HolderA4
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual void v3(void);
	virtual void v4(void);
	virtual void v5(void);
	virtual void v6(void);
	virtual void v7(void);
	virtual void v8(void);
	virtual void v9(void *a, int b);
};

struct ParticleView
{
	unsigned char pad0[4];
	unsigned char flag4;
	unsigned char pad5[0x44 - 5];
	GameClientRandomVariable var44;
	GameClientRandomVariable var50;
	unsigned char pad5C[0x6C - 0x5C];
	Coord3D off6C;
	unsigned char pad78[0xA4 - 0x78];
	HolderA4 *holderA4;
	unsigned char padA8[0xEC - 0xA8];
	FortyEight fieldEC;
	int count11C;
	unsigned char pad120[0x13C - 0x120];
	float scale13C;
	float scale140;
	Coord3D pos144;
	unsigned char pad150[0x15C - 0x150];
	BfmeParticleSystemPtr slave15C;
	unsigned char pad160[0x16C - 0x160];
	int flag16C;
	unsigned char pad170[0x1A1 - 0x170];
	bool flag1A1;
};

class ParticleSystem
{
public:
	void rva001F4696(void *pos, void *arg, bool b, void *info);
};

void ParticleSystem::rva001F4696(void *posArg, void *arg2, bool b, void *infoArg)
{
	ParticleView *self = (ParticleView *)this;
	Coord3D *pos = (Coord3D *)posArg;
	FortyEight *info = (FortyEight *)infoArg;

	if (self->flag16C != 0)
	{
		self->flag1A1 = b;
		if (!b)
		{
			self->fieldEC.v[0] = info->v[0];
			self->fieldEC.v[1] = info->v[1];
			self->fieldEC.v[2] = info->v[2];
			self->fieldEC.v[3] = info->v[3];
			int *d1 = &self->fieldEC.v[4];
			int *s1 = &info->v[4];
			d1[0] = s1[0];
			d1[1] = s1[1];
			d1[2] = s1[2];
			d1[3] = s1[3];
			int *d2 = &self->fieldEC.v[8];
			int *s2 = &info->v[8];
			d2[0] = s2[0];
			d2[1] = s2[1];
			d2[2] = s2[2];
			d2[3] = s2[3];
		}
		Coord3D *dstPos = &self->pos144;
		*dstPos = *pos;
		dstPos->x += self->off6C.x;
		dstPos->y += self->off6C.y;
		dstPos->z += self->off6C.z;
	}

	if (self->count11C == 0)
	{
		int n = (int)self->var50.getValue();
		if (self->holderA4 != 0)
		{
			int scaled = (int)((float)n * self->scale13C);
			self->holderA4->v9(arg2, scaled);
		}
		int m = (int)self->var44.getValue();
		float f = (float)(unsigned int)m;
		float g = f * self->scale140;
		self->count11C = (int)g;
	}
	else
	{
		if (self->flag4 != 0)
		{
			self->count11C = 1;
		}
		else
		{
			self->count11C -= 1;
		}
	}

	BfmeParticleSystemPtr *slavePtr = &self->slave15C;
	if (slavePtr->m_target == 0)
		return;
	_ReadWriteBarrier();
	ParticleSystem *next = slavePtr->operator->();
	next->rva001F4696(&self->pos144, arg2, b, info);
}
