// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
//
// ?doDrawModule@W3DBoatWakeModelDraw@@UAEXPBVMatrix3D@@@Z, retail
// 0x000D0D24..0x000D100A (742 bytes), thiscall RET 4; vtable entry
// 0x007CDD9C of the rowed W3DBoatWakeModelDraw module (deleting dtor
// 0x000D0D08 two slots before its name getters). WB 0x0095EF10 is the debug
// twin (Locomotor::getMaxSpeed, Matrix3D::Get_Z_Rotation, cos, sin).
// Target facts: module data +0x04 (wake offset +0x0C), drawable +0x08 whose
// object is at +0xFC, last speed ratio +0x0C and render object +0x14 (slot
// 21, Set_Transform). The speed ratio steps toward the locomotor's current
// over maximum speed by at most the .data float at VA 0x00DB52E8 (0.005);
// the wake transform is identity, moved to the drawable, turned to its Z
// rotation, offset and scaled by the ratio. Matrix3D/Vector3 inlines are the
// real Zero Hour WWMath headers. Locomotor and render object views keep the
// rowed address-derived spellings.
//
// The speed-ratio test calls fabsf directly. The C++ fabs(float) overload
// inlines through fabsf to the same call, but its extra inline level makes
// cl issue the first argument pop after the fxch instead of before it.
// One view of the W3DBoatWakeModelDraw module for every source of this unit:
// the canonical ObjectModule chain, the Zero Hour WWMath Matrix3D/Vector3
// headers, and address-derived spellings for the locomotor and the render
// object. Target facts: the module data's wake offset is at +0x0C, the
// drawable at +0x08 (ObjectModule's +0x08 slot) holds its object at +0xFC,
// the speed ratio is at +0x0C, a flag at +0x10, the render object at +0x14
// (slot 21, Set_Transform) and the host the destructor unregisters from at
// +0x18; xfer is slot 3 (Snapshot's).
#include "always.h"
#include "vector3.h"
#include "matrix3d.h"
#include <math.h>

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

#include "../../../../../../GameEngine/Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#include "../../../../../../GameEngine/Include/Common/ObjectModule.h"

typedef float Real;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct Rva0028AC4EEntry;
class Rva0008BB38FloatField { public: Real get() const; };
class Locomotor { public: Real getMaxSpeed(Object *obj) const; };

class Object
{
public:
	const Rva0028AC4EEntry *rva0028AC4E() const;
};

class Drawable
{
public:
	Object *getObject() const { return m_object; }
private:
	char m_pad00[0xFC];
	Object *m_object;					// +0xFC
};

class RenderObjClass
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20();
	virtual void Set_Transform(const Matrix3D &m);	// +0x54
};

class DrawModule : public ObjectModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

	Drawable *getDrawable() const { return (Drawable *)m_object; }
};

class W3DBoatWakeModelDrawModuleData;

class W3DBoatWakeModelDraw : public DrawModule
{
public:
	W3DBoatWakeModelDraw(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void doDrawModule(const Matrix3D *transformMtx);

protected:
	virtual void xfer(Xfer *xfer);

	const W3DBoatWakeModelDrawModuleData *getW3DBoatWakeModelDrawModuleData() const
	{
		return (const W3DBoatWakeModelDrawModuleData *)getModuleData();
	}

private:
	Real m_speedRatio;					// +0x0C
	bool m_flag10;						// +0x10
	RenderObjClass *m_renderObject;		// +0x14
	int m_18;							// +0x18
};

class MultiIniFieldParse;

class INI;

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

extern "C" const unsigned char __identifier("??_7W3DBoatWakeModelDrawModuleData@@6B@")[];

class W3DBoatWakeModelDrawModuleData
{
public:
	W3DBoatWakeModelDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

	// +0x00 vtable (installed explicitly by the ctor; no base, no virtuals here).
	const void *m_vtable;
	// +0x04 opaque pad (untouched by the ctor).
	unsigned int m_pad04;
	// +0x08 cleared word (ModelName offset per table 0xBCDEE4).
	unsigned int m_modelName;
	// +0x0C wake offset (Offset per table 0xBCDEE4).
	Vector3 m_wakeOffset;
};

// Native writable speed-ratio step; retail RVA 0x009B52E8 is 0A D7 A3 3B.
Real g_wakeSpeedRatioStep = 0.005f;

static __forceinline void translateWake(Matrix3D &mtx,float m_offsetX,float offsetY,float m_offsetZ){mtx[0][3]+=(mtx[0][0]*m_offsetX)+((mtx[0][1]*offsetY)+((*(const volatile float *)&(mtx[0][2]))*m_offsetZ));
mtx[1][3]+=mtx[1][0]*m_offsetX+mtx[1][1]*offsetY+mtx[1][2]*m_offsetZ;
mtx[2][3]+=mtx[2][0]*m_offsetX+mtx[2][1]*offsetY+mtx[2][2]*m_offsetZ;}
void W3DBoatWakeModelDraw::doDrawModule(const Matrix3D *transformMtx)
{
	Vector3 offset = getW3DBoatWakeModelDrawModuleData()->m_wakeOffset;
	Object *obj = getDrawable()->getObject();
	const Rva0028AC4EEntry *locomotor = obj->rva0028AC4E();
	Real speedRatio = ((const Rva0008BB38FloatField *)locomotor)->get()
		/ ((const Locomotor *)locomotor)->getMaxSpeed(obj);
	if (fabsf(speedRatio - m_speedRatio) > g_wakeSpeedRatioStep)
	{
		if (speedRatio > m_speedRatio)
			speedRatio = m_speedRatio + g_wakeSpeedRatioStep;
		else
			speedRatio = m_speedRatio - g_wakeSpeedRatioStep;
	}
	Matrix3D mtx(true);
	mtx.Translate(transformMtx->Get_Translation());
	mtx.Rotate_Z(transformMtx->Get_Z_Rotation());
	translateWake(mtx,offset.X,offset.Y,offset.Z);
	mtx.Scale(speedRatio);
	m_speedRatio = speedRatio;
	if (m_renderObject)
		m_renderObject->Set_Transform(mtx);
}
