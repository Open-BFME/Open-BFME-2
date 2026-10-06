// cl: /DNDEBUG /MD

// ?Rva0039D8FBLess@@YAHABURva0039D8FBKey@@0@Z @0x0039D8FB (36B).
// Free lexicographic less for an 8-byte two-int key (TeamFactory prototype map
// key is pair<NameKeyType NameKeyType> at +0xB0; 0x3A2B78 builds it from two
// nameToKey calls). Callers are RB-tree find/insert bodies at 0x39EA4E 0x39F597
// 0x39F5FE 0x39F692 0x39FB87 0x3A2943. Twin pair operator< at 0x169F50 (38B)
// uses mov eax 1 tail; this TU uses /O1 xor-inc tail. Neighbours share /O1.
struct Rva0039D8FBKey
{
	int m_first;
	int m_second;
};

int __cdecl Rva0039D8FBLess(const Rva0039D8FBKey& a, const Rva0039D8FBKey& b)
{
	return a.m_first < b.m_first || (!(b.m_first < a.m_first) && a.m_second < b.m_second);
}
