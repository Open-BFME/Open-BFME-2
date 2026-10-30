// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ?rva001F465E@ParticleSystem@@QAEXPAX@Z, retail 0x001F465E, 56 bytes.
// ParticleSystem slave-chain setter for +0x98 with same +0x15C Make001FCBD7
// chain as neighbour ?rva001F45F4 (0x001F45F4 56B). Gap between destroy
// 0x001F462C and 0x001F4696; offsets from retail disassembly.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct Rva003AFA0BVector
{
public:
	Rva003AFA0BVector() {}
	Rva003AFA0BVector(float a, float b, float c) : x(a), y(b), z(c) {}
	__forceinline Rva003AFA0BVector(const Rva003AFA0BVector &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	float x; // +0x00
	float y; // +0x04
	float z; // +0x08
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
	enum DistributionType { CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS };
	float getValue(void) const;
	void setRange(float low, float high, DistributionType type);
	char data[0x20]; // +0x00
};

struct Rva001F55A8Info;
struct Coord3D;
class ParticleSystem
{
public:
	Rva003AFA0BVector rva001F54C5(const Rva003AFA0BVector *pos);
	void rva001F55A8(Rva001F55A8Info *info, int particleNum, int particleCount);
	bool isSaveable() const;
	void destroy(void);
	void rva001F45F4(bool flag);
	void rva001F465E(void *val);
	int getSystemID()const{return systemID;}
	char m_pad00[0x14];
	GameClientRandomVariable lifetime; // +0x14 +0x14
	GameClientRandomVariable sizeBonusRate; // +0x34 +0x34
	char m_pad54[0x2E];
	char upFlag82; // +0x82 +0x82
	char m_pad83[0x15];
	void *m_val98; // +0x98 +0x98
	char m_pad9C[0xC];
	int systemID; // +0xA8
	char m_padAC[0x40];
	Matrix3DView xform; // +0xEC +0xEC
	char m_pad11C[0x28];
	Coord3D pos; // +0x144 +0x144
	Coord3D lastPos; // +0x150 +0x150
	ParticleSystem *m_next15C; // +0x15C +0x15C
	char m_pad160[0x20];
	float accumulatedSizeBonus; // +0x180 +0x180
	char m_pad184[0x1D];
	bool isIdentity; // +0x1A1 +0x1A1
	char m_pad1A2[0x3];
	bool isFirstPos; // +0x1A5 +0x1A5
	bool m_flag1A6; // +0x1A6 +0x1A6
	char m_pad1A7[0x193];
	bool m_saveable; // +0x33A +0x33A
	char m_pad33B[0x1];
};

extern ParticleSystem *Make001FCBD7(void);

void ParticleSystem::rva001F465E(void *val)
{
	m_val98 = val;
	if (m_next15C == 0)
		return;
	ParticleSystem *cur = this;
	ParticleSystem *nxt;
	do
	{
		nxt = cur->m_next15C;
		if (nxt == 0)
			nxt = Make001FCBD7();
		nxt->m_val98 = val;
		_ReadWriteBarrier();
		cur = nxt;
	} while (nxt->m_next15C != 0);
}
