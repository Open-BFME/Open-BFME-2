// cl: /MD
// ?rva005CC9F8@Rva005CC9F8@@QAEXXZ @0x005CC9F8 19B evidence: calls rowed ?Release_Ref@RefCountClass@@QAEXXZ; tail-jmp target of 0x005CCA57
// Clears a RefCountClass pointer at +0: if set, Release_Ref then null it.
class RefCountClass {
public:
	void Release_Ref();
};
class Rva005CC9F8 {
public:
	void rva005CC9F8();
	RefCountClass *m_ptr;
};
void Rva005CC9F8::rva005CC9F8()
{
	if (m_ptr) {
		m_ptr->Release_Ref();
		m_ptr = 0;
	}
}
