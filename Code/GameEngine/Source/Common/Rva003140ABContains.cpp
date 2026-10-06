// cl: /DNDEBUG /MD
//
// ?rva003140AB@Rva003140AB@@QAE_NPAV1@@Z @0x003140AB (29B).
// Searches intrusive list starting at head->m_next (stride +0x200) for this.
// Retail walks [arg+0x200] comparing ECX, returning true on match else false.
// Evidence: 4 callers in large builders; honest Rva class, no donor.

class Rva003140AB
{
public:
	bool rva003140AB(Rva003140AB *head);

private:
	unsigned char m_pad[0x200];
	Rva003140AB *m_next;
};

bool Rva003140AB::rva003140AB(Rva003140AB *head)
{
	Rva003140AB *cur = head;
	if (!cur)
		return false;
	do {
		cur = cur->m_next;
		if (this == cur)
			return true;
	} while (cur);
	return false;
}
