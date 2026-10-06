// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Four more tiny ones: a value taken from a source or zeroed, a singleton
// field tested for zero, an identity test against a singleton, and a choice
// between two fields.
//
// The two tests differ in their return type again: the one that hands back a
// comparison is a bool, which zero-extends the setne through another register
// before moving it into al; a one-byte type would stop at the setne.

extern void *g_bfmeCurrentCB;					// retail 0x012F7094

// ?bfmeIsCurrent@@YGEPAX@Z
unsigned char __stdcall bfmeIsCurrent(void *thing)
{
	void *current = g_bfmeCurrentCB;

	if (current && current == thing)
		return 1;

	return 0;
}