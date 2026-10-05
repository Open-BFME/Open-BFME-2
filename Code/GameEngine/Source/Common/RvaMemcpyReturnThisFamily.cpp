// cl: /O1
// Three intrinsic-memcpy-return-this members (20B each): push esi,
// mov esi, [esp+8], push edi, mov eax, ecx, push N, pop ecx, mov edi, eax,
// rep movsd [edi], [esi], pop edi, pop esi, ret 4. Each copies N dwords
// from its argument to this and returns this. /O1 gives the
// push-imm/pop-ecx count setup.
// 0x005E35B5 (8 dwords), 0x005EEEFF (5 dwords), 0x005F8F00 (9 dwords).
// Member/owner identities unproven; names are address-derived.
// One ledger row per member.

#include <string.h>

#pragma intrinsic(memcpy)

class Rva005E35B5
{
public:
	Rva005E35B5 *copyFrom(const void *src);
};

class Rva005EEEFF
{
public:
	Rva005EEEFF *copyFrom(const void *src);
};

class Rva005F8F00
{
public:
	Rva005F8F00 *copyFrom(const void *src);
};

Rva005E35B5 *Rva005E35B5::copyFrom(const void *src)
{
	memcpy(this, src, 8 * sizeof(int));
	return this;
}

Rva005EEEFF *Rva005EEEFF::copyFrom(const void *src)
{
	memcpy(this, src, 5 * sizeof(int));
	return this;
}

Rva005F8F00 *Rva005F8F00::copyFrom(const void *src)
{
	memcpy(this, src, 9 * sizeof(int));
	return this;
}
