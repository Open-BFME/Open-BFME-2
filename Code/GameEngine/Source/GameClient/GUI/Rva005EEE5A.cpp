// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// Address-derived constructor; packet callers are 0x005E20B8 0x005E2CAF
// and 0x005E38FD. Vtable owner and class identity are unresolved.
class Rva005EEE5A
{
public:
	Rva005EEE5A();
	virtual void slot0() {}
	int m_at4;
	unsigned char m_at8;
};

Rva005EEE5A::Rva005EEE5A()
{
	m_at4 = 0;
	m_at8 = 0;
}
