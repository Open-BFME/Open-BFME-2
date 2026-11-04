// cl: /MD /EHsc
//
// ?Rva00248CBF@BfmeNetAddress@@QBE_NPBU1@@Z, retail 0x00248CBF, 30 bytes.
// Const 6-byte key equality (dword +0 word +4), 1 if equal else 0.
// Evidence: pinned name plus cmp jne twice plus xor inc plus ret 4,
// 39 callers plus donor-adjacent 0x00248CDD twin.

#include "../../../Include/GameNetwork/BfmeNetAddress.h"

bool BfmeNetAddress::Rva00248CBF(const BfmeNetAddress *other) const
{
	return ip == other->ip && port == other->port;
}
