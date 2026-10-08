// Indexed call through a 28-byte table entry: the body loads the table at
// this+0x18, selects entry i (stride 1Ch, base pointer at +4), offsets it by
// j * 30h and tail-calls the method on that object (ret 8). The callee is the
// address-named method Rva003F44A9::rva003F44A9, rowed in Rva003F44A9.cpp.
// Identity of the owner class is not recoverable from these 29 bytes; the
// names are address-derived.
// No // cl: line (defaults match the frameless shape).

class Rva003F44A9
{
public:
	void *rva003F44A9();
};

struct Rva003F4ABBEntry
{
	int m_lead;
	char *m_base;
	char m_tail[0x14];
};

class Rva003F4ABBOwner
{
public:
	void *indexedCall(int index, int stride);
	char m_lead[0x18];
	Rva003F4ABBEntry *m_entries;
};

void *Rva003F4ABBOwner::indexedCall(int index, int stride)
{
	return reinterpret_cast<Rva003F44A9 *>(m_entries[index].m_base + stride * 0x30)->rva003F44A9();
}
