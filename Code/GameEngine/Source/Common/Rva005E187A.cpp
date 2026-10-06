// cl: /DNDEBUG /MD
// ?rva005E187A@Rva005E187A@@QAEX_N@Z @0x005E187A 33B unlock bool setter storing byte at +0x20 and forwarding 1/2 to iface at +0x18 slot 3.
// Evidence: retail mov al [esp+4] mov [ecx+0x20] al mov ecx [ecx+0x18] test je then vcall [edx+0xc] with setne-inc 1/2; callers 0x005E1A0E push 0 and 0x005E1A1E push 1.
class Rva005E187AInterface
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v3(int value);
};

class Rva005E187A
{
	char m_pad[0x18];
	Rva005E187AInterface *m_18;
	char m_fill[4];
	bool m_20;
public:
	void rva005E187A(bool value);
};

void Rva005E187A::rva005E187A(bool value)
{
	m_20 = value;
	Rva005E187AInterface *iface = m_18;
	if (iface)
		iface->v3(value ? 2 : 1);
}
