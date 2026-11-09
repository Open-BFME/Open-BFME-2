// cl: /O1 /arch:SSE /G7 /MD /Oy-
// ?rva003FD27E@Rva003FD2C2@@QAE_NXZ
//
// ?rva003FD27E@Rva003FD2C2@@QAE_NXZ, retail 0x003FD27E, 68 bytes.
// Slot 4 of vtable 0x007FE058 (neighbours slot 3 Xfer rva003FD2C2,
// slot 2 name, slot 6 MotionChannel). Class Rva003FD2C2 proven by members
// +0x0C (Coord), +0x18 (float), +0x1C (uint) matching Rva003FD2C2Xfer.cpp
// layout, plus add esi+0x0C pointer use. Global g_00DFEF18 (no name yet)
// with virtuals slot 0x64 (float from uint) and slot 0x9C (void from
// Coord ptr plus two floats). Float literal 0.017453292f (deg2rad).
// Returns true.

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
class DamageInfo;

#include "../../Include/Common/BfmeXfer.h"

#include "../../../Libraries/Include/Lib/Coord3DBase.h"

class Rva002B3092
{
public:
	virtual ~Rva002B3092();
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned int m_04;
	bool m_08;
};

class Rva003FD27EGlobal
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24();
	virtual float slot25(unsigned int v);
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38();
	virtual void slot39(Coord3DBase *p, float a, float b);
};

class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;

class Rva003FD2C2 : public Rva002B3092
{
public:
	bool rva003FD27E();
protected:
	virtual void rva003FD2C2(Xfer *xfer);
private:
	Coord3DBase m_0c;
	float m_18;
	unsigned int m_1c;
};

bool Rva003FD2C2::rva003FD27E()
{
	float deg = m_18 * 0.017453292f;
	reinterpret_cast<Rva003FD27EGlobal *>(((Rva002D3627Host *)TheLivingWorld))->slot39(&m_0c, deg, reinterpret_cast<Rva003FD27EGlobal *>(((Rva002D3627Host *)TheLivingWorld))->slot25(m_1c));
	return true;
}
