// cl: /O1 /MD
// ??0Rva00402F28Item@@QAE@PAX@Z @0x0056BEFB 36B. Ctor via pinned 0x0056B7E4 init plus vtable 0x00C37898 and bytes 0,1,0 at +0x58..0x5A. Evidence: same pad 0x58 as Rva0056B63E sibling, vtable and 3-byte layout match Rva00402F28Item copy ctor 0x00402F28, caller 0x0056BFA6.
class Rva0056B7E4
{
public:
	void rva0056B7E4(void *arg);
};

extern const void *const g_00C37898[];

class Rva00402F28Item
{
public:
	Rva00402F28Item(void *arg);
private:
	char m_pad[0x58];
	unsigned char m_58;
	unsigned char m_59;
	unsigned char m_5A;
};

Rva00402F28Item::Rva00402F28Item(void *arg)
{
	((Rva0056B7E4 *)this)->rva0056B7E4(arg);
	*(unsigned int *)this = (unsigned int)g_00C37898;
	m_58 = 0;
	m_59 = 1;
	m_5A = 0;
}
