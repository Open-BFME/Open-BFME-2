// cl: /O1 /EHsc /MD
//
// 0x000CF503 (38B): STLport's __uninitialized_copy loop over 0x8-byte records.
// Each element goes through the placement copy at 0x000CF4D6, which the ledger owns
// as Rva000CF4D6Construct: retail keeps several identical placement copies apart (each with
// its own EH data), so they and this loop carry address names rather than a
// template over an element type nobody has recovered. The tag argument is
// pushed by the caller and never read.

namespace _STL { struct __false_type; }

struct TreeKey00242F5E
{
	unsigned char m_bytes[0x8];
};

void Rva000CF4D6Construct(TreeKey00242F5E *dest, const TreeKey00242F5E &source);

TreeKey00242F5E *Rva000CF503UninitializedCopy(const TreeKey00242F5E *first, const TreeKey00242F5E *last, TreeKey00242F5E *result,
	const _STL::__false_type &)
{
	TreeKey00242F5E *cur = result;
	for (; first != last; ++first, ++cur)
		Rva000CF4D6Construct(cur, *first);
	return cur;
}
