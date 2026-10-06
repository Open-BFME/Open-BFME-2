// cl: /DNDEBUG /MD
// ?rva0039F597@Rva0039EA4E@@QAEPAURva0039EA4ENode@@ABURva0039D8FBKey@@@Z @0x0039F597 49B
// RB-tree walk for the TeamFactory prototype map without the trailing
// header correction of sibling 0x0039EA4E. Same header/root/left/right/key
// layout and same rowed Rva0039D8FBLess 0x0039D8FB comparator; callers at
// 0x0039FB77 and 0x003A2952. Returns the last node where less is false.
// Evidence: ret 4 thiscall; [ecx] header and [header+4] root; node +0x08 left
// +0x0C right +0x10 key; all callees rowed.
struct Rva0039D8FBKey
{
	int m_first;
	int m_second;
};

int __cdecl Rva0039D8FBLess(const Rva0039D8FBKey &a, const Rva0039D8FBKey &b);

struct Rva0039EA4ENode
{
	int m_color00;
	Rva0039EA4ENode *m_parent04;
	Rva0039EA4ENode *m_left08;
	Rva0039EA4ENode *m_right0C;
	Rva0039D8FBKey m_key10;
};

class Rva0039EA4E
{
public:
	Rva0039EA4ENode *rva0039F597(const Rva0039D8FBKey &key);
private:
	Rva0039EA4ENode *m_header00;
};

Rva0039EA4ENode *Rva0039EA4E::rva0039F597(const Rva0039D8FBKey &key)
{
	Rva0039EA4ENode *j = m_header00;
	Rva0039EA4ENode *x = m_header00->m_parent04;
	while (x) {
		if (!(unsigned char)Rva0039D8FBLess(x->m_key10, key)) {
			j = x;
			x = x->m_left08;
		} else
			x = x->m_right0C;
	}
	return j;
}
