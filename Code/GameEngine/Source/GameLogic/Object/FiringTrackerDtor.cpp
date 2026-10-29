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

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern AudioManager *TheAudio;

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

#include "../../../Include/Common/ObjectModule.h"

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class FiringTracker : public UpdateModule
{
public:
	virtual ~FiringTracker();

private:
	unsigned char m_unreconstructed_20[0x38];
	AudioHandle m_audioHandle;
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
