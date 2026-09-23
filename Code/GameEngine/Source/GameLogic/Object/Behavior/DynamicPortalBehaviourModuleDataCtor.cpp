// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0DynamicPortalBehaviourModuleData@@QAE@XZ, retail 0x0046142A (261 bytes).
// DynamicPortal wall-portal data over the rowed OpenContainModuleData base
// ctor (0x253487, 0x118 base): NumberOfBones at +0x118 is zero,
// BonePrefix at +0x11C is an inline-null AsciiString cleared through the
// folded clear at 0x00036410 (Image clear-after-null precedent),
// WayPoint at +0x120 is an 8B-element vector built through the folded
// Vector_base at 0x00211E58 and cleared through erase at 0x003FA4DB
// (OCL clear-lowers-to-erase precedent), Link at +0x12C is a second
// 8B-element vector, WallBoundsMesh at +0x138 is op='d from "", GenerateNow
// at +0x13C and AllowEnemies at +0x13D are false, AboveWall at +0x140 is -1,
// TopAttackPos at +0x144 is zero, TopAttackRadius at +0x150 is 5.0f,
// ActivationDelaySeconds at +0x154 is 0.0f, and DestroyedDamageTimeoutMS at
// +0x158 builds through the opaque 0x3623E5 pin with one 28B FixedStorage
// temp from the prototype at 0x00DFEFA4 fed through applyFilter at
// 0x00362120 (CallHelp single-storage precedent). Own table 0x00C42A38
// proves every field; the DynamicPortalBehaviour data factory at 0x0024B4B3
// news 0x15C with this ctor pinned as sole caller. Explicit vtable store
// through a TU-local static (no ??_7 pin at 0x00C42930); base and derived
// dtors declared-only so no vtable is emitted here. Scalar defaults ride the
// init-list (the init region schedules ahead of the implicit filter
// construction, which is how those stores land before the filter call with
// no cross-call motion); TopAttackPos stays a body statement through a
// pointer local, which is what emits retail's lea-plus-indirect zero stores.
#include <vector>

class OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();

private:
	unsigned char m_pad[0x118 - 4]; // +0x04..+0x117
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	AsciiString &operator=(const char *str);
	~AsciiString();

private:
	void *m_data;
};

// 8B INI-list element (erase at 0x3FA4DB is the 8B-element build);
// WayPoint/Link parse procs 0x86133B/0x8616B1 are unclaimed, so the two
// fields stay a neutral ordered pair here.
struct DynamicPortalWayPoint
{
	int m_first;
	int m_second;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D storage);

private:
	int m_timeoutMs;
};

struct Coord3D
{
	float m_x;
	float m_y;
	float m_z;
};

static int s_vtable;

class DynamicPortalBehaviourModuleData : public OpenContainModuleData
{
public:
	DynamicPortalBehaviourModuleData();
	virtual ~DynamicPortalBehaviourModuleData();

private:
	int m_numberOfBones; // +0x118, NumberOfBones
	AsciiString m_bonePrefix; // +0x11C, BonePrefix
	_STL::vector<DynamicPortalWayPoint> m_wayPoint; // +0x120, WayPoint
	_STL::vector<DynamicPortalWayPoint> m_link; // +0x12C, Link
	AsciiString m_wallBoundsMesh; // +0x138, WallBoundsMesh
	bool m_generateNow; // +0x13C, GenerateNow
	bool m_allowEnemies; // +0x13D, AllowEnemies
	unsigned char m_pad13E[2];
	int m_aboveWall; // +0x140, AboveWall
	Coord3D m_topAttackPos; // +0x144, TopAttackPos
	float m_topAttackRadius; // +0x150, TopAttackRadius
	float m_activationDelaySeconds; // +0x154, ActivationDelaySeconds
	Rva003623E5Filter m_destroyedDamageTimeout; // +0x158, DestroyedDamageTimeoutMS
};

// ??0DynamicPortalBehaviourModuleData@@QAE@XZ @0x0046142A
DynamicPortalBehaviourModuleData::DynamicPortalBehaviourModuleData() :
	OpenContainModuleData(),
	m_numberOfBones(0),
	m_generateNow(false),
	m_allowEnemies(false),
	m_aboveWall(-1),
	m_topAttackRadius(5.0f),
	m_activationDelaySeconds(0.0f)
{
	m_wallBoundsMesh = "";
	m_bonePrefix.clear();
	m_wayPoint.clear();
	Coord3D *topAttackPos = &m_topAttackPos;
	topAttackPos->m_x = 0.0f;
	topAttackPos->m_y = 0.0f;
	topAttackPos->m_z = 0.0f;
	m_destroyedDamageTimeout.applyFilter(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
