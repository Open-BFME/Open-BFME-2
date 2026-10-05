// ?rva0005E322@Rva0005E322Host@@QAEXPBVAsciiString@@H@Z
// partial score=0.8 date=2026-10-05
// cl: /O1 /G7 /MD /EHsc
//
// 0x0005E322 (85B): guarded indexed tree-erase. Raises the MilesMutexGuard
// over the mutex zone at +0x9D4, erases the key through the 12-byte tree at
// index (idx + 0xD7) of the array at +0x0 through the view pinned at the
// rowed 0x0005B5EA (gen-alias for the Rb_tree AsciiString single erase),
// then drops the guard under the SEH frame. Address names.

class AsciiString;

class MilesMutexGuard
{
public:
	MilesMutexGuard(void *m, int x);
	~MilesMutexGuard();
private:
	void *m_mutex; // +0x00
	bool m_flag; // +0x04
};

struct Rva0005E322TreeView
{
	char m_space[0x0C];
	unsigned erase(const AsciiString &key);
};

class Rva0005E322Host
{
public:
	void rva0005E322(const AsciiString *key, int idx);
private:
	Rva0005E322TreeView m_trees[0x80]; // +0x00
	char m_pad[0x9D4 - 0x600];
	char m_mutexzone[4]; // +0x9D4
};

void Rva0005E322Host::rva0005E322(const AsciiString *key, int idx)
{
	MilesMutexGuard guard(m_mutexzone, 0);
	int n = idx + 0xD7;
	int off = n * 12;
	Rva0005E322TreeView *t = (Rva0005E322TreeView *)((char *)this + off);
	t->erase(*key);
}
