// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005D3D4B@Rva005D3D4B@@QAEXXZ retail 0x005D3D4B 76B
// Evidence: chain from just-landed 0x005D3AF2 plus rowed 0x005D3B9A portrait plus AptCall rowed 0x005FB5E6 with SetState _hide using level +0x04 outer +0x08 prefix from +8 else g_Rva0107301CEmptyString plus flags +0x30 +0x32; same level outer pattern as Rva005D39EACpState.cpp
struct Rva005D2FD0Inner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

class Rva005D3AF2
{
public:
	void rva005D3AF2();
};

class Rva005D3B9A
{
public:
	void rva005D3B9A();
};

class Rva005D3D4B
{
public:
	void rva005D3D4B();
private:
	void *m_unused00;
	int m_level04;
	Rva005D2FD0Inner *m_inner08;
	char m_pad0C[0x30 - 0x0C];
	unsigned char m_flag30;
	char m_pad31;
	unsigned char m_flag32;
};

void Rva005D3D4B::rva005D3D4B()
{
	if (m_flag30 == 0)
		return;
	((Rva005D3AF2 *)this)->rva005D3AF2();
	((Rva005D3B9A *)this)->rva005D3B9A();
	const char *prefix = m_inner08 ? m_inner08->m_name : g_Rva0107301CEmptyString;
	Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level04, prefix, "SetState", "_hide");
	m_flag30 = 0;
	m_flag32 = 0;
}
