// ?Rva000B2B95FloatMax@@YAMMM@Z
// partial score=1.0 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /MD /EHsc /Oy /O1 /G7 /arch:SSE
// BFME2 W3DView transform builder, native8A653..8AACF, 1148B.
// BFME1 clean donor W3DViewBuildCameraTransformBfme.cpp reviewed at
// 2f243e26d; WB986DA0's transfer/call graph independently links this helper
// to named setCameraTransform and update. Native bytes establish the E0
// context, member offsets, primary slots, globals, and Object position+38.
// Donor supplies the camera-state/smoothing/world-yaw semantics; unexplained
// context fields and the 102F83 state owner retain neutral address names.
// Context constructor10274F and destructor899E5 already own its lifetime.
// Its string handles are non-owning views because that destructor releases
// both. Native RET4 state helper consumes context+0..DC and receiver=this+C0.

#include "Coord3D.h"
#include "Coord2D.h"
#include "ascii_string.h"
#include "matrix3d.h"
#include "GameLogicObjectLookupView.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

struct Region2D{Coord2D lo,hi;};
struct CameraRealTriplet:Coord3D {CameraRealTriplet&operator=(const Coord3D&p){x=p.x;y=p.y;z=p.z;return *this;}};
class Matrix3D;
// Native reads VA DB457C and DE2020 as float; semantic names unknown.
extern Real g_Va00DB457C;
extern Real g_Va00DE2020;

// Opaque ABI views of the two narrow StringBase<char> handles. The existing
// whole-context destructor owns both releases; this view must not duplicate
// member cleanup. The setter is the canonical char specialization at RVA366F0.
struct CameraStringHandle {void*data;void set(const AsciiString&s){reinterpret_cast<StringBase<char>*>(this)->set(*reinterpret_cast<const StringBase<char>*>(&s));} };
// Native constructor10274F zeroes this E0 record; wrapper copies preserve
// donor field interpretations separately from the raw target layout facts.
class Rva000899E5 { public: ~Rva000899E5(); };

class Rva0010274F
{
public:
	Rva0010274F(void);
	~Rva0010274F() { reinterpret_cast<Rva000899E5 *>(this)->~Rva000899E5(); }

	Matrix3D *m_bfme00;
	Real m_bfme04;
	CameraRealTriplet m_group08;
	CameraRealTriplet m_group14;
	CameraRealTriplet m_group20;

	Real m_bfme2c;
	Real m_bfme30;
	Real m_bfme34;
	Real m_bfme38;
	Real m_bfme3c;
	Real m_bfme40;
	Real m_bfme44;
	Real m_bfme48;
	Coord3D m_sourcePosition;

	Coord3D m_outputPosition;

	Coord3D m_targetPosition;

	Int m_bfme70;
	Int m_bfme74;
	unsigned char m_bfme78;
	unsigned char m_bfmeGap79[3];
	Region2D m_constraint;

	unsigned char m_bfme8c;
	unsigned char m_bfmeGap8d[3];
	Coord3D m_cameraOffset;

	unsigned char m_bfme9c;
	unsigned char m_bfmeGap9d[3];
	Real m_bfmea0;
	Int m_bfmea4;
	unsigned char m_bfmea8;
	unsigned char m_bfmea9;
	unsigned char m_bfmeaa;
	unsigned char m_bfmeGapab[1];
	CameraStringHandle m_bfmeac;
	CameraStringHandle m_bfmeb0;
	Int m_bfmeb4;
	Int m_bfmeb8;
	Int m_bfmebc;
	Int m_bfmec0;
	Int m_bfmec4;
	Int m_bfmec8;
	Int m_bfmecc;
	unsigned char m_bfmed0;
	unsigned char m_bfmed1;
	unsigned char m_bfmed2;
	unsigned char m_bfmed3;
	Int m_bfmed4;
 Int m_bfmed8;
 Real m_bfmedc;
};

extern GameLogic *TheGameLogic;

class GameClient
{
	char m_padding00[0xc0];

public:
	Bool m_cameraSlaveActive;
	Bool m_cameraSlaveGuard;
};

extern GameClient *TheGameClient;

enum NameKeyType { NAMEKEY_INVALID = 0, NAMEKEY_MAX = 1 << 23 };
class Rva00148F5ECache{public:NameKeyType get();int key;const char*name;};
class Dict{void*data;public:void setReal(int,float);};
extern Dict g_Va00E00944;
extern Rva00148F5ECache g_00DBDEEC;

// CameraClass::unused050 is slot 20; the raw transform begins at +0x18.
#define CAMERA_UNUSED(n) virtual void unused##n() = 0;
class CameraClass
{
public:
	CAMERA_UNUSED(00) CAMERA_UNUSED(01) CAMERA_UNUSED(02)
	CAMERA_UNUSED(03) CAMERA_UNUSED(04) CAMERA_UNUSED(05)
	CAMERA_UNUSED(06) CAMERA_UNUSED(07) CAMERA_UNUSED(08)
	CAMERA_UNUSED(09) CAMERA_UNUSED(10) CAMERA_UNUSED(11)
	CAMERA_UNUSED(12) CAMERA_UNUSED(13) CAMERA_UNUSED(14)
	CAMERA_UNUSED(15) CAMERA_UNUSED(16) CAMERA_UNUSED(17)
	CAMERA_UNUSED(18) CAMERA_UNUSED(19) CAMERA_UNUSED(20)

	char m_padding04[0x18 - 4];
	Matrix3D m_transform;
};
#undef CAMERA_UNUSED

class W3DViewVtable
{
public:
#define W3D_VOID(n) virtual void w3d##n() = 0;
 
	W3D_VOID(00) W3D_VOID(01) W3D_VOID(02) W3D_VOID(03)
	W3D_VOID(04) W3D_VOID(05) W3D_VOID(06) W3D_VOID(07)
	W3D_VOID(08) W3D_VOID(09) W3D_VOID(10) W3D_VOID(11)
	W3D_VOID(12) W3D_VOID(13) W3D_VOID(14)
	virtual Int w3d15() = 0;
	W3D_VOID(16)
	virtual Int w3d17() = 0;
 virtual void targetSlot48()=0;
	W3D_VOID(18) W3D_VOID(19) W3D_VOID(20) W3D_VOID(21)
	W3D_VOID(22) W3D_VOID(23) W3D_VOID(24) W3D_VOID(25)
	W3D_VOID(26) W3D_VOID(27) W3D_VOID(28) W3D_VOID(29)
	W3D_VOID(30) W3D_VOID(31) W3D_VOID(32) W3D_VOID(33)
	W3D_VOID(34) W3D_VOID(35) W3D_VOID(36) W3D_VOID(37)
	W3D_VOID(38) W3D_VOID(39) W3D_VOID(40) W3D_VOID(41)
	W3D_VOID(42) W3D_VOID(43)
	virtual void w3d44(Int) = 0;
	W3D_VOID(45)
	virtual void w3d46(Int) = 0;
	W3D_VOID(47) W3D_VOID(48) W3D_VOID(49) W3D_VOID(50)
	W3D_VOID(51) W3D_VOID(52) W3D_VOID(53) W3D_VOID(54)
	W3D_VOID(55) W3D_VOID(56) W3D_VOID(57) W3D_VOID(58)
	W3D_VOID(59) W3D_VOID(60) W3D_VOID(61) W3D_VOID(62)
	virtual Real w3d63() = 0;
	W3D_VOID(64)
	virtual Real w3d65() = 0;
	W3D_VOID(66)
	virtual Real w3d67() = 0;
	W3D_VOID(68) W3D_VOID(69) W3D_VOID(70) W3D_VOID(71)
	virtual Real w3d72() = 0;
	W3D_VOID(73) W3D_VOID(74) W3D_VOID(75) W3D_VOID(76)
	W3D_VOID(77) W3D_VOID(78) W3D_VOID(79) W3D_VOID(80)
	W3D_VOID(81) W3D_VOID(82) W3D_VOID(83) W3D_VOID(84)
	W3D_VOID(85) W3D_VOID(86) W3D_VOID(87) W3D_VOID(88)
	W3D_VOID(89) W3D_VOID(90) W3D_VOID(91) W3D_VOID(92)
	W3D_VOID(93) W3D_VOID(94) W3D_VOID(95) W3D_VOID(96)
	W3D_VOID(97) W3D_VOID(98) W3D_VOID(99) W3D_VOID(100)
	W3D_VOID(101) W3D_VOID(102) W3D_VOID(103) W3D_VOID(104)
	W3D_VOID(105) W3D_VOID(106) W3D_VOID(107) W3D_VOID(108)
	W3D_VOID(109) W3D_VOID(110) W3D_VOID(111) W3D_VOID(112)
	W3D_VOID(113)
	virtual Bool w3d114() = 0;
	W3D_VOID(115)
	virtual Int w3d116() = 0;
#undef W3D_VOID
};

class W3DView : public W3DViewVtable
{
private:
	void buildCameraTransform(Matrix3D *transform);

	char m_padding04[0x0c - 4];
	Coord3D m_pos;
	char m_padding18[0x20 - 0x18];
	Int m_field20;
	Int m_field24;
	Real m_field28;
	char m_padding2c[0x6c - 0x2c];
	Real m_field6c;
	Real m_field70;
	char m_padding74[0xc0 - 0x74];
	char m_buildState[4];
	char m_paddingc4[0x104 - 0xc4];
	CameraClass *m_3DCamera;
	char m_padding108[0x10c - 0x108];
	Int m_field10c;
	Int m_field110;
	char m_padding114[0x118 - 0x114];
	Int m_field118;
	Int m_field11c;
	char m_padding120[0x12c - 0x120];
	Real m_field12c;
	Real m_field130;
	Real m_field134;
	Real m_field138;
	char m_padding13c[0x1cc - 0x13c];
	Int m_field1cc;
	char m_padding1d0[0x1dc - 0x1d0];
	Bool m_cameraSlaveObject;
	char m_padding1dd[0x2354 - 0x1dd];
	Int m_cameraMovementMode;
	char m_padding2358[0x2364 - 0x2358];
 Real m_modeFov;
 char m_padding2368[0x23c8 - 0x2368];
	Bool m_cameraState23b8;
	char m_padding23b9[0x23e8 - 0x23c9];
	Coord3D m_cameraOffset;
	char m_padding23e4[0x2408 - 0x23f4];
	Real m_groundLevel;
	Region2D m_cameraConstraint;
	Bool m_cameraConstraintValid;
	char m_padding240d[0x2420 - 0x241d];
	Real m_field2410;
	Real m_field2414;
	Real m_field2418;
	Real m_field241c;
	Real m_field2420;
	Real m_field2424;
	unsigned char m_field2428;
	unsigned char m_field2429;
	unsigned char m_field242a;
	unsigned char m_padding242b;
	AsciiString m_field242c;
	AsciiString m_field2430;
	char m_padding2434[8];
	Coord3D m_cameraPoint243c;
};

// Native receiver=this+C0, context pointer stack argument, RET4 at10404B.
class Rva00102F83Owner
{
public: void rva00102F83(Rva0010274F *context);
};

typedef char CameraContextMustBe224Bytes[(sizeof(Rva0010274F) == 0xE0) ? 1 : -1];
typedef char CameraTransformMustBe48Bytes[(sizeof(Matrix3D) == 48) ? 1 : -1];

// Native B2B87..B2B95 and B2B95..B2BA3 are complete 14-byte float
// minimum/maximum helpers. Retail and MSVC optimize these internal helpers
// to a private XMM0 plus stack-float ABI with an XMM0 result. The original
// names and source argument order are unknown; CameraMin/CameraMax are donor
// labels only (BFME1 clean donor at 575ba2b). No native call/data reference
// establishes a public cdecl ABI. /Oy preserves the existing 1148-byte camera
// builder and naturally emits these helpers with their complete retail bodies.
static __forceinline float Rva000B2B95FloatMax(float a,float b) { return a>b?a:b; }
static __forceinline float Rva000B2B87FloatMin(float a,float b) { return a<b?a:b; }
void W3DView::buildCameraTransform(Matrix3D *transform)
{
	if (TheGameLogic == 0) return;
	if (m_cameraMovementMode == 3)
	{
		CameraClass *camera = m_3DCamera;
		camera->unused20();
		*transform = camera->m_transform;
		return;
	}

	Rva0010274F context;
	context.m_bfme00 = transform;
	context.m_bfme04 = g_Va00DB457C;
	context.m_group08 = *reinterpret_cast<const Coord3D*>(&m_field2410);
	context.m_group14 = *reinterpret_cast<const Coord3D*>(&m_field241c);
	context.m_group20 = *reinterpret_cast<const Coord3D*>(&m_field12c);
	context.m_bfme2c = m_groundLevel;
	context.m_bfme30 = w3d72();
	context.m_bfme34 = w3d63();
	context.m_bfme38 = w3d65();
	context.m_bfme3c = w3d67();
	context.m_bfme40 = m_field6c;
	context.m_bfme44 = g_Va00DE2020;
	Coord3D *position = &m_pos;
	context.m_sourcePosition = *position;
	context.m_outputPosition = *position;
	context.m_bfme70 = m_field118;
	context.m_bfme74 = m_field11c;
	context.m_bfme78 = m_cameraConstraintValid;

	if (m_cameraConstraintValid)
	{
		context.m_constraint = m_cameraConstraint;
	}

	context.m_bfme8c = m_field242a;
	context.m_cameraOffset = m_cameraOffset;
	context.m_bfme9c = w3d114();
	context.m_bfmea0 = m_field70;
	context.m_bfmea4 = w3d116();
	context.m_bfmea8 = m_field2428;
	context.m_bfmea9 = m_cameraSlaveObject;
	context.m_bfmeaa = m_field2429;
	context.m_bfmeac.set(m_field242c);
	context.m_bfmeb0.set(m_field2430);

	context.m_bfmeb4 = m_field10c;
	context.m_bfmeb8 = m_field110;
	context.m_bfmebc = w3d15();
	context.m_bfmec0 = w3d17();
	context.m_bfmec4 = m_field20;
	context.m_bfmec8 = m_field24;
	context.m_bfmecc = (Int)m_3DCamera;
	context.m_bfmed0 = false;
	context.m_bfmed4 = m_cameraMovementMode;
 context.m_bfmed8=(Int)*(void**)((char*)this+0x235c);

	if (m_field138 != 0.0f)
	{
		if (m_cameraSlaveObject)
		{ context.m_bfme48 = m_field138; }
		else
		{
			Real step = m_field138 * 0.1f;
			if (m_field138 < 3.0f && m_field138 > -3.0f)
				m_field138 = 0.0f;
			else if (step > 0.0f)
			{
				step = Rva000B2B95FloatMax(3.0f, step);
				m_field138 -= step;
			}
			else if (step < 0.0f)
			{
				step = Rva000B2B87FloatMin(-3.0f, step);
				m_field138 += step;
			}
			context.m_bfme48 = m_field138;
		}
	}

	if (m_cameraState23b8)
	{
		context.m_targetPosition = m_cameraPoint243c;
	}
	else if (m_cameraSlaveObject)
	{
		Object *result = TheGameLogic->findObjectByID((ObjectID)m_field1cc);
		if (result != 0)
		{
			// Native copies Object+38 directly, then applies context height.
			const Coord3D *point = reinterpret_cast<const Coord3D*>(reinterpret_cast<const char*>(result)+0x38);
			context.m_targetPosition = *point;
			context.m_targetPosition.z += context.m_bfme48;
		}
		else { context.m_targetPosition.x=0.0f;context.m_targetPosition.y=0.0f;context.m_targetPosition.z=0.0f; }
	}
	else { context.m_targetPosition.x=0.0f;context.m_targetPosition.y=0.0f;context.m_targetPosition.z=0.0f; }

	reinterpret_cast<Rva00102F83Owner *>(reinterpret_cast<char *>(this) + 0xc0)->rva00102F83(&context);

	m_cameraMovementMode=context.m_bfmed4;
 m_modeFov=context.m_bfmedc;
	w3d44(context.m_bfmeb4);
	w3d46(context.m_bfmeb8);
	*position = context.m_outputPosition;

	if (TheGameClient->m_cameraSlaveGuard || TheGameClient->m_cameraSlaveActive)
	{
		NameKeyType key = g_00DBDEEC.get();
		g_Va00E00944.setReal(key, m_field28 * 57.2957763671875f);
	}

}
