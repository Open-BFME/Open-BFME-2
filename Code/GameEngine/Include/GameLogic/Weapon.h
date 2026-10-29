#pragma once
// Weapon: canonical BFME2 header (hand-written; the contract leaves vslots
// 1-3 undecided and reads sizeof 8, because most private views stop at
// m_template). upstream layout:
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
//
// Target facts, read off game.dat:
//  - WeaponStore::allocateNewWeapon (0x0028AA81) news 0x60 bytes and calls the
//    protected ctor 0x002CC23D, so sizeof is 0x60.
//  - The ctors 0x002CC23D and 0x002CC2FC and the dtor 0x002CC39E install
//    vftable 0x00C0214C; the dtor ends on Snapshot's table 0x00BBB554. So
//    Weapon : Snapshot, one vptr at +0 (no MemoryPoolObject table as in ZH).
//  - Table 0x00C0214C has four slots, Snapshot's: 0 ??_G 0x002CCE37, 1
//    loadPostProcess (the folded empty body 0x000B3FD0), 2 the name slot
//    (0x002CC2F6 returns the string "Weapon"; its row is the free
//    Rva002CC2F6Get), 3 xfer 0x002CDD47.
//  - Data offsets are the matched ctor's (WeaponCtor.cpp); names follow ZH
//    where ZH has the field. The scatter-target vector at +0x40 is opaque:
//    the views spell its element five ways (BfmeE16, int, Coord2D, ...).
//
// Members: every Weapon row of reverse/functions.csv, with the access,
// constness and parameter types its decorated name states. Addresses are
// target RVAs. Data is public so units outside the class's own rows can
// adopt the header; ZH keeps it private, which does not change the layout.
#ifndef CANONICAL_WEAPON_H
#define CANONICAL_WEAPON_H

#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class AsciiString;
class Matrix3D;
class Object;
class WeaponBonus;
class WeaponTemplate;
class Xfer;
struct Coord3D;
struct SavedWeaponState;
enum WeaponSlotType;
enum WeaponStatus;

class Weapon : public Snapshot
{
	friend class WeaponStore;

protected:
	Weapon(const WeaponTemplate *tmpl, WeaponSlotType wslot);	// 0x002CC23D
	Weapon(const Weapon &that);									// 0x002CC2FC
	virtual ~Weapon();											// 0x002CC39E (slot 0: ??_G 0x002CCE37)

	// Snapshot slots, spelled the way the unit selected Snapshot.h's.
	virtual void loadPostProcess();								// slot 1, 0x000B3FD0
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();						// slot 2, 0x002CC2F6
#else
	virtual const char *GetSnapshotName() const;				// slot 2, 0x002CC2F6
#endif
#else
	virtual void crc(Xfer *xfer);
#endif

public:
	virtual void xfer(Xfer *xfer);								// slot 3, 0x002CDD47

	inline const WeaponTemplate *getTemplate() const { return m_template; }
	inline WeaponSlotType getWeaponSlot() const { return m_wslot; }
	inline unsigned int getLastShotFrame() const { return m_lastFireFrame; }
	inline unsigned int getPossibleNextShotFrame() const { return m_whenWeCanFireAgain; }
	inline bool isPitchLimited() const { return m_pitchLimited; }
	inline int getMaxShotCount() const { return m_maxShotCount; }
	inline unsigned int getSuspendFXFrame() const { return m_suspendFXFrame; }

	AsciiString getName() const;	// 0x0028F95C
	void cacheStatus(WeaponStatus) const;	// 0x002C94F5
	float rva002C957E() const;	// 0x002C957E
	bool rva002C9586();	// 0x002C9586
	void rva002C959E();	// 0x002C959E
	void rva002C95DE(int);	// 0x002C95DE
	bool rva002C95F0() const;	// 0x002C95F0
	bool isClearFiringLineOfSightTerrain(const Object *, const Coord3D &) const;	// 0x002C961F
	bool isClearGoalFiringLineOfSightTerrain(const Object *, const Coord3D &, const Coord3D &) const;	// 0x002C9655
	bool rva002C969D(const void *, int);	// 0x002C969D
	bool rva002C96D8();	// 0x002C96D8
	int getClipReloadTime(const Object *) const;	// 0x002C9AC5
	bool isTooClose(const Object *, const Object *) const;	// 0x002C9AFE
	bool isTooClose(const Object *, const Coord3D *) const;	// 0x002C9B3D
	float getAttackRange(const Object *, const Object *) const;	// 0x002C9BE4
	float getAttackRange(const Object *) const;	// 0x002C9BF8
	float getAttackDistance(const Object *, const Object *, const Coord3D *) const;	// 0x002C9C37
	bool isWithinTargetPitch(const Object *, const Object *) const;	// 0x002C9C82
	int rva002C9D3B(const Object *, unsigned int) const;	// 0x002C9D3B
	static void calcProjectileLaunchPosition(const Object *, WeaponSlotType, int, Matrix3D &, Coord3D &);	// 0x002C9E48
	static void positionProjectileForLaunch(Object *, const Object *, WeaponSlotType, int);	// 0x002CA753
	bool computeApproachTarget(const Object *, const Object *, const Coord3D *, float, Coord3D &) const;	// 0x002CAEA3
	bool isSourceObjectWithGoalPositionWithinAttackRange(const Object *, const Coord3D *, const Object *, const Coord3D *) const;	// 0x002CB2D1
	bool isWithinAttackRange(Object *, const Coord3D *, Object *, const Coord3D *, float, bool);	// 0x002CB35C
	Coord3D bfmeGetLOSVictimPos(const Object *, const Object *, int) const;	// 0x002CB65B
	bool isWithinAttackRange(const Object *, const Object *, float, int) const;	// 0x002CB933
	char isWithinAttackRange(Object *, void *, float, int) const;	// 0x002CB902
	void rva002CB967(const Object *, const Object *);	// 0x002CB967
	int isClearGoalFiringLineOfSightTerrain(const Object *, const Coord3D *, const Object *);	// 0x002CB9BD
	bool isAmmoReady() const;	// 0x002CC3FF
	WeaponStatus computeStatus(bool *) const;	// 0x002CC422
	void prepareProjectileStreamForFiring();	// 0x002CC4DD
	unsigned int getRemainingAmmo(bool) const;	// 0x002CC578
	float getPercentReadyToFire() const;	// 0x002CCE53
	bool rva002CCED3(const Object *, const Object *);	// 0x002CCED3
	WeaponStatus getStatus() const;	// 0x002CCFC7
	int getPreAttackDelay(const Object *, const Object *, const Coord3D *) const;	// 0x002CCFF0
	void preFireWeapon(const Object *, const Object *, const Coord3D *);	// 0x002CDC3D
	void loadAmmoNow(const Object *);	// 0x002CE1AC
	void reloadAmmo(const Object *);	// 0x002CE1E9
	void rva002CE226(const Object *, const SavedWeaponState *);	// 0x002CE226
	void setClipPercentFull(float, bool);	// 0x002CE280
	bool privateFireWeapon(const Object *, const Coord3D *, const Object *, int, const Coord3D *, bool, bool, unsigned int, int *);	// 0x002CE30A
	bool rva002CE6C5(const Object *, int, const Object *, int *);	// 0x002CE6C5
	bool fireWeapon(const Object *, const Coord3D *, int *);	// 0x002CE6E8
	bool bfmeFireYC(const Object *, const Coord3D *, const Object *, int);	// 0x002CE708
	bool fireProjectileDetonationWeapon(const Object *, const Coord3D *, const Coord3D *, int);	// 0x002CE72B
	bool rva002CE74B(const Object *, const Object *);	// 0x002CE74B
	Object * forceFireWeapon(const Object *, const Coord3D *);	// 0x002CE76F
	Object * forceFireWeapon(const Object *, const Object *);	// 0x002CE7A4
	void setLeechRangeActive(bool);	// 0x002D95FE
	void setMaxShotCount(int);	// 0x00661D50

protected:
	void getFiringLineOfSightOrigin(const Object *, Coord3D &) const;	// 0x002C9601
	void computeBonus(const Object *, unsigned int, WeaponBonus &) const;	// 0x002C9A6F
	void processRequestAssistance(const Object *, Object *);	// 0x002C9DF5
	void rebuildScatterTargets();	// 0x002CDB53
	void reloadWithBonus(const Object *, const WeaponBonus &, bool);	// 0x002CDB99

public:
	const WeaponTemplate *m_template;			// +0x04
	unsigned int m_ownerID;						// +0x08
	WeaponSlotType m_wslot;						// +0x0C
	mutable WeaponStatus m_status;				// +0x10
	unsigned int m_ammoInClip;					// +0x14
	unsigned int m_whenWeCanFireAgain;			// +0x18
	unsigned int m_whenPreAttackFinished;		// +0x1C
	unsigned int m_whenLastReloadStarted;		// +0x20
	unsigned int m_lastFireFrame;				// +0x24
	unsigned int m_projectileStreamID;			// +0x28
	unsigned int m_unknown2C;					// +0x2C
	unsigned int m_suspendFXFrame;				// +0x30
	int m_maxShotCount;							// +0x34
	int m_curBarrel;							// +0x38
	int m_numShotsForCurBarrel;					// +0x3C
	void *m_scatterTargets[3];					// +0x40 vector: begin, end, capacity
	bool m_pitchLimited;						// +0x4C
	char m_pad4D[3];
	unsigned int m_leechWeaponRangeActive;		// +0x50
	unsigned int m_unknown54;					// +0x54
	unsigned int m_tailState;					// +0x58
	unsigned int m_extra5C;						// +0x5C
};

#endif // CANONICAL_WEAPON_H
