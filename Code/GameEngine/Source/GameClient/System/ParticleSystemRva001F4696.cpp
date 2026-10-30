// cl: /DNDEBUG /MD /EHsc
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
	ParticleSystem *m_target; // +0x00
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
	GameClientRandomVariable m_burstDelay;
	GameClientRandomVariable m_burstCount;
	unsigned char pad5C[0x6C - 0x5C];
	Coord3D m_slavePosOffset;
	unsigned char pad78[0xA4 - 0x78];
	HolderA4 *holderA4;
	unsigned char padA8[0xEC - 0xA8];
	FortyEight fieldEC;
	int m_burstDelayLeft;
	unsigned char pad120[0x13C - 0x120];
	float m_countCoeff;
	float m_delayCoeff;
	Coord3D m_pos;
	unsigned char pad150[0x15C - 0x150];
	BfmeParticleSystemPtr m_slaveSystem;
	unsigned char pad160[0x16C - 0x160];
	int flag16C;
	unsigned char pad170[0x1A1 - 0x170];
	bool flag1A1;
};

class ParticleSystem
{
public:
	void rva001F4696(void *pos, void *arg, bool m_isIdentity, void *info);
};

void ParticleSystem::rva001F4696(void *posArg, void *priority, bool m_isIdentity, void *infoArg)
{
	ParticleView *self = (ParticleView *)this;
	Coord3D *pos = (Coord3D *)posArg;
	FortyEight *info = (FortyEight *)infoArg;

	if (self->flag16C != 0)
	{
		self->flag1A1 = m_isIdentity;
		if (!m_isIdentity)
		{
			self->fieldEC.v[0] = info->v[0];
			self->fieldEC.v[1] = info->v[1];
			self->fieldEC.v[2] = info->v[2];
			self->fieldEC.v[3] = info->v[3];
			int *destinationYRow = &self->fieldEC.v[4];
			int *sourceYRow = &info->v[4];
			destinationYRow[0] = sourceYRow[0];
			destinationYRow[1] = sourceYRow[1];
			destinationYRow[2] = sourceYRow[2];
			destinationYRow[3] = sourceYRow[3];
			int *destinationZRow = &self->fieldEC.v[8];
			int *sourceZRow = &info->v[8];
			destinationZRow[0] = sourceZRow[0];
			destinationZRow[1] = sourceZRow[1];
			destinationZRow[2] = sourceZRow[2];
			destinationZRow[3] = sourceZRow[3];
		}
		Coord3D *dstPos = &self->m_pos;
		*dstPos = *pos;
		dstPos->x += self->m_slavePosOffset.x;
		dstPos->y += self->m_slavePosOffset.y;
		dstPos->z += self->m_slavePosOffset.z;
	}

	if (self->m_burstDelayLeft == 0)
	{
		int count = (int)self->m_burstCount.getValue();
		if (self->holderA4 != 0)
		{
			int scaled = (int)((float)count * self->m_countCoeff);
			self->holderA4->v9(priority, scaled);
		}
		int burstDelay = (int)self->m_burstDelay.getValue();
		float burstDelayFloat = (float)(unsigned int)burstDelay;
		float scaledBurstDelay = burstDelayFloat * self->m_delayCoeff;
		self->m_burstDelayLeft = (int)scaledBurstDelay;
	}
	else
	{
		if (self->flag4 != 0)
		{
			self->m_burstDelayLeft = 1;
		}
		else
		{
			self->m_burstDelayLeft -= 1;
		}
	}

	BfmeParticleSystemPtr *slavePtr = &self->m_slaveSystem;
	if (slavePtr->m_target == 0)
		return;
	_ReadWriteBarrier();
	ParticleSystem *next = slavePtr->operator->();
	next->rva001F4696(&self->m_pos, priority, m_isIdentity, info);
}
