// cl: /GX-
// ?_RTC_GetErrorFunc@@YAP6AHHPBDH00ZZPBX@Z @ 0x0075ACE1 (6B).
// MSVC 7.1 CRT run-time-check support (userapi.obj file-unit): returns the
// currently installed RTC error handler from its .data slot. Follows
// __RTC_SetErrorFunc at 0x0075ACD1 which writes the same slot; Ghidra size 6
// agrees; boundary prev C3 next CC. The handler signature (two trailing
// const char * params before the ellipsis) is proven by the obj symbol's own
// mangling; a probe TU reproduced YAP6AHHPBDH00ZZPBX@Z exactly.
typedef int (__cdecl *_RTC_error_fn)(int, char const *, int, char const *, char const *, ...);

extern _RTC_error_fn g_Va00E1F55C;

// ?_RTC_GetErrorFunc@@YAP6AHHPBDH00ZZPBX@Z @ 0x0075ACE1 (6B) over 0x00E1F55C.
_RTC_error_fn __cdecl _RTC_GetErrorFunc(void const *)
{
	return g_Va00E1F55C;
}
