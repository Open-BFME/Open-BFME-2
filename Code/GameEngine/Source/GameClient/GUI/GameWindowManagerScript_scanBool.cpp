// cl: /Oy- /DNDEBUG /MD /EHsc
//
// ?scanBool@@YAHPBDAA_N@Z, retail 0x00314E42, 43 bytes.
// Dedicated TU.
//
// GameWindowManagerScript file-static sscanf wrapper (Bool out-param).
// Retail keeps the ebp frame (/Oy-); the temp int is zeroed with
// and-mem-0, sscanf rides the msvcr71 import at 0xBBA5E4 via FF15,
// and the setne/materialize tail stores through the Bool reference.
// "%d" literal at 0xBBE164.

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);

// ?scanBool@@YAHPBDAA_N@Z
Int scanBool(const char *source, Bool &val)
{
	Int temp = 0;
	Int ret = sscanf(source, "%d", &temp);
	val = (Bool)temp;

	return ret;
}

static const void *s_scanBoolAnchor = (const void *)scanBool;
