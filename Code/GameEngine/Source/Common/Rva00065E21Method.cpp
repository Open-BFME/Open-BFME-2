// cl: /MD
// ?rva00065E21@Rva00065E21@@QAE_NXZ @0x00065E21 27B list scan for nonzero flag
// Scans embedded head at +4 from [this+8] until this+4 checking [node+0xC]; callers 0x0008C833; prev ctor at 0x00065D40 same flags
struct Rva00065E21Node
{
	void *m_prev00;
	Rva00065E21Node *m_next04;
	void *m_pad08;
	int m_flag0C;
};
class Rva00065E21
{
public:
	bool rva00065E21();
private:
	char m_pad00[4];
	Rva00065E21Node m_head04;
};
bool Rva00065E21::rva00065E21()
{
	for (Rva00065E21Node *p = m_head04.m_next04; p != &m_head04; p = p->m_next04) {
		if (p->m_flag0C != 0)
			return true;
	}
	return false;
}
