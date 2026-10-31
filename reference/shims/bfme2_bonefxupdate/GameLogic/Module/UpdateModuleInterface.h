// BFME 2 BoneFXUpdate TU's copy of reference/shims/update_modules_bfme2/GameLogic/Module/UpdateModuleInterface.h, verbatim.
// BFME 2 update interface: native tables have update, disabled-mask and wake slots.
#pragma once

template <unsigned int NUM_BITS> class BitFlags;
typedef BitFlags<11> DisabledMaskType;

enum UpdateSleepTime 
{ 
	UPDATE_SLEEP_INVALID	= 0,
	UPDATE_SLEEP_NONE			= 1,
	// (we use 0x3fffffff so that we can add offsets and not overflow...
	//	and also 'cuz we shift the value up by two bits for the phase.
	// note that at 30fps, this is ~414 days...
	UPDATE_SLEEP_FOREVER	= 0x3fffffff
};
#define UPDATE_SLEEP(numFrames)				((UpdateSleepTime)(numFrames))

class UpdateModuleInterface
{
public:

	virtual UpdateSleepTime update() = 0;

	virtual DisabledMaskType getDisabledTypesToProcess() const = 0;

	virtual void rva0044DF8D(UpdateSleepTime wakeDelay) = 0;

};
