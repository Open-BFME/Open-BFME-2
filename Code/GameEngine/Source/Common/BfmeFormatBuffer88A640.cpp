// cl: /Oy-
// A varargs message formatted into a half-kilobyte frame buffer and then
// dropped: nothing here reads the text back. The frame pointer is kept, which
// is what puts the buffer at ebp-0x200 and the argument list at ebp+0xc.
#include <stdarg.h>

extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *, unsigned int, const char *, va_list);

void bfmeFormatToBuffer88A640(const char *format, ...)
{
	char buffer[512];
	va_list args;

	va_start(args, format);
	_vsnprintf(buffer, sizeof(buffer) - 1, format, args);
	va_end(args);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeWriteSWA@@YAXPAXHH0@Z=?bfmeFormatToBuffer88A640@@YAXPBDZZ")
#pragma comment(linker, "/alternatename:?bfmeWriteSXA@@YAXPAXZZ=?bfmeFormatToBuffer88A640@@YAXPBDZZ")
#pragma comment(linker, "/alternatename:?bfmeWriteSTA@@YAXPAXHHH@Z=?bfmeFormatToBuffer88A640@@YAXPBDZZ")
