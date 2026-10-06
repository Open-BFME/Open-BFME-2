// cl: /O1 /MD /arch:SSE /G7
// ?rva005EB8CA@Rva005EB8CA@@QAEXXZ, RVA 0x005EB8CA, 7 bytes.
// Address-based thiscall thunk. Evidence: retail dereferences this and tail-calls the rowed state-switch method at 0x005EB88F.
class Rva005EB88F
{
public:
	void rva005EB88F();
};
class Rva005EB8CA
{
public:
	Rva005EB88F *m_target;
	void rva005EB8CA();
};
void Rva005EB8CA::rva005EB8CA()
{
	m_target->rva005EB88F();
}
