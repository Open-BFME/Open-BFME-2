// cl: /O1 /EHsc /MD
//
// 0x00205709 (38B): STLport's __uninitialized_copy loop over 0x8-byte records.
// Each element goes through the placement copy at 0x0020596A, which the ledger owns
// as Rva0020596AConstruct: retail keeps several identical placement copies apart (each with
// its own EH data), so they and this loop carry address names rather than a
// template over an element type nobody has recovered. The tag argument is
// pushed by the caller and never read.

namespace _STL { struct __false_type; }

struct Rva00205709Record
{
	unsigned char m_bytes[0x8];
};

void Rva0020596AConstruct(void *dest, const void *source);

Rva00205709Record *Rva00205709UninitializedCopy(const Rva00205709Record *first, const Rva00205709Record *last, Rva00205709Record *result,
	const _STL::__false_type &)
{
	Rva00205709Record *cur = result;
	for (; first != last; ++first, ++cur)
		Rva0020596AConstruct(cur, first);
	return cur;
}
