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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};


float __cdecl ACos(float);
class Rva001F37C4 {public:void rva001F37C4(Xfer*);};
class Rva001FA7AC {public:void rva001FA7AC(int);};
class ParticleSystem {public:int getSystemID()const{return systemID;}char unknown[0xA8];int systemID;};
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
