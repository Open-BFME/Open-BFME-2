// cl: /DNDEBUG /MD
// ?rva001D98BD@Rva001D98BD@@QAE_NH@Z @0x001D98BD 79B unlock
// Recursive predicate: +0xB0 type; 5 means internal node over vector at +0x80/+0x84
// of 8B entries whose first dword is child pointer, else compare type to arg.
// Caller 0x0005AF27 passes int through; self-call at 0x001D98E4.
// Neighbour FXBoneInfoAssign shares /O1 flags; no floats or EH.
class Rva001D98BD
{
public:
	bool rva001D98BD(int v);
private:
	unsigned char m_pad00[0x80];
	struct Entry
	{
		Rva001D98BD *child;
		int unk;
	};
	Entry *m_begin;
	Entry *m_end;
	unsigned char m_pad88[0xB0 - 0x88];
	int m_B0;
};

bool Rva001D98BD::rva001D98BD(int v)
{
	int t = m_B0;
	if (t == 5) {
		Entry *end = m_end;
		Entry *beg = m_begin;
		bool ok = false;
		for (Entry *p = beg; p != end; ++p) {
			Rva001D98BD *child = p->child;
			if (child) {
				if (!child->rva001D98BD(v))
					return false;
				ok = true;
			}
		}
		return ok;
	} else {
		return t == v;
	}
}
