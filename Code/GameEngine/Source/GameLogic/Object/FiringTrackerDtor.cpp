// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1FiringTracker@@UAE@XZ retail 0x004DEA0C 86 bytes.
// FiringTracker public virtual destructor over UpdateModule base 0x0024A797.
// Restores three vtable slots at +0x00 +0x0C +0x10 then removes audio handle
// at +0x58 through TheAudio slot 0x6c then sets it to 1 then calls base.
// Donor BFME1 FiringTrackerBFMEDtor plus FiringTracker cpp protected dtor.
// Identity via deleting wrapper 0x004DEBA5 slot0 vtable 0x00C61530
// and pool key 0x004DEACB with FiringTracker string.
// Layout from donor UpdateModule 0x20 plus 0x38 pad to audio at 0x58.
// Shape follows AudioLoopUpgradeDtor plus FoundationAIUpdateSlot14 precedent.

typedef int AudioHandle;

#include "../../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

#include "../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../Include/GameLogic/Module/UpdateModule.h"

#include "../../../Include/Common/ObjectModule.h"



class FiringTracker : public UpdateModule
{
public:
	virtual ~FiringTracker();
	// Update-interface slot 1 (retail table 0x00C61524): defined inline in
	// FiringTrackerCtor.cpp (0x004DF396).
	virtual DisabledMaskType getDisabledTypesToProcess() const;

private:
	unsigned char m_unreconstructed_20[0x38];
	AudioHandle m_audioHandle;
public:
	// retail slot 4: the rowed ?getModuleNameKey@FiringTracker@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
protected:
	// retail vftable slot: the rowed override
	virtual const char * GetSnapshotName() const;
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
public:
	// retail vftable slot: the rowed override
	virtual UpdateSleepTime update();
protected:
	// primary table 0x00C61530 slot 1: the UpdateModule base call (0x00497805 fold),
	// defined in FiringTracker.cpp
	virtual void loadPostProcess();
	// primary table slot 12: 0x0044827C (`push 3; pop eax; ret`, a body retail folds)
	virtual SleepyUpdatePhase getUpdatePhase() const;
};

inline FiringTracker::~FiringTracker()
{
	TheAudio->removeAudioEvent(m_audioHandle);
	m_audioHandle = 1;
}

// This destructor is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeFiringTrackerDtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeFiringTrackerDtorInlineAnchor()
{
    static_cast<FiringTracker *>(0)->FiringTracker::~FiringTracker();
}
#pragma inline_depth()
