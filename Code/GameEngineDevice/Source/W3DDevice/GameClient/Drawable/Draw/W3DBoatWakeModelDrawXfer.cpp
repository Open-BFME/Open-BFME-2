// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
//
// ?xfer@W3DBoatWakeModelDraw@@MAEXPAVXfer@@@Z, retail 0x000D0BC3, 58 bytes.
// Slot 3 (offset 0x0C) of vtable 0x007CDD70 (VA 0x00BCDD70, class of rowed ctor
// ??0W3DBoatWakeModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z in
// W3DBoatWakeModelDrawCtor.cpp): base DrawModule xfer via rowed 0x004CBF58,
// then Version(1,2) via Xfer slot 0x28, then version-gated float at +0x0C
// via Xfer slot 0x70. Layout is the rowed ctor shape (DrawModule base 0x0C
// plus float m_speedRatio plus bool plus two pointers); only m_speedRatio is persistent (v2 adds
// it, v1 has none). Recipe is InvisibilityUpdateXfer slot-3 pattern with
// GameSlot Version(1,2) gating and Random float slot 0x70.

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

void W3DBoatWakeModelDraw::xfer(Xfer *xfer)
{
	DrawModule::xfer(xfer);
	Xfer::Version version(1, 2);
	*xfer == version;
	if (version.m_minimum >= 2) {
		*xfer == m_speedRatio;
	}
}
