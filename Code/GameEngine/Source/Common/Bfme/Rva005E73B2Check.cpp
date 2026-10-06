// cl: /DNDEBUG /MD /EHsc
// ?rva005E73B2@Rva005E73B2@@QAEXXZ @0x005E73B2 42B
// Unlock check: if m_1C is 0 return; call no-arg virtual int getter at
// [[m_4]+0x14] via pinned twin 0x005CB265 and compare to m_1C; if equal tail
// to rowed 0x005CB260 forwarder. Row 0x005CB265 types are ICF alias (takes
// AnimateWindow) but this site passes no args and cmps eax edi per pin
// ?rva005CB265@Rva005CB265@@UAEHXZ. Evidence: packet disassembly plus callers
// 0x005E788E 0x005E7994 plus prev/next same flags.
class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class Rva005CB260
{
public:
	void rva005CB260();
};

struct Rva005E73B2Outer
{
	char m_pad[0x14];
	Rva005CB265 *m_14;
};

class Rva005E73B2
{
public:
	void rva005E73B2();
private:
	char m_pad0[4];
	Rva005E73B2Outer *m_4;
	char m_pad8[0x1C - 8];
	int m_1C;
};

void Rva005E73B2::rva005E73B2()
{
	int v = m_1C;
	if (v == 0)
		return;
	int r = m_4->m_14->Rva005CB265::rva005CB265();
	if (r != v)
		return;
	Rva005CB260 *p = (Rva005CB260 *)m_4->m_14;
	p->rva005CB260();
}
