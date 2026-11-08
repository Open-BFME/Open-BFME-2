// cl: /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc
// ??0Locomotor@@QAE@PBVLocomotorTemplate@@_N@Z, retail 0x001E449A..0x001E4625
// (395 bytes, EH, ret 8): Locomotor's constructor, called by the rowed
// LocomotorStore::newLocomotor (0x001E4A81) on its 0xB0-byte allocation
// (pinned name). Zero Hour's constructor body as BFME 2 builds it: the final
// override of the template (inline Overridable::getFinalOverride over the
// rowed friend_getFinalOverride 0x001E35DF), the zeroed maintain/position
// coords, braking factor 1, BIGNUM limits (retail keeps -1 in the +0x2C slot),
// the template's close-enough distance (+0xC4) and preferred-height pair
// (+0x58..+0x60), the PI/40 wander increment (no random draws in BFME 2), the
// identity transform whose three 16-byte rows go through the vector
// constructor iterator over the folded empty row ctor 0x0047A6A9, the BFME 2
// tail state (+0x98..+0xAC, 100 at +0xAC), the live-locomotor counter the
// rowed destructor decrements (data ledger name kept), and the
// IS_CLOSE_ENOUGH_DIST_3D flag from the template (+0xC8). Table 0x00BDE888.
// Field names past Zero Hour's are offsets only.
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#define BIGNUM 99999.0f

class Overridable
{
public:
	Overridable *friend_getFinalOverride();					// 0x001E35DF
	// Keep the retail inline walk without an extra competing outline.
	__declspec(dllimport) __forceinline const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
protected:
	virtual ~Overridable();
private:
	Overridable *m_nextOverride;							// +0x04
};

class LocomotorTemplate : public Overridable
{
public:
	unsigned char m_pad08[0x58 - 0x08];
	Real m_58;												// +0x58
	Real m_5C;												// +0x5C
	Real m_60;												// +0x60
	unsigned char m_pad64[0xC4 - 0x64];
	Real m_closeEnoughDist;									// +0xC4
	Bool m_isCloseEnoughDist3D;								// +0xC8
};

// The transform rows: 16 bytes with the folded empty out-of-line ctor.
struct Rva0047A6A9Row16
{
	Rva0047A6A9Row16();										// 0x0047A6A9
	Real x, y, z, w;
};

// Zero Hour's Coord3D zeroing (its inline zero()), which re-reads nothing it
// stores; the locomotor's two coords are constructed zeroed.
struct LocomotorCoord3D
{
	Real x, y, z;
	__forceinline LocomotorCoord3D() { zero(); }
	__forceinline void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

// The transform: WWMath's Matrix3D (three 16-byte rows) built identity by its
// inline ctor.
struct LocomotorMatrix3D
{
	Rva0047A6A9Row16 Row[3];
	__forceinline LocomotorMatrix3D(bool init) { if (init) Make_Identity(); }
	__forceinline void Make_Identity()
	{
		Row[0].x = 1.0f; Row[0].y = 0.0f; Row[0].z = 0.0f; Row[0].w = 0.0f;
		Row[1].x = 0.0f; Row[1].y = 1.0f; Row[1].z = 0.0f; Row[1].w = 0.0f;
		Row[2].x = 0.0f; Row[2].y = 0.0f; Row[2].z = 1.0f; Row[2].w = 0.0f;
	}
};

extern int g_Va00DFDC64;									// live locomotors

class Locomotor : public Snapshot
{
public:
	Locomotor(const LocomotorTemplate *tmpl, Bool unused);

protected:
	virtual ~Locomotor(); // protected, as rowed at 0x003067D2 (Locomotor.cpp)
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	enum LocoFlag
	{
		IS_CLOSE_ENOUGH_DIST_3D = 10
	};
	void setFlag(LocoFlag f, Bool b);						// 0x001E3459

	const LocomotorTemplate *m_template;					// +0x04
	LocomotorCoord3D m_maintainPos;							// +0x08
	LocomotorCoord3D m_position;							// +0x14
	Real m_brakingFactor;									// +0x20
	Real m_maxLift;											// +0x24
	Real m_maxSpeed;										// +0x28
	Real m_2C;												// +0x2C
	Real m_maxAccel;										// +0x30
	Real m_maxBraking;										// +0x34
	Real m_maxTurnRate;										// +0x38
	Real m_closeEnoughDist;									// +0x3C
	Real m_40;												// +0x40
	UnsignedInt m_flags;									// +0x44
	Real m_preferredHeight;									// +0x48
	Real m_4C;												// +0x4C
	Real m_preferredHeightDamping;							// +0x50
	Real m_angleOffset;										// +0x54
	Real m_offsetIncrement;									// +0x58
	Real m_5C;												// +0x5C
	Int m_60;												// +0x60
	Int m_64;												// +0x64
	LocomotorMatrix3D m_transform;							// +0x68
	Bool m_98;												// +0x98
	Bool m_99;												// +0x99
	Bool m_9A;												// +0x9A
	Int m_9C;												// +0x9C
	Real m_A0;												// +0xA0
	Real m_A4;												// +0xA4
	Int m_A8;												// +0xA8
	Int m_AC;												// +0xAC
};

Locomotor::Locomotor(const LocomotorTemplate *locomotorTemplate, Bool unused)
	: m_template((const LocomotorTemplate *)locomotorTemplate->getFinalOverride()),
	  m_brakingFactor(1.0f),
	  m_maxLift(BIGNUM), m_maxSpeed(BIGNUM), m_2C(-1.0f),
	  m_maxAccel(BIGNUM), m_maxBraking(BIGNUM), m_maxTurnRate(BIGNUM),
	  m_closeEnoughDist(m_template->m_closeEnoughDist),
	  m_40(0.0f), m_flags(0),
	  m_preferredHeight(m_template->m_58), m_4C(m_template->m_5C),
	  m_preferredHeightDamping(m_template->m_60),
	  m_angleOffset(0.0f), m_offsetIncrement(0.0785398185f), m_5C(0.0f),
	  m_60(0), m_64(0), m_transform(true)
{
	m_98 = false;
	m_99 = false;
	m_9A = false;
	m_9C = 0;
	m_A0 = 0.0f;
	m_A4 = 0.0f;
	m_A8 = 0;
	m_AC = 100;
	++g_Va00DFDC64;
	setFlag(IS_CLOSE_ENOUGH_DIST_3D, m_template->m_isCloseEnoughDist3D);
}
