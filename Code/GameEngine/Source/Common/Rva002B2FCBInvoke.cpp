// cl: /MD
// ?rva002B2FCB@Rva002B2FCB@@QAEXPAX@Z, retail 0x002B2FCB, 23 bytes.
// Forwarder: this holds member-fn ptr at +0 and four params at +4/+8/+c/+10;
// invokes it with ecx = stack arg and the four members as stack args.
// Evidence: retail mov eax,ecx; push [eax+0x10]; mov ecx,[esp+8]; push x3;
// call [eax]; ret 4. Caller at 0x002B5711 passes vector element as stack arg.
class Rva002B2FCBElem
{
public:
	void Method(int a, int b, int c, int d);
};
typedef void (Rva002B2FCBElem::*Rva002B2FCBFn)(int, int, int, int);
class Rva002B2FCB
{
public:
	void rva002B2FCB(void *elem);
private:
	Rva002B2FCBFn m_fn;
	int m_4;
	int m_8;
	int m_c;
	int m_10;
};
void Rva002B2FCB::rva002B2FCB(void *elem)
{
	Rva002B2FCBElem *e = (Rva002B2FCBElem *)elem;
	(e->*m_fn)(m_4, m_8, m_c, m_10);
}
