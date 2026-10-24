// cl: /O1 /EHsc /MD
//
// 0x00288A37 (37B): STLport's __uninitialized_fill_n loop over 0x8-byte records.
// Each element goes through the placement copy at 0x002889E4, which the ledger owns
// as Rva002889E4Construct: retail keeps several identical placement copies apart (each with
// its own EH data), so they and this loop carry address names rather than a
// template over an element type nobody has recovered. The tag argument is
// pushed by the caller and never read.

namespace _STL { struct __false_type; }

struct TreeKey00242F5E
{
	unsigned char m_bytes[0x8];
};

void Rva002889E4Construct(TreeKey00242F5E *dest, const TreeKey00242F5E &source);

TreeKey00242F5E *Rva00288A37UninitializedFill(TreeKey00242F5E *first, unsigned int count, const TreeKey00242F5E &value,
	const _STL::__false_type &)
{
	TreeKey00242F5E *cur = first;
	for (; count > 0; --count, ++cur)
		Rva002889E4Construct(cur, value);
	return cur;
}
