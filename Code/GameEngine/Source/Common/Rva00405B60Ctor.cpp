// cl: /EHsc /MD
//
// ??0Rva00405B60@@QAE@ABV0@@Z @0x00405B60 (45B):
// Derived copy ctor: calls base 0x00405A45 with (int)&o, installs vtable
// 0x00838970, copies 12 bytes at +4/+8/+0xC. Evidence: chain lane calls
// 0x00405A45, vtable store plus 3-dword copy, caller 0x00405D9D thunk.
extern const void *const g_00C38970[];

class Rva00405A45
{
public:
	Rva00405A45(int dummy);
protected:
	const void *m_vtable;
};

class Rva00405B60 : public Rva00405A45
{
public:
	Rva00405B60(const Rva00405B60 &o);
private:
	int m_4;
	int m_8;
	int m_c;
};

Rva00405B60::Rva00405B60(const Rva00405B60 &o) : Rva00405A45((int)&o)
{
	m_vtable = g_00C38970;
	m_4 = o.m_4;
	m_8 = o.m_8;
	m_c = o.m_c;
}
