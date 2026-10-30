// cl: /O1 /G7 /arch:SSE /MD /EHsc
#include "../../../../../Libraries/Include/Lib/Coord2D.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

struct Coord3DBase
{
public:
	float x; // +0x00
	float y; // +0x04
	float z; // +0x08
};


float __cdecl ACos(float);
class Rva001F37C4 {public:void rva001F37C4(Xfer*);};
class Rva001FA7AC {public:void rva001FA7AC(int);};
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

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
ParticleSystem *Make001FCBD7();
struct SlaveHandleFAA { void*system;void*prev,*next;operator bool()const{return system!=0;}ParticleSystem*operator->()const{if(!system)return Make001FCBD7();return (ParticleSystem*)system;} };
void XferParticleSystemID(Xfer*,int*);

// Existing rowed module-chain update, called on the two words at particle +94.
class Rva001FA795
{
public:
    void rva001FA795();
};

// Unnamed completion predicate: retail 1F4E2D..1F4E82, WB B0D730.
// Its whole-particle receiver, bool result and zero arguments are established
// by this caller and WB. The original method name remains unknown.
class Rva001F4E2D
{
public:
    bool rva001F4E2D();
};

// Declaration-only view; this unit creates no vtable. Retail and WB both call
// +24 with one float. The earlier slots are outside this body's evidence.
class ParticleAngleModuleView
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void setAngle(float angle);
};

namespace FXParticleSystem
{
// Identity: WB B0D4B0 explicitly names FXParticleSystem::CPUParticle::update
// and asserts m_lifetimeLeft at FXParticleSystem.cpp:918. Target 1FA971..1FAA8D
// establishes the consumed prefix below, including position/previous-position
// pairs and module fields. Unused bytes and original member names stay unknown.
class CPUParticle
{
public:
    bool update();
    void rva001FAA8D(Xfer*);

private:
    char unknown00[0x1C];
    float x, y, z;
    float previousX, previousY, previousZ;
    char unknown34[4];
    bool orientWithMovement;
    char unknown39[0x1B];
    unsigned lifetimeLeft;
    unsigned createdFrame;
    char unknown5C[0x1C];
    SlaveHandleFAA slave;
    unsigned value84,particleID;
    char unknown8C[8];
    void *modules[2];
    ParticleAngleModuleView *angleModule;
};

// CPUParticle::update is provided by FXParticleSystem.cpp.
// Keep this split unit for the independently recovered transfer below.

// Native 1FAA8D..1FAB1E (145B), WB B0D800: light-CRC early return,
// base/module transfers, particle state at88/48/54/58, slave handle78 ID+A8.
// Method name is unknown; transfer offsets and scalar/Coord slots are target facts.
void CPUParticle::rva001FAA8D(Xfer *xfer)
{
 if(xfer->IsLightCRC())return;
 xfer->Version1();
 ((Rva001F37C4*)this)->rva001F37C4(xfer);
 ((Rva001FA7AC*)&modules)->rva001FA7AC((int)xfer);
 *xfer==*(unsigned*)((char*)this+0x88);
 *xfer==*(Coord3DBase*)((char*)this+0x48);
 *xfer==lifetimeLeft;
 *xfer==*(unsigned*)((char*)this+0x58);
 int id=slave?slave->getSystemID():0;
 XferParticleSystemID(xfer,&id);
}
}
