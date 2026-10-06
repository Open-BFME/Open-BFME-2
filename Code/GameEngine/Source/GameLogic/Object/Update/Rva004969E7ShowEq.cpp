// cl: /GX /MD /DNDEBUG
// ?rva004969E7@@YA_NPBD@Z 0x004969E7 24 caller 0x0049735A string Show
#include <string.h>
bool __cdecl rva004969E7(const char *s)
{
	bool r = _strcmpi(s, "Show") == 0;
	return r;
}
