// cl: /MD
// ?Rva00523EFFEqual@@YAHPBURva00523DB7@@0@Z @0x00523EFF 35B:
// 2-ptr equality for 8B struct (int +0 plus StringBase<char> +4 via rowed
// compare 0x000069D6). Called 7x by array-find 0x0052408B. Owner unproven,
// honest Rva names matching Rva00528B37Equal precedent.
#include "string_base.h"
struct Rva00523DB7
{
	int m_00;
	StringBase<char> m_04;
};
int __cdecl Rva00523EFFEqual(const Rva00523DB7 *a, const Rva00523DB7 *b)
{
	if (a->m_00 == b->m_00) {
		if (a->m_04.compare(b->m_04) == 0)
			return 1;
	}
	return 0;
}
