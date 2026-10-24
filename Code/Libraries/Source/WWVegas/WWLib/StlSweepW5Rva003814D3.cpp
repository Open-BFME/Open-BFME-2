// cl: /O1 /EHsc /MD
//
// 0x003814D3 (38B): STLport's __uninitialized_copy loop over 0x8-byte records.
// Each element goes through the placement copy at 0x003814A6, which the ledger owns
// as Rva003814A6Construct: retail keeps several identical placement copies apart (each with
// its own EH data), so they and this loop carry address names rather than a
// template over an element type nobody has recovered. The tag argument is
// pushed by the caller and never read.

namespace _STL { struct __false_type; }

struct BfmeStringRecord005DDD40
{
	unsigned char m_bytes[0x8];
};

void Rva003814A6Construct(BfmeStringRecord005DDD40 *dest, const BfmeStringRecord005DDD40 &source);

BfmeStringRecord005DDD40 *Rva003814D3UninitializedCopy(const BfmeStringRecord005DDD40 *first, const BfmeStringRecord005DDD40 *last, BfmeStringRecord005DDD40 *result,
	const _STL::__false_type &)
{
	BfmeStringRecord005DDD40 *cur = result;
	for (; first != last; ++first, ++cur)
		Rva003814A6Construct(cur, *first);
	return cur;
}
