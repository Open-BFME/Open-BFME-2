// cl: /O1 /arch:SSE /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1DynamicPortalBehaviourModuleData@@UAE@XZ, retail 0x00461602 (120 bytes).
// ??_GDynamicPortalBehaviourModuleData@@UAEPAXI@Z, retail 0x004615E6 (26 bytes).
// Destruction shard for the DynamicPortal wall-portal data (ctor lives in
// DynamicPortalBehaviourModuleDataCtor.cpp, which keeps its own decls; this
// shard declares the destruction view with stlport-free member views so the
// teardown calls resolve exactly). Members die in reverse declaration
// order: the +0x158 filter through the opaque dtor at 0x00360D26, the
// +0x138 WallBoundsMesh through the folded string dtor at 0x00036410, the
// +0x12C Link vector through the 12B-element vector dtor at 0x004613EB
// (its clearer at 0x003F29F8 steps with stride 0xC and destroys each
// element through 0x0007FAB3, so Link elements are 12B owner records, not
// the 8B pods the ctor shard assumes for the shared Vector_base call),
// the +0x120 WayPoint 8B-pod vector by inline null-checked free through
// 0x00030830, and the +0x11C BonePrefix through 0x00036410.
// The WayPoint free uses a TU-local C++-linkage spelling (pinned at
// 0x00030830 beside the pre-existing ?free@@ alias): the C++ decoration is
// throwing, which is what makes the caller emit retail's state-1 store
// ahead of the branch (?free@@ precedent). The vptr is restored to the
// base table at 0x00BBB554 with no base call (the inline-empty virtual
// base dtor inlines to nothing while still earning the reset). The dtor
// itself is implicit (a user-defined empty body earns a vptr install
// retail does not have; UpgradeModuleDataDtor precedent) forced out by the
// delete helper, which also emits the vtable and scalar-deleting dtor.

class OpenContainModuleData
{
public:
	virtual ~OpenContainModuleData() {}

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

// TU-local throwing free spelling for the WayPoint inline teardown
// (pinned at 0x00030830; see header note).
void freeWayPointVecStorage(void *ptr);

// 8B-pod vector view (three pointers). The inline dtor frees through the
// TU-local throwing spelling, which earns retail's state-1 store.
struct DynamicPortalWayPointVec
{
	~DynamicPortalWayPointVec()
	{
		if (m_start != 0)
			freeWayPointVecStorage(m_start);
	}

	void *m_start;
	void *m_finish;
	void *m_end;
};

// 12B-element vector view (three pointers). The dtor is declared-only and
// resolves to the 12B-element teardown at 0x004613EB via pin.
struct DynamicPortalLinkVec
{
	~DynamicPortalLinkVec();

	void *m_start;
	void *m_finish;
	void *m_end;
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

class DynamicPortalBehaviourModuleData : public OpenContainModuleData
{
public:
	DynamicPortalBehaviourModuleData();

// Implicit virtual dtor (never declared, never defined): the compiler
// emits it for the vtable/??_G chain with member teardown in reverse
// order, the base vtable restore, and the trivial base inlined away.
private:
	int m_numberOfBones; // +0x118, NumberOfBones
	AsciiString m_bonePrefix; // +0x11C, BonePrefix
	DynamicPortalWayPointVec m_wayPoint; // +0x120, WayPoint
	DynamicPortalLinkVec m_link; // +0x12C, Link
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

// ??0DynamicPortalBehaviourModuleData@@QAE@XZ present-unmatched
DynamicPortalBehaviourModuleData::DynamicPortalBehaviourModuleData()
{
}

// Forces the vtable, implicit virtual dtor and scalar-deleting dtor to be
// emitted here (UpgradeModuleDataDtor precedent).
void deleteDynamicPortalBehaviourModuleData(DynamicPortalBehaviourModuleData *p)
{
	delete p;
}
