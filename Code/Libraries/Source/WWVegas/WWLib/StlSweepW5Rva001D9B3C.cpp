// cl: /O1 /EHsc /MD
//
// 0x001D9B3C (38B): STLport's __uninitialized_copy loop over 0x8-byte records.
// Each element goes through the placement copy at 0x001D9B0F, which the ledger owns
// as Rva001D9B0FConstruct: retail keeps several identical placement copies apart (each with
// its own EH data), so they and this loop carry address names rather than a
// template over an element type nobody has recovered. The tag argument is
// pushed by the caller and never read.

namespace _STL { struct __false_type; }

struct Rva001D9B3CRecord
{
	unsigned char m_bytes[0x8];
};

void Rva001D9B0FConstruct(void *dest, const void *source);

Rva001D9B3CRecord *Rva001D9B3CUninitializedCopy(const Rva001D9B3CRecord *first, const Rva001D9B3CRecord *last, Rva001D9B3CRecord *result,
	const _STL::__false_type &)
{
	Rva001D9B3CRecord *cur = result;
	for (; first != last; ++first, ++cur)
		Rva001D9B0FConstruct(cur, first);
	return cur;
}
