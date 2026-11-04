// cl: /DNDEBUG /EHs-c-
// ?Rva006CC110Log@@YAXHPBDZZ @ 0x006CC110 (59B). Apt variadic log: vsprintf
// into a 4KB stack buffer, then forward via "%s" through the hookable
// .data slot at 0x00E1773C. Evidence: callers pass (0/4, fmt, ...) e.g.
// 0x006CC9B0 (0, "WARNING: trying to add input when Apt not initalized"),
// 0x006CDA60 (4, fmt, edi+1), 0x006CDAE5 (4, "%d :: ZOMBIE SPRITE...");
// retail ignores the int channel, reads fmt from [esp+0x1008] and va_list
// from [esp+0x100C]; init at 0x00ABA59 sets [0x00E1773C]=0x004B3FD0 (empty ret).

#include <stdio.h>
// _g_bfmeAptLogAtE1773C: VA 0x00E1773C (.data BSS), zero-filled before init.
extern "C" void (__cdecl *g_bfmeAptLogAtE1773C)(const char *fmt, const char *text) = 0;

void __cdecl Rva006CC110Log(int, const char *fmt, ...)
{
	char buf[0x1000];
	vsprintf(buf, fmt, (char *)(&fmt + 1));
	g_bfmeAptLogAtE1773C("%s", buf);
}
