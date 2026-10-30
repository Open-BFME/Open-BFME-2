// cl: /MD
// Transferred unchanged from Open-BFME-1 5cae4bdff game/GameEngine/Source/GameNetwork/GameSpy/Rva0085A660TimeString.c;
// bfme1_sweep places the same masked body: Rva0085A660TimeString at BFME2 0x0069BB50. Addresses in the donor text are BFME1.
/* 0x0085A660 (160 B): formats the current local time as "mm.dd.yy hh:mm.ss"
   into a static buffer, or "00.00.00 00:00.00" when localtime fails. It sits
   in the GameSpy SDK block (after sb_server.c's SBServerGetTeamIntValueA,
   before chat's ciBufferInit) and has no remaining references, so its name
   keeps the address. */
#include <time.h>
#include <stdio.h>
#include <string.h>
#pragma intrinsic(strcpy)

static char Rva0085A660TimeBuffer[20];

char *Rva0085A660TimeString(void)
{
	time_t now;
	struct tm *local;

	now = time(0);
	local = localtime(&now);
	if (local)
	{
		if (local->tm_year > 99)
			local->tm_year -= 100;
		sprintf(Rva0085A660TimeBuffer, "%02d.%02d.%02d %02d:%02d.%02d",
			local->tm_mon + 1, local->tm_mday, local->tm_year,
			local->tm_hour, local->tm_min, local->tm_sec);
		return Rva0085A660TimeBuffer;
	}
	strcpy(Rva0085A660TimeBuffer, "00.00.00 00:00.00");
	return Rva0085A660TimeBuffer;
}
