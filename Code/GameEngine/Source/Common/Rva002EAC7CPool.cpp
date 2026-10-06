// cl: /O1 /DNDEBUG /MD
// Dump lane range 13: ?rva002EAC7C @0x002EAC7C 35B. Branchless modulo-0x200
// round-robin pool: counter at +0x800 wraps to 0 after 0x1FF (cl lowers the
// conditional to the sub/neg/sbb/and mask retail has), then table lookup
// by the pre-wrap index. Identity unproven.
class Rva002EAC7CPool
{
public:
	void *rva002EAC7C();
private:
	void *m_entries[0x200];
	int m_counter800;
};
// ?rva002EAC7C@Rva002EAC7CPool@@QAEPAXXZ @0x002EAC7C 35B.
void *Rva002EAC7CPool::rva002EAC7C()
{
	int idx = m_counter800;
	m_counter800 = (idx == 0x1ff) ? 0 : idx + 1;
	return m_entries[idx];
}
