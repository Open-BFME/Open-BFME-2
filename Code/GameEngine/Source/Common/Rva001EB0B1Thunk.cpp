// cl: /MD
// ?rva001EB0B1@Rva001EB0B1Holder@@QAEXXZ @0x001EB0B1 8B: add ecx 0x10 plus jmp.
// Tail-jmp thunk to pinned ?clear@Rva000AD6F4@@QAEXXZ at 0x000AD6F4; same
// shape as Rva000A89C1Thunk (return member clear gives add plus jmp at /O1).
// Callers at 0x0023D131 and 0x003777A4. No donor; honest address names.
class Rva000AD6F4
{
public:
	void clear();
};
class Rva001EB0B1Holder
{
public:
	char m_pad[0x10];
	Rva000AD6F4 m_holder;
	void rva001EB0B1();
};
void Rva001EB0B1Holder::rva001EB0B1()
{
	return m_holder.clear();
}
