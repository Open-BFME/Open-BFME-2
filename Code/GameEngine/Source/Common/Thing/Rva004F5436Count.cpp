// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004F5436@Rva004F5436@@QAEHPAVBfmeTab1026@@@Z, retail 0x004F5436, 61 bytes.
// Counts list nodes at +0x10 whose +8 value is in the given table via rowed
// bfmeHas1026 0x00362437; NULL table returns +0x18. Evidence: unlock packet
// with 4 callers; sibling Rva004F553FEnum proves circular list with head at
// +0x10 and data at +8; Rva00421A57Search proves BfmeTab1026::bfmeHas1026(int,int).
class BfmeTab1026;
class Object;
class Player;
struct Rva2225E0Filter
{
  bool accepts(Object *, Player *);
};

struct Rva004F5436Node {
	Rva004F5436Node *m_next;
	Rva004F5436Node *m_prev;
	int m_value;
};

class Rva004F5436
{
public:
	int rva004F5436(BfmeTab1026 *tab);
private:
	char m_lead[0x10];
	Rva004F5436Node *m_head;
	int m_14;
	int m_18;
};

int Rva004F5436::rva004F5436(BfmeTab1026 *tab)
{
	int n = 0;
	if (tab == 0)
		return m_18;
	for (Rva004F5436Node *cur = m_head->m_next; cur != m_head; cur = cur->m_next) {
		if (((Rva2225E0Filter *)tab)->accepts((Object *)cur->m_value, (Player *)0))
			++n;
	}
	return n;
}
