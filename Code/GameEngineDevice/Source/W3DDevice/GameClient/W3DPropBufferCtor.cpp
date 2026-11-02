// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ??0W3DPropBuffer@@QAE@XZ retail 0x000EF008..0x000EF137 (303 bytes).
// Zero Hour's W3DPropBuffer constructor (GameEngineDevice/Source/W3DDevice/
// GameClient/W3DPropBuffer.cpp, GeneralsMD tree) on the BFME 2 layout used by
// W3DPropBufferAddProp.cpp: TProp[4000] (0x30) at +0x04, m_numProps
// +0x2EE04, three flags +0x2EE08..A, TPropType[96] (0x18) at +0x2EE18,
// m_numPropTypes +0x2F718, the shroud pass +0x2F71C and the light +0x2F724.
// Target facts: vtable 0x00BCEECC (VA); BaseHeightMapRenderObjClass's
// constructor 0x0006C9CF allocates 0x2F728 bytes and calls this; the light is
// the rowed LightClass(LightType) 0x00130AC0 with DIRECTIONAL and the pass is
// the rowed W3DShroudMaterialPassClass ctor 0x0006E29F. BFME 2 adds a
// 12-byte vector holder at +0x2EE0C (its out-of-line default ctor is the ICF
// body 0x001F81BF) and a cleared dword at +0x2F720. clearAllProps is inlined
// in BFME 2's form: each type's render object is cleared and its bounds set to
// a unit sphere at the origin (WorldBuilder twin 0x0088F030 writes the same).
// The array element constructors and destructors are the ICF bodies at
// 0x0047A6A9 / 0x000B3FD0 (TProp) and 0x004B9910 / 0x0029D7C2 (TPropType).
#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
static __forceinline Vector3 &copyStorageVector3(Vector3 &out,const Vector3 &in) {out.X=in.X;out.Y=in.Y;out.Z=in.Z;return out;}



class SphereClass
{
public:
	SphereClass() {}
	void Init(const Vector3 &pos, float radius) { copyStorageVector3(Center,pos); Radius = radius; }
	Vector3 Center;
	float Radius;
};

class RenderObjClass;

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID
};

struct TProp
{
	TProp() {}
	~TProp() {}

	RenderObjClass *m_robj;
	Int id;
	Coord3D location;
	Int propType;
	ObjectShroudStatus ss;
	Bool visible;
	SphereClass bounds;
};

struct TPropType
{
	RenderObjClass *m_robj;
	AsciiString m_robjName;
	SphereClass m_bounds;
};

class LightClass
{
public:
	enum LightType
	{
		POINT = 0,
		DIRECTIONAL,
		SPOT
	};
	LightClass(LightType type);

private:
	unsigned char m_unrecovered[0x120];
};

class W3DShroudMaterialPassClass
{
public:
	W3DShroudMaterialPassClass();

private:
	unsigned char m_unrecovered[0x3C];
};

// The BFME 2 vector holder at +0x2EE0C; element type and role unrecovered.
// Its default constructor is the ICF body 0x001F81BF (rowed as
// Rva00174753Allocation's); its unwind copy of the destructor is 0x0008B4CD,
// a tail jump to the rowed vector destructor 0x0008B470.
class Rva00174753Allocation
{
public:
	Rva00174753Allocation() throw();

private:
	void *m_vector[3];
};

class Rva0008B470
{
public:
	~Rva0008B470();
};

struct Rva0008B4CD : public Rva00174753Allocation
{
	~Rva0008B4CD() { reinterpret_cast<Rva0008B470 *>(this)->~Rva0008B470(); }
};

class W3DPropBuffer : public Snapshot
{
public:
	W3DPropBuffer(void);
	virtual ~W3DPropBuffer(void);

protected:
	virtual void loadPostProcess(void);
	virtual const char *GetSnapshotName(void) const;
	virtual void xfer(Xfer *xfer);

	enum { MAX_PROPS = 4000 };
	enum { MAX_TYPES = 96 };

	TProp m_props[MAX_PROPS];
	Int m_numProps;
	Bool m_anythingChanged;
	Bool m_initialized;
	Bool m_doCull;
	Rva0008B4CD m_list2EE0C;
	TPropType m_propTypes[MAX_TYPES];
	Int m_numPropTypes;
	W3DShroudMaterialPassClass *m_propShroudMaterialPass;
	Int m_bfme2F720;
	LightClass *m_light;
};

W3DPropBuffer::W3DPropBuffer(void)
	: m_numProps(0), m_anythingChanged(false), m_initialized(false), m_doCull(false)
{
	m_numPropTypes = 0;
	m_bfme2F720 = 0;
	Int i;
	for (i = 0; i < MAX_TYPES; i++) {
		m_propTypes[i].m_robj = 0;
		m_propTypes[i].m_bounds.Init(Vector3(0.0f, 0.0f, 0.0f), 1.0f);
	}
	for (i = 0; i < MAX_PROPS; i++) {
		m_props[i].m_robj = 0;
	}
	m_light = new LightClass(LightClass::DIRECTIONAL);
	m_propShroudMaterialPass = new W3DShroudMaterialPassClass;
	m_initialized = true;
}
