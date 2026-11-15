// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2 W3DView::W3DView, retail RVA 0x0008B7CF (827 bytes, RET), plus the
// implicit constructors of its four camera-move record types
// (0x00085858, 0x0008587B, 0x0008589E, 0x000858C1, 35 bytes each).
//
// Target evidence: the slot-118 factory 0x0008EFD8 constructs this object;
// native 8B7CF..8BB0A builds View (0x0025EDE6), a data-only base at +0xC0
// (its inline constructor clears +0x28), SubsystemInterface at +0xB4
// (0x001B4E63), then stores the W3DView vftables 0x00BC7568 / 0x00BC7530.
// The EH unwind map (FuncInfo 0x00D02884, nine states) names the destroyed
// subobjects: ~View 0x0025EF18, ~SubsystemInterface 0x001B4E74, the camera
// path at +0x280 (0x00089971), the two 0x60-byte movers at +0x22F4/+0x2368
// (0x0008B77D), the vectors at +0x23DC/+0x2458 (folded 0x0007FAB3) and the
// AsciiStrings at +0x243C/+0x2440 (0x0048BA39). The camera-move records at
// +0x1AC/+0x1E0/+0x208/+0x22C/+0x258 are value-initialized members: retail
// zero-fills each (rep stosd) and then calls its implicit constructor, which
// default-constructs the ParabolicEase inside it through 0x0008517E (0, 0, 1).
// The WorldBuilder twin 0x00985680 gives the member order, constructs the
// +0x2478 member with the same constructor as the +0xC0 base (its +0x28 is
// the +0x24A0 store) and calls the +0x24F4 member's constructor 0x000857CD.
// The body reloads the camera settings (+0x24C8 slots 17/18), scales the
// camera offset by View +0xA0, reserves 50 location requests, sets View +0x70
// to 1 and calls 0x00087973 with 0.
// Donor: Zero Hour W3DView::W3DView supplies the class identity and the names
// of the rotate/pitch/zoom records, their flags and the camera path/lock
// members; every other member keeps an offset name. Record field layouts past
// the ease member are structural inferences from the zero-fill extents.
#define BFME_ASCII_DTOR_DECL
#include "../../../../GameEngine/Include/GameClient/Rva0008990CArrayOwner.h"
#include <vector>
#if defined(BFME2_MODERN)
#include "../../../../GameEngine/Include/Common/ModernCameraInterpolation.h"
#endif

typedef bool Bool;
typedef int Int;

// Camera-move records (ZH TRotateCameraInfo / TPitchCameraInfo /
// TZoomCameraInfo shape: plain fields plus one ParabolicEase).
struct Rva00085858 { Int m_00[5]; ParabolicEase m_ease; Int m_1C[5]; };
struct Rva000858C1 { Int m_00[7]; ParabolicEase m_ease; };
struct Rva0008587B { Int m_00[6]; ParabolicEase m_ease; };
struct Rva0008589E { Int m_00[8]; ParabolicEase m_ease; };

struct Rva0008B7CFPair { Real x, y; Rva0008B7CFPair() { x = 0.0f; y = 0.0f; } };
struct Rva0008B7CFTriple { Real x, y, z; Rva0008B7CFTriple() { x = 0.0f; y = 0.0f; z = 0.0f; } };

class View
{
public:
	View();
	virtual ~View();
	char m_pad04[0x28 - 4];
	Real m_angle;
	char m_pad2c[0x70 - 0x2c];
	Real m_unknown70;
	char m_pad74[0xa0 - 0x74];
	Real m_unknowna0;
	char m_pada4[0xb4 - 0xa4];
};

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

// Data-only record used as the +0xC0 base and the +0x2478 member.
class Rva000C0Record
{
public:
	Rva000C0Record() { m_28 = 0; }
private:
	char m_pad00[0x28];
	int m_28;
	char m_pad2c[0x44 - 0x2c];
};

class Rva00085815
{
public:
	Rva00085815();
private:
	char m_pad[0x70];
};

class Rva00312C95 : public Rva000851F3
{
public:
	Rva00312C95();
	virtual ~Rva00312C95();
	virtual void rva00047A69C(int);
	virtual void rva00086B2C(int, int, Real, Real, int, int);
private:
	char m_pad2c[0x60 - 0x2c];
};

struct Rva0008DE1CElement { char m_pad[24]; };
namespace _STL {
template <> void vector<Rva0008DE1CElement, allocator<Rva0008DE1CElement> >::reserve(size_t);
}

class Rva0030E7D0
{
public:
	Rva0030E7D0();
	~Rva0030E7D0();
private:
	char m_pad[0x20];
};

class Rva00BCF670CameraSettings
{
public:
	Rva00BCF670CameraSettings();
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual void reload();
	virtual void getOffset(Rva0008B7CFTriple *offset, Real *angle);
private:
	char m_pad[0x2c - 4];
};

class Rva000857CD
{
public:
	Rva000857CD();
private:
	Real m_0, m_4, m_8;
	unsigned char m_C, m_D, m_E, m_F, m_10;
};

class W3DView : public View, public Rva000C0Record, public SubsystemInterface
{
public:
	W3DView();
	virtual ~W3DView();
	void rva00087973(Int value);
private:
	int m_104;
	int m_108;
	int m_10C;
	int m_110;
	Bool m_114, m_115;
	Rva0008B7CFPair m_118;
	Real m_120, m_124, m_128;
	Rva0008B7CFTriple m_12C;
	Real m_138;
	Rva00085815 m_13C;
	Rva00085858 m_rcInfo;
	Bool m_doingRotateCamera;
	Rva000858C1 m_pcInfo;
	Bool m_doingPitchCamera;
	Rva0008587B m_zcInfo;
	Bool m_doingZoomCamera;
	Rva0008589E m_22C;
	Bool m_254;
	Rva000858C1 m_258;
	Bool m_doingScriptedCameraLock, m_CameraArrivedAtWaypointOnPathFlag;
	Rva0089971 m_cameraPath;
	Rva00312C95 m_22F4;
	int m_cameraMovementMode, m_2358, m_235C, m_2360;
	int m_2364;
	Rva00312C95 m_2368;
	Bool m_23C8;
	int m_23CC;
	Bool m_23D0;
	int m_23D4;
	Bool m_cameraHasMovedSinceRequest;
	_STL::vector<Rva0008DE1CElement> m_locationRequests;
	Rva0008B7CFTriple m_cameraOffset;
	Rva0008B7CFPair m_23F4;
	Rva0008B7CFPair m_23FC;
	Real m_2404;
	Real m_groundLevel;
	char m_pad240c[0x241c - 0x240c];
	Bool m_cameraConstraintValid;
	Rva0008B7CFTriple m_2420;
	Rva0008B7CFTriple m_242C;
	Bool m_2438, m_2439, m_243A;
	AsciiString m_243C;
	AsciiString m_2440;
	Real m_2444;
	Bool m_2448, m_2449;
	Rva0008B7CFTriple m_244C;
	Rva0030E7D0 m_cameraHeightField;
	Rva000C0Record m_2478;
	int m_24BC;
	Bool m_24C0;
	int m_24C4;
	Rva00BCF670CameraSettings m_cameraLimits;
	Rva000857CD m_24F4;
};

W3DView::W3DView()
	: m_104(0), m_108(0), m_10C(15), m_110(9), m_114(false), m_115(false),
	  m_120(0.0f), m_124(0.0f), m_128(0.0f), m_138(0.0f),
	  m_rcInfo(), m_doingRotateCamera(false),
	  m_pcInfo(), m_doingPitchCamera(false),
	  m_zcInfo(), m_doingZoomCamera(false),
	  m_22C(), m_254(false),
	  m_258(), m_doingScriptedCameraLock(false), m_CameraArrivedAtWaypointOnPathFlag(false),
	  m_cameraMovementMode(0), m_2358(0), m_235C(0), m_2360(0),
	  m_23C8(false), m_23CC(0), m_23D0(false), m_23D4(0), m_cameraHasMovedSinceRequest(true),
	  m_2404(0.0f), m_groundLevel(10.0f),
	  m_cameraConstraintValid(false),
	  m_2438(false), m_2439(false), m_243A(false),
	  m_2444(1.0f), m_2448(false), m_2449(false),
	  m_24BC(0), m_24C0(false), m_24C4(0)
{
#if defined(BFME2_MODERN)
    modernResetCamera(this);
#endif
	m_cameraLimits.reload();
	m_cameraLimits.getOffset(&m_cameraOffset, &m_angle);
	m_cameraOffset.x = m_unknowna0 * m_cameraOffset.x;
	m_cameraOffset.y = m_unknowna0 * m_cameraOffset.y;
	m_locationRequests.reserve(50);
	m_unknown70 = 1.0f;
	rva00087973(0);
}

// Names this unit's unwind graph references that no unit defines under this spelling. ~W3DView is
// the rowed destructor at 0x0008BD5E (W3DViewAggregateDtor.cpp). Retail's constructor unwind
// funclets 0x0075FC37 and 0x0075FC45 both jump to 0x0048BA39, the StringBase<char> destructor row,
// which is the cleanup of the string-holding camera-height member (Rva0030E7D0, 0x20 bytes).
#pragma comment(linker, "/alternatename:??1W3DView@@UAE@XZ=??1Rva008BD5E@@UAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0030E7D0@@QAE@XZ=??1?$StringBase@D@@AAE@XZ")
