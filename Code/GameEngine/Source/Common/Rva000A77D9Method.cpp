// ?rva000A77D9@Rva000A77D9@@QAEXPAX@Z @0x000A77D9 40B.
// Thiscall setter storing its pointer arg at +0x40 under a MilesMutexGuard
// over +0x50 (rowed ctor 0x0004120E plus rowed dtor 0x0004122F via pins).
// No EH frame; guard dtor is an explicit call. Prev 0x000A77B3 defines the
// neighbouring +0x48/+0x4C thread-handle layout in the same page; this TU
// keeps an honest page-local class with retail-measured +0x40/+0x50.
// Caller 0x00061ABD/277.
// cl: /MD
class MilesMutexGuard
{
public:
	MilesMutexGuard(void *obj, int flags);
	~MilesMutexGuard();
private:
	void *m_obj;
	int m_flags;
};
class Rva000A77D9
{
public:
	void rva000A77D9(void *val);
private:
	char m_pad[0x40];
	void *m_40;
	char m_pad2[0x50 - 0x44];
	void *m_50;
};
void Rva000A77D9::rva000A77D9(void *val)
{
	MilesMutexGuard guard(m_50, 0);
	m_40 = val;
}
