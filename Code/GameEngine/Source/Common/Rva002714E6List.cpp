// cl: /MD
//
// ?rva002714E6@Rva002714E6@@QAEXPAPAV1@@Z retail 0x002714E6 36 bytes.
// Doubly-linked push-front with next +0x104 prev +0x108 via head pointer.
// Unblocks 0x00238E25. Prev/next in Common with /O1 /MD.
// Evidence: caller 0x00238E43 plus and-0 clear plus reload for alias.

class Rva002714E6
{
public:
	void rva002714E6(Rva002714E6 **head);

private:
	unsigned char m_pre104[0x104];
	Rva002714E6 *m_next;
	Rva002714E6 *m_prev;
};

void Rva002714E6::rva002714E6(Rva002714E6 **head)
{
	m_prev = 0;
	m_next = *head;
	if (*head != 0)
		(*head)->m_prev = (Rva002714E6 *)this;
	*head = (Rva002714E6 *)this;
}
