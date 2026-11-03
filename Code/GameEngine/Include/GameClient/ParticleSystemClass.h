// FILE: ParticleSystemClass.h ////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 ParticleSystem (base FXParticleSystem::ParticleSystemInfo in FXParticleSystemInfo.h). Named
//         ParticleSystemClass.h so that units including shim headers spelled GameClient/ParticleSys.h
//         never reach this file.
//
// Target facts (RVAs unless marked VA):
//  - Factory 0x001F50BC pushes 0x1DC to operator new 0x0002FDA0 and calls the ctor 0x001FC701
//    (ret 0x0C); the scalar deleting dtor 0x001FC17F calls the dtor 0x001FBD17 and operator delete
//    0x0002FD60: sizeof 0x1DC, no memory pool.
//  - The ctor calls the exported ??0ParticleSystemInfo@FXParticleSystem@@QAE@XZ (0x001F4E82) on
//    this, then stores VA 0x00BE1A10 at +0; the dtor stores VA 0x00BE1A10 and ends with the
//    exported base dtor 0x0000240E (call at 0x001FBE9E). One ParticleSystemInfo base at +0.
//  - Table VA 0x00BE1A10 has six slots (slot 6 is ParticleSystemTemplate's 0x001FC052): 0 deleting
//    dtor 0x001FC17F, 1 0x001F628F, 2 0x001FBEB1 returning "FXParticleSystem" (VA 0x00BE19FC),
//    3 0x001FB201, 4 update 0x001FAB59, 5 createParticle 0x001FCC73. 0x001F9BA4 calls slot 5.
//  - The exports name this object FXParticleSystem::ParticleSystem: createSlaveSystem 0x001F9CF3
//    returns TrackingPtr<FXParticleSystem::ParticleSystem>, and the ctor stores that result through
//    0x001F5496. The ledger's rows spell the class in the global namespace.
//  - Ctor 0x001FC701 stores: +0x9C/+0xA0 0 (the TrackingPtr chain attach 0x0004CB9A appends to),
//    +0xA8 the id argument, +0xB8 string, matrices +0xBC/+0xEC (three 16-byte rows through 0x00001423
//    with 0x0047A6A9), +0x11C 0, +0x120 (unsigned)template+0x5C.getValue(), +0x124 the client frame,
//    +0x128 template+0x20, +0x1A2 (template+0x20 == 0), +0x12C 0, +0x130 1.0 x3, +0x13C/+0x140 1.0,
//    +0x144/+0x150 zero triples, handles +0x15C/+0x16C cleared inline, +0x168/+0x178 0, +0x17C/+0x184
//    1.0, +0x180 0.0, +0x188 zero triple, +0x194 0, +0x198 the template, +0x19C 0, bytes +0x1A0 1,
//    +0x1A1 1, +0x1A3 0, +0x1A4 0, +0x1A5 1, +0x1A6 1, +0x1A7 0, +0x1A8 0; +0xA4 takes a new storage
//    object whose virtual slot 0 the dtor calls at 0x001FBE04. The 0x30-byte member +0x1AC is built
//    by 0x001FBF37 (call at 0x001FC791) and destroyed by 0x001FBCDC (call at 0x001FBE66).
//  - update 0x001FAB59 tests +0x1A8 before +0x1A0 (0x001FACA9/0x001FACB6), as Zero Hour tests
//    m_skipParentXfrm before m_isLocalIdentity; destroy 0x001F462C sets +0x1A4 along the +0x15C chain;
//    0x001F3852 sets +0x1A3; 0x001F3C20 writes +0xB0 and 0x001F3C43 writes +0xB4. loadPostProcess
//    0x001F628F looks up +0x168 and +0x178 through findParticleSystemByID 0x001F5B0A, assigns the
//    results to +0x15C/+0x16C and tests their +0x1A4. The dtor calls 0x001F4A22 on +0x19C and clears it.
//  - Member types without a registered header stay untyped: +0xA4 and +0x19C as void *, the +0x1AC
//    member as twelve words.
//  - The row at 0x002AA223 that some units call ParticleSystem::isSaveable reads +0x33A, beyond
//    sizeof; it is Player::isPlayerObserver and is not declared here.
// Donor (Zero Hour ParticleSys.h) facts: the method names update, createParticle, destroy,
// loadPostProcess and rotateLocalTransformX/Y/Z, the base field names m_isOneShot, m_shaderType,
// m_particleType, m_particleTypeName, m_lifetime, m_startSizeRate, m_systemLifetime,
// m_initialDelay, m_slaveSystemName, m_slavePosOffset, m_attachedSystemName and m_priority, and the
// system field names matched to the offsets above by Zero Hour's ctor values and order and by the
// bodies listed. Fields without such evidence keep m_NN names.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef CANONICAL_PARTICLESYSTEMCLASS_H
#define CANONICAL_PARTICLESYSTEMCLASS_H

// The exported ParticleSystemInfo overriders spell the capitalized, non-const, reference-xfer
// surface; a unit that defines them selects it before including (Player.h and ParticleSys.h refuse it).
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/Region2D.h"
#include "../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
#include "GameClientRandomVariable.h"
#include "BfmeParticleSystemHandle.h"
#include "FXParticleSystemInfo.h"

class ParticleSystemTemplate;
class Rva001F376E;
struct Rva001F55A8Info;
struct Rva003AFA0BVector;
class Xfer;
enum ParticleSystemID;

// The base unqualified: header_adopt_lane's layout probe names the header's classes so.
using FXParticleSystem::ParticleSystemInfo;

//-------------------------------------------------------------------------------------------------
class ParticleSystem : public FXParticleSystem::ParticleSystemInfo
{
public:
	ParticleSystem(const FXParticleSystem::ParticleSystemTemplate *sysTemplate, ParticleSystemID id,
		bool createSlaves);										// 0x001FC701
	virtual ~ParticleSystem();									// 0x001FBD17 (slot 0: 0x001FC17F)

protected:
	// Snapshot slots, spelled the way the unit selected Snapshot.h's.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();								// slot 1, 0x001F628F
#else
	virtual void loadPostProcess();								// slot 1, 0x001F628F
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();						// slot 2, 0x001FBEB1
#else
	virtual const char *GetSnapshotName() const;				// slot 2, 0x001FBEB1
#endif
#else
	virtual void crc(Xfer *xfer);								// slot 2, 0x001FBEB1
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &xfer);							// slot 3, 0x001FB201
#else
	virtual void DoXfer(Xfer *xfer);							// slot 3, 0x001FB201
#endif
#else
	virtual void xfer(Xfer *xfer);								// slot 3, 0x001FB201
#endif

public:
	virtual bool update(int localPlayerIndex);					// slot 4, 0x001FAB59
	virtual bool createParticle(const Rva001F376E *info, int priority,
		const ParticleSystemTemplate *slaveTemplate, bool forceCreate);	// slot 5, 0x001FCC73

	void destroy();												// 0x001F462C
	void rotateLocalTransformX(float x);						// 0x001F392E
	void rotateLocalTransformY(float y);						// 0x001F3A25
	void rotateLocalTransformZ(float z);						// 0x001F3B1C
	unsigned int rva001F3C6B();									// 0x001F3C6B
	void rva001F45F4(bool flag);								// 0x001F45F4
	void rva001F465E(void *value);								// 0x001F465E
	void rva001F4696(void *pos, void *arg, bool isIdentity, void *info);	// 0x001F4696
	Rva003AFA0BVector rva001F54C5(const Rva003AFA0BVector *pos);	// 0x001F54C5
	void rva001F55A8(Rva001F55A8Info *info, int particleNum, int particleCount);	// 0x001F55A8

	ParticleSystemID getSystemID() const { return m_systemID; }
	const FXParticleSystem::ParticleSystemTemplate *getTemplate() const { return m_template; }
	bool isDestroyed() const { return m_isDestroyed; }
	bool isSystemForever() const { return m_isForever; }

	BfmeParticleSystemHandle *m_9C;							// +0x9C, first handle tracking this system
	BfmeParticleSystemHandle *m_A0;							// +0xA0, last handle tracking this system
	void *m_A4;												// +0xA4, particle storage (virtual slot 0 destroys it)
	ParticleSystemID m_systemID;							// +0xA8
	float m_AC;												// +0xAC
	unsigned int m_attachedToDrawableID;					// +0xB0
	unsigned int m_attachedToObjectID;						// +0xB4
	AsciiString m_B8;										// +0xB8
	Matrix3D m_localTransform;								// +0xBC
	Matrix3D m_transform;									// +0xEC
	unsigned int m_burstDelayLeft;							// +0x11C
	unsigned int m_delayLeft;								// +0x120
	unsigned int m_startTimestamp;							// +0x124
	unsigned int m_systemLifetimeLeft;						// +0x128
	unsigned int m_personalityStore;						// +0x12C
	Coord3D m_velCoeff;										// +0x130
	float m_countCoeff;										// +0x13C
	float m_delayCoeff;										// +0x140
	Coord3D m_pos;											// +0x144
	Coord3D m_lastPos;										// +0x150
	BfmeParticleSystemHandle m_slaveSystem;					// +0x15C
	ParticleSystemID m_slaveSystemID;						// +0x168
	BfmeParticleSystemHandle m_masterSystem;				// +0x16C
	ParticleSystemID m_masterSystemID;						// +0x178
	float m_17C;											// +0x17C
	float m_accumulatedSizeBonus;							// +0x180
	float m_184;											// +0x184
	Coord3D m_188;											// +0x188
	unsigned char m_194;									// +0x194
	const FXParticleSystem::ParticleSystemTemplate *m_template;	// +0x198
	void *m_controlParticle;								// +0x19C
	bool m_isLocalIdentity;									// +0x1A0
	bool m_isIdentity;										// +0x1A1
	bool m_isForever;										// +0x1A2
	bool m_isStopped;										// +0x1A3
	bool m_isDestroyed;										// +0x1A4
	bool m_isFirstPos;										// +0x1A5
	bool m_isSaveable;										// +0x1A6
	unsigned char m_1A7;									// +0x1A7
	bool m_skipParentXfrm;									// +0x1A8
	unsigned int m_1AC[12];									// +0x1AC, member built by 0x001FBF37
};

typedef char ParticleSystemInfoSizeCheck[sizeof(FXParticleSystem::ParticleSystemInfo) == 0x9C ? 1 : -1];
typedef char ParticleSystemSizeCheck[sizeof(ParticleSystem) == 0x1DC ? 1 : -1];

#endif // CANONICAL_PARTICLESYSTEMCLASS_H
