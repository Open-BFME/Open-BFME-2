// cl: /EHsc /MD
//
// ??0Rva00405A45@@QAE@H@Z @0x00405A45 (11B):
// Vtable-store ctor: installs vtable 0x00838958 at [this], ignores 4-byte
// arg (ret 4). Evidence: unlock lane, vtable store at [this], caller
// 0x00405B60 base-ctor call then installs 0x00838970 plus 12-byte copy.
extern const void *const g_00C38958[];

class Rva00405A45
{
public:
	Rva00405A45(int dummy);
private:
	const void *m_vtable;
};

Rva00405A45::Rva00405A45(int dummy)
{
	(void)dummy;
	m_vtable = g_00C38958;
}
