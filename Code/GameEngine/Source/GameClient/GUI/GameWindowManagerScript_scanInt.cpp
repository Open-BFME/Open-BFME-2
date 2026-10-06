// cl: /DNDEBUG /MD /EHsc
//
// ?scanInt@@YAHPBDAAH@Z, retail 0x00314E96, 22 bytes.
// Dedicated TU.
//
// GameWindowManagerScript file-static sscanf wrapper (the helper behind
// every parseSlider/Radio/Tooltip verb in this family). The in-tree TU
// inlines it at some sites and emits a 16B register-pushed copy; retail
// keeps the 22B out-of-line push-mem form with a direct FF15 to the
// msvcr71 sscanf import at 0xBBA5E4, so it lives here (callee-visibility
// split: GetFrameEntry/AddFrameEntry precedent).
// BFME2 facts (all retail-measured):
// - sscanf via explicit dllimport decl (FF15, not the E8 thunk).
// - "%d" literal at 0xBBE164.

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);

// ?scanInt@@YAHPBDAAH@Z
Int scanInt(const char *source, Int &val)
{
	Int ret = sscanf(source, "%d", &val);

	return ret;
}

static const void *s_scanIntAnchor = (const void *)scanInt;
