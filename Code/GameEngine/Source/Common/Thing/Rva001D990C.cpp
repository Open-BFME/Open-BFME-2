// cl: /DNDEBUG /MD
// ?rva001D990C@Rva001D990C@@QAE_NH@Z @0x001D990C 105B unlock
// Recursive predicate: +0xB0 type; 5 means internal node over vector at +0x80/+0x84
// of 8B entries whose first dword is child pointer, else compare type to arg.
// Extra gate vs neighbour 0x001D98BD: second true child needs +0x4C bit 0x80.
// Callers 0x00059AD0/0x0005A9F8 pass int 2 through; self-call at 0x001D993B.
// Neighbours Rva001D98BD/FXBoneInfoAssign share /O1 flags; no floats or EH.
class Rva001D990C
{
public:
	bool rva001D990C(int v);
private:
	unsigned char m_pad00[0x4C];
	unsigned char m_4C;
	unsigned char m_pad4D[0x80 - 0x4D];
	struct Entry
	{
		Rva001D990C *child;
		int unk;
	};
	Entry *m_begin;
	Entry *m_end;
	unsigned char m_pad88[0xB0 - 0x88];
	int m_B0;
};

bool Rva001D990C::rva001D990C(int v)
{
	int t = m_B0;
	if (t == 5) {
		Entry *end = m_end;
		Entry *beg = m_begin;
		bool ok = false;
		for (Entry *p = beg; p != end; ++p) {
			Rva001D990C *child = p->child;
			if (child) {
				if (!child->rva001D990C(v))
					return false;
				if (ok && ((m_4C & 0x80) == 0))
					return false;
				ok = true;
			}
		}
		return ok;
	} else {
		return t == v;
	}
}
