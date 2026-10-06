// cl: /MD
// ??0Rva00575540@@QAE@PAX00@Z @0x00575540 (36B):
// Sibling of ??0Rva0057551C@@QAE@PAX00@Z @0x0057551C (same vtable 0x00C6E614,
// same m4/m8, swapped tail: here m0c=0 via and and m10=arg3, there m10=0 and
// m0c=arg3). Manual vtable (no virtuals) for exact store order. Caller at
// 0x00575D2F in FUN_00975CAE (second new+ctor+setter sequence). Honest name.

class Rva00575540
{
public:
	Rva00575540(void *a, void *b, void *c);

private:
	void *m_vtable;
	void *m_04;
	void *m_08;
	int m_0c;
	int m_10;
};

Rva00575540::Rva00575540(void *a, void *b, void *c)
{
	m_0c = 0;
	m_04 = a;
	m_08 = b;
	m_vtable = (void *)0x00C6E614;
	m_10 = (int)c;
}
