// cl: /EHsc
// ?rva005D4E6F@Rva005D4E6F@@QAEHXZ @0x005D4E6F 21B
// Leaf predicate over pointee at +0: true if dword at +0xC or +0x8 is nonzero.
// Evidence: retail mov eax,[ecx] then cmp [eax+0xC],0 jne then cmp [eax+8],0 jne; single caller site.
struct Rva005D4E6FInner
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};
class Rva005D4E6F
{
public:
	int rva005D4E6F();
private:
	Rva005D4E6FInner *m_p00;
};
int Rva005D4E6F::rva005D4E6F()
{
	Rva005D4E6FInner *p = m_p00;
	if (p->m_0C != 0 || p->m_08 != 0)
		return 1;
	return 0;
}
