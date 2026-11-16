// cl: /GS
// The 'RESV' category serializes user IDs, a timeout and an optional ACTION.
#include "../../Include/GameNetwork/Rva007E8810Message.h"

void Rva00800040JoinI64(const __int64 *parts, unsigned count,
	char *dest, unsigned destSize, char separator);

void __stdcall Rva007FCDA0ReserveRequest(Rva007E8810Message *message,
	const __int64 *ids, unsigned count, int action, int timeout)
{
	char text[0x100];
	message->reset();
	message->m_1C = 'RESV';
	message->m_2C = 3;
	text[0] = 0;
	Rva00800040JoinI64(ids, count, text, sizeof(text), ';');
	message->addString("UIDS", text);
	message->addInt("TIMO", timeout);
	switch (action)
	{
	case 0: message->addString("ACTION", "HLD"); break;
	case 1: message->addString("ACTION", "REL"); break;
	case 2: message->addString("ACTION", "RAL"); break;
	}
}
