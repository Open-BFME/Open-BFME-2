// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?frameToSleepTime@UpdateModule@@IAE?AW4UpdateSleepTime@@IIII@Z,
// retail 0x0044DF28, 51 bytes. UpdateModule sleep-time helper: returns the
// minimum of the four candidate frames as a sleep delta from the current
// GameLogic frame, with a 1-frame minimum when already due.
//
// Shape: min-chain via ternary cmova (retail uses three cmova for the four
// inputs; /arch:SSE enables cmov where plain /O1 gives branches) with
// TheGameLogic->getFrame() hoisted after the first min (retail interleaves
// the pointer load between cmp1/cmova1 and the frame load between cmp2/cmova2;
// source hoisting reproduces it) at +0x40 (Poisoned precedent), then
// greater-than early-return for the delta (retail jbe-shared 1 vs sub tails;
// less-equal form inverts to ja). Zero new pins
// (TheGameLogic is DIR32-masked; all callees are inline). Row supersedes
// the frameToSleepTime pin.

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class GameLogic
{
public:
	UnsignedInt getFrame() { return m_frame; }

private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame; // +0x40 (Poisoned precedent)
};

extern GameLogic *TheGameLogic;

class UpdateModule
{
protected:
	UpdateSleepTime frameToSleepTime(UnsignedInt frame1, UnsignedInt frame2, UnsignedInt frame3, UnsignedInt frame4);
};

// ?frameToSleepTime@UpdateModule@@IAE?AW4UpdateSleepTime@@IIII@Z @0x0044DF28
UpdateSleepTime UpdateModule::frameToSleepTime(UnsignedInt frame1, UnsignedInt frame2, UnsignedInt frame3, UnsignedInt frame4)
{
	UnsignedInt firstFrame = frame1;
	firstFrame = firstFrame > frame2 ? frame2 : firstFrame;
	UnsignedInt nowFrame = TheGameLogic->getFrame();
	firstFrame = firstFrame > frame3 ? frame3 : firstFrame;
	firstFrame = firstFrame > frame4 ? frame4 : firstFrame;
	if (firstFrame > nowFrame)
		return (UpdateSleepTime)(firstFrame - nowFrame);
	return (UpdateSleepTime)1;
}
