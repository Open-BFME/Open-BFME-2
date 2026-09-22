// ?scanShort@@YAHPBDAAF@Z
// partial score=0.8 date=2026-09-22
// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?scanShort@@YAHPBDAAF@Z, retail 0x00314E6D, 41 bytes.
// Dedicated TU.
//
// GameWindowManagerScript file-static sscanf wrapper for short fields.
// Mirrors the rowed scanInt TU: sscanf via explicit dllimport (FF15 to the
// msvcr71 sscanf import at 0xBBA5E4) with the "%d" literal at 0xBBE164 into
// a stack int temp, then narrows to the short out-param. Returns the sscanf
// count in eax.

typedef int Int;
typedef short Short;

extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);

// ?scanShort@@YAHPBDAAF@Z
static Int scanShort(const char *source, Short &val)
{
	Int temp = 0;
	Int ret = sscanf(source, "%d", &temp);
	Short narrowed = (Short)temp;
	val = narrowed;

	return ret;
}

static const void *s_scanShortAnchor = (const void *)scanShort;
