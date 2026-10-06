// cl: /DNDEBUG /MD
// ?rva0056F43E@Rva0056F43E@@QAEXPAX@Z @0x0056F43E 53B
// Recursive list/tree cleanup: recurse on [node+0xc], iterate on [node+8],
// clear the Unicode string at [node+0x10], then free the node.
// Unlocks 0x0056F503.
// Evidence: push ebx/esi/edi shape with self-call, StringBase<G>::clear call,
// _free call, ret 4; caller 0x0056F503 passes [eax+4] with same this.
template <typename T>
class StringBase
{
public:
	void clear();
private:
	void *m_data;
};
extern "C" void __cdecl free(void *p);
struct Rva0056F43E
{
	int m_00;
	int m_04;
	void *m_08;
	void *m_0c;
	StringBase<unsigned short> m_10;
	void rva0056F43E(void *node);
	void rva0056F503();
};
void Rva0056F43E::rva0056F43E(void *p)
{
	Rva0056F43E *node = (Rva0056F43E *)p;
	if (!node)
		return;
	do {
		rva0056F43E(node->m_0c);
		Rva0056F43E *next = (Rva0056F43E *)node->m_08;
		node->m_10.clear();
		free(node);
		node = next;
	} while (node);
}
// ?rva0056F503@Rva0056F43E@@QAEXXZ @0x0056F503 41B
// Clear the table: if m_04 is set, run this->rva0056F43E over the root at
// [m_00+4], reset the header at m_00 to self-links, and zero m_04.
// Same class as 0x0056F43E: the call threads the same this (no ecx reload).
// Evidence: cmp [esi+4]0 je, push [eax+4] call 0x0056F43E with live ecx,
// then mov [eax+8]eax / and [eax+4]0 / mov [eax+0xc]eax / and [esi+4]0.
void Rva0056F43E::rva0056F503()
{
	if (m_04 == 0)
		return;
	rva0056F43E((void *)((Rva0056F43E *)m_00)->m_04);
	((Rva0056F43E *)m_00)->m_08 = (void *)m_00;
	((Rva0056F43E *)m_00)->m_04 = 0;
	((Rva0056F43E *)m_00)->m_0c = (void *)m_00;
	m_04 = 0;
}
