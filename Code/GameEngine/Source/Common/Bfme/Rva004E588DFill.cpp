// cl: /MD
// ?Rva004E588DFill@@YAXPAHHPAPAU... @0x004E588D (45B)
// Free __cdecl 5-arg range walk: stamps each node's +0x10 with the running
// total, accumulates +0x0C, stamps +0x14, writes (total, stamp) to out[2].
// Node offsets match Rva0048E3D0Source (+0x0C delta, +0x10 first, +0x14 second)
// in the adjacent TU; callers 0x004E5942 (5 pushes, add esp,0x14) and
// 0x004E592C unblock. Prev/next: Rva0048E3D0PairRefAssign, Rva004E6273Method.
struct Rva004E588DNode {
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

void __cdecl Rva004E588DFill(int *out, Rva004E588DNode **first, Rva004E588DNode **last, int acc, int stamp)
{
	Rva004E588DNode **p = first;
	while (p != last) {
		Rva004E588DNode *node = *p;
		node->m_10 = acc;
		acc += node->m_0C;
		node->m_14 = stamp;
		++p;
	}
	out[1] = stamp;
	out[0] = acc;
}
