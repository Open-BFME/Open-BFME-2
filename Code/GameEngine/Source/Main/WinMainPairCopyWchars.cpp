// cl: /O1 /G7 /Oi- /EHsc
//
// Shard (not graft): copyWchars needs /G7 P4 tuning, under which the m_len
// doubling emits add-eax-eax where /O1-/O2/G6 all fold to shl-eax-1, while
// /Oi- keeps the memcpy a real out-of-line call (/O2 and bare /G7 both fold
// it to rep-movsd). Same-class-in-2-TUs precedent; the home pair TU keeps
// its own flags untouched and stays green through the row.

class Rva000B3F84Pair
{
public:
	int copyWchars(unsigned short *dst);

	const char *m_ptr;
	int m_len;
};

extern "C" void *memcpy(void *dst, const void *src, unsigned int n);

// ?copyWchars@Rva000B3F84Pair@@QAEHPAG@Z, retail 0x002342A7, 30 bytes.
// Copies the m_len wide chars and returns the count. Serve sizes say 28;
// the true body is 30 (ret-inclusive, like its 0x2343C3 sibling).
int Rva000B3F84Pair::copyWchars(unsigned short *dst)
{
	int lo = m_len;
	int hi = m_len;
	memcpy(dst, m_ptr, lo + hi);
	return m_len;
}
