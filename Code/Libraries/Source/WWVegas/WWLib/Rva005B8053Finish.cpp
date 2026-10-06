// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005B8053@Rva005B8053@@QAEPAXPBE@Z @0x005B8053 58B. Unlock lane tree
// lookup shared by 0x005B808D/0x005B80AF/0x005B80D0/0x005B80F2 plus 0x00559DA0
// and 0x00553CDE. Evidence: lower_bound walk over byte key at node+0x10 with
// left at +8 right at +0xC root at header+4, end sentinel is header itself,
// equality_tail returns header on miss. Callers compare result to [container]
// and read word at +0x12 dword-float at +0x14. ReadWriteBarrier before the
// equality tail keeps the eager push edi and the shared sentinel store that
// MSVC otherwise shrink-wraps and folds.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva005B8053Node
{
	int _plus0;
	int _plus4;
	Rva005B8053Node *_left;
	Rva005B8053Node *_right;
	unsigned char _key;
};

struct Rva005B8053Header
{
	int _plus0;
	Rva005B8053Node *_root;
};

class Rva005B8053
{
	Rva005B8053Header *m_header;
public:
	void *rva005B8053(unsigned char const *key);
};

void *Rva005B8053::rva005B8053(unsigned char const *key)
{
	Rva005B8053Header *h = m_header;
	Rva005B8053Node *cur = h->_root;
	Rva005B8053Node *sentinel = (Rva005B8053Node *)(void *)h;
	Rva005B8053Node *best = sentinel;
	unsigned char const volatile *vkey = key;
	if (cur != 0) {
		unsigned char k = *vkey;
		do {
			if (cur->_key >= k) {
				best = cur;
				cur = cur->_left;
			} else
				cur = cur->_right;
		} while (cur != 0);
	}
	_ReadWriteBarrier();
	if (best == sentinel || *vkey < best->_key)
		best = sentinel;
	return best;
}
