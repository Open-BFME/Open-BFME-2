// cl: /O1 /MD
// ?Rva0038768DCopy@@YAXPAURva0038768DData@@PBU1@@Z retail 0x0038768D 23 bytes.
// LINK body: 1 matched file waits via 0x0038766B. Copies byte at +0 and dword
// at +4 with null check on dest. Caller 0x0038766B allocates 0x18 via 0x307F0
// then copies +0x10 tail. Identity honest address name free function.
struct Rva0038768DData
{
	unsigned char m_b;
	int m_x;
};
void __cdecl Rva0038768DCopy(Rva0038768DData *dest, const Rva0038768DData *src)
{
	if (dest == 0)
		return;
	dest->m_b = src->m_b;
	dest->m_x = src->m_x;
}
