// cl: /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1Weapon@@MAE@XZ @0x002CC39E 97B
// Donor: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/WeaponDestructorThunk.cpp
//   (BFME1 protected virtual Weapon dtor, one vector plus inlined Snapshot base)
//   plus ZH Weapon.h (Weapon : MemoryPoolObject, Snapshot; no default ctor).
// Target evidence: vtable 0x0080214C at +0 then base 0x007BB554; EH frame;
//   TheGameLogic findObjectByID/destroyObject on +0x5C; vector free at +0x40;
//   deleting dtor 0x002CCE37 slot 0 calls this body.
#include <vector>
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

#include "../../../../Libraries/Include/Lib/BfmeE16.h"

#include "../../Common/GameLogicObjectLookupView.h"

#include "object.h"


extern GameLogic *TheGameLogic;

class Weapon : public Snapshot
{
protected:
	virtual ~Weapon();
	// Retail's table 0x00C0214C: the deleting destructor, an empty loadPostProcess (0x000B3FD0, shared),
	// the name getter 0x002CC2F6 and xfer 0x002CDD47. GameState::addPostProcessSnapshot leaves Weapons
	// off its post-process list by this name, so a pure slot here calls __purecall on load.
	virtual void loadPostProcess() {}
	virtual const char *GetSnapshotName() const { return "Weapon"; }
public:
	virtual void xfer(Xfer *xfer);


private:
	const void *m_template; // +4
	unsigned int m_ownerID; // +8
	unsigned int m_wslot; // +0xC
	unsigned int m_status; // +0x10
	unsigned int m_ammoInClip; // +0x14
	unsigned int m_whenWeCanFireAgain; // +0x18
	unsigned int m_whenPreAttackFinished; // +0x1C
	unsigned int m_whenLastReloadStarted; // +0x20
	unsigned int m_lastFireFrame; // +0x24
	unsigned int m_projectileStreamID; // +0x28
	unsigned int m_unknown2C; // +0x2C
	unsigned int m_suspendFXFrame; // +0x30
	int m_maxShotCount; // +0x34
	int m_curBarrel; // +0x38
	int m_numShotsForCurBarrel; // +0x3C
	_STL::vector<BfmeE16> m_scatterTargets; // +0x40
	bool m_pitchLimited; // +0x4C
	char m_pad4D[3];
	unsigned int m_leechWeaponRangeActive; // +0x50
	unsigned int m_unknown54; // +0x54
	unsigned int m_tailState; // +0x58
	ObjectID m_extra5C; // +0x5C
};

Weapon::~Weapon()
{
	GameLogic *logic = TheGameLogic;
	Object *obj = logic->findObjectByID(m_extra5C);
	if (obj)
		logic->destroyObject(obj);
}
