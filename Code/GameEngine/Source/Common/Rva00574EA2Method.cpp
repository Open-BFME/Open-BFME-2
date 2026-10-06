// cl: /DNDEBUG /MD /EHsc
// ?rva00574EA2@Rva00574EA2@@QAEXXZ retail 0x00574EA2 71B method.
// Evidence: lazy caches +0x6C +0x74 via rowed getters 0x0042D6D6
// 0x0042D6C6; listeners +8 +0xC via rowed append 0x005A0B4C;
// chain unblocks 0x00575038; caller 0x0057503C.
class Rva0042D6D6PtrChaseField
{
public:
	int get() const;
};
class Rva0042D6C6PtrChaseField
{
public:
	int get() const;
};
struct Rva002BA8F1Listener { char opaque[4]; };
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};
class Rva00574EA2
{
public:
	void rva00574EA2();
private:
	char m_pad00[8];
	Rva002BA8F1Listener m_lis08; // +8
	Rva002BA8F1Listener m_lis0C; // +0xC
	char m_pad10[0x10];
	void *m_mgr20; // +0x20
	char m_pad24[0x48];
	int m_cache6C; // +0x6C
	char m_pad70[4];
	int m_cache74; // +0x74
};
void Rva00574EA2::rva00574EA2()
{
	if (m_cache6C == 0) {
		int p = ((Rva0042D6D6PtrChaseField *)m_mgr20)->get();
		m_cache6C = p;
		if (p != 0)
			((Rva005A0B4CList *)(p + 4))->append(&m_lis08);
	}
	if (m_cache74 == 0) {
		int q = ((Rva0042D6C6PtrChaseField *)m_mgr20)->get();
		m_cache74 = q;
		if (q != 0)
			((Rva005A0B4CList *)(q + 4))->append(&m_lis0C);
	}
}
